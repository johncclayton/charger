#!/bin/bash
echo "Running charger service..."

if [ -d "/data/charger" ]; then
	cd /data/charger 
	export FLASK_APP=main.py
        export FLASK_DEBUG=1
        flask run --host=0.0.0.0
fi
