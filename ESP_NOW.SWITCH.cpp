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

// Structure to receive data
// Must match the sender structure
typedef struct struct_message {
    char acct[50];
    char dvcGroup[50];
    char macAddr[18]; 
    char myMAC[18];
    int Threshold;
    bool Relay_1;
    bool Relay_2;
} struct_message;

// Create a struct_message called myData = > broadcast
struct_message broadcast;

// Global variables
int led1Status;
int led2Status;
long timer;

// callback function that will be executed when data is received
void OnDataRecv(const uint8_t * mac, const uint8_t *incomingData, int len) {
  memcpy(&broadcast, incomingData, sizeof(broadcast));
  Serial.print("Bytes received: ");
  Serial.println(len);
  Serial.print("Account Name: ");
  Serial.println(broadcast.acct);
  Serial.print("Device Group Name: ");
  Serial.println(broadcast.dvcGroup);
  Serial.print("Main Device MAC Address: ");
  Serial.println(broadcast.macAddr);
  Serial.println();
  Serial.print("Addressed Device MAC Address: ");
  Serial.println(broadcast.myMAC);
  Serial.print("Threshold value: ");
  Serial.println(broadcast.Threshold);
  Serial.print("Relay 1 Command");
  Serial.println(broadcast.Relay_1);
  Serial.print("Relay 2 Command");
  Serial.println(broadcast.Relay_2);
  //digitalWrite(45,Relay_1);
  //digitalWrite(48,Relay_2);
}
 
void setup() {  
  // Setup pins and relays
  pinMode(45,OUTPUT);
  pinMode(48,OUTPUT);
  pinMode(1,INPUT);

  // Reset everything
  digitalWrite(45, LOW);
  digitalWrite(48, LOW);
  
  // Initialize Serial Monitor
  Serial.begin(115200);
  
  // Set device as a Wi-Fi Station
  WiFi.mode(WIFI_STA);

  // Init ESP-NOW
  if (esp_now_init() != ESP_OK) {
    Serial.println("Error initializing ESP-NOW");
    return;
  }
  
  // Once ESPNow is successfully Init, we will register for recv CB to
  // get recv packer info
  esp_now_register_recv_cb(OnDataRecv);

  timer = millis();
}
 
void loop() {
  led1Status = broadcast.Relay_1;
  led2Status = broadcast.Relay_2;
  if ((millis()-timer)>500) {
    timer = millis();
    digitalWrite(45,led1Status);
    digitalWrite(48,led2Status);
  }
}
