<?php

declare(strict_types=1);

namespace gapple\StructuredFields;

class Item implements TupleInterface
{
    use TupleTrait;

    public function __construct(mixed $value, ?object $parameters = null)
    {
        $this->value = $value;
        $this->parameters = $parameters ?? new Parameters();
    }
}
