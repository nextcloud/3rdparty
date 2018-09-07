#!/bin/bash

set -ev

composer install

MODIFIED=$(git ls-files -m)

if [[ $MODIFIED != "" ]]
then
	echo "Changes detected."

	git status
	git config user.email 'drone@nextcloud.com'
	git config user.name 'Nextcloud Drone'
	git add -A
	git commit -m 'Update composer dependency files'
	git status

else
	echo "No changes detected."
fi

