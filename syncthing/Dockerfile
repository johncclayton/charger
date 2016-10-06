FROM hypriot/rpi-python
MAINTAINER john_clayton@me.com

RUN apt-get update
RUN apt-get -y install wget
RUN wget --no-check-certificate -O - https://syncthing.net/release-key.txt | sudo apt-key add -
RUN echo "deb http://apt.syncthing.net/ syncthing release" | sudo tee -a /etc/apt/sources.list.d/syncthing-release.list
RUN sudo apt-get update

RUN sudo apt-get install syncthing supervisor -y

# setup the supervisord configuration for syncthing
COPY supervisor_config.ini /etc/supervisor/conf.d/syncthing.conf

# add the configuration directory
RUN mkdir -p /syncthing/config

# pop. the config directory
COPY syncthing_config/* /syncthing/config/

EXPOSE 8384 22000 21027

CMD [ "/usr/bin/syncthing", "-home=/syncthing/config" ]
