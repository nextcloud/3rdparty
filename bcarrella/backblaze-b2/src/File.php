<?php

namespace obregonco\B2;

class File implements \JsonSerializable
{
    protected $accountId;
    protected $action;
    protected $bucketId;
    protected $contentLength;
    protected $contentSha1;
    protected $contentType;
    protected $fileId;
    protected $fileInfo;
    protected $fileName;
    protected $uploadTimestamp;

    /**
     * File constructor.
     * @param array $values
     */
    public function __construct(array $values)
    {
        foreach ($values as $key => $value) {
            $this->{$key} = $value;
        }
    }

    /**
     * @return mixed
     */
    public function getAccountId()
    {
        return $this->accountId;
    }

    /**
     * @return string
     */
    public function getFileId()
    {
        return $this->fileId;
    }

    /**
     * @return string
     */
    public function getFileName()
    {
        return $this->fileName;
    }

    /**
     * @return string
     */
    public function getContentSHA1()
    {
        return $this->contentSha1;
    }

    /**
     * @return int
     */
    public function getContentLength()
    {
        return $this->contentLength;
    }

    /**
     * @return string
     */
    public function getContentType()
    {
        return $this->contentType;
    }

    /**
     * @return array
     */
    public function getFileInfo()
    {
        return $this->fileInfo;
    }

    /**
     * @return string
     */
    public function getBucketId()
    {
        return $this->bucketId;
    }

    /**
     * @return string
     */
    public function getAction()
    {
        return $this->action;
    }

    /**
     * @return string
     */
    public function getUploadTimestamp()
    {
        return $this->uploadTimestamp;
    }

    /**
     * @return array
     */
    public function jsonSerialize()
    {
        return $this->asArray();
    }

    /**
     * @return array
     */
    public function asArray()
    {
        return get_object_vars($this);
    }
}
