<?php

namespace obregonco\B2;

use Illuminate\Cache\CacheManager;
use Illuminate\Container\Container;
use Illuminate\Filesystem\Filesystem;
use obregonco\B2\Exceptions\CacheException;
use obregonco\B2\Exceptions\NotFoundException;
use obregonco\B2\Exceptions\ValidationException;
use obregonco\B2\Http\Client as HttpClient;

class Client
{
    protected $accountId;

    /**
     * @var \Illuminate\Contracts\Cache\Repository
     */
    protected $cache;

    protected $authToken;
    protected $apiUrl = '';
    protected $downloadUrl;
    protected $recommendedPartSize;

    protected $client;

    public $version = 1;

    public $cacheParentDir = __DIR__;

    /**
     * If you setup CNAME records to point to backblaze servers (for white-label service)
     * assign this property with the equivalent URLs
     * ['f0001.backblazeb2.com' => 'alias01.mydomain.com']
     * @var array
     */
    public $domainAliases = [];

    /**
     * Lower limit for using large files upload support. More information:
     * https://www.backblaze.com/b2/docs/large_files.html. Default: 3 GB
     * Files larger than this value will be uploaded in multiple parts.
     *
     * @var int
     */
    public $largeFileLimit = 3000000000;

    /**
     * Client constructor. Accepts the account ID, application key and an optional array of options.
     * @param string $accountId
     * @param array $authorizationValues
     * @param array $options
     * @throws CacheException
     */
    public function __construct(string $accountId, array $authorizationValues, array $options = [])
    {
        $this->accountId = $accountId;
        $keyId = $authorizationValues['keyId'] ?? $accountId;
        $applicationKey = $authorizationValues['applicationKey'];

        if (empty($keyId) or empty($applicationKey)) {
            throw new \Exception('Please provide "keyId" and "applicationKey"');
        }

        if (isset($options['client'])) {
            $this->client = $options['client'];
        } else {
            $this->client = new HttpClient(['exceptions' => false]);
        }

        if (isset($options['cacheParentDir'])) {
            $this->cacheParentDir = $options['cacheParentDir'];
        }        

        // initialize cache
        $this->createCacheContainer();

        $this->authorizeAccount($keyId, $applicationKey);
    }

    private function createCacheContainer()
    {
        if (!file_exists($this->cacheParentDir . '/Cache')) {
            mkdir($this->cacheParentDir . '/Cache', 0700, true);
        }

        $container = new Container();
        $container['config'] = [
            'cache.default' => 'file',
            'cache.stores.file' => [
                'driver' => 'file',
                'path' => $this->cacheParentDir . '/Cache',
            ],
        ];
        $container['files'] = new Filesystem;

        try {
            $cacheManager = new CacheManager($container);
            $this->cache = $cacheManager->store();
        } catch (\Exception $e) {
            throw new CacheException(
                $e->getMessage()
            );
        }
    }

    /**
     * Create a bucket with the given name and type.
     *
     * @param array $options
     * @return Bucket
     * @throws ValidationException
     */
    public function createBucket(array $options)
    {
        if (!in_array($options['BucketType'], [Bucket::TYPE_PUBLIC, Bucket::TYPE_PRIVATE])) {
            throw new ValidationException(
                sprintf('Bucket type must be %s or %s', Bucket::TYPE_PRIVATE, Bucket::TYPE_PUBLIC)
            );
        }

        $lastVersionOnly = [    
            [
                'daysFromHidingToDeleting' => 1,
                'daysFromUploadingToHiding' => null,
                'fileNamePrefix' => '',
            ]
        ];

        $response = $this->request('POST', '/b2_create_bucket', [
            'json' => [
                'accountId' => $this->accountId,
                'bucketName' => $options['BucketName'],
                'bucketType' => $options['BucketType'],
                'lifecycleRules' => ((isset($options['KeepLastVersionOnly']) && $options['KeepLastVersionOnly']) ? $lastVersionOnly : null)
            ],
        ]);

        return new Bucket($response);
    }

