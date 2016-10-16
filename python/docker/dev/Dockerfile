FROM alpine:latest
MAINTAINER john_clayton@me.com

RUN apk update && apk add syncthing

# add the configuration directory
RUN mkdir -p /syncthing/config

# pop. the config directory
COPY syncthing_config/* /syncthing/config/

EXPOSE 8384 22000 21027

CMD [ "/usr/bin/syncthing", "-home=/syncthing/config" ]
