#change keyboard layout
1. sudo nano /etc/default/keyboard
	a. set XKBLAYOUT="us"

1. sudo raspi-config
	a. set up network
	b. enable ssh
2. sudo apt-get update
3. sudo apt-get dist-upgrade



#install node
curl -sL https://deb.nodesource.com/setup_8.x | sudo -E bash -
sudo apt-get install -y nodejs
node -v


#enable remote editing
1. install rmate
sudo wget -O /usr/local/bin/rmate https://raw.githubusercontent.com/aurora/rmate/master/rmate
sudo chmod a+x /usr/local/bin/rmate

in vscode integrated terminal

ctrl+shift+p Remote-Start Server
ssh -R 52698:127.0.0.1:52698 pi@192.168.0.130

sudo rmate test.txt