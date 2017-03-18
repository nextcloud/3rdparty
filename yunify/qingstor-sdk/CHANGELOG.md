# Change Log

All notable changes to this project will be documented in this file.

The format is based on [Keep a Changelog](http://keepachangelog.com/) and this project adheres to [Semantic Versioning](http://semver.org/).

## [2.2.1] - 2017-03-14

### Changed

- Split handler from Request, use stream in req

### Fixed

- Fix query_sign error in Request

## [2.2.0] - 2017-02-27

### Added

- Add list multipart uploads API

## [2.1.2] - 2017-02-20

### Changed

- Use PsrRequest instead of Request in Builder

## [2.1.1] - 2017-02-11

### Changed

- Refactor Signer class to Request, support guzzle 5

## [2.1.0] - 2016-12-28

### Changed

- Fix signer && Builder bug
- Add more parameters to sign

### Added

- Add request parameters for GET Object
- Add IP address conditions for bucket policy

## [2.0.1] - 2016-10-14

### Changed

- Fix katzgrau/klogger require version to 1.2.1
- Update installation docs

## 2.0.0 - 2016-10-14

### Added

- Provide Official Qingstor SDK for PHP

[2.2.1]: https://github.com/yunify/qingstor-sdk-php/compare/2.1.0...2.2.1
[2.2.0]: https://github.com/yunify/qingstor-sdk-php/compare/2.1.2...2.2.0
[2.1.2]: https://github.com/yunify/qingstor-sdk-php/compare/2.1.1...2.1.2
[2.1.1]: https://github.com/yunify/qingstor-sdk-php/compare/2.1.0...2.1.1
[2.1.0]: https://github.com/yunify/qingstor-sdk-php/compare/2.0.1...2.1.0
[2.0.1]: https://github.com/yunify/qingstor-sdk-php/compare/2.0.0...2.0.1
