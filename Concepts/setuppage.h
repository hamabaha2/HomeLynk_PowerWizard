R"(
<!DOCTYPE html>
<html lang="en" dir="ltr">
  <head>
    <meta charset="utf-8">
    <title>HomeLynk Setup</title>
    <style media="screen">
      body {
        margin: 2% 10% 2% 10%;
        background-color: #2C3333;
        font-family: verdana;
        color: #E7F6F2;
      }
      h1 {
        color: #A5C9CA;
        text-align: center;
        padding: 2%;
        background-color: #395B64;
      }
      .btn {
        margin-left: 40%;
        margin-top: 15px;
        padding: 20px 80px 20px 80px;
        border: none;
        font-size: 150%;
        color: #2C3333;
        background-color: #A5C9CA;
      }
      .btn:hover {
        color: #F5F9FA;
        background-color: #B5D9DA;
      }
      .sec {
        background-color: #395B64;
        padding-top: 10px;
        padding-bottom: 5px;
      }
    </style>
  </head>
  <body>
    <h1>HomeLynk setup</h1>
    <hr>
    <p>
      Welcome to setup mode on your HomeLynk device.
      Please follow the instructions and fill the form in order to complete the setup of your device. Finish by pressing the submit button and you should be all set.
    </p>
    <hr>
    <form action="" method="post">
      <h2>Account Information</h2>
      <p>Please fill in your account information here</p>
      <div class="sec">
        <label for="Email">Account Email Address </label><input type="text" name="Email" value="email@example.com"><br>
        <label for="Password">Account Password </label><input type="password" name="Password" value=""><br>
        <label for="dvc_group">Device Group name </label> <input type="text" name="dvc_group" value=""><br>
      </div>
      <hr>
      <h2>WiFi Settings</h2>
      <p>Please enter home WiFi SSID and Password</p>
      <div class="sec">
        Wireless Netwrok Name "SSID" <input type="text" name="SSID" value=""><br>
        Wireless Password <input type="password" name="wpassword" value=""><br>
      </div>
      <hr>
      <h2>Smart things</h2>
      <p>Below is a list of smart devices connected</p>
      <div class="sec">
        <label for="DVC1">Device 1 Name: </label> <input type="text" name="DVC1" value="Device 1">
        <label for="MAC1">Device 1 MAC Address: </label> <input type="text" name="MAC1" value=""><br>
        <label for="DVC1">Device 2 Name: </label> <input type="text" name="DVC2" value="Device 1">
        <label for="MAC2">Device 2 MAC Address: </label> <input type="text" name="MAC2" value=""><br>
        <label for="DVC1">Device 3 Name: </label> <input type="text" name="DVC3" value="Device 3">
        <label for="MAC3">Device 3 MAC Address: </label> <input type="text" name="MAC3" value=""><br>
        <label for="DVC1">Device 4 Name: </label> <input type="text" name="DVC4" value="Device 4">
        <label for="MAC4">Device 4 MAC Address: </label> <input type="text" name="MAC4" value=""><br>
        <label for="DVC1">Device 5 Name: </label> <input type="text" name="DVC5" value="Device 5">
        <label for="MAC5">Device 5 MAC Address: </label> <input type="text" name="MAC5" value=""><br>
        <label for="DVC1">Device 6 Name: </label> <input type="text" name="DVC6" value="Device 6">
        <label for="MAC6">Device 6 MAC Address: </label> <input type="text" name="MAC6" value=""><br>
        <label for="DVC1">Device 7 Name: </label> <input type="text" name="DVC7" value="Device 7">
        <label for="MAC7">Device 7 MAC Address: </label> <input type="text" name="MAC7" value=""><br>
        <label for="DVC1">Device 8 Name: </label> <input type="text" name="DVC8" value="Device 8">
        <label for="MAC8">Device 8 MAC Address: </label> <input type="text" name="MAC8" value=""><br>
      </div>
      <input class="btn" type="submit" name="submit" value="Submit">
    </form>
    <hr>
    <h2>
      Device Information
    </h2>
    <div class="sec">
      <p>Temperature: 50</p>
      <p>Time: 13:04:00</p>
      <p>Date: 13:04:00</p>
      <p>Time since last reboot: 123042 seconds</p>
    </div>
  </body>
</html>
  )"
