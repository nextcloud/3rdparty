NextCloud 3rdparty Dependency Info
==================================

External PHP libs required by core.
See the `composer.json` file in this directory.

| Library | Version | License           | Comment/Patch Info (if applicable)  |
| ---     | ---     | ---               | ---                                 |
| aws/aws-sdk-php | ^3.35 | Apache-2.0  |                                     |
| bantu/ini-get-wrapper | v1.0.1 | MIT  |                                     |
| deepdiver1975/TarStreamer | v0.1.0 | MIT | NOTE: Despite the different namespace this lives in the name is correct |
| doctrine/dbal | dev-2.5.-pg10 | MIT   | PATCH: fix error handling for not null columns on some mysql servers https://github.com/doctrine/dbal/pull/2422 |
| doctrine/annotations | 1.2.7 | MIT    | Dependency of doctrine/dbal         |
| doctrine/cache | 1.5.1 | MIT          | Dependency of doctrine/dbal         |
| doctrine/collections | 1.3.0 | MIT    | Dependency of doctrine/dbal         |
| doctrine/common | 2.7 | MIT           | Dependency of doctrine/dbal         |
| doctrine/inflector | 1.1.0 | MIT      | Dependency of doctrine/dbal         |
| doctrine/lexer | 1.0.1 | MIT          | Dependency of doctrine/dbal         |
| guzzlehttp/guzzle | 6.3.0 | MIT       |                                     |
| icewind/searchdav | 1.0.0 | AGPL-3.0  |                                     |
| icewind/streams | 0.5.2 | MIT         |                                     |
| interfasys/lognormalizer | ^v1.0 | AGPL-3.0 |                               |
| jeremeamia/SuperClosure | 2.1.0 | MIT |                                     |
| leafo/scssphp | ^0.7.2 | MIT          |                                     |
| league/flysystem | ^1.0 | MIT         |                                     |
| lukasreschke/id3parser | ^0.0.1 | GPL-3.0 |                                 |
| mcnetic/zipstreamer | ^1.0 | GPL-3.0  | PATCH: Fix zip generation for 7zip https://github.com/McNetic/PHPZipStreamer/pull/39 |
| natxet/CssMin | dev-master | MIT      |                                     |
| nikic/php-parser | 1.4.1 | BSD-3-Clause |                                   |
| patchwork/jsqueeze | ^2.0 | Apache-2.0 v GPL-2.0 |                          |
| patchwork/utf8 | 1.2.6 | Apache-2.0 v GPL-2.0 | PATCH: Remove trigger_error() that spammed the error log |
| pear/archive_tar | 1.4.3  | BSD-3-Clause |                                  |
| pear/pear-core-minimal | v1.10 | BSD-3-Clause |                             |
| php-opencloud/openstack | 3.0.6 | Apache-2.0 |                              |
| phpseclib/phpseclib | 2.0.4 | MIT     |                                     |
| pimple/pimple | 3.2.3 | MIT           |                                     |
| punic/punic | ^1.6 | MIT              |                                     |
| sabre/dav | ^3.2.0 | BSD-3-Clause     | PATCH: Make sure that files that are children of directories, are reported as files https://github.com/fruux/sabre-dav/issues/982 |
| sabre/event | 3.0.0 | BSD-3-Clause    | Dependency of sabre/dav             |
| sabre/http | 4.3.2 | BSD-3-Clause     | Dependency of sabre/dav             |
| sabre/uri | 1.2.1 | BSD-3-Clause      | Dependency of sabre/dav             |
| sabre/vobject | 4.0 | BSD-3-Clause    | Dependency of sabre/dav             |
| sabre/xml | 1.5.0 | BSD-3-Clause      | Dependency of sabre/dav<br>PATCH: Fix invalid PHP docs https://github.com/fruux/sabre-xml/pull/128<br>PATCH: Prevent infinite loops for empty props element https://github.com/fruux/sabre-xml/pull/132 |
| stecman/symfony-console-completion | ^0.7.0 | MIT |                         |
| swiftmailer/swiftmailer | ^5.4 | MIT  |                                     |
| symfony/console | ^3.3.0 | MIT        |                                     |
| symfony/event-dispatcher | ^3.3.0 | MIT |                                   |
| symfony/process | ^3.3.0 | MIT        |                                     |
| symfony/routing | ^3.3.0 | MIT        |                                     |
| symfony/translation | ^3.3.0 | MIT    |                                     |
