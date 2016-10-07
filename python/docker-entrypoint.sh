#!/bin/bash
echo "Running charger service..."

if [ -d "/data/charger" ]; then
	cd /data/charger 
        export FLASK_DEBUG=1
	python -u main.py
fi
