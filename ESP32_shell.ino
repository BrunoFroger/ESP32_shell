//
//  module de test de la feather ESP32
//  test de création d'un serveur ssh 
//  afin de se connecter a l'esp32 en ssh 
// (c) B. Froger 2020


#include <arduino.h>
#include <WiFi.h>

#include "wifi.hpp"
#include "clavier.hpp"

//=========================================
//
//          setup
//
//=========================================
void setup() {
    delay(2000);
    // initialize serial communication
    Serial.begin(115200);
    int timeoutInitSerial = 100;
    while (timeoutInitSerial-- > 0)
    {
        if (Serial)
        break;
        delay(10);
    }
    delay(5000);
    if (timeoutInitSerial != 0)
    {
        Serial.println("Serial initialized");
    } else
    {
        Serial.println("Serial not initialized");
        exit(0);
    }

    Serial.println("debut de setup");
    initWifi();
    Serial.println("Init Wifi OK");

    delay(1000);

    Serial.println("Fin de setup");
}


//=========================================
//
//          Loop
//
//=========================================
void loop() {

    if (Serial.available() > 0) {
        lireClavier();
    }

    delay (1);
}