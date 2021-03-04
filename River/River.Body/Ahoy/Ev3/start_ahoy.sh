#!/bin/bash
echo "clearing port 5000"
fuser -k 5000/tcp
echo "starting server, please allow up to 30 seconds"
cd Ahoy
python3 -m Ev3.main
cd ..
echo "program terminated.."

