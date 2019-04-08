echo 'building app..'
npm run build
echo 'fixing html paths'
node fixHtmlPaths.js
echo 'copying files'
rm -r ../robot-io-server/build
cp -r ./build ../robot-io-server