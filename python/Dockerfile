FROM hypriot/rpi-python
MAINTAINER john_clayton@me.com

RUN pip install pyusb

COPY requirements.txt /
RUN pip install -r /requirements.txt

COPY docker-entrypoint.sh / 
RUN chmod +x /docker-entrypoint.sh 

EXPOSE 5000

CMD [ "/docker-entrypoint.sh" ]


