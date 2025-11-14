<?php
/**
 * SPDX-FileCopyrightText: 2015 Robin Appelman <robin@icewind.nl>
 * SPDX-License-Identifier: MIT
 */
namespace Icewind\SMB;

/**
 * @psalm-suppress ClassMustBeFinal
 */
class TimeZoneProvider implements ITimeZoneProvider {
	/**
	 * @var string[]
	 */
	private $timeZones = [];

	/**
	 * @var ISystem
	 */
	private $system;

	/**
	 * @param ISystem $system
	 */
	public function __construct(ISystem $system) {
		$this->system = $system;
	}

	public function get(string $host): string {
		if (!isset($this->timeZones[$host])) {
			$timeZone = null;
			$net = $this->system->getNetPath();
			// for local domain names we can assume same timezone
			if ($net !== null && $host && strpos($host, '.') !== false) {
				$command = sprintf(
					'%s time zone -S %s',
					$net,
					escapeshellarg($host)
				);
				$timeZone = exec($command);
			}

			if (!is_string($timeZone)) {
				$date = $this->system->getDatePath();
				if ($date !== null) {
					$timeZone = exec($date . " +%z");
				}
				if (!is_string($timeZone)) {
					$timeZone = date_default_timezone_get();
				}
			}
			$this->timeZones[$host] = $timeZone;
		}
		return $this->timeZones[$host];
	}
}
