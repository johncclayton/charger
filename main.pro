TEMPLATE = subdirs
CONFIG += ordered

SUBDIRS = bonjour \
          messaging \
          client \  
#          service \ 
          charger_gui 

messaging.depends = bonjour
client.depends = messaging
#service.depends = messaging

charger_gui.depends = bonjour, messaging, client
