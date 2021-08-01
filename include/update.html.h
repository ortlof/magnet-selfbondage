const char update_page[] PROGMEM = R"=====(
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

.update {
     color: rgb(0, 0, 0);
     margin:auto;
     text-align: center;
}

#file-input,input{
  width:100%;
  height:44px;
  border-radius:4px;
  margin:10px auto;
  font-size:15px
}

input{
background:#f1f1f1;
border:0;
padding:0 15px
}

#file-input{
padding:0;
border:1px solid #ddd;
line-height:44px;
text-align:left;
display:block;
cursor:pointer
}
#bar,#prgbar{
background-color:#f1f1f1;
border-radius:10px
}
#bar{
  background-color:#3498db;width:0%;height:10px
}
form{
background:#fff;
max-width:30vh;
margin:75px auto;
padding:3vh;
border-radius:5px;
text-align:center
}
.btn{
  background:#000;color:#fff;cursor:pointer
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
  <div class="update">
<script src='https://ajax.googleapis.com/ajax/libs/jquery/3.2.1/jquery.min.js'></script>
<form method='POST' action='#' enctype='multipart/form-data' id='upload_form'>
<input type='file' name='update' id='file' onchange='sub(this)' style=display:none>
<label id='file-input' for='file'>   Choose file...</label>
<input type='submit' class=btn value='Update'>
<br><br>
<div id='prg'></div>
<br><div id='prgbar'><div id='bar'></div></div><br></form>
</div>
</div>


<script>
function sub(obj){
var fileName = obj.value.split('\\\\');
document.getElementById('file-input').innerHTML = '   '+ fileName[fileName.length-1];
};
$('form').submit(function(e){
e.preventDefault();
var form = $('#upload_form')[0];
var data = new FormData(form);
$.ajax({
url: '/update',
type: 'POST',
data: data,
contentType: false,
processData:false,
xhr: function() {
var xhr = new window.XMLHttpRequest();
xhr.upload.addEventListener('progress', function(evt) {
if (evt.lengthComputable) {
var per = evt.loaded / evt.total;
$('#prg').html('progress: ' + Math.round(per*100) + '%');
$('#bar').css('width',Math.round(per*100) + '%');
}
}, false);
return xhr;
},
success:function(d, s) {
console.log('success!') 
},
error: function (a, b, c) {
}
});
});
</script>
</body>
</html>
)=====";