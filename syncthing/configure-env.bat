docker run --name keys --env=KEY_HOSTS="rpi3 dev host1 host2" johncclayton/syncthing-cli "/generate-identities.sh"
del /q /s keys
docker cp keys:/keys ./
docker rm -f keys
