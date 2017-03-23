<?php
/**
 * @copyright Copyright (c) 2017 Robin Appelman <robin@icewind.nl>
 *
 * @license GNU AGPL version 3 or any later version
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Affero General Public License as
 * published by the Free Software Foundation, either version 3 of the
 * License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Affero General Public License for more details.
 *
 * You should have received a copy of the GNU Affero General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
 */

namespace SearchDAV\DAV;

use Sabre\DAV\PropFind;
use Sabre\DAV\Server;
use Sabre\HTTP\ResponseInterface;
use SearchDAV\Backend\ISearchBackend;
use SearchDAV\Backend\SearchResult;
use SearchDAV\XML\BasicSearch;

class SearchHandler {
	/** @var ISearchBackend */
	private $searchBackend;

	/** @var PathHelper */
	private $pathHelper;

	/** @var Server */
	private $server;

	/**
	 * @param ISearchBackend $searchBackend
	 * @param PathHelper $pathHelper
	 * @param Server $server
	 */
	public function __construct(ISearchBackend $searchBackend, PathHelper $pathHelper, Server $server) {
		$this->searchBackend = $searchBackend;
		$this->pathHelper = $pathHelper;
		$this->server = $server;
	}

	public function handleSearchRequest($xml, ResponseInterface $response) {
		if (!isset($xml['{DAV:}basicsearch'])) {
			$response->setStatus(400);
			$response->setBody('Unexpected xml content for searchrequest, expected basicsearch');
			return false;
		}
		/** @var BasicSearch $query */
		$query = $xml['{DAV:}basicsearch'];
		if (!$query->where) {
			$response->setStatus(400);
			$response->setBody('Parse error: Missing {DAV:}where from {DAV:}basicsearch');
			return false;
		}
		if (!$query->select) {
			$response->setStatus(400);
			$response->setBody('Parse error: Missing {DAV:}select from {DAV:}basicsearch');
			return false;
		}
		$response->setStatus(207);
		$response->setHeader('Content-Type', 'application/xml; charset="utf-8"');
		foreach ($query->from as $scope) {
			$scope->path = $this->pathHelper->getPathFromUri($scope->href);
		}
		$results = $this->searchBackend->search($query);
		$data = $this->server->generateMultiStatus(iterator_to_array($this->getPropertiesIteratorResults($results, $query->select)), false);
		$response->setBody($data);
		return false;
	}

	/**
	 * Returns a list of properties for a given path
	 *
	 * The path that should be supplied should have the baseUrl stripped out
	 * The list of properties should be supplied in Clark notation. If the list is empty
	 * 'allprops' is assumed.
	 *
	 * If a depth of 1 is requested child elements will also be returned.
	 *
	 * @param SearchResult[] $results
	 * @param array $propertyNames
	 * @param int $depth
	 * @return \Iterator
	 */
	private function getPropertiesIteratorResults($results, $propertyNames = [], $depth = 0) {
		$propFindType = $propertyNames ? PropFind::NORMAL : PropFind::ALLPROPS;

		foreach ($results as $result) {
			$node = $result->node;
			$propFind = new PropFind($result->href, (array)$propertyNames, $depth, $propFindType);
			$r = $this->server->getPropertiesByNode($propFind, $node);
			if ($r) {
				$result = $propFind->getResultForMultiStatus();
				$result['href'] = $propFind->getPath();

				// WebDAV recommends adding a slash to the path, if the path is
				// a collection.
				// Furthermore, iCal also demands this to be the case for
				// principals. This is non-standard, but we support it.
				$resourceType = $this->server->getResourceTypeForNode($node);
				if (in_array('{DAV:}collection', $resourceType) || in_array('{DAV:}principal', $resourceType)) {
					$result['href'] .= '/';
				}
				yield $result;
			}
		}
	}
}
