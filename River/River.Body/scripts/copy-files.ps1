echo "purging directory.."
plink -ssh -pw maker robot@192.168.1.9 -m scripts/purge-directory.sh
echo "directory purged"


echo "copying files.."
pscp -r -pw maker C:\Users\darkmoon\coding\River\River.Body\Ahoy robot@192.168.1.9:/home/robot
echo "files copied"


echo "enabling startup.."
plink -ssh -pw maker robot@192.168.1.9 -m scripts/enable-startup.sh
echo "startup enabled"