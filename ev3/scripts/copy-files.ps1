echo "purging directory.."

plink -ssh -pw maker robot@169.254.182.36 -m purge-directory.sh

echo "directory purged"
echo "copying files.."

pscp -r -pw maker C:\Users\darkmoon\coding\robot-io\ev3\server robot@169.254.182.36:/home/robot
echo "data copied"


echo "enabling startup"
plink -ssh -pw maker robot@169.254.182.36 -m enable-startup.sh