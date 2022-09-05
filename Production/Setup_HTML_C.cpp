/*********
  Rui Santos
  Complete project details at https://randomnerdtutorials.com  
*********/

// Load Wi-Fi library
#include <WiFi.h>

// Set web server port number to 80
WiFiServer server(80);

// Variable to store the HTTP request
String header;

// Auxiliar variables to store the current output state
//String output26State = "off";
//String output27State = "off";

// Assign output variables to GPIO pins
//const int output26 = 26;
//const int output27 = 27;

// Current time
unsigned long currentTime = millis();
// Previous time
unsigned long previousTime = 0; 
// Define timeout time in milliseconds (example: 2000ms = 2s)
const long timeoutTime = 2000;

void setup() {
  Serial.begin(115200);
  // Initialize the output variables as outputs
  //pinMode(output26, OUTPUT);
  //pinMode(output27, OUTPUT);
  // Set outputs to LOW
  //digitalWrite(output26, LOW);
  //digitalWrite(output27, LOW);

  // Connect to Wi-Fi network with SSID and password
  Serial.print("Connecting to MOTOEDA2");
   WiFi.begin("MOTOEDA2" , "ka24yxsr4f");
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  // Print local IP address and start web server
  Serial.println("");
  Serial.println("WiFi connected.");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
  server.begin();
}


