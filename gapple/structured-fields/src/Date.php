<?php

declare(strict_types=1);

namespace gapple\StructuredFields;

class Date extends \DateTimeImmutable
{
    public function __construct(int $timestamp)
    {
        parent::__construct("@{$timestamp}");
    }

    /**
     * @deprecated in 2.3.0 and will be removed from 3.0.0.  Use Date::getTimestamp() instead.
     * @codeCoverageIgnore
     */
    public function toInt(): int
    {
        return $this->getTimestamp();
    }
}
