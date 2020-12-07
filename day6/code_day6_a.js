const fs = require('fs');

// array that is to hold each group's count/number of unique choices
const countArr = [];
// form set that will hold all unique letters (choices) of group
// currently being processed
let groupSet = new Set();
// variable for holding the previously read character
let lastChar = '';

// open stream to read from input file
const inStream = fs.createReadStream(
    __dirname + '/input_day6.txt',
    encoding='utf8'
);

// upon the stream becoming ready to be read from
inStream.on('readable', () => {
    // variable for holding character currently being processed
    let readChar;
    // keep reading in single characters from stream until it's been
    // depleted
    while (null !== (readChar = inStream.read(1))) {
        if (readChar !== '\n') {
            groupSet.add(readChar);
        // if a group has been finished
        } else if (lastChar === '\n') {
            countArr.push(groupSet.size);
            groupSet.clear();
        }
        // store the character for making it possible to check if
        // group has ended
        lastChar = readChar;
    }
})

// when all data from input file have been streamed
inStream.on('end', () => {
    // store final group's count
    countArr.push(groupSet.size);
    inStream.close();
    saveFun();
})

const saveFun = () => {
    // sum up count and save to output file
    const countSum = countArr.reduce( (x, y) => x + y);
    const outStream = fs.createWriteStream('output_day6_a.txt');
    outStream.write(`${countSum}`);
    outStream.close();
}
