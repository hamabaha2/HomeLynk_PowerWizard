/*
  Rui Santos
  Complete project details at https://RandomNerdTutorials.com/esp-now-esp32-arduino-ide/
  
  Permission is hereby granted, free of charge, to any person obtaining a copy
  of this software and associated documentation files.
  
  The above copyright notice and this permission notice shall be included in all
  copies or substantial portions of the Software.
*/

#include <esp_now.h>
#include <WiFi.h>

// REPLACE WITH YOUR RECEIVER MAC Address
uint8_t broadcastAddress[] = {0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF};
// constants
//string myMAC1="";
//const char* myMAC;

// Structure example to send data
// Must match the receiver structure
typedef struct struct_message {
  char acct[50];
  char dvcGroup[50];
  char macAddr[18];
  char yourMAC[18];
  int Threshold;
  bool Relay_1;
  bool Relay_2;
} struct_message;

// Create a struct_message called broadcast (I think this is wrong, needs stuct in the beginning)
struct_message broadcast;

bool led1Status;
bool led2Status;
bool btnStatus;
long timer;
int i;

esp_now_peer_info_t peerInfo;

// callback when data is sent
void OnDataSent(const uint8_t *mac_addr, esp_now_send_status_t status) {
  Serial.print("\r\nLast Packet Send Status:\t");
  Serial.println(status == ESP_NOW_SEND_SUCCESS ? "Delivery Success" : "Delivery Fail");
}
 
void setup() {
  // Init Serial Monitor
  Serial.begin(115200);
 
  // Set device as a Wi-Fi Station
  WiFi.mode(WIFI_STA);
  //myMAC1 = WiFi.macAddress()
  //myMAC = myMAC1.c_str();
  Serial.println("MAC Address: "+WiFi.macAddress());

  // Setup the pins
  pinMode (45, OUTPUT);
  pinMode (48, OUTPUT);
  pinMode (1, INPUT);

  // setup timer
  timer = millis();
  
  // Init ESP-NOW
  if (esp_now_init() != ESP_OK) {
    Serial.println("Error initializing ESP-NOW");
    return;
  }

  // Once ESPNow is successfully Init, we will register for Send CB to
  // get the status of Trasnmitted packet
  esp_now_register_send_cb(OnDataSent);
  
  // Register peer
  memcpy(peerInfo.peer_addr, broadcastAddress, 6);
  peerInfo.channel = 0;  
  peerInfo.encrypt = false;
  
  // Add peer        
  if (esp_now_add_peer(&peerInfo) != ESP_OK){
    Serial.println("Failed to add peer");
    return;
  }
}
 
void loop() {
  // Set values to send
  strcpy(broadcast.acct, "hamabaha2@yahoo.com");
  strcpy(broadcast.dvcGroup, "home");
  strcpy(broadcast.macAddr, "7C:df:A1:E8:7B:B0");
  broadcast.Threshold = 100;
  broadcast.Relay_1 = led1Status;
  broadcast.Relay_2 = led2Status;
  
  
  if (millis()-timer>2000) {
    // reset time
    timer = millis();
    Serial.print("i: ");
    Serial.println(i);
    Serial.print("LED 1 Status: ");
    Serial.println(led1Status);
    Serial.print("LED 2 Status: ");
    Serial.println(led2Status);
    Serial.print("Button Status: ");
    Serial.println(btnStatus);
    
    // Send message via ESP-NOW
    esp_err_t result = esp_now_send(broadcastAddress, (uint8_t *) &broadcast, sizeof(broadcast));
   
    if (result == ESP_OK) {
      Serial.println("Sent with success");
    }
    else {
      Serial.println("Error sending the data");
    }
  }
  btnStatus = digitalRead(1);
  if (btnStatus == HIGH) {
    i++;                  // increase i which is a counter
    if (i>3) {i=0;}       // make sure i is between 0 and 3
    led1Status = i%2;     // led1 will light when i is odd
    if (i>1) {led2Status = 1;} else {led2Status = 0;} // led2 will light when i is 2 or 3
    while (digitalRead(1)==HIGH) {delay(10);} // do not read button until it is released
    digitalWrite(45,led1Status);
    digitalWrite(48,led2Status);
  }

}
