FROM hypriot/rpi-alpine-scratch
MAINTAINER john_clayton@me.com

RUN apk update && apk upgrade && apk add bash && apk add syncthing && rm -rf /var/cache/apk/*

# add the configuration directory
RUN mkdir -p /syncthing/config

# pop. the config directory
COPY config.xml /syncthing/config/

# copy the right keys into place
COPY *.pem /syncthing/config/

EXPOSE 8384 22000 21027/udp

CMD [ "/usr/bin/syncthing", "-home=/syncthing/config" ]
