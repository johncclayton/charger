FROM alpine:latest
MAINTAINER john_clayton@me.com

RUN apk update && apk add syncthing
ENV KEY_HOSTS="rpi3 dev1 dev2"
COPY generate-identities.sh /
RUN chmod +x /generate-identities.sh

EXPOSE 8384 22000 21027

CMD [ "/bin/sh" ]
