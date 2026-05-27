<?php

declare(strict_types=1);

namespace gapple\StructuredFields;

class Parser
{
    public static function parseDictionary(string $string): Dictionary
    {
        $value = new Dictionary();

        $input = new ParsingInput($string);
        $input->trim();

        if ($input->empty()) {
            return $value;
        }

        while (true) {
            $key = self::parseKey($input);

            if ($input->skipNextCharIf('=')) {
                $value->{$key} = self::parseItemOrInnerList($input);
            } else {
                // Bare boolean true value.
                $value->{$key} = new Item(true, self::parseParameters($input));
            }

            // Optional whitespace before comma or at end of string.
            $input->trim(true);

            if ($input->empty()) {
                return $value;
            }

            try {
                $input->consumeChar(',');
            } catch (\RuntimeException) {
                throw new ParseException('Expected comma at position ' . $input->position());
            }
            // Optional whitespace after comma.
            $input->trim(true);

            if ($input->empty()) {
                throw new ParseException('Unexpected end of input');
            }
        }
    }

    public static function parseList(string $string): OuterList
    {
        $value = new OuterList();
        $input = new ParsingInput($string);
        $input->trim();

        if ($input->empty()) {
            return $value;
        }

        while (true) {
            $value[] = self::parseItemOrInnerList($input);

            // Optional whitespace before comma or at end of string.
            $input->trim(true);

            if ($input->empty()) {
                return $value;
            }

            try {
                $input->consumeChar(',');
            } catch (\RuntimeException) {
                throw new ParseException('Expected comma at position ' . $input->position());
            }
            // Optional whitespace after comma.
            $input->trim(true);

            if ($input->empty()) {
                throw new ParseException('Unexpected end of input');
            }
        }
    }

    private static function parseItemOrInnerList(ParsingInput $input): TupleInterface
    {
        if ($input->isNextChar('(')) {
            return self::parseInnerList($input);
        } else {
            return self::doParseItem($input);
        }
    }

    /**
     * @phpstan-impure
     */
    private static function parseInnerList(ParsingInput $input): InnerList
    {
        $startPosition = $input->position();
        $value = [];

        $input->consumeChar('(');
        while (!$input->empty()) {
            $input->trim();

            if ($input->skipNextCharIf(')')) {
                return new InnerList(
                    $value,
                    self::parseParameters($input)
                );
            }

            $value[] = self::doParseItem($input);

            if (!($input->isNextChar(' ') || $input->isNextChar(')'))) {
                if ($input->empty()) {
                    break;
                }
                throw new ParseException('Unexpected character in inner list at position ' . $input->position());
            }
        }

        throw new ParseException('Unexpected end of list started at position ' . $startPosition);
    }

    /**
     * @return Item
     *  A [value, parameters] tuple.
     */
    public static function parseItem(string $string): Item
    {
        $input = new ParsingInput($string);

        $input->trim();
        if ($input->empty()) {
            throw new ParseException('Unexpected empty input');
        }

        $value = self::doParseItem($input);
        $input->trim();

        if ($input->empty()) {
            return $value;
        }

        throw new ParseException('Unexpected characters at position ' . $input->position());
    }

    /**
     * Internal implementation of parseItem that doesn't fail if input string
     * has remaining characters after parsing.
     *
     * @phpstan-impure
     */
    private static function doParseItem(ParsingInput $input): Item
    {
        return new Item(
            self::parseBareItem($input),
            self::parseParameters($input),
        );
    }

    /**
     * @return bool|float|int|string|Bytes|Date|DisplayString|Token
     *
     * @phpstan-impure
     */
    private static function parseBareItem(ParsingInput $input): mixed
    {
        $char = $input->getChar();
        return match (true) {
            preg_match('/(-|\d)/', $char) === 1  => self::parseNumber($input),
            '"' === $char                        => self::parseString($input),
            preg_match('/[a-z*]/i', $char) === 1 => self::parseToken($input),
            ':' === $char                        => self::parseByteSequence($input),
            '?' === $char                        => self::parseBoolean($input),
            '@' === $char                        => self::parseDate($input),
            '%' === $char                        => self::parseDisplayString($input),
            default => throw new ParseException('Unknown item type at position ' . $input->position()),
        };
    }

    /**
     * @phpstan-impure
     */
    private static function parseParameters(ParsingInput $input): Parameters
    {
        $parameters = new Parameters();
        while ($input->skipNextCharIf(';')) {
            $input->trim();

            $key = self::parseKey($input);

            if ($input->skipNextCharIf('=')) {
                $parameters->{$key} = self::parseBareItem($input);
            } else {
                $parameters->{$key} = true;
            }
        }

        return $parameters;
    }

    /**
     * @phpstan-impure
     */
    private static function parseKey(ParsingInput $input): string
    {
        try {
            return $input->consumeRegex('/^[a-z*][a-z0-9.*_-]*/');
        } catch (\RuntimeException) {
            throw new ParseException('Invalid key at position ' . $input->position());
        }
    }

    /**
     * @phpstan-impure
     */
    private static function parseBoolean(ParsingInput $input): bool
    {
        $input->consumeChar('?');
        return match ($input->consumeChar()) {
            '0' => false,
            '1' => true,
            default => throw new ParseException('Invalid boolean at position ' . $input->position()),
        };
    }

