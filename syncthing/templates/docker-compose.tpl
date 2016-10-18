version: '2'

services:
  {% for device in devices %}

  sync-{{device.docker_name}}:
    image: syncthing-{{device.docker_name}}
    build:
      context: {{device.name}}

    restart: unless-stopped

    ports:
      - "8384:8384"
      - "22000:22000"
      - "21027:21027"

    networks:
      - net

    labels:
      com.syncthing.platform: {{device.docker_type}}

  {% endfor %}

networks:
  net:


