
#include <Arduino.h>

#include "wifi.hpp"
#include "commandes.hpp"

String ListeCommandes[NB_COMMANDES]={
    "help",  "reboot", "ifconfig", 
    "wifi", "get", "set", "i2cScan"
    "variable","affiche"
};
String ipAdress;

//=========================================
//
//          ifconfig 
//
//=========================================
void ifconfig(void){
    Serial.print("ipAdress = ");
    Serial.println(ipAdress);
}

//=========================================
//
//          reboot 
//
//=========================================
void (* reboot)(void) = 0;

//=========================================
//
//          analyseCommande 
//
//=========================================
void analyseCommande(String cde){
    cde=cde.substring(0,cde.length()-1);
    int index = cde.indexOf(' ');
    String subCommand="";
    if (index != -1){
        subCommand = cde.substring(index+1,cde.length());
    }
    if (cde.startsWith("help")){
        help(subCommand);
    } else if (cde.equals("reboot")){
        reboot();
    } else if (cde.equals("ifconfig")){
        // visualise le contenu d'une variables
        ifconfig();
    } else if (cde.startsWith("wifi ")){
        analyseWifi(subCommand);
    }else if (cde.startsWith("get ")){
        // visualise le contenu d'une variables
        analyseGet(subCommand);
    }else if (cde.startsWith("set ")){
        // visualise le contenu d'une variables
        analyseSet(subCommand);
    }else if (cde.startsWith("variable")){
        // visualise le contenu d'une variables
        analyseVariable(subCommand);
    }else if (cde.startsWith("affiche")){
        // visualise le contenu d'une variables
        analyseAfficheur(subCommand);
    }else if (cde.startsWith("i2cscan")){
        // visualise le contenu d'une variables
        i2cScan();
    } else if (cde.equals("")){
        Serial.println();
    } else {
        Serial.print("ERREUR => <");
        Serial.print(cde);
        Serial.println("> => commande inconnue");
        help();
    }
}
