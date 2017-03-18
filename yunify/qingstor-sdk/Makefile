SHELL := /bin/bash
version = $(shell grep "$GLOBALS\['version'\]" src/Config.php | grep -oE '[0-9.]+')

help:
	@echo "Please use \`make <target>' where <target> is one of"
	@echo "  all               to update, generate and test this SDK"
	@echo "  test              to run service test"
	@echo "  unit              to run all sort of unit tests except runtime"
	@echo "  build             to build phar"
	@echo "  update            to update git submodules"
	@echo "  generate          to generate service code"

all: update generate unit

test:
	@echo "run service test"
	pushd "scenarios"; \
	composer update; \
	vendor/bin/behat; \
	popd
	@echo "ok"

generate:
	@if [[ ! -f "$$(which snips)" ]]; then \
		echo "ERROR: Command \"snips\" not found."; \
	fi
	snips \
		--service=qingstor --service-api-version=latest \
		--spec="./specs" --template="./template" --output="./src/QingStor"
	rm ./src/QingStor/Object.php
	-php-cs-fixer fix --level=symfony .
	@echo "ok"

update:
	git submodule update --remote
	@echo "ok"

unit:
	@echo "run unit test"
	composer install
	php vendor/phpunit/phpunit/phpunit --no-configuration tests
	@echo "ok"

build:
	@echo "build phar"
	rm -rf composer.lock vendor/
	composer install --no-dev
	phar-composer build . qingstor-sdk-php-$(version).phar
	@echo "ok"