    /**
     * Updates the type attribute of a bucket by the given ID.
     *
     * @param array $options
     * @return Bucket
     * @throws ValidationException
     */
    public function updateBucket(array $options)
    {
        if (!in_array($options['BucketType'], [Bucket::TYPE_PUBLIC, Bucket::TYPE_PRIVATE])) {
            throw new ValidationException(
                sprintf('Bucket type must be %s or %s', Bucket::TYPE_PRIVATE, Bucket::TYPE_PUBLIC)
            );
        }

        if (!isset($options['BucketId']) && isset($options['BucketName'])) {
            $options['BucketId'] = $this->getBucketIdFromName($options['BucketName']);
        }

        $response = $this->request('POST', '/b2_update_bucket', [
            'json' => [
                'accountId' => $this->accountId,
                'bucketId' => $options['BucketId'],
                'bucketType' => $options['BucketType'],
            ],
        ]);

        return new Bucket($response);
    }

    /**
     * Returns a list of bucket objects representing the buckets on the account.
     *
     * @return Bucket[]
     */
    public function listBuckets($refresh = false)
    {
        $cacheKey = 'B2-SDK-Buckets';
        $bucketsObj = [];
        if (!$this->cache->has($cacheKey)) {
            $refresh = true;
        }
        if ($refresh === true) {
            $buckets = $this->request('POST', '/b2_list_buckets', [
                'json' => [
                    'accountId' => $this->accountId,
                ],
            ])['buckets'];
            $this->cache->set($cacheKey, $buckets, 10080);
        } else {
            $buckets = $this->cache->get($cacheKey);
        }

        foreach ($buckets as $bucket) {
            $bucketsObj[] = new Bucket($bucket);
        }

        return $bucketsObj;
    }

    /**
     * Deletes the bucket identified by its ID.
     *
     * @param array $options
     * @return bool
     */
    public function deleteBucket(array $options)
    {
        if (!isset($options['BucketId']) && isset($options['BucketName'])) {
            $options['BucketId'] = $this->getBucketIdFromName($options['BucketName']);
        }

        $this->request('POST', '/b2_delete_bucket', [
            'json' => [
                'accountId' => $this->accountId,
                'bucketId' => $options['BucketId'],
            ],
        ]);

        return true;
    }

    /**
     * Uploads a file to a bucket and returns a File object.
     *
     * @param array $options
     * @return File
     */
    public function upload(array $options)
    {
        // Clean the path if it starts with /.
        if (substr($options['FileName'], 0, 1) === '/') {
            $options['FileName'] = ltrim($options['FileName'], '/');
        }

        if (!isset($options['BucketId']) && isset($options['BucketName'])) {
            $options['BucketId'] = $this->getBucketIdFromName($options['BucketName']);
        }

        if (!isset($options['FileLastModified'])) {
            $options['FileLastModified'] = round(microtime(true) * 1000);
        }

        if (!isset($options['FileContentType'])) {
            $options['FileContentType'] = 'b2/x-auto';
        }

        list($options['hash'], $options['size']) = $this->getFileHashAndSize($options['Body']);

        if ($options['size'] <= $this->largeFileLimit && $options['size'] <= $this->recommendedPartSize) {
            return $this->uploadStandardFile($options);
        } else {
            return $this->uploadLargeFile($options);
        }
    }

    /**
     * @param $bucket
     * @param $path
     * @param int $validDuration
     * @return string
     */
    public function getDownloadAuthorization($bucket, $path, $validDuration = 60)
    {
        if ($bucket instanceof Bucket) {
            $bucketId = $bucket->getId();
        } else {
            $bucketId = $bucket;
        }

        $response = $this->request('POST', '/b2_get_download_authorization', [
            'json' => [
                'bucketId' => $bucketId,
                'fileNamePrefix' => $path,
                'validDurationInSeconds' => $validDuration,
            ],
        ]);

        return $response['authorizationToken'];
    }

    /**
     * @param Bucket|string $bucket
     * @param string $filePath
     * @param bool $appendToken
     * @param int $tokenTimeout
     * @return string
     */
    public function getDownloadUrl($bucket, string $filePath, $appendToken = false, $tokenTimeout = 60)
    {
        if (!$bucket instanceof Bucket) {
            $bucket = $this->getBucketFromId($bucket);
        }

        $baseUrl = strtr($this->downloadUrl, $this->domainAliases);
        $path = $baseUrl . '/file/' . $bucket->getName() . '/' . $filePath;

        if ($appendToken) {
            $path .= '?Authorization='
            . $this->getDownloadAuthorization($bucket, dirname($filePath) . '/', $tokenTimeout);
        }

        return $path;
    }

