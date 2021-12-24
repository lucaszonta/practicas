function convertToRoman(num) {
    let numArr = num
    .toString()
    .split("")
    .reverse();

    const dict = [
        ["", "I", "V", "X"],
        ["", "X", "L", "C"],
        ["", "C", "D", "M"],
        ["", "M"]
    ];

    for (let i=0; i<numArr.length; i++){
        switch (numArr[i]) {
            case "0": 
                numArr[i] = dict[i][0]; 
                break;
            case "1":
            case "2":
            case "3":
               numArr[i] = dict[i][1].repeat(numArr[i]);
               break;
            case "4":
                numArr[i] = dict[i][1] + dict[i][2];
                break;
            case "5":
            case "6":
            case "7":
            case "8":
                numArr[i] = dict[i][2] + dict[i][1].repeat(numArr[i] - 5);
                break;
            case "9":
                numArr[i] = dict[i][1] + dict[i][3];
        } 
    }

    numArr = numArr
    .reverse()
    .join("");

 return numArr;
}


convertToRoman(36);