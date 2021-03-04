



const a = 5;
const b = -16;
const max = 15;


console.log(wrap(b, max));

function wrap(i, i_max) {
    return ((i % i_max) + i_max) % i_max;
}