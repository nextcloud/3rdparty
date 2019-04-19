## Backblaze B2 SDK for PHP
[![Software License](https://img.shields.io/badge/license-LGPL-brightgreen.svg?style=flat-square)](LICENSE.md)
[![Latest Version](https://img.shields.io/github/release/bcarrella/backblaze-b2.svg?style=flat-square)](https://github.com/bcarrella/backblaze-b2/releases)
[![Build Status](https://img.shields.io/travis/bcarrella/backblaze-b2.svg?style=flat-square)](https://travis-ci.org/bcarrella/backblaze-b2)

`backblaze-b2` is a client library for working with Backblaze's B2 storage service. It aims to make using the service as
easy as possible by exposing a clear API and taking influence from other SDKs that you may be familiar with.

This package will **cache authorization request** for 1 hour so that you won't receive API Limit from B2.

This version works with both master key and application key, and version 2 (look below).

## Example

This is just a short example, full examples to come on the wiki.

```php
use obregonco\B2\Client;
use obregonco\B2\Bucket;

$client = new Client('accountId', 
    [
	'keyId' => 'your-key-id', // optional if you want to use master key (account Id)
	'applicationKey' => 'your-application-key',
	'version' => 2, // By default will use version 1
	'domainAliases' => [ // When you want to use your own domains (using CNAME)
		'f0001.backblazeb2.com' => 'alias01.mydomain.com',
	                   ]
    ],
    [
    'largeFileLimit' => 3000000000, // Lower limit for using large files upload support. Default: 3GB
    'cacheParentDir' => '/path/to/your-php-writable-dir',
    ]
    
);

// Returns a Bucket object.
$bucket = $client->createBucket([
    'BucketName' => 'my-special-bucket',
    'BucketType' => Bucket::TYPE_PRIVATE // or TYPE_PUBLIC
]);

// Change the bucket to private. Also returns a Bucket object.
$updatedBucket = $client->updateBucket([
    'BucketId' => $bucket->getId(),
    'BucketType' => Bucket::TYPE_PUBLIC
]);

// Retrieve an array of Bucket objects on your account.
$buckets = $client->listBuckets();

// Delete a bucket.
$client->deleteBucket([
    'BucketId' => '4c2b957661da9c825f465e1b'
]);

// Upload a file to a bucket. Returns a File object.
$file = $client->upload([
    'BucketName' => 'my-special-bucket',
    'FileName' => 'path/to/upload/to',
    'Body' => 'I am the file content'

    // The file content can also be provided via a resource.
    // 'Body' => fopen('/path/to/input', 'r')
]);

// Download a file from a bucket. Returns the file content.
$fileContent = $client->download([
    'FileId' => $file->getId()

    // Can also identify the file via bucket and path:
    // 'BucketName' => 'my-special-bucket',
    // 'FileName' => 'path/to/file'

    // Can also save directly to a location on disk. This will cause download() to not return file content.
    // 'SaveAs' => '/path/to/save/location'
]);

// Delete a file from a bucket. Returns true or false.
$fileDelete = $client->deleteFile([
    'FileId' => $file->getId()
    
    // Can also identify the file via bucket and path:
    // 'BucketName' => 'my-special-bucket',
    // 'FileName' => 'path/to/file'
]);

// Retrieve an array of file objects from a bucket.
$fileList = $client->listFiles([
    'BucketId' => '4d2dbbe08e1e983c5e6f0d12'
]);
```

## Installation

Installation is via Composer:

```bash
$ composer require bcarrella/backblaze-b2
```

## Tests

Tests are run with PHPUnit. After installing PHPUnit via Composer (under development):

```bash
$ vendor/bin/phpunit
```

## Contributors

Feel free to contribute in any way you can whether that be reporting issues, making suggestions or sending PRs. :)

## License

LGPL.
