<?php

declare(strict_types=1);

namespace gapple\StructuredFields;

/**
 * Interface for objects that represent a [value, parameters] tuple.
 *
 * @see TupleTrait
 * @extends \ArrayAccess<int, mixed>
 */
interface TupleInterface extends \ArrayAccess
{
    public function getValue(): mixed;
    public function getParameters(): object;
}
