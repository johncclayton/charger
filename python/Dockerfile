FROM hypriot/rpi-python
MAINTAINER john_clayton@me.com

RUN pip install pyusb

COPY requirements.txt /
RUN pip install -r /requirements.txt

WORKDIR /data/charger
CMD [ "python", "-u", "main.py" ]


