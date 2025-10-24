<?php

declare(strict_types=1);

/**
 * SPDX-FileCopyrightText: 2016-2025 Nextcloud GmbH and Nextcloud contributors
 * SPDX-FileCopyrightText: 2015 Olivier Paroz <dev-lognormalizer@interfasys.ch>
 * SPDX-FileCopyrightText: 2014-2015 Jordi Boggiano <j.boggiano@seld.be>
 * SPDX-License-Identifier: AGPL-3.0-or-later
 */

namespace Nextcloud\LogNormalizer;

use Throwable;
use function is_float;
use function is_scalar;

/**
 * Converts any variable to a string
 *
 * @package Nextcloud\LogNormalizer
 * @api
 */
class Normalizer {

	/**
	 * @type string
	 */
	private const SIMPLE_DATE = 'Y-m-d H:i:s';

	/**
	 * @var int
	 */
	private $maxRecursionDepth;

	/**
	 * @var int
	 */
	private $maxArrayItems;

	/**
	 * @var string
	 */
	private $dateFormat;

	/**
	 * @param int $maxRecursionDepth The maximum depth at which to go when inspecting objects
	 * @param int $maxArrayItems The maximum number of Array elements you want to show, when
	 *                           parsing an array
	 * @param null|string $dateFormat The format to apply to dates
	 */
	public function __construct($maxRecursionDepth = 4, $maxArrayItems = 20, $dateFormat = null) {
		$this->maxRecursionDepth = $maxRecursionDepth;
		$this->maxArrayItems = $maxArrayItems;
		if ($dateFormat !== null) {
			$this->dateFormat = $dateFormat;
		} else {
			$this->dateFormat = static::SIMPLE_DATE;
		}
	}

	/**
	 * Normalizes the variable, JSON encodes it if needed and cleans up the result
	 *
	 * @param mixed $data
	 * @return string|null
	 */
	#[\NoDiscard]
	public function format($data): ?string {
		$data = $this->normalize($data);
		return $this->convertToString($data);
	}

	/**
	 * Converts Objects, Arrays, Dates and Exceptions to a string or an Array
	 *
	 * @uses Nextcloud\LogNormalizer\Normalizer::normalizeTraversable
	 * @uses Nextcloud\LogNormalizer\Normalizer::normalizeDate
	 * @uses Nextcloud\LogNormalizer\Normalizer::normalizeObject
	 * @uses Nextcloud\LogNormalizer\Normalizer::normalizeResource
	 *
	 * @param mixed $data
	 * @param int $depth
	 *
	 * @return mixed|array
	 */
	public function normalize($data, ?int $depth = 0) {
		$scalar = $this->normalizeScalar($data);
		if ($scalar !== null) {
			return $scalar;
		}
		$decisionArray = [
			'normalizeTraversable' => [$data, $depth],
			'normalizeDate' => [$data],
			'normalizeObject' => [$data, $depth],
			'normalizeResource' => [$data],
		];

		foreach ($decisionArray as $functionName => $arguments) {
			$dataType = call_user_func_array([$this, $functionName], $arguments);
			if ($dataType !== null) {
				return $dataType;
			}
		}

		return '[unknown(' . gettype($data) . ')]';
	}

	/**
	 * JSON encodes data which isn't already a string and cleans up the result
	 *
	 * @todo: could maybe do a better job removing slashes
	 *
	 * @param mixed $data
	 *
	 * @return string|null
	 */
	public function convertToString($data): ?string {
		if (!is_string($data)) {
			$data = @json_encode($data, JSON_UNESCAPED_SLASHES | JSON_UNESCAPED_UNICODE | JSON_PARTIAL_OUTPUT_ON_ERROR);
			// Removing null byte and double slashes from object properties
			$data = str_replace(['\\u0000', '\\\\'], ['', '\\'], $data);
		}

		return $data;
	}

	/**
	 * Returns various, filtered, scalar elements
	 *
	 * We're returning an array here to detect failure because null is a scalar and so is false
	 *
	 * @param mixed $data
	 *
	 * @return string|mixed|null
	 */
	private function normalizeScalar($data) {
		if ($data === null) {
			return null;
		}

		if (is_float($data)) {
			return $this->normalizeFloat($data);
		}

		if (is_scalar($data)) {
			return $data;
		}

		return null;
	}

