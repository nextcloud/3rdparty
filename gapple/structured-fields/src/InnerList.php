<?php

declare(strict_types=1);

namespace gapple\StructuredFields;

class InnerList implements TupleInterface
{
    use TupleTrait;

    /**
     * @param array<TupleInterface|array{mixed, object}> $value
     */
    public function __construct(array $value, ?object $parameters = null)
    {
        array_walk($value, self::validateItemType(...));

        $this->value = $value;
        $this->parameters = $parameters ?? new Parameters();
    }

    /**
     * Create an InnerList from an array of bare values.
     *
     * @param array<mixed> $array
     *   An array of bare items or TupleInterface objects.
     */
    public static function fromArray(array $array): InnerList
    {
        array_walk($array, function (&$item): void {
            if (!$item instanceof TupleInterface) {
                $item = new Item($item);
            } elseif ($item instanceof InnerList) {
                throw new \InvalidArgumentException('InnerList objects cannot be nested');
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
            if ($value instanceof InnerList) {
                throw new \InvalidArgumentException('InnerList objects cannot be nested');
            }
        } elseif (is_array($value)) {
            if (count($value) !== 2) {
                throw new \InvalidArgumentException();
            }
        } else {
            throw new \InvalidArgumentException();
        }
    }
}
