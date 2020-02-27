

#include <Arduino.h>
#include <string.h>

#include "commandes.hpp"

char carLu;
char commande[50];
String cde;
int indexCarLu=0;

//=========================================
//
//          lireClavier 
//
//=========================================
void lireClavier(void){
    while (Serial.available() > 0){
        carLu = Serial.read();
        commande[indexCarLu++] = carLu;
        commande[indexCarLu]='\0';
        if (carLu == '\n'){
            // retour chariot saisi
            // on analyse la commande
            cde = String(commande);
            // cde.toLowerCase();
            // suppression des doublons de blancs
            while (cde.indexOf("  ") > 0){
                cde.replace("  ", " ");
            }
            cde.toCharArray(commande,50);
            Serial.print(commande);
            analyseCommande(String(commande));
            indexCarLu=0;
            commande[indexCarLu]='\0';
        }
    }
}