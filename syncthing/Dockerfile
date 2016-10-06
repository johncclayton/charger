FROM hypriot/rpi-python
MAINTAINER john_clayton@me.com

RUN apt-get update
RUN apt-get -y install wget
RUN wget --no-check-certificate -O - https://syncthing.net/release-key.txt | sudo apt-key add -
RUN echo "deb http://apt.syncthing.net/ syncthing release" | sudo tee -a /etc/apt/sources.list.d/syncthing-release.list
RUN sudo apt-get update

RUN sudo apt-get install syncthing supervisor -y
COPY supervisor_config.ini /etc/supervisor/conf.d/syncthing.conf

RUN useradd -m syncthing && mkdir -p /home/syncthing/.config/syncthing

COPY syncthing_config/* /home/syncthing/.config/syncthing/
RUN sudo chown -R syncthing:syncthing /home/syncthing/.config/syncthing

EXPOSE 8384 22000 21027

CMD [ "/usr/bin/syncthing" ]
