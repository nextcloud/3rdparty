#!/bin/bash
MODULE_CACHE_DIR=${TRAVIS_BUILD_DIR}/travis/module-cache/`php-config --vernum`
PHP_CONFIG=${TRAVIS_BUILD_DIR}/travis/phpconfig.ini
PHP_TARGET_DIR=`php-config --extension-dir`

if [ -d ${MODULE_CACHE_DIR} ]; then
  cp ${MODULE_CACHE_DIR}/* ${PHP_TARGET_DIR}
fi

touch ${PHP_CONFIG}
mkdir -p ${MODULE_CACHE_DIR}

pecl_module_install() {
  if [[ "-f" = $1 ]]; then
    force="-f"
    shift
  else
    force=""
  fi
  package=$1
  filename=$2

  if [ ! -f ${PHP_TARGET_DIR}/${filename} ]
  then
    echo "$filename not found in extension dir, compiling"
    pecl install $force ${package}
  else
    echo "Adding $filename to php config"
    echo "extension = $filename" >> ${PHP_CONFIG}
  fi
  cp ${PHP_TARGET_DIR}/${filename} ${MODULE_CACHE_DIR}
}

if [[ 1 < $(echo ${PECL_HTTP_VERSION} | cut -d. -f 1) ]]; then
  yes | pecl_module_install raphf raphf.so
  yes | pecl_module_install propro propro.so
fi
printf "\n\n\n" | pecl_module_install -f pecl_http-$PECL_HTTP_VERSION http.so

phpenv config-add ${PHP_CONFIG}
