const char SUB_page[] PROGMEM = R"=====(
<!DOCTYPE html>
<html>
<style>
body{
    background-color: rgb(0,0,0);
    font-family: "Lucida Console", Monaco, monospace;
}    

p.header1{
    font-size: 6vh;
    text-align: center;
    text-transform: uppercase;
    margin-top: 0.1vh;
    margin-bottom: 0.1vh;
    color: #fff;
}

p.header2{
    font-size: 10vh;
    text-align: center;
    text-transform: uppercase;
    margin-top: 0.1vh;
    margin-bottom: 0.1vh;
    border: black;
    left: 50%;
    background-color: rgba(0, 0, 0, 0.85);
    color: #fff;
    padding: 5vw;
    border: none;
    text-align: center;
    box-shadow: 3vw 2vw 1vw -4vw rgba(0, 0, 0, 0.85);
    text-transform: uppercase;
    border-radius: 5vh;
}

.card{
     max-width: 800px;
     min-height: 98%;
     background: #6602b8cc;
     padding: 2vh;
     box-sizing: border-box;
     color: rgb(0, 0, 0);
     margin:auto;
     box-shadow: 0px 2px 18px -4px rgba(0, 0, 0, 0.95);
     margin-top: 10px;
     border-radius: 3vh;
}

.container {
     padding: 3vh;
     color: rgb(0, 0, 0);
     margin:auto;
     text-align: center;
}

.container .btn {
  font-size: 3vh;
  transform: translate(-50%, -50%);
  -ms-transform: translate(-50%, -50%);
  background-color: rgb(0, 0, 0);
  color: #fff;
  padding: 2vh;
  border: none;
  cursor: pointer;
  border-radius: 5px;
  text-align: center;
  text-transform: uppercase;
  box-shadow: 0px 2px 18px -4px rgba(0, 0, 0, 0.85);
  border-radius: 3vh;
}

.container .btn:hover {
  background-color: #fff;
  color: #000;
  box-shadow: 0px 2px 18px -4px rgba(0, 0, 0, 0.85);
  border-radius: 3vh;
}


</style>
<head>
  <meta name="viewport" content="width=device-width, initial-scale=0.6, maximum-scale=0.6, user-scalable=no, shrink-to-fit=no">
</head>
<body>

<div class="card">
  <div class="container">
    <a class="btn"  onclick="window.location.href = '/';">Home</a>
  </div>
  <div class="container">
    <a class="btn"  onclick="btn1()">+ 10 Minutes</a>
 </div>
 <div class="container">   
    <a class="btn"  onclick="btn2()">+ 5 Minutes</a>
 </div>
 <div class="container">
    <a class="btn"  onclick="btn3()">Start Lock</a>
 </div>
 <div class="container">
  <a class="btn"  onclick="btn4()">Stop Lock</a>
</div>
<div class="container">
  <a class="btn"  onclick="btn5()">Scare Mode <span id="subby">OFF</span></a>
</div>
<div class="container">
  <a class="btn"  onclick="btn6()">Disable Safety</a>
</div>
<div class="container">
  <a class="btn"  onclick="btn7()">Reset</a>
</div>
</div>
<script>

function btn1() {
  var xhttp = new XMLHttpRequest();
  xhttp.onreadystatechange = function() {
    if (this.readyState == 4 && this.status == 200) {
      document.getElementById("demo").innerHTML = this.responseText;
    }
  };
  xhttp.open("GET", "time1", true);
  xhttp.send();
}

function btn2() {
  var xhttp = new XMLHttpRequest();
  xhttp.onreadystatechange = function() {
    if (this.readyState == 4 && this.status == 200) {
      document.getElementById("demo").innerHTML = this.responseText;
    }
  };
  xhttp.open("GET", "time2", true);
  xhttp.send();
}

function btn3() {
  var xhttp = new XMLHttpRequest();
  xhttp.onreadystatechange = function() {
    if (this.readyState == 4 && this.status == 200) {
      document.getElementById("demo").innerHTML = this.responseText;
    }
  };
  xhttp.open("GET", "time3", true);
  xhttp.send();
}

function btn4() {
  var xhttp = new XMLHttpRequest();
  xhttp.onreadystatechange = function() {
    if (this.readyState == 4 && this.status == 200) {
      document.getElementById("demo").innerHTML = this.responseText;
    }
  };
  xhttp.open("GET", "time4", true);
  xhttp.send();
}
function btn5() {
  var xhttp = new XMLHttpRequest();
  xhttp.onreadystatechange = function() {
    if (this.readyState == 4 && this.status == 200) {
      document.getElementById("subby").innerHTML = this.responseText;
    }
  };
  xhttp.open("GET", "btn5", true);
  xhttp.send();
}
function btn6() {
  var xhttp = new XMLHttpRequest();
  xhttp.onreadystatechange = function() {
    if (this.readyState == 4 && this.status == 200) {
      document.getElementById("demo").innerHTML = this.responseText;
    }
  };
  xhttp.open("GET", "btn6", true);
  xhttp.send();
}
function btn7() {
  var xhttp = new XMLHttpRequest();
  xhttp.onreadystatechange = function() {
    if (this.readyState == 4 && this.status == 200) {
      document.getElementById("demo").innerHTML = this.responseText;
    }
  };
  xhttp.open("GET", "btn7", true);
  xhttp.send();
}
</script>
</body>
</html>
)=====";