    /**
     * @param File $file
     * @param bool $appendToken
     * @param int $tokenTimeout
     * @return string
     */
    public function getDownloadUrlForFile(File $file, $appendToken = false, $tokenTimeout = 60)
    {
        return $this->getDownloadUrl($file->getBucketId(), $file->getFileName(), $appendToken, $tokenTimeout);
    }

    /**
     * Download a file from a B2 bucket.
     *
     * @param array $options
     * @return bool|mixed|string
     */
    public function download(array $options)
    {
        $requestUrl = null;
        $requestOptions = [
            'sink' => isset($options['SaveAs']) ? $options['SaveAs'] : fopen('php://temp', 'w'),
        ];

        if (isset($options['FileId'])) {
            $requestOptions['query'] = ['fileId' => $options['FileId']];
            $requestUrl = $this->downloadUrl . '/b2api/v1/b2_download_file_by_id';
        } else {
            if (!isset($options['BucketName']) && isset($options['BucketId'])) {
                $options['BucketName'] = $this->getBucketNameFromId($options['BucketId']);
            }

            $requestUrl = sprintf('%s/file/%s/%s', $this->downloadUrl, $options['BucketName'], $options['FileName']);
        }

        if (isset($options['stream'])) {
            $requestOptions['stream'] = $options['stream'];
            $response = $this->request('GET', $requestUrl, $requestOptions, false, false);
        } else {
            $response = $this->request('GET', $requestUrl, $requestOptions, false);
        }

        return isset($options['SaveAs']) ? true : $response;
    }

    public function accelRedirectData(array $options)
    {
        $parsed = parse_url($this->downloadUrl);

        return [
            'host' => $parsed['host'],
            'query' => sprintf("fileId=%s", $options['FileId']),
        ];
    }

    /**
     * Retrieve a collection of File objects representing the files stored inside a bucket.
     *
     * @param array $options
     * @return array
     */
    public function listFiles(array $options)
    {
        // if FileName is set, we only attempt to retrieve information about that single file.
        $fileName = !empty($options['FileName']) ? $options['FileName'] : null;

        $nextFileName = null;
        $maxFileCount = 1000;
        $files = [];

        if (!isset($options['BucketId']) && isset($options['BucketName'])) {
            $options['BucketId'] = $this->getBucketIdFromName($options['BucketName']);
        }

        if ($fileName) {
            $nextFileName = $fileName;
            $maxFileCount = 1;
        }

        // B2 returns, at most, 1000 files per "page". Loop through the pages and compile an array of File objects.
        while (true) {
            $response = $this->request('POST', '/b2_list_file_names', [
                'json' => [
                    'bucketId' => $options['BucketId'],
                    'startFileName' => $nextFileName,
                    'maxFileCount' => $maxFileCount,
                ],
            ]);

            foreach ($response['files'] as $file) {
                // if we have a file name set, only retrieve information if the file name matches
                if (!$fileName || ($fileName === $file['fileName'])) {
                    $files[] = new File($file);
                }
            }

            if ($fileName || $response['nextFileName'] === null) {
                // We've got all the files - break out of loop.
                break;
            }

            $nextFileName = $response['nextFileName'];
        }

        return $files;
    }

    /**
     * Test whether a file exists in B2 for the given bucket.
     *
     * @param array $options
     * @return boolean
     */
    public function fileExists(array $options)
    {
        $files = $this->listFiles($options);

        return !empty($files);
    }

    /**
     * Returns a single File object representing a file stored on B2.
     *
     * @param array $options
     * @throws NotFoundException If no file id was provided and BucketName + FileName does not resolve to a file, a NotFoundException is thrown.
     * @return File
     */
    public function getFile(array $options)
    {
        if (!isset($options['FileId']) && isset($options['BucketName']) && isset($options['FileName'])) {
            $options['FileId'] = $this->getFileIdFromBucketAndFileName($options['BucketName'], $options['FileName']);

            if (!$options['FileId']) {
                throw new NotFoundException();
            }
        }

        $response = $this->request('POST', '/b2_get_file_info', [
            'json' => [
                'fileId' => $options['FileId'],
            ],
        ]);

        return new File($response);
    }

