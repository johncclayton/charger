#!/bin/bash

if [ -d "/data/charger" ]; then
	cd /data/charger
	python -u main.py
fi
