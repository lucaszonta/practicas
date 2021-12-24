function palindrome(str) {
  let newStr = str.match(/[a-z0-9]+/ig);
  newStr = newStr
  .join("")
  .toLowerCase();

  let isPalindrome = (first, second) =>{
   return (first == second) ? true : false;
  }
  let mirrorStr = (string) =>{
     string = string
          .split("")
          .sort(()=>{return -1;})
          .join("");
    return string;
  }

  let firstHalf, secondHalf;
  
  if(newStr.length % 2 == 0){ //cantidad par
    firstHalf = newStr.slice(0, (newStr.length/2));
    secondHalf = newStr.slice(newStr.length/2);
  } else { //cantidad impar 
    firstHalf = newStr.slice(0, ((newStr.length-1)/2));
    secondHalf = newStr.slice((newStr.length-1)/2 +1);
  }

  return isPalindrome(firstHalf, mirrorStr(secondHalf));
}



palindrome("CUATROS");