    /**
     * Deletes the file identified by ID from Backblaze B2.
     *
     * @param array $options
     * @return bool
     */
    public function deleteFile(array $options)
    {
        if (!isset($options['FileName'])) {
            $file = $this->getFile($options);

            $options['FileName'] = $file->getFileName();
        }

        if (!isset($options['FileId']) && isset($options['BucketName']) && isset($options['FileName'])) {
            $file = $this->getFile($options);

            $options['FileId'] = $file->getFileId();
        }

        $this->request('POST', '/b2_delete_file_version', [
            'json' => [
                'fileName' => $options['FileName'],
                'fileId' => $options['FileId'],
            ],
        ]);

        return true;
    }

    /**
     * Maps the provided bucket name to the appropriate bucket ID.
     *
     * @param $name
     * @return string|null
     */
    public function getBucketIdFromName($name)
    {
        $bucket = $this->getBucketFromName($name);

        if ($bucket instanceof Bucket) {
            return $bucket->getId();
        }

        return null;
    }

    /**
     * Maps the provided bucket ID to the appropriate bucket name.
     *
     * @param $id
     * @return string|null
     */
    public function getBucketNameFromId($id)
    {
        $bucket = $this->getBucketFromId($id);

        if ($bucket instanceof Bucket) {
            return $bucket->getName();
        }

        return null;
    }

    /**
     * @param $bucketId
     * @return Bucket|null
     */
    public function getBucketFromId($id)
    {
        $buckets = $this->listBuckets();

        foreach ($buckets as $bucket) {
            if ($bucket->getId() === $id) {
                return $bucket;
            }
        }

        return null;
    }

    /**
     * @param $name
     * @return Bucket|null
     */
    public function getBucketFromName($name)
    {

        $buckets = $this->listBuckets();

        foreach ($buckets as $bucket) {
            if ($bucket->getName() === $name) {
                return $bucket;
            }
        }

        return null;
    }

    protected function getFileIdFromBucketAndFileName($bucketName, $fileName)
    {
        $files = $this->listFiles([
            'BucketName' => $bucketName,
            'FileName' => $fileName,
        ]);

        foreach ($files as $file) {
            if ($file->getFileName() === $fileName) {
                return $file->getFileId();
            }
        }

        return null;
    }

    /**
     * Calculate hash and size of file/stream. If $offset and $partSize is given return
     * hash and size of this chunk
     *
     * @param $content
     * @param int $offset
     * @param null $partSize
     * @return array
     */
    protected function getFileHashAndSize($data, $offset = 0, $partSize = null)
    {
        if (!$partSize) {
            if (is_resource($data)) {
                // We need to calculate the file's hash incrementally from the stream.
                $context = hash_init('sha1');
                hash_update_stream($context, $data);
                $hash = hash_final($context);
                // Similarly, we have to use fstat to get the size of the stream.
                $size = fstat($data)['size'];
                // Rewind the stream before passing it to the HTTP client.
                rewind($data);
            } else {
                // We've been given a simple string body, it's super simple to calculate the hash and size.
                $hash = sha1($data);
                $size = mb_strlen($data, '8bit');
            }
        } else {
            $dataPart = $this->getPartOfFile($data, $offset, $partSize);
            $hash = sha1($dataPart);
            $size = mb_strlen($dataPart, '8bit');
        }

        return array($hash, $size);
    }

    /**
     * Return selected part of file
     *
     * @param $data
     * @param $offset
     * @param $partSize
     * @return bool|string
     */
    protected function getPartOfFile($data, $offset, $partSize)
    {
        // Get size and hash of one data chunk
        if (is_resource($data)) {
            // Get data chunk
            fseek($data, $offset);
            $dataPart = fread($data, $partSize);
            // Rewind the stream before passing it to the HTTP client.
            rewind($data);
        } else {
            $dataPart = substr($data, $offset, $partSize);
        }
        return $dataPart;
    }

    /**
     * Upload single file (smaller than 3 GB)
     *
     * @param array $options
     * @return File
     */
    protected function uploadStandardFile($options = array())
    {
        // Retrieve the URL that we should be uploading to.
        $response = $this->request('POST', '/b2_get_upload_url', [
            'json' => [
                'bucketId' => $options['BucketId'],
            ],
        ]);

        $uploadEndpoint = $response['uploadUrl'];
        $uploadAuthToken = $response['authorizationToken'];

        $response = $this->request('POST', $uploadEndpoint, [
            'headers' => [
                'Authorization' => $uploadAuthToken,
                'Content-Type' => $options['FileContentType'],
                'Content-Length' => $options['size'],
                'X-Bz-File-Name' => $options['FileName'],
                'X-Bz-Content-Sha1' => $options['hash'],
                'X-Bz-Info-src_last_modified_millis' => $options['FileLastModified'],
            ],
            'body' => $options['Body'],
        ]);

        return new File($response);
    }

