const char MAIN_page[] PROGMEM = R"=====(
<!DOCTYPE html>
<html>
<style>
body{
    background-color: rgb(121, 121, 121);
    font-family: "Lucida Console", Monaco, monospace;
}    

p.header1{
    font-size: 45px;
    text-align: center;
    text-transform: uppercase;
    margin-top: 30px;
    margin-bottom: 30px;
    color: #000;
}

p.header2{
    font-size: 100px;
    text-align: center;
    text-transform: uppercase;
    margin-top: 20px;
    margin-bottom: 20px;
    border: black;
    left: 50%;
    background-color: rgba(0, 0, 0, 0.85);
    color: #7403d0;
    padding: 16px 30px;
    border: none;
    border-radius: 5px;
    text-align: center;
    box-shadow: 0px 2px 18px -4px rgba(0, 0, 0, 0.85);
    text-transform: uppercase;
    border-radius: 25px;
}

.card{
    max-width: 600px;
     min-height: 600px;
     background: #6602b8cc;
     padding: 30px;
     box-sizing: border-box;
     color: rgb(0, 0, 0);
     margin:auto;
     box-shadow: 0px 2px 18px -4px rgba(0, 0, 0, 0.95);
     margin-top: 10px;
     border-radius: 25px;
}

.container {
     max-width: max-content;
     min-height: auto;
     padding: 30px;
     color: rgb(0, 0, 0);
     margin:auto;
}

.container .btn {
  left: 50%;
  transform: translate(-50%, -50%);
  -ms-transform: translate(-50%, -50%);
  background-color: rgb(0, 0, 0);
  color: #8c00ff;
  font-size: 25px;
  padding: 16px 30px;
  border: none;
  cursor: pointer;
  border-radius: 5px;
  text-align: center;
  box-shadow: 0px 2px 18px -4px rgba(0, 0, 0, 0.85);
  text-transform: uppercase;
  border-radius: 25px;
}

.container .btn:hover {
  background-color: #8c00ff;
  color: white;
  box-shadow: 0px 2px 18px -4px rgba(0, 0, 0, 0.85);
  border-radius: 25px;
}
.container .btn2 {
  left: 50%;
  transform: translate(-50%, -50%);
  -ms-transform: translate(-50%, -50%);
  background-color: rgb(0, 0, 0);
  color: #8c00ff;
  font-size: 25px;
  padding: 16px 30px;
  border: none;
  cursor: pointer;
  border-radius: 5px;
  text-align: center;
  box-shadow: 0px 2px 18px -4px rgba(0, 0, 0, 0.85);
  text-transform: uppercase;
  border-radius: 25px;
}

.container .btn2:hover {
  background-color: #8c00ff;
  color: white;
  box-shadow: 0px 2px 18px -4px rgba(0, 0, 0, 0.85);
  border-radius: 25px;
}

.container .btn3 {
  left: 50%;
  transform: translate(-50%, -50%);
  -ms-transform: translate(-50%, -50%);
  background-color: rgb(0, 0, 0);
  color: #8c00ff;
  font-size: 25px;
  padding: 16px 30px;
  border: none;
  cursor: pointer;
  border-radius: 5px;
  text-align: center;
  box-shadow: 0px 2px 18px -4px rgba(0, 0, 0, 0.85);
  text-transform: uppercase;
  border-radius: 25px;
}

.container .btn3:hover {
  background-color: #8c00ff;
  color: white;
  box-shadow: 0px 2px 18px -4px rgba(0, 0, 0, 0.85);
  border-radius: 25px;
}

.container .btn4 {
  left: 50%;
  transform: translate(-50%, -50%);
  -ms-transform: translate(-50%, -50%);
  background-color: rgb(0, 0, 0);
  color: #8c00ff;
  font-size: 25px;
  padding: 16px 30px;
  border: none;
  cursor: pointer;
  border-radius: 5px;
  text-align: center;
  box-shadow: 0px 2px 18px -4px rgba(0, 0, 0, 0.85);
  text-transform: uppercase;
  border-radius: 25px;
}

.container .btn4:hover {
  background-color: #8c00ff;
  color: white;
  box-shadow: 0px 2px 18px -4px rgba(0, 0, 0, 0.85);
  border-radius: 25px;
}

.container .btn5 {
  left: 50%;
  transform: translate(-50%, -50%);
  -ms-transform: translate(-50%, -50%);
  background-color: rgb(0, 0, 0);
  color: #8c00ff;
  font-size: 25px;
  padding: 16px 30px;
  border: none;
  cursor: pointer;
  border-radius: 5px;
  text-align: center;
  box-shadow: 0px 2px 18px -4px rgba(0, 0, 0, 0.85);
  text-transform: uppercase;
  border-radius: 25px;
}

.container .btn5:hover {
  background-color: #8c00ff;
  color: white;
  box-shadow: 0px 2px 18px -4px rgba(0, 0, 0, 0.85);
  border-radius: 25px;
}

</style>
<head>
  <meta name="viewport" content="width=device-width, initial-scale=0.6, maximum-scale=0.6, user-scalable=no, shrink-to-fit=no">
</head>
<body>

<div class="card">
  <p class="header1">LockMeUP</p>
  <p class="header1">Your Bondage Lock</p>
  <div class="container">
  <p class="header2"><span id="timevalue">00:00</span></p>
  </div>
 <div class="container">
    <a class="btn"  onclick="btn1()">+ 10 Minutes</a>
 </div>
 <div class="container">   
    <a class="btn2"  onclick="btn2()">+ 5 Minutes</a>
 </div>
 <div class="container">
    <a class="btn3"  onclick="btn3()">Start Lock</a>
 </div>
 <div class="container">
  <a class="btn4"  onclick="btn4()">Stop Lock</a>
</div>
<div class="container">
  <a class="btn5"  onclick="btn5()">Scare It</a>
</div>
</div>
<script>

setInterval(function() {
  getData();// Call a function repetatively with 2 Second interval
}, 800); //2000mSeconds update rate

function getData() {
  var xhttp = new XMLHttpRequest();
  xhttp.onreadystatechange = function() {
    if (this.readyState == 4 && this.status == 200) {
      document.getElementById("timevalue").innerHTML =
      this.responseText;
    }
  };
  xhttp.open("GET", "readADC", true);
  xhttp.send();
}

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
      document.getElementById("demo").innerHTML = this.responseText;
    }
  };
  xhttp.open("GET", "time5", true);
  xhttp.send();
}
</script>
</body>
</html>
)=====";