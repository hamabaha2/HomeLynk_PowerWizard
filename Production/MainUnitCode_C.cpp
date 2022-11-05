
/* +-------------------------------------+
   |               Libraries             |
   +-------------------------------------+ */
 #include <Arduino.h>
 #include <WiFi.h>
 #include <Preferences.h>
 #include <esp_now.h>
 #include <AsyncTCP.h>
 #include <ESPAsyncWebServer.h>

/* +-------------------------------------+
   |        Structure Templates          |
   +-------------------------------------+*/
typedef struct masterMsg {
   // masterMsg will include messages to switches
   char acct[50]; 	// account identifier
   char dvcGroup[50];	// device group identifier
   char macAddr[18];	// MAC address of main unit
   char yourMAC[18];	// MAC address of the swtich (software level decision on message)
   int threshold;	// Ampere threshold to cutoff
   bool Relay_1;	// Relay command (On/Off)
   bool Relay_2;	// Command for switches with two relays (On/Off)
} masterMsg;

typedef struct switchMsg {
   // this will include messages from the switches (not ready yet)
   int test;
} switchMsg;

/* +-------------------------------------+
   |          Global Variables           |
   +-------------------------------------+*/


const int setup_btn = 1; 			// This is the pin that has the setup button

const int act_ledr = 36;          // pins for act LED, red green, blue, and power
const int act_ledg = 37;
const int act_ledb = 38;
const int act_ledk = 39;
const int act_ledr_pwmc = 0;
const int act_ledg_pwmc = 1;
const int act_ledb_pwmc = 2;
const int act_ledk_pwmc = 3;

const int wfi_ledr = 15;          // pins for Wifi LED, red green, blue, and power
const int wfi_ledg = 16;
const int wfi_ledb = 17;
const int wfi_ledk = 18;
const int wfi_ledr_pwmc = 4;
const int wfi_ledg_pwmc = 5;
const int wfi_ledb_pwmc = 6;
const int wfi_ledk_pwmc = 7;

unsigned int setup_btn_timer; 	// How many millis the button is pressed



// Wifi variables
const char ssid[] = "ssid";
const char password[] = "wifi_password";

// ESP_NOW variable
uint8_t broadcastAddress[] = {0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF};


/* +-------------------------------------+
   |         Global Structures           |
   +-------------------------------------+*/

// Global structures are defined here

struct masterMsg broadcastMsg; // Create a structure called broadcast
struct masterMsg historyMasterMsg; // Create a structure for last broadcast message

switchMsg switch1; // Create a structure for each switch
switchMsg switch2;
switchMsg switch3;
switchMsg switch4;
switchMsg switch5;
switchMsg switch6;
switchMsg switch7;
switchMsg switch8;


/* +-------------------------------------+
   |       Function Declarations         |
   +-------------------------------------+ */

// Setup Function
void setup_mode() {
   // define local variables
   unsigned long int setup_timer; 
   unsigned long int currentTime; 
   unsigned long int previousTime;
   bool submitted = 0;
   String email;
   String password;
   String deviceGrpName;
   String SSID;
   String WifiPwd;

   const char index_html[] = R"rawliteral(
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
               <form action="/get">
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
      )rawliteral";
   
   // end of raw HTML page here

   // ****** webserver settings ********
   AsyncWebServer server(80);
   // Local function declaration
   /* I am not sure why this is not working, saying that a function-definition is not allowed here before the "{" token 
   void notFound(AsyncWebServerRequest *request) {
      request->send(404, "text/plain", "Not found");
   }
   */

   // Checking setup button before actually starting
   while (digitalRead(setup_btn)==HIGH) {
      // feedback on setup led while button is pressed
      Serial.println("Waiting for button release to start setup mode");
   }
   while (digitalRead(setup_btn)==LOW) {
      // start the setup process when button released
      Serial.println("Entering setup mode");
   }
   setup_btn_timer = millis();	// reset the button timer (not sure if this works)
   // return 0;


   // Here we will setup interrupts for web page
   server.on("/", HTTP_GET, [](AsyncWebServerRequest *request) {
      request->send_P(200, "text/html", index_html);
   });
     // Send a GET request to <ESP_IP>/get?input1=<inputMessage>
   server.on("/get", HTTP_GET, [] (AsyncWebServerRequest *request) {
      // GET email value on <ESP_IP>/get?email=email
         email = request->getParam("Email")->value();
                  
      Serial.println(email);
      
      request->send(200, "text/html", "HTTP GET request sent to your ESP on input field (Email) with value: " 
                           + email + "<br><a href=\"/\">Return to Home Page</a>");
   });
   server.onNotFound(notFound);
   server.begin();

   // ****** WiFi settings ***********

   // Start Wifi
   Serial.println("Starting WiFi ...");
   WiFi.softAP("HLSetup", "hlsetup1");

   IPAddress IP = WiFi.softAPIP();
   Serial.print("AP IP address: ");
   Serial.println(IP);
   server.begin();

   setup_timer = millis(); // timer to expire setup mode if left for too long
  
   while (digitalRead(setup_btn)==LOW) {  // exit setup mode when setup is pressed again
         
         // setup timer expiry
         if ((( millis() - setup_timer ) > 300000 ) || ( digitalRead(setup_btn) == HIGH )) {
            // close wifi
            // close server
            // get out of setup mode (Maybe we should call setup function?)
            break;   
         }
   }
}
	// Peering mode configuration here
	// exit setup mode using button or time expiry
	// the main unit ESPNOW's on standard SSID, will listen to returning MAC addresses
	// Newly learned MAC addresses will be added to list
	// lights indicate peering success and failure (If 8 is already there)

