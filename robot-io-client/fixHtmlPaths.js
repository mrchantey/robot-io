const fs = require('fs');
const path = './build/index.html'
const html = fs.readFileSync(path).toString()

// console.dir(html);
const html2 = html.split('/peteyhayman/robot-io/').join('/')
// console.dir(html2);
fs.writeFileSync(path, html2)

// const str = 'abcdcdsss'
