<?php

declare(strict_types=1);

namespace gapple\StructuredFields;

/**
 * @internal
 */
class ParsingInput
{
    private readonly int $length;
    private int $position = 0;

    public function __construct(
        private readonly string $value,
    ) {
        $this->length = strlen($this->value);
    }

    public function position(): int
    {
        return $this->position;
    }

    public function empty(): bool
    {
        return $this->position >= $this->length;
    }

    public function remaining(): string
    {
        return substr($this->value, $this->position);
    }

    public function remainingLength(): int
    {
        return $this->length - $this->position();
    }

    /**
     * Trim whitespace from beginning of string.
     *
     * @param bool $ows
     *   Whether all Optional Whitespace characters should be trimmed.  If false, only space characters are trimmed.
     *   @see https://tools.ietf.org/html/rfc7230#section-3.2.3
     */
    public function trim(bool $ows = false): void
    {
        while (
            $this->position < $this->length
            && (
                $this->value[$this->position] === ' '
                || ($ows && $this->value[$this->position] === "\t")
            )
        ) {
            $this->position++;
        }
    }

    /**
     * @deprecated in 2.3.0 and will be removed in 3.0.0
     * @codeCoverageIgnore
     */
    public function isChar(string $char): bool
    {
        return $this->isNextChar($char);
    }

    public function isNextChar(string $char): bool
    {
        assert(strlen($char) === 1);

        return $this->position < $this->length
            && $this->value[$this->position] === $char;
    }

    public function getChar(): string
    {
        if ($this->position >= $this->length) {
            throw new \RuntimeException('Reached end of value');
        }
        return $this->value[$this->position];
    }

    public function skipNextCharIf(string $char): bool
    {
        if ($this->isNextChar($char)) {
            $this->position++;
            return true;
        }
        return false;
    }

    /**
     * @phpstan-impure
     */
    public function consume(int $length, ?string $expected = null): string
    {
        assert($length > 0);
        assert($expected === null || strlen($expected) === $length);

        if ($length > $this->length - $this->position) {
            throw new \RuntimeException('Reached end of value');
        }

        $output = substr($this->value, $this->position, $length);
        if (!is_null($expected) && $expected !== $output) {
            throw new \RuntimeException('Unexpected character');
        }
        $this->position += $length;
        return $output;
    }

    /**
     * @phpstan-impure
     */
    public function consumeChar(?string $value = null): string
    {
        assert($value === null || strlen($value) === 1);

        return $this->consume(1, $value);
    }

    /**
     * @phpstan-impure
     */
    public function consumeString(string $value): void
    {
        $this->consume(strlen($value), $value);
    }

    /**
     * @phpstan-impure
     */
    public function consumeRegex(string $pattern): string
    {
        assert(str_starts_with($pattern, '/^'), "Regular expression must be anchored to beginning of string");
        assert(!preg_match('/\$\/[a-z]+$/i', $pattern), "Regular expression must not be anchored to end of string");

        if (preg_match($pattern, $this->remaining(), $matches)) {
            $this->position += strlen($matches[0]);
            return $matches[0];
        }

        throw new \RuntimeException('Expression did not match');
    }
}
