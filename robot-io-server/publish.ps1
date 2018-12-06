#do not call this script directly, will be called on npm publish

# rm ./package-lock.json
# npm i

npm run build
npm version patch
cd ../
git add .
git commit -m 'patch'
git push origin master
cd ./robot-io-server