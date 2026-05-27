<?php

declare(strict_types=1);

namespace gapple\StructuredFields;

/**
 * Trait for implementing TupleInterface, including ArrayAccess methods.
 */
trait TupleTrait
{
    /**
     * The tuple's value.
     */
    protected mixed $value;

    /**
     * The tuple's parameters
     */
    protected object $parameters;

    public function getValue(): mixed
    {
        return $this->value;
    }

    public function getParameters(): object
    {
        return $this->parameters;
    }

    // phpcs:disable SlevomatCodingStandard.TypeHints.ParameterTypeHint.MissingNativeTypeHint
    /**
     * @param int $offset
     */
    public function offsetExists($offset): bool
    {
        return $offset === 0 || $offset === 1;
    }

    /**
     * @param 0|1 $offset
     * @phpstan-return ($offset is 0 ? mixed : $offset is 1 ? object : null)
     */
    public function offsetGet($offset): mixed
    {
        return match ($offset) {
            0 => $this->value,
            1 => $this->parameters,
            default => null,
        };
    }

    /**
     * @param 0|1 $offset
     * @param mixed|object $value
     */
    public function offsetSet($offset, $value): void
    {
        if ($offset === 0) {
            $this->value = $value;
        } elseif ($offset === 1) {
            if (!is_object($value)) {
                throw new \InvalidArgumentException('Tuple parameters must be an object');
            }
            $this->parameters = $value;
        }
    }

    /**
     * @param 0|1 $offset
     */
    public function offsetUnset($offset): void
    {
        if ($offset === 0) {
            $this->value = null;
        } elseif ($offset === 1) {
            $this->parameters = new Parameters();
        }
    }
    // phpcs:enable SlevomatCodingStandard.TypeHints.ParameterTypeHint.MissingNativeTypeHint
}