    /**
     * @phpstan-impure
     */
    private static function parseNumber(ParsingInput $input): int|float
    {
        $startPosition = $input->position();
        try {
            $number = $input->consumeRegex('/^(-?\d+(?:\.\d+)?)/');
        } catch (\RuntimeException) {
            throw new ParseException('Invalid number format at position ' . $startPosition);
        }

        if (preg_match('/^-?\d{1,12}\.\d{1,3}$/', $number)) {
            return (float) $number;
        } elseif (preg_match('/^-?\d{1,15}$/', $number)) {
            return (int) $number;
        }
        throw new ParseException('Number contains too many digits at position ' . $startPosition);
    }

    /**
     * @phpstan-impure
     */
    private static function parseString(ParsingInput $input): string
    {
        $output = '';

        $input->consumeChar('"');
        while (!$input->empty()) {
            $char = $input->consumeChar();

            if ($char === '\\') {
                if ($input->empty()) {
                    throw new ParseException("Invalid end of string");
                }

                $char = $input->consumeChar();
                if ($char !== '"' && $char !== '\\') {
                    throw new ParseException(
                        'Invalid escaped character in string at position ' . ($input->position() - 1)
                    );
                }
            } elseif ($char === '"') {
                return $output;
            } elseif (
                !ctype_print($char)
                || (PHP_OS_FAMILY === 'Darwin' && mb_detect_encoding($char, ['ASCII'], true) === false)
            ) {
                throw new ParseException('Invalid character in string at position ' . ($input->position() - 1));
            }

            $output .= $char;
        }

        throw new ParseException("Invalid end of string");
    }

    /**
     * @phpstan-impure
     */
    private static function parseDisplayString(ParsingInput $string): DisplayString
    {
        $startPosition = $string->position();
        try {
            $string->consumeString('%"');
        } catch (\RuntimeException) {
            throw new ParseException('Invalid start of display string at position ' . $startPosition);
        }

        $encodedString = '';
        while (!$string->empty()) {
            $char = $string->consumeChar();

            if (
                !ctype_print($char)
                || (PHP_OS_FAMILY === 'Darwin' && mb_detect_encoding($char, ['ASCII'], true) === false)
            ) {
                throw new ParseException(
                    'Invalid character in display string at position ' . ($string->position() - 1)
                );
            } elseif ($char === '%') {
                if ($string->remainingLength() < 2) {
                    break;
                }
                $encodedChar = $string->consume(2);
                if (!ctype_xdigit($encodedChar) || ctype_upper($encodedChar)) {
                    throw new ParseException(
                        'Invalid hex values in display string at position ' . ($string->position() - 1)
                    );
                }
                $encodedString .= '%' . $encodedChar;
            } elseif ($char === '"') {
                $displayString = new DisplayString(rawurldecode($encodedString));
                // An invalid UTF-8 subject will cause the preg_* function to match nothing.
                // @see https://www.php.net/manual/en/reference.pcre.pattern.modifiers.php
                if (!preg_match('/^\X*$/u', (string) $displayString)) {
                    throw new ParseException('Invalid byte sequence in display string at position ' . $startPosition);
                }
                return $displayString;
            } else {
                $encodedString .= $char;
            }
        }

        throw new ParseException('Invalid end of display string started at position ' . $startPosition);
    }

    /**
     * @phpstan-impure
     */
    private static function parseToken(ParsingInput $input): Token
    {
        // RFC 9110: HTTP Semantics (5.6.2. Tokens)
        // @see https://www.rfc-editor.org/rfc/rfc9110.html#name-tokens
        // $tchar = preg_quote("!#$%&'*+-.^_`|~");
        $tchar = "!#$%&'*+\-.^_`|~";

        // parseToken is only called by parseBareItem if the initial character
        // is valid, so a Token object is always returned.  If there is an
        // invalid character in the token, the public function that was called
        // will detect that the remainder of the input string is invalid.
        return new Token($input->consumeRegex('/^(
                (?:\*|[a-z])                # an alphabetic character or "*"
                [a-z0-9:\/' . $tchar . ']*  # zero to many token characters
            )/ix'));
    }

    /**
     * Parse Base64-encoded data.
     *
     * @phpstan-impure
     */
    private static function parseByteSequence(ParsingInput $input): Bytes
    {
        $startPosition = $input->position();
        $input->consumeChar(':');
        try {
            $bytes = $input->consumeRegex('/^([a-z0-9+\/]*=*)(?=:)/i');
            $input->consumeChar(':');
            return new Bytes(base64_decode($bytes));
        } catch (\RuntimeException) {
            throw new ParseException('Invalid byte sequence at position ' . $startPosition);
        }
    }

    /**
     * @phpstan-impure
     */
    private static function parseDate(ParsingInput $input): Date
    {
        $startPosition = $input->position();
        $input->consumeChar('@');
        try {
            $value = self::parseNumber($input);

            if (is_int($value)) {
                return new Date($value);
            }
        } catch (ParseException) {
        }

        throw new ParseException('Invalid Date format at position ' . $startPosition);
    }
}
