//
//  module de test de la feather ESP32
//  test de création d'un shell
//  afin de tester des fonctionnalite
//  de l'arduino connecté
// (c) B. Froger 2020


#include <arduino.h>

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
    delay(2000);
    if (timeoutInitSerial != 0)
    {
        Serial.println("Serial initialized");
    } else
    {
        Serial.println("Serial not initialized");
        exit(0);
    }

    Serial.println("debut de setup");

    //delay(1000);

    Serial.println("Fin de setup");
    Serial.println("ESP32_shell.ino");
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