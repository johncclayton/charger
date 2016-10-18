FROM alpine:latest
MAINTAINER john_clayton@me.com

RUN apk update && apk add syncthing
ENV KEY_HOSTS="rpi3"
COPY config/generate-identities.sh /
RUN chmod +x /generate-identities.sh

CMD [ "/generate-identities.sh" ]
