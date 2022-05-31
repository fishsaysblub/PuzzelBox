#!/bin/bash
# Bombs
python3 /home/jef/git/PuzzelBox/PiHub/socketcom/client/ClientTest.py bomb1 1 &
python3 /home/jef/git/PuzzelBox/PiHub/socketcom/client/ClientTest.py bomb2 1 &
python3 /home/jef/git/PuzzelBox/PiHub/socketcom/client/ClientTest.py bomb3 1 &
python3 /home/jef/git/PuzzelBox/PiHub/socketcom/client/ClientTest.py bomb4 1 &

# Boxes
python3 /home/jef/git/PuzzelBox/PiHub/socketcom/client/ClientTest.py box1 2 &
python3 /home/jef/git/PuzzelBox/PiHub/socketcom/client/ClientTest.py box2 2 &
python3 /home/jef/git/PuzzelBox/PiHub/socketcom/client/ClientTest.py box3 2 &
python3 /home/jef/git/PuzzelBox/PiHub/socketcom/client/ClientTest.py box4 2 &
