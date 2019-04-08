#do not call this script directly, will be called on npm publish
echo 'building app..'
npm run build
echo 'fixing html paths..'
node fixHtmlPaths.js
npm version patch