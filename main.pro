TEMPLATE = subdirs
CONFIG += ordered

SUBDIRS = bonjour \
          messaging \
          client \  
          service \ 
          charger_gui 

client.depends = bonjour messaging
service.depends = bonjour messaging
charger_gui.depends = client