	/**
	 * Normalizes infinite and trigonometric floats
	 *
	 * @param float $data
	 *
	 * @return string|float
	 */
	private function normalizeFloat(float $data) {
		if (is_infinite($data)) {
			$postfix = 'INF';
			if ($data < 0) {
				$postfix = '-' . $postfix;
			}
			return $postfix;
		}

		if (is_nan($data)) {
			return 'NaN';
		}

		return $data;
	}

	/**
	 * Returns an array containing normalized elements
	 *
	 * @used-by Nextcloud\LogNormalizer\Normalizer::normalize
	 *
	 * @param mixed $data
	 * @param int $depth
	 *
	 * @return array|null
	 */
	private function normalizeTraversable($data, int $depth = 0): ?array {
		if (is_array($data) || $data instanceof \Traversable) {
			return $this->normalizeTraversableElement($data, $depth);
		}

		return null;
	}

	/**
	 * Converts each element of a traversable variable to String
	 *
	 * @param mixed $data
	 * @param int $depth
	 *
	 * @return array
	 */
	private function normalizeTraversableElement($data, int $depth): array {
		$maxObjectRecursion = $this->maxRecursionDepth;
		$maxArrayItems = $this->maxArrayItems;
		$count = 1;
		$normalized = [];
		$nextDepth = $depth + 1;
		foreach ($data as $key => $value) {
			if ($count >= $maxArrayItems) {
				$normalized['...']
					= 'Over ' . $maxArrayItems . ' items, aborting normalization';
				break;
			}
			$count++;
			if ($depth < $maxObjectRecursion) {
				$normalized[$key] = $this->normalize($value, $nextDepth);
			}
		}

		return $normalized;
	}

	/**
	 * Converts a date to String
	 *
	 * @used-by Nextcloud\LogNormalizer\Normalizer::normalize
	 *
	 * @param mixed $data
	 *
	 * @return null|string
	 */
	private function normalizeDate($data): ?string {
		if ($data instanceof \DateTimeInterface) {
			return $data->format($this->dateFormat);
		}

		return null;
	}

	/**
	 * Converts an Object to an Array
	 *
	 * We don't convert to json here as we would double encode them
	 *
	 * @used-by Nextcloud\LogNormalizer\Normalizer::normalize
	 *
	 * @param mixed $data
	 * @param int $depth
	 *
	 * @return mixed[]|string|null
	 */
	private function normalizeObject($data, int $depth) {
		if (is_object($data)) {
			if ($data instanceof Throwable) {
				return $this->normalizeException($data);
			}
			// We don't need to go too deep in the recursion
			$maxObjectRecursion = $this->maxRecursionDepth;
			$arrayObject = new \ArrayObject($data);
			$serializedObject = $arrayObject->getArrayCopy();
			if ($depth < $maxObjectRecursion) {
				$depth++;
				$response = $this->normalize($serializedObject, $depth);

				return [$this->getObjetName($data) => $response];
			}

			return $this->getObjetName($data);
		}

		return null;
	}

	/**
	 * Converts an Exception to a string array
	 *
	 * @param Throwable $exception
	 *
	 * @return mixed[]
	 */
	private function normalizeException(Throwable $exception): array {
		$data = [
			'class' => get_class($exception),
			'message' => $exception->getMessage(),
			'code' => $exception->getCode(),
			'file' => $exception->getFile() . ':' . $exception->getLine(),
		];
		$trace = $exception->getTraceAsString();
		$data['trace'] = $trace;

		$previous = $exception->getPrevious();
		if ($previous) {
			$data['previous'] = $this->normalizeException($previous);
		}

		return $data;
	}

	/**
	 * Formats the output of the object parsing
	 *
	 * @param object $object
	 *
	 * @return string
	 */
	private function getObjetName(object $object): string {
		return sprintf('[object] (%s)', get_class($object));
	}

	/**
	 * Converts a resource to a string
	 *
	 * @used-by Nextcloud\LogNormalizer\Normalizer::normalize
	 *
	 * @param resource|mixed $data
	 *
	 * @return string|null
	 */
	private function normalizeResource($data): ?string {
		if (is_resource($data)) {
			return '[resource] ' . substr((string)$data, 0, 40);
		}

		return null;
	}
}
