# 3rdparty

Some 3rd party libraries that are necessary to run Nextcloud.

[![Dependency Status](https://www.versioneye.com/user/projects/576c043fcd6d510048bab256/badge.svg?style=flat-square)](https://www.versioneye.com/user/projects/576c043fcd6d510048bab256)

## Updating libraries manually

1. Make sure to use the latest version of composer.phar
2. Edit composer.json and adjust the version of the library to the one to update to
3. Run `composer update thevendor/thelib` (replace accordingly)
4. Delete all installed dependencies with `rm -rf ./*/`
5. Run `composer install --no-dev`
5. Run `git clean -X -d -f`
7. Run `dump-autoload`
8. Commit all changes onto a new branch
9. You might need the following command for pushing if used as submodule: `git push git@github.com:nextcloud/3rdparty.git branchname`
