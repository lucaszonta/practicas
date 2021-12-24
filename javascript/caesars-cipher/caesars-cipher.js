function rot13(str) {
  const alph1 = "ABCDEFGHIJKLM", alph2 ="NOPQRSTUVWXYZ";
  let decoded = str.split("");
  decoded = decoded
  .map(word => {
    if (alph1.indexOf(word) != -1){
      return word = alph2[alph1.indexOf(word)];
    } else if (alph2.indexOf(word) != -1){
      return word = alph1[alph2.indexOf(word)];
    } else {
      return word;
    }
  })
  .join("");
  console.log(decoded)
  
  return decoded;
}

rot13("SERR PBQR PNZC");