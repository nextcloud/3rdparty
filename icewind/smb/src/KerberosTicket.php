<?php

declare(strict_types=1);
/**
 * SPDX-FileCopyrightText: 2022 Robin Appelman <robin@icewind.nl>
 * SPDX-License-Identifier: AGPL-3.0-or-later
 */

namespace Icewind\SMB;

use Icewind\SMB\Exception\InvalidTicket;
use KRB5CCache;

final class KerberosTicket {
	/** @var KRB5CCache */
	private $krb5;
	/** @var string */
	private $cacheName;

	public function __construct(KRB5CCache $krb5, string $cacheName) {
		$this->krb5 = $krb5;
		$this->cacheName = $cacheName;
	}

	public function getCacheName(): string {
		return $this->cacheName;
	}

	public function getName(): string {
		return $this->krb5->getName();
	}

	public function isValid(): bool {
		return count($this->krb5->getEntries()) > 0;
	}

	public function validate(): void {
		if (!$this->isValid()) {
			throw new InvalidTicket("No kerberos ticket found.");
		}
	}

	/**
	 * Load the ticket from the cache specified by the KRB5CCNAME variable.
	 *
	 * @return KerberosTicket|null
	 */
	public static function fromEnv(): ?KerberosTicket {
		$ticketName = getenv("KRB5CCNAME");
		if ($ticketName === false) {
			return null;
		}
		$krb5 = new KRB5CCache();
		$krb5->open($ticketName);
		return new KerberosTicket($krb5, $ticketName);
	}

	private static function tmpNam(): string {
		$tmpFilename = tempnam(sys_get_temp_dir(), "krb5cc_php_");
		if ($tmpFilename === false) {
			throw new \Exception("Failed to create temporary file for ticket");
		}
		return $tmpFilename;
	}

	public static function load(string $ticket): KerberosTicket {
		$tmpFilename = self::tmpNam();
		file_put_contents($tmpFilename, $ticket);
		register_shutdown_function(function () use ($tmpFilename) {
			if (file_exists($tmpFilename)) {
				unlink($tmpFilename);
			}
		});

		$ticketName = "FILE:" . $tmpFilename;
		$krb5 = new KRB5CCache();
		$krb5->open($ticketName);
		return new KerberosTicket($krb5, $ticketName);
	}

	public function save(): string {
		if (substr($this->cacheName, 0, 5) === 'FILE:') {
			$ticket = file_get_contents(substr($this->cacheName, 5));
		} else {
			$tmpFilename = self::tmpNam();
			$tmpCacheFile = "FILE:" . $tmpFilename;
			$this->krb5->save($tmpCacheFile);
			$ticket = file_get_contents($tmpFilename);
			unlink($tmpFilename);
		}
		if ($ticket === false) {
			throw new \Exception("Failed to read saved ticket");
		}
		return $ticket;
	}
}
