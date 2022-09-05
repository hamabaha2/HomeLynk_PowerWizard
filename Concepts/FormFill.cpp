
/* +-------------------------------------+
   |               Libraries             |
   +-------------------------------------+ */
 #include <WiFi.h>
 #include <Preferences.h>
 #include <esp_now.h>

/* +-------------------------------------+
   |        Structure Templates          |
   +-------------------------------------+*/
typedef struct masterMsg {
   // masterMsg will include messages to switches
   char acct[50];
   char dvcGroup[50];
   char macAddr[18];
   char yourMAC[18];
   int threshold;
   bool Relay_1;
   bool Relay_2;
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

   // wifi settings


   // ****** webserver settings ********

   // Start server
   WiFiServer server(80);
   // header information variable
   String header;

   // ****** WiFi settings ***********

   // Start Wifi
   Serial.println("Starting WiFi ...");
   WiFi.softAP("HLSetup", "1235678");

   IPAddress IP = WiFi.softAPIP();
   Serial.print("AP IP address: ");
   Serial.println(IP);
   server.begin();

   setup_timer = millis(); // timer to expire setup mode if left for too long
  
   while (digitalRead(setup_btn)==LOW) {  // exit setup mode when setup is pressed again
   
   WiFiClient client = server.available(); // listen to incoming clients

   // ************** client connection management and HTML page ************************
   
   if (client) {
      currentTime = millis();
      previousTime = currentTime;
      Serial.println("Client connected");
      String currentLine = "";
      while (client.connected() && currentTime - previousTime <= 2000) { // Loop while client is connected
         currentTime = millis();
         if (client.available()) {
            setup_timer = millis();    // restart setup timer 
            char c = client.read();    // read a byte from the client
            Serial.write(c);
            header += c;
            if (c == '\n') { //HTTP ends with two blanks, check if blank
               if (currentLine.length() == 0) {
                  client.println("HTTP/1.1 200 OK");
                  client.println("Content-type:text/html");
                  client.println("Connection: close");
                  client.println();

                  // ******** receiving the bytes starts here *************
                  // in previous tests, we checked if 'header' variable included GET /26/on in the request
                  // maybe we check with line instead here.
                  // the command they used was if (header.indexOf("GET /26/on") >= 0 ) 
                                    
                  //****************** display webpage here ***************

               }
            }
         }
         // clear header variable
         header = "";
         // close connection
         client.stop();
         Serial.println("Client disconnected");
         Serial.println("");

         // setup timer expiry
         if ((( millis() - setup_timer ) > 300000 ) || ( digitalRead(setup_btn) == HIGH )) {
            // close wifi
            // close server
            // get out of setup mode (Maybe we should call setup function?)
            break;
         }
      }
   }
	// setup mode configuration here

	// exit setup mode using button

   }
   }

//Factory Reset Function
void factory_reset(){
   // led feedback
   // allow button release
   // save original parameters
   // reboot
}


/* +-------------------------------------+
   |                Setup                |
   +-------------------------------------+ */
void setup() {
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
   ledcSetup(0, 50, 8);
   ledcSetup(1, 50, 8);
   ledcSetup(2, 50, 8);
   ledcSetup(3, 500, 8);
   ledcSetup(4, 500, 8);
   ledcSetup(5, 500, 8);
   ledcSetup(6, 500, 8);

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
   digitalWrite(act_ledk,LOW);   // turn off led before changing color

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
   digitalWrite(act_ledk,LOW);   // turn off led before changing color

   //setup act LED pins
   ledcWrite(wfi_ledr_pwmc,r);
   ledcWrite(wfi_ledg_pwmc,g);
   ledcWrite(wfi_ledb_pwmc,b);
   ledcWrite(wfi_ledk_pwmc,s);
}