    /**
     * Upload large file. Large files will be uploaded in chunks of recommendedPartSize bytes (usually 100MB each)
     *
     * @param array $options
     * @return File
     */
    protected function uploadLargeFile($options)
    {
        // Prepare for uploading the parts of a large file.
        $response = $this->request('POST', '/b2_start_large_file', [
            'json' => [
                'bucketId' => $options['BucketId'],
                'fileName' => $options['FileName'],
                'contentType' => $options['FileContentType'],
                /**
                 * 'fileInfo' => [
                 * 'src_last_modified_millis' => $options['FileLastModified'],
                 * 'large_file_sha1' => $options['hash']
                 * ]
                 **/
            ],
        ]);
        $fileId = $response['fileId'];

        $partsCount = ceil($options['size'] / $this->recommendedPartSize);

        $hashParts = [];
        for ($i = 1; $i <= $partsCount; $i++) {
            $bytesSent = ($i - 1) * $this->recommendedPartSize;
            $bytesLeft = $options['size'] - $bytesSent;
            $partSize = ($bytesLeft > $this->recommendedPartSize) ? $this->recommendedPartSize : $bytesLeft;

            // Retrieve the URL that we should be uploading to.
            $response = $this->request('POST', '/b2_get_upload_part_url', [
                'json' => [
                    'fileId' => $fileId,
                ],
            ]);

            $uploadEndpoint = $response['uploadUrl'];
            $uploadAuthToken = $response['authorizationToken'];

            list($hash, $size) = $this->getFileHashAndSize($options['Body'], $bytesSent, $partSize);
            $hashParts[] = $hash;

            $response = $this->request('POST', $uploadEndpoint, [
                'headers' => [
                    'Authorization' => $uploadAuthToken,
                    'X-Bz-Part-Number' => $i,
                    'Content-Length' => $size,
                    'X-Bz-Content-Sha1' => $hash,
                ],
                'body' => $this->getPartOfFile($options['Body'], $bytesSent, $partSize),
            ]);
        }

        // Finish upload of large file
        $response = $this->request('POST', '/b2_finish_large_file', [
            'json' => [
                'fileId' => $fileId,
                'partSha1Array' => $hashParts,
            ],
        ]);
        return new File($response);
    }

    /**
     * @param Key $key
     * @throws \Exception
     */
    public function createKey($key)
    {
        throw new \Exception(__FUNCTION__ . ' has not been implemented yet');
    }

    /**
     * Authorize the B2 account in order to get an auth token and API/download URLs.
     * @param string $keyId
     * @param string $applicationKey
     */
    protected function authorizeAccount(string $keyId, string $applicationKey)
    {
        $baseApiUrl = 'https://api.backblazeb2.com';
        $versionPath = '/b2api/v' . $this->version;

        $response = $this->cache->remember('B2-SDK-Authorization', 60,
            function () use ($keyId, $applicationKey, $baseApiUrl, $versionPath) {
                return $this->request('GET', $baseApiUrl . $versionPath . '/b2_authorize_account', [
                    'auth' => [$keyId, $applicationKey],
                ]);
            });

        $this->authToken = $response['authorizationToken'];
        $this->apiUrl = $response['apiUrl'] . $versionPath;
        $this->downloadUrl = $response['downloadUrl'];
        $this->recommendedPartSize = $response['recommendedPartSize'];
    }

    /**
     * Wrapper for $this->client->request
     * @param string $method
     * @param string $uri
     * @param array $options
     * @param bool $asJson
     * @param bool $wantsGetContents
     * @return mixed|string
     */
    protected function request($method, $uri = null, array $options = [], $asJson = true, $wantsGetContents = true)
    {
        $headers = [];

        // Add Authorization token if defined
        if ($this->authToken) {
            $headers['Authorization'] = $this->authToken;
        }

        $options = array_replace_recursive([
            'headers' => $headers,
        ], $options);

        $fullUri = $uri;

        if (substr($uri, 0, 8) !== 'https://') {
            $fullUri = $this->apiUrl . $uri;
        }

        return $this->client->request($method, $fullUri, $options, $asJson, $wantsGetContents);
    }
}
