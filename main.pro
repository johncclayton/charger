TEMPLATE = subdirs
CONFIG += ordered

SUBDIRS = service \  
    tester

tests.depends = service
