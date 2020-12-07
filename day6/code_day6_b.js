const fs = require('fs');

// array that is to hold each group's count/number of unique choices
const countArr = [];
// form set that will hold all letters (choices) of member currently being
// processed that previously processed group members also had
let newSet = new Set();
// variable for holding the previously read character
let lastChar = '';
// form set that holds all lowercase English letters
let alphaSet = new Set();
for (let i = 97; i < 123; i++) {
    alphaSet.add(String.fromCharCode(i));
}
// variable for holding set of all letters (choices) of group member that
// came directly before the one currently being processed
let prevSet = alphaSet;

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
        if (prevSet.has(readChar)) {
            newSet.add(readChar);
        // if a member has been finished
        } else if (readChar === '\n') {
            // if a group has been finished
            if (lastChar === '\n') {
                countArr.push(prevSet.size);
                prevSet = alphaSet;
            } else {
                prevSet = new Set(newSet);
            }
            newSet.clear();
        }
        // store the character for making it possible to check if
        // group has ended
        lastChar = readChar;
    }
})

// when all data from input file have been streamed
inStream.on('end', () => {
    // store final group's count
    countArr.push(prevSet.size);
    inStream.close();
    saveFun();
})

const saveFun = () => {
    // sum up count and save to output file
    const countSum = countArr.reduce( (x, y) => x + y);
    const outStream = fs.createWriteStream('output_day6_b.txt');
    outStream.write(`${countSum}`);
    outStream.close();
}
