#!/bin/bash
# closing sockets properly in deconstructor, should no longer be an issue
# echo "clearing port 5000"
# fuser -k 5000/tcp

echo "starting server, please allow up to 30 seconds"

python3 -m Ev3.main

echo "program terminated.."

