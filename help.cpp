

#include <Arduino.h>
#include <string.h>

#include "commandes.hpp"

//=========================================
//
//          help 
//
//=========================================
void help(){
    help("");
}
void help(String commande){
    String subCommand = "";
    String param1 = "";

    int index = commande.indexOf(' ');
    subCommand = commande.substring(index+1,commande.length());
    index = commande.indexOf(' ');
    if (index != -1){
        param1 = commande.substring(0,index);
        subCommand = commande.substring(index+1,commande.length());
    } else {
        param1 = commande;
    }
    //Serial.print("param1 = ");
    //Serial.println(param1);

    if (param1.equals("variable")){
        variableHelp();
    } else if (param1.equals("help")) {
        Serial.print (" help : ");
        Serial.println(" help       => affiche l'aide");
    } else if (param1.equals("affiche")) {
        afficheurHelp();
    } else if (param1.equals("set")) {
        setGetHelp();
    } else if (param1.equals("get")) {
        setGetHelp();
    } else if (param1.equals("wifi")) {
        wifiHelp();
    } else if (param1.equals("ifconfig")) {
        Serial.print (" ifconfig : ");
        Serial.println(" ifconfig       => affiche l'adresse IP de l'arduino");
    } else if (param1.equals("reboot")) {
        Serial.print (" reboot : ");
        Serial.println(" reboot     => reinitialise le systeme");
    } else {
        int idx = 0;
        Serial.println("Shell ESP32 : Comamndes disponibles");
        for (idx = 0 ; idx < NB_COMMANDES ; idx++){
            if (ListeCommandes[idx] != NULL){
                if ((idx % 5) != 0) Serial.print(" / ");
                Serial.print(ListeCommandes[idx]);
                if ((idx % 5) == 4){
                    Serial.println();
                }
            }
        }
        if ((idx % 5) != 4){
            Serial.println();
        }
    }
}