//Factory Reset Function
void factory_reset() {
   // led feedback
   // allow button release
   // save original parameters
   // reboot
}

/* +-------------------------------------+
   |                Setup                |
   +-------------------------------------+ */
void setup() {
	// Init Serial Monitor
	
  	  Serial.begin(115200);
 
  	// Set device as a Wi-Fi Station
	
  	  WiFi.mode(WIFI_STA);
	
	// Initialize ESP NOW
	
	  if (esp_now_init() != ESP_OK) {
	    Serial.println("Error initializing ESP-NOW");
	    return;
	  }

	// setup pins

	   pinMode( setup_btn, INPUT );
	   pinMode( act_ledr , OUTPUT );
	   pinMode( act_ledg , OUTPUT );
	   pinMode( act_ledb , OUTPUT );
	   pinMode( act_ledk , OUTPUT );

	   pinMode( wfi_ledr , OUTPUT );
	   pinMode( wfi_ledg , OUTPUT );
	   pinMode( wfi_ledb , OUTPUT );
	   pinMode( wfi_ledk , OUTPUT );

	// configure PWM for LEDs
	
	   ledcSetup(act_ledr_pwmc, 5000, 8);  // Frequency 50 was not accepted for some reason.
	   ledcSetup(act_ledg_pwmc, 5000, 8);
	   ledcSetup(act_ledb_pwmc, 5000, 8);
	   ledcSetup(act_ledk_pwmc, 5000, 8);

	   ledcSetup(wfi_ledr_pwmc, 5000, 8);
	   ledcSetup(wfi_ledg_pwmc, 5000, 8);
	   ledcSetup(wfi_ledb_pwmc, 5000, 8);
      ledcSetup(wfi_ledk_pwmc, 5000, 8);

	   ledcAttachPin( act_ledr , act_ledr_pwmc );
	   ledcAttachPin( act_ledg , act_ledg_pwmc );
	   ledcAttachPin( act_ledb , act_ledb_pwmc );
	   ledcAttachPin( act_ledk , act_ledk_pwmc );

	   ledcAttachPin( wfi_ledr , wfi_ledr_pwmc );
	   ledcAttachPin( wfi_ledg , wfi_ledg_pwmc );
	   ledcAttachPin( wfi_ledb , wfi_ledb_pwmc );
	   ledcAttachPin( wfi_ledk , wfi_ledk_pwmc );
}

/* +-------------------------------------+
   |                 Loop                |
   +-------------------------------------+*/
void loop() {
	// setup button check
	setup_btn_timer = millis();
	while (digitalRead(setup_btn)==HIGH) {
    if ((millis() - setup_btn_timer) > 5000) {  // pressed for 5 seconds
      setup_btn_timer = millis(); 				   // reset setup button timer
      setup_mode();  							      // enter setup mode
      }
	}
}

/* +------------------------------------+
   |         Act LED function           |
   +------------------------------------+*/

void act_led(int color, int s) {
   // function to turn act led on or off with a specific color

   int r = color / 0x10000;  // find red value (most significant 8 bits)
   int g = ( color - (r*0x10000) ) / 0x100;   // find green vlaue (most significant 8 bits after taking away the r)
   int b = ( color - (r*0x10000) - (g*0x100) );     // find blue value (least significant 8 bits)
   
   //setup act LED pins
   ledcWrite(act_ledr_pwmc,r);
   ledcWrite(act_ledg_pwmc,g);
   ledcWrite(act_ledb_pwmc,b);
   ledcWrite(act_ledk_pwmc,s);
   
}

void wfi_led(int color, int s) {
   // function to turn Wifi led on or off with a specific color

   int r = color / 0x10000;  // find red value (most significant 8 bits)
   int g = ( color - (r*0x10000) ) / 0x100;   // find green vlaue (most significant 8 bits after taking away the r)
   int b = ( color - (r*0x10000) - (g*0x100) );     // find blue value (least significant 8 bits)
   
   //setup act LED pins
   ledcWrite(wfi_ledr_pwmc,r);
   ledcWrite(wfi_ledg_pwmc,g);
   ledcWrite(wfi_ledb_pwmc,b);
   ledcWrite(wfi_ledk_pwmc,s);
}

