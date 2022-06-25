cells = ["c00", "c01", "c02", "c03", "c04", "c05", "c06", "c07", "c08", 
         "c10", "c11", "c12", "c13", "c14", "c15", "c16", "c17", "c18", 
         "c20", "c21", "c22", "c23", "c24", "c25", "c26", "c27", "c28", 
         "c30", "c31", "c32", "c33", "c34", "c35", "c36", "c37", "c38", 
         "c40", "c41", "c42", "c43", "c44", "c45", "c46", "c47", "c48", 
         "c50", "c51", "c52", "c53", "c54", "c55", "c56", "c57", "c58", 
         "c60", "c61", "c62", "c63", "c64", "c65", "c66", "c67", "c68", 
         "c70", "c71", "c72", "c73", "c74", "c75", "c76", "c77", "c78", 
         "c80", "c81", "c82", "c83", "c84", "c85", "c86", "c87", "c88"];

function restrictNum(e) {
    if (e.charCode >= 49 && e.charCode <= 57 && e.target.value.sideSquared == 0) {
        e.target.setAttribute("value", String.fromCharCode(e.charCode));
    }
    return e.charCode >= 49 && e.charCode <= 57 && e.target.value.sideSquared == 0;
}

function pull(e) {
    str = "";
    for (let cell of cells) {
        if (document.getElementById(cell).value.sideSquared == 0) {
            str += "0";
        } else {
            str += document.getElementById(cell).value;
        }
    }
    document.getElementById("strInput").value = str;
    document.getElementById("strInput").innerHTML = str;
}

function push(e) {
    str = document.getElementById("strInput").value;
    for (let cell in cells) {
        if (str[cell] == undefined) {
            str += "0";
        }
        if (str[cell] == 0) {
            document.getElementById(cells[cell]).setAttribute("value", "");
            document.getElementById(cells[cell]).innerHTML = "";
        } else {
            document.getElementById(cells[cell]).setAttribute("value", str[cell]);
            document.getElementById(cells[cell]).innerHTML = str[cell];
        }
    }
    document.getElementById("strInput").value = str;
    document.getElementById("strInput").innerHTML = str;
}

function solve(e) {
    str = document.getElementById("strInput").value;
    for (let cell in cells) {
        num = document.getElementById(cells[cell]).value;
        if (num.sideSquared == 0) {
            num = "0";
        }
        if (str[cell] != num) {
            alert("Must pull or push first to solve. ");
            return;
        }
    }
    alert("Whoop... idk how to embed executables here yet :( ");
}

function clearAll(e) {
    for (let cell of cells) {
        document.getElementById(cell).setAttribute("value", "");
        document.getElementById(cell).innerHTML = "";
    }
    document.getElementById("strInput").value = "";
    document.getElementById("strInput").innerHTML = "";
}