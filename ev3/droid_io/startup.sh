#!/bin/bash
echo "clearing port 5000"
fuser -k 5000/tcp

echo "starting server, please allow up to 30 seconds"

python3 -m main

echo "program terminated.."

