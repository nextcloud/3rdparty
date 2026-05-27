<?php

declare(strict_types=1);

namespace gapple\StructuredFields;

class Serializer
{
    /**
     * Serialize an item with optional parameters.
     *
     * @param Item|mixed $value
     *   A bare value, or an Item object.
     * @param object|null $parameters
     *   If a bare value is provided, an optional object containing parameter values.
     */
    public static function serializeItem(mixed $value, ?object $parameters = null): string
    {
        if ($value instanceof Item) {
            if (!is_null($parameters)) {
                throw new \InvalidArgumentException(
                    'Parameters argument is not allowed when serializing an Item object'
                );
            }

            $bareValue = $value->getValue();
            $parameters = $value->getParameters();
        } else {
            $bareValue = $value;
        }

        $output = self::serializeBareItem($bareValue);

        if (!empty($parameters)) {
            $output .= self::serializeParameters($parameters);
        }

        return $output;
    }

    /**
     * @param iterable<TupleInterface|array{mixed, object}> $value
     */
    public static function serializeList(iterable $value): string
    {
        if ($value instanceof \Traversable) {
            // @todo Checking for Traversable is not required for PHP ^8.2.0.
            $value = iterator_to_array($value);
        }

        $returnValue = array_map(function ($item) {
            if ($item instanceof TupleInterface) {
                $itemValue = $item->getValue();
                $itemParameters = $item->getParameters();
            } elseif (is_array($item) && count($item) === 2) {
                $itemValue = $item[0];
                $itemParameters = $item[1];
            } else {
                throw new SerializeException("Invalid item in list");
            }

            if (is_array($itemValue)) {
                return self::serializeInnerList($itemValue, $itemParameters);
            } else {
                return self::serializeItem($itemValue, $itemParameters);
            }
        }, $value);

        return implode(', ', $returnValue);
    }

    /**
     * Serialize an object as a dictionary.
     *
     * Either a Traversable object can be provided, or the public properties of the object will be extracted.
     *
     * @param Dictionary|object $value
     */
    public static function serializeDictionary(object $value): string
    {
        $returnValue = '';

        if (!$value instanceof \Traversable) {
            $value = get_object_vars($value);
        }

        foreach ($value as $key => $item) {
            if (!empty($returnValue)) {
                $returnValue .= ', ';
            }

            $returnValue .= self::serializeKey($key);

            if ($item instanceof TupleInterface) {
                $itemValue = $item->getValue();
                $itemParameters = $item->getParameters();
            } else {
                $itemValue = $item[0];
                $itemParameters = $item[1];
            }

            if ($itemValue === true) {
                $returnValue .= self::serializeParameters($itemParameters);
            } elseif (is_array($itemValue)) {
                $returnValue .= '=' . self::serializeInnerList($itemValue, $itemParameters);
            } else {
                $returnValue .= '=' . self::serializeItem($itemValue, $itemParameters);
            }
        }

        return $returnValue;
    }

    /**
     * @param array<TupleInterface|array{mixed, object}> $value
     */
    private static function serializeInnerList(array $value, ?object $parameters = null): string
    {
        $returnValue = '(';

        while ($item = array_shift($value)) {
            if ($item instanceof TupleInterface) {
                if ($item instanceof InnerList) {
                    throw new SerializeException("Inner lists cannot be nested");
                }
                $returnValue .= self::serializeItem($item);
            } else {
                if (is_array($item[0])) {
                    throw new SerializeException("Inner lists cannot be nested");
                }
                $returnValue .= self::serializeItem($item[0], $item[1]);
            }

            if (!empty($value)) {
                $returnValue .= ' ';
            }
        }

        $returnValue .= ')';

        if (!empty($parameters)) {
            $returnValue .= self::serializeParameters($parameters);
        }

        return $returnValue;
    }

    private static function serializeBareItem(mixed $value): string
    {
        if (is_int($value)) {
            return self::serializeInteger($value);
        } elseif (is_float($value)) {
            return self::serializeDecimal($value);
        } elseif (is_bool($value)) {
            return self::serializeBoolean($value);
        } elseif ($value instanceof \DateTimeInterface) {
            return self::serializeDate($value);
        } elseif ($value instanceof Bytes) {
            return self::serializeByteSequence($value);
        } elseif ($value instanceof DisplayString) {
            return self::serializeDisplayString($value);
        } elseif ($value instanceof Token) {
            return self::serializeToken($value);
        } elseif (is_string($value) || $value instanceof \Stringable) {
            return self::serializeString((string) $value);
        }

        throw new SerializeException("Unrecognized type");
    }

    private static function serializeBoolean(bool $value): string
    {
        return '?' . ($value ? '1' : '0');
    }

    private static function serializeInteger(int $value): string
    {
        if ($value > 999999999999999 || $value < -999999999999999) {
            throw new SerializeException("Integers are limited to 15 digits");
        }
        return (string) $value;
    }

    private static function serializeDecimal(float $value): string
    {
        if (abs(floor($value)) > 999999999999) {
            throw new SerializeException("Integer portion of decimals is limited to 12 digits");
        }

        // Casting to a string loses a digit on long numbers, but is preserved
        // by json_encode (e.g. 111111111111.111).
        /** @var string $result */
        $result = json_encode(round($value, 3, PHP_ROUND_HALF_EVEN));

        if (!str_contains($result, '.')) {
            $result .= '.0';
        }

        return $result;
    }

    private static function serializeString(string $value): string
    {
        if (!empty($value) && !ctype_print($value)) {
            throw new SerializeException("Invalid characters in string");
        }
        return '"' . str_replace(['\\', '"'], ['\\\\', '\"'], $value) . '"';
    }

    private static function serializeDisplayString(DisplayString $value): string
    {
        return '%"'
        . preg_replace_callback(
            '/[%"\x00-\x1F\x7F-\xFF]/',
            fn($matches) => strtolower(rawurlencode($matches[0])),
            (string) $value
        )
        . '"';
    }

    private static function serializeToken(Token $value): string
    {
        // RFC 9110: HTTP Semantics (5.6.2. Tokens)
        // @see https://www.rfc-editor.org/rfc/rfc9110.html#name-tokens
        // $tchar = preg_quote("!#$%&'*+-.^_`|~");
        $tchar = "!#$%&'*+\-.^_`|~";

        if (
            !preg_match('/^(
                (?:\*|[a-z])                # an alphabetic character or "*"
                [a-z0-9:\/' . $tchar . ']*  # zero to many token characters
            )$/ix', (string) $value)
        ) {
            throw new SerializeException('Invalid characters in token');
        }

        return (string) $value;
    }

    private static function serializeByteSequence(Bytes $value): string
    {
        return ':' . base64_encode((string) $value) . ':';
    }

    private static function serializeParameters(object $value): string
    {
        $returnValue = '';

        if (!$value instanceof \Traversable) {
            $value = get_object_vars($value);
        }

        foreach ($value as $key => $item) {
            $returnValue .= ';' . self::serializeKey($key);

            if ($item !== true) {
                $returnValue .= '=' . self::serializeBareItem($item);
            }
        }

        return $returnValue;
    }

    private static function serializeDate(\DateTimeInterface $value): string
    {
        return '@' . self::serializeInteger($value->getTimestamp());
    }

    private static function serializeKey(string $value): string
    {
        if (!preg_match('/^[a-z*][a-z0-9.*_-]*$/', $value)) {
            throw new SerializeException("Invalid characters in key");
        }

        return $value;
    }
}
