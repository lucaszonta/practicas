function checkCashRegister(price, cash, cid) {
  var i, change, myDrawer, qtyPerUnit, output = {status: "" , change: []};

  change = cash - price; // change due
            // console.log("tengo que dar:",change);
  myDrawer = cid.map(item => {return [...item];});
  myDrawer.reverse(); // [valorBillete, cantidad, cantBilletes]


  const currencies = {
    "PENNY": 0.01,
    "NICKEL": 0.05,
    "DIME": 0.1,
    "QUARTER": 0.25,
    "ONE": 1,
    "FIVE": 5,
    "TEN": 10,
    "TWENTY": 20,
    "ONE HUNDRED": 100
  };
  let howManyOfEach = (actualDrawer)=>{ //qty of each unit in cid
    for (i=0; i<actualDrawer.length; i++){
      actualDrawer[i].push(currencies[actualDrawer[i][0]]);
    }
    actualDrawer.map(curr =>{
        curr.push(Math.round(curr[1]/curr[2]));
    });
  };
  let separateChange = (curr)=>{ // change array to output
      if (change >= curr[2]) {
        qtyPerUnit = 0;
        while ((qtyPerUnit < Math.trunc(change/curr[2])) && curr[3] > 0){
          qtyPerUnit++;
          curr[3]--;
        }
        output.change.push([curr[0], qtyPerUnit * curr[2]]);
                // console.log("cantidad por billete:", qtyPerUnit, "de", curr[2]);
        change -= (qtyPerUnit * curr[2]);
        change = Math.round(change * 100) / 100;
                // console.log("Cambio que todavia debo:", change);
      }
  };
  
  howManyOfEach(myDrawer); 
  // myDrawer[i] = [nombre, cant, valorBillete, cantBilletes]
            // console.log(myDrawer);
  console.log(cid);

  myDrawer.map(separateChange); // returns "output.change"
            // console.log(output.change);
            // console.log(myDrawer);


  let drawerTotal = myDrawer.reduce((sum, unit) =>{
    return sum + unit[1];
  }, 0);

  if (change != 0){
    output.change = [];
    output.status = "INSUFFICIENT_FUNDS";
  } else if ( change == 0 && drawerTotal == (cash - price) ){
    output.change = [...cid];
    output.status = "CLOSED";
  } else {
    output.status = "OPEN";
  }
              // console.log(output);
              console.log(cid);

  return output;
}

checkCashRegister(19.5, 20, [["PENNY", 0.5], ["NICKEL", 0], ["DIME", 0], ["QUARTER", 0], ["ONE", 0], ["FIVE", 0], ["TEN", 0], ["TWENTY", 0], ["ONE HUNDRED", 0]]);