TEMPLATE = subdirs
CONFIG += ordered

SUBDIRS = core tests

tests.depends = core
