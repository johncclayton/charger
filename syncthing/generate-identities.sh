#!/bin/sh

mkdir -p /keys
for ID in $KEY_HOSTS; do
  cd /keys
  syncthing -generate="$ID"
done