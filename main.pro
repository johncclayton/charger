TEMPLATE = subdirs
CONFIG += ordered

SUBDIRS = lib \ 
          service \ 
          charger_gui \
          tester

service.depends = lib
charger_gui.depends = lib
tester.depends = lib

