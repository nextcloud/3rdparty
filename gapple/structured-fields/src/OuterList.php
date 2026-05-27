<?php

declare(strict_types=1);

namespace gapple\StructuredFields;

/**
 * @implements \IteratorAggregate<int, TupleInterface|array{mixed, object}>
 * @implements \ArrayAccess<int, TupleInterface|array{mixed, object}>
 */
class OuterList implements \IteratorAggregate, \ArrayAccess
{
    /**
     * The array of values.
     *
     * @var array<TupleInterface|array{mixed, object}>
     */
    public array $value;

    /**
     * @param array<TupleInterface|array{mixed, object}> $value
     */
    public function __construct(array $value = [])
    {
        array_walk($value, self::validateItemType(...));

        $this->value = $value;
    }

    /**
     * Create an OuterList from an array of bare values.
     *
     * @param array<mixed> $array
     */
    public static function fromArray(array $array): OuterList
    {
        array_walk($array, function (&$item): void {
            if (!$item instanceof TupleInterface) {
                if (is_array($item)) {
                    $item = InnerList::fromArray($item);
                } else {
                    $item = new Item($item);
                }
            }
        });

        /** @var TupleInterface[] $array */
        return new self($array);
    }

    /**
     * @param TupleInterface|array{mixed, object} $value
     */
    private static function validateItemType(mixed $value): void
    {
        if (is_object($value)) {
            if (!($value instanceof TupleInterface)) {
                throw new \InvalidArgumentException(
                    'Objects as list values must implement ' . TupleInterface::class
                );
            }
        } elseif (is_array($value)) {
            if (count($value) !== 2) {
                throw new \InvalidArgumentException();
            }
        } else {
             throw new \InvalidArgumentException();
        }
    }

    public function getIterator(): \Iterator
    {
        return new \ArrayIterator($this->value);
    }

    // phpcs:disable SlevomatCodingStandard.TypeHints.ParameterTypeHint.MissingNativeTypeHint
    /**
     * @param int $offset
     */
    public function offsetExists($offset): bool
    {
        return isset($this->value[$offset]);
    }

    /**
     * @param int $offset
     * @phpstan-return TupleInterface|array{mixed, object}|null
     */
    public function offsetGet($offset): mixed
    {
        return $this->value[$offset] ?? null;
    }

    /**
     * @param int|null $offset
     * @param TupleInterface|array{mixed, object} $value
     */
    public function offsetSet($offset, $value): void
    {
        self::validateItemType($value);

        if (is_null($offset)) {
            $this->value[] = $value;
        } else {
            $this->value[$offset] = $value;
        }
    }

    /**
     * @param int $offset
     */
    public function offsetUnset($offset): void
    {
        unset($this->value[$offset]);
    }
    // phpcs:enable SlevomatCodingStandard.TypeHints.ParameterTypeHint.MissingNativeTypeHint
}
