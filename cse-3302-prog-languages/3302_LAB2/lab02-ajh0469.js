// Aman Hogan-Bailey
// 1001830469
// 03/09/2022

// Initializing an array with numbers from 1 to 10
var inputtable = [1, 2, 3, 4, 5, 6, 7, 8, 9, 10];

// Initializing new array with the 
// product of each element and '5'
var fiveTable = inputtable.map(v => v * 5, 1);

// Initializing new array with the 
// product of each element and '13'
var thirteenTable = inputtable.map(v => v * 13, 1);

// Initializing new array with the 
// product of each element and itself
var squaresTable = inputtable.map(v => v * v, 1);


// Initializing a new array with numbers from 1 to 100
var oneToHundred = 
[
    1,  2,  3,  4,  5,  6,  7,  8,  9,  10,
    11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 
    21, 22, 23, 24, 25, 26, 27, 28, 29, 30,
    31, 32, 33, 34, 35, 36, 37, 38, 39, 40, 
    41, 42, 43, 44, 45, 46, 47, 48, 49, 50,
    51, 52, 53, 54, 55, 56, 57, 58, 59, 60,
    61, 62, 63, 64, 65, 66, 67, 68, 69, 70,
    71, 72, 73, 74, 75, 76, 77, 78, 79, 80,
    81, 82, 83, 84, 85, 86, 87, 88, 89, 90,
    91, 92, 93, 94, 95, 96, 97, 98, 99, 100
]

// Creating a 'condition' in which a number is a multiple of five  
// and is an odd number
var isOddFiveMult = x => x % 5 == 0  && x % 2 != 0;

// Initializing new array by using 'condition' to 
// filter the "oneToHundred" array
var oddFiveMult = oneToHundred.filter(isOddFiveMult, oneToHundred)

// Creating a 'condition' in which a number is a multiple of seven  
// and is an even number
var isEvenSevenMult = x => x % 7 == 0 && x % 2 == 0;

// Initializing new array by using 'condition' to 
// filter the "oneToHundred" array
var evenSevenMult = oneToHundred.filter(isEvenSevenMult, oneToHundred);

// Defining the additon operation to be used in function composition
var sumOperation = (x, y) => x+y;

// Calling function that returns the sum of all elements
// Storing the sum in "evenSevenMultSum"
var evenSevenMultSum = evenSevenMult.reduce(sumOperation, 0, isEvenSevenMult);

// Block of Code prints all output for questions 1 through 4
console.log("1) inputtable: " + inputtable + "\n");
console.log("2 a) fiveTable: " + fiveTable);
console.log("2 b) thirtenTable: " + thirteenTable);
console.log("2 c) squaresTable: " + squaresTable + "\n");
console.log("3) Odd multiples of 5 between 1 and 100: " + oddFiveMult + "\n");
console.log("4) Sum of even multiples of 7 between 1 and 100 : " + evenSevenMultSum + "\n");

// Currying Function//
// The variable "volume" will store the result of composite funciton r( h (r, h) ) 
// Achived through currying in which the functions take only one parameter
// The composite curried function calculates the volume of a cylinder
let volume = r => h => r * r * Math.PI * h

// Calculating and printing using r = 5, h = 10
console.log("5 a) r =5, h = 10, V = " + volume(5)(10));

// Calculating and printing using r = 5, h = 17
console.log("5 b) r =5, h = 17, V = " + volume(5)(17));

// Calculating and printing using r = 5, h = 11
console.log("5 c) r =5, h = 11, V = " + volume(5)(11) + "\n");

console.log("6)");

// Funciton utilizes closures to print tags in HTML
// Function returns enclosed tags
makeTag = function(beginTag, endTag)
{ 
    return function(textcontent)
    { 
        return beginTag +textcontent +endTag;
    } 
}

// Creating tags that will store the content of the Header
var H1 = makeTag("\n  <th>", "</th>")("Pokemon") + makeTag("\n  <th>", "</th>")("Type");

// Creating tags that will store the content of the innermost rows in HTML table format
var E1 =makeTag("\n  <td>", "</td>")("Pikachu") + makeTag("\n  <td>", "</td>")("Lightning");
var E2 =makeTag("\n  <td>", "</td>")("Charizard") + makeTag("\n  <td>", "</td>")("Fire");
var E3 =makeTag("\n  <td>", "</td>")("Jigglypuff") + makeTag("\n  <td>", "</td>")("Psychic");

// Enclosing header in begin tags and end tags
var Head = makeTag("\n <tr>", "\n </tr>")(H1);

// Enclosing each row in begin tags and end tags
var R1 = makeTag("\n <tr>", "\n </tr>")(E1);
var R2 = makeTag("\n <tr>", "\n </tr>")(E2);
var R3 = makeTag("\n <tr>", "\n </tr>")(E3);

//Enclosing enitre table in begin tags and end tags
console.log(makeTag("<table>", "\n</table>")(Head + R1 + R2 + R3));