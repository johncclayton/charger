#!/usr/bin/env bash
docker run -d --name syncthing-dev -v $PWD:/data/charger johncclayton/syncthing-dev