void loop(){
  
  
  //WiFiClient client = server.available();   // Listen for incoming clients
  WiFiClient client = server.available();   // Listen for incoming clients
  
  if (client) {                             // If a new client connects,
    currentTime = millis();
    previousTime = currentTime;
    Serial.println("New Client.");          // print a message out in the serial port
    String currentLine = "";                // make a String to hold incoming data from the client
    while (client.connected() && currentTime - previousTime <= timeoutTime) {  // loop while the client's connected
      client.println("client.print<!DOCTYPE html>");
client.println("<html lang=\"en\" dir=\"ltr\">");
  client.println("<head>");
    client.println("<meta charset=\"utf-8\">");
    client.println("<title>HomeLynk Setup</title>");
    client.println("<style media=\"screen\">");
      client.println("body {");
        client.println("margin: 2% 10% 2% 10%;");
        client.println("background-color: #2C3333;");
        client.println("font-family: verdana;");
        client.println("color: #E7F6F2;");
      client.println("}");
      client.println("h1 {");
        client.println("color: #A5C9CA;");
        client.println("text-align: center;");
        client.println("padding: 2%;");
        client.println("background-color: #395B64;");
      client.println("}");
      client.println(".btn {");
        client.println("margin-left: 40%;");
        client.println("margin-top: 15px;");
        client.println("padding: 20px 80px 20px 80px;");
        client.println("border: none;");
        client.println("font-size: 150%;");
        client.println("color: #2C3333;");
        client.println("background-color: #A5C9CA;");
      client.println("}");
      client.println(".btn:hover {");
        client.println("color: #3C4343;");
        client.println("background-color: #B5D9DA;");
      client.println("}");
      client.println(".sec {");
        client.println("background-color: #395B64;");
        client.println("padding-top: 10px;");
        client.println("padding-bottom: 5px;");
      client.println("}");
    client.println("</style>");
  client.println("</head>");
  client.println("<body>");
    client.println("<h1>HomeLynk setup</h1>");
    client.println("<hr>");
    client.println("<p>");
      client.println("Welcome to setup mode on your HomeLynk device.");
      client.println("Please follow the instructions and fill the form in order to complete the setup of your device. Finish by pressing the submit button and you should be all set.");
    client.println("</p>");
    client.println("<hr>");
    client.println("<form action=\"\" method=\"post\">");
      client.println("<h2>Account Information</h2>");
      client.println("<p>Please fill in your account information here</p>");
      client.println("<div class=\"sec\">");
        client.println("<label for=\"Email\">Account Email Address </label><input type=\"text\" name=\"Email\" value=\"email@example.com\"><br>");
        client.println("<label for=\"Password\">Account Password </label><input type=\"password\" name=\"Password\" value=\"\"><br>");
        client.println("<label for=\"dvc_group\">Device Group name </label> <input type=\"text\" name=\"dvc_group\" value=\"\"><br>");
      client.println("</div>");
      client.println("<hr>");
      client.println("<h2>WiFi Settings</h2>");
      client.println("<p>Please enter home WiFi SSID and Password</p>");
      client.println("<div class=\"sec\">");
        client.println("Wireless Netwrok Name \"SSID\" <input type=\"text\" name=\"SSID\" value=\"\"><br>");
        client.println("Wireless Password <input type=\"password\" name=\"wpassword\" value=\"\"><br>");
      client.println("</div>");
      client.println("<hr>");
      client.println("<h2>Smart things</h2>");
      client.println("<p>Below is a list of smart devices connected</p>");
      client.println("<div class=\"sec\">");
        client.println("<label for=\"DVC1\">Device 1 Name: </label> <input type=\"text\" name=\"DVC1\" value=\"Device 1\">");
        client.println("<label for=\"MAC1\">Device 1 MAC Address: </label> <input type=\"text\" name=\"MAC1\" value=\"\"><br>");
        client.println("<label for=\"DVC1\">Device 2 Name: </label> <input type=\"text\" name=\"DVC2\" value=\"Device 1\">");
        client.println("<label for=\"MAC2\">Device 2 MAC Address: </label> <input type=\"text\" name=\"MAC2\" value=\"\"><br>");
        client.println("<label for=\"DVC1\">Device 3 Name: </label> <input type=\"text\" name=\"DVC3\" value=\"Device 3\">");
        client.println("<label for=\"MAC3\">Device 3 MAC Address: </label> <input type=\"text\" name=\"MAC3\" value=\"\"><br>");
        client.println("<label for=\"DVC1\">Device 4 Name: </label> <input type=\"text\" name=\"DVC4\" value=\"Device 4\">");
        client.println("<label for=\"MAC4\">Device 4 MAC Address: </label> <input type=\"text\" name=\"MAC4\" value=\"\"><br>");
        client.println("<label for=\"DVC1\">Device 5 Name: </label> <input type=\"text\" name=\"DVC5\" value=\"Device 5\">");
        client.println("<label for=\"MAC5\">Device 5 MAC Address: </label> <input type=\"text\" name=\"MAC5\" value=\"\"><br>");
        client.println("<label for=\"DVC1\">Device 6 Name: </label> <input type=\"text\" name=\"DVC6\" value=\"Device 6\">");
        client.println("<label for=\"MAC6\">Device 6 MAC Address: </label> <input type=\"text\" name=\"MAC6\" value=\"\"><br>");
        client.println("<label for=\"DVC1\">Device 7 Name: </label> <input type=\"text\" name=\"DVC7\" value=\"Device 7\">");
        client.println("<label for=\"MAC7\">Device 7 MAC Address: </label> <input type=\"text\" name=\"MAC7\" value=\"\"><br>");
        client.println("<label for=\"DVC1\">Device 8 Name: </label> <input type=\"text\" name=\"DVC8\" value=\"Device 8\">");
        client.println("<label for=\"MAC8\">Device 8 MAC Address: </label> <input type=\"text\" name=\"MAC8\" value=\"\"><br>");
      client.println("</div>");
      client.println("<input class=\"btn\" type=\"submit\" name=\"submit\" value=\"Submit\">");
    client.println("</form>");
    client.println("<hr>");
    client.println("<h2>");
      client.println("Device Information");
    client.println("</h2>");
    client.println("<div class=\"sec\">");
      client.println("<p>Temperature: 50</p>");
      client.println("<p>Time: 13:04:00</p>");
      client.println("<p>Date: 13:04:00</p>");
      client.println("<p>Time since last reboot: 123042 seconds</p>");
    client.println("</div>");
  client.println("</body>");
client.println("</html>");
client.println("");
    client.stop();
    Serial.println("Client disconnected.");
    Serial.println("");
  }
}
}
