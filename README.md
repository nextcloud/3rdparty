# 3rdparty

Some 3rd party libraries that are necessary to run Nextcloud.

[![Dependency Status](https://www.versioneye.com/user/projects/576c043fcd6d510048bab256/badge.svg?style=flat-square)](https://www.versioneye.com/user/projects/576c043fcd6d510048bab256)

## Updating libraries manually

1. Make sure to use the latest version of composer: `composer self-update`
2. Edit composer.json and adjust the version of the library to the one to update to
3. Run `composer update thevendor/thelib` (replace accordingly)
4. Delete all installed dependencies with `rm -rf ./*/`
5. Run `composer install --no-dev`
6. Run `git clean -X -d -f`
7. Run `composer dump-autoload`
8. Commit all changes onto a new branch
9. You might need the following command for pushing if used as submodule: `git push git@github.com:nextcloud/3rdparty.git branchname`

## Testing your PR with server

1. On https://github.com/nextcloud/server make a new branch `3rdparty/my-dependency`
2. Navigate into the 3rdparty directory
3. Checkout the commit sha of the **last commit** of your PR in the 3rdparty repository
4. Leave the directory
5. Add the change to the stash
6. Commit (with sign-off and message)
7. Push the branch and send a PR
8. ⏳ Wait for CI and reviews
9. Navigate into the 3rdparty directory
10. Checkout the commit sha of the **merge commit** of your PR in the 3rdparty repository
11. Leave the directory
12. Add the change to the stash
13. Amend to the previous dependency bump
14. Push with lease force
15. ⏳ Wait for CI
16. Merge 🎉

```sh
cd 3rdparty
git checkout 16cd747ebb8ab4d746193416aa2448c8114d5084
cd ..
git add 3rdparty
git commit
git push origin 3rdparty/my-dependency

# Wait for CI and reviews

cd 3rdparty
git checkout 54b63cc87af3ddb0ddfa331f20ecba5fcc01d495
cd ..
git add 3rdparty
git commit --amend
git push --force-with-lease origin 3rdparty/my-dependency
```
