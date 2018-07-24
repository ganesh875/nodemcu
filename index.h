const char MAIN_page[] PROGMEM = R"=====(
<!DOCTYPE html>
<html>
<head>
<meta charset="utf-8">
<title>POSCO Maharashtra CAL ELectrical Temp Monitor</title>
<script src="https://code.jquery.com/jquery-2.2.3.min.js"></script>
    <script src="https://assets.shiftr.io/js/mqtt-2.9.0.js"></script>
    <script language = "javascript">
  $(function(){
  var client = mqtt.connect('mqtt://try:try@broker.shiftr.io', {
    clientId: 'arduino'
  });

  client.on('connect', function(){
    console.log('client has connected!');
  });

  client.on('message', function(topic, message) {
    //console.log('new message:', topic, message.toString());
  $('#data').text(message.toString());
  });
  client.subscribe('nodemcu/temprature');
})</script>
<script>
function startTime() {
    var today = new Date();
    var h = today.getHours();
    var m = today.getMinutes();
    var s = today.getSeconds();
    m = checkTime(m);
    s = checkTime(s);
    document.getElementById('txt').innerHTML =
    h + ":" + m + ":" + s;
    var t = setTimeout(startTime, 500);
}
function checkTime(i) {
    if (i < 10) {i = "0" + i};  // add zero in front of numbers < 10
    return i;
}
</script>
<style>
div.card {
  width: 250px;
  box-shadow: 0 4px 8px 0 rgba(0, 0, 0, 0.2), 0 6px 20px 0 rgba(0, 0, 0, 0.19);
  text-align: center;
  border-radius: 5px;
  background-color: #5DADE2
}

div.header {
    background-color: #E03C3C;
    color: white;
    padding: 10px;
    font-size: 35px;
    border-radius: 5px;
}

div.container {
    padding: 4px; 
}
</style>
</head>

<center><h2>POSCO Maharashtra CAL Electrical Temp Monitor </h2>

<div class="card">
  <div class="header">
   <p id = "data"></p>
  </div>

  <div class="container">
    <h2>Temperature</h2>

<p>Date: <span id="datetime"></span></p>
Time: <body onload="startTime()">                         

<script>
var dt = new Date();
document.getElementById("datetime").innerHTML = (("0"+(dt.getMonth()+1)).slice(-2)) +"/"+ 
(("0"+dt.getDate()).slice(-2)) +"/"+ (dt.getFullYear()) ;
</script>

<div id="txt"></div>

</div>
<a href="https://google.co.in">sudhansu03@posco.net</a>
</center>
</body>
</html>

)=====";

