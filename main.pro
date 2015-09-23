TEMPLATE = subdirs
CONFIG += ordered

SUBDIRS = service gui 

tests.depends = service
