<?php

declare(strict_types=1);

namespace gapple\StructuredFields;

/**
 * @implements \IteratorAggregate<string, mixed>
 */
class Parameters implements \IteratorAggregate
{
    /**
     * @var array<string, mixed>
     */
    protected array $value = [];

    /**
     * @param array<string, mixed> $array
     * @return Parameters
     */
    public static function fromArray(array $array): self
    {
        $parameters = new self();
        $parameters->value = $array;

        return $parameters;
    }

    public function __get(string $name): mixed
    {
        return $this->value[$name] ?? null;
    }

    public function __set(string $name, mixed $value): void
    {
        $this->value[$name] = $value;
    }

    public function __isset(string $name): bool
    {
        return isset($this->value[$name]);
    }

    public function __unset(string $name): void
    {
        unset($this->value[$name]);
    }

    public function getIterator(): \Iterator
    {
        return new \ArrayIterator($this->value);
    }
}
