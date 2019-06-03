#!/bin/bash

# echo "starting in 10 seconds"
echo "clearing port 5000"
fuser -k 5000/tcp

# echo "improvise running in 10 seconds..."

# sleep 10

echo "starting server, please allow up to 30 seconds"

./main.py
# python3 -m main
# python3 main.py

echo "program terminated.."

