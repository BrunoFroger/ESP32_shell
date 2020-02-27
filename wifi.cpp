

#include <Arduino.h>
#include <WiFi.h>

#include "commandes.hpp"

char wifiSsid[25];
char wifiPassword[50];
WiFiClient wifiClient;
WiFiServer wifiServer(80);//Ecouter le port 80

//=========================================
//
//          wifiHelp 
//
//=========================================
void wifiHelp(){
    Serial.println("Syntaxe des commandes wifi : ");
    Serial.println(" wifi stop          => arret du serveur wifi");
    Serial.println(" wifi start         => demarrage du serveur wifi");
    Serial.println(" wifi status        => etat du serveur wifi");
    Serial.println(" wifi rescan        => scan des reseau wifi a proximite et connexion si rencontre d'un reseau connu");
}

//=========================================
//
//          wifiScanNetworks
//
//=========================================
void wifiScanNetworks(void){    // search for availables Wifi Networks
    int nbSsid = WiFi.scanNetworks();
    if (nbSsid != -1){
        Serial.print(nbSsid);
        Serial.println(" wifi networks found");
        strcpy(wifiSsid,"");
        while (strcmp(wifiSsid,"") == 0){        
            for (int ssidNetwork = 0 ; ssidNetwork < nbSsid ; ssidNetwork++){
                Serial.print("  check network : ");
                Serial.print(WiFi.SSID(ssidNetwork));
                if (WiFi.SSID(ssidNetwork) == "NETGEAR17"){
                    strcpy(wifiSsid,"NETGEAR17");
                    strcpy(wifiPassword, "largesea818");
                    Serial.println(" => OK");
                    break;
                }
                if (WiFi.SSID(ssidNetwork) == "Livebox-006d"){
                    strcpy(wifiSsid,"Livebox-006d");
                    strcpy(wifiPassword, "A23F1F7979C9DD3C5916324123");
                    Serial.println(" => OK");
                    break;
                }
                if (WiFi.SSID(ssidNetwork) == "AndroidAPBruno"){
                    strcpy(wifiSsid,"AndroidAPBruno");
                    strcpy(wifiPassword, "0296072588");
                    Serial.println(" => OK");
                    break;
                }
                Serial.println(" => NOK");
            }
            if (strcmp(wifiSsid,"") == 0 || strcmp(wifiSsid,"0.0.0.0") == 0){
                delay(2000);
                Serial.println("No Wifi network found ==> rescan ......");
                nbSsid = WiFi.scanNetworks();
            }
        }
    }
}

//=========================================
//
//          wifiInit
//
//=========================================
void wifiInit(void){    // init wifi connection

    wifiScanNetworks();
    // Connect to WiFi network
    Serial.print("Connecting to ");
    Serial.println(wifiSsid);
    WiFi.begin(wifiSsid, wifiPassword);
    int cpt=0;
    while (WiFi.status() != WL_CONNECTED) {  //Attente de la connexion
        delay(500);
        Serial.print(".");   //Typiquement 5 à 10 points avant la connexion
        if (cpt++ >= 5){
            Serial.println();
            cpt=0;
            WiFi.begin(wifiSsid, wifiPassword);
        }
    }
    Serial.println("");
    Serial.println("WiFi connected");

    // Start the server
    wifiServer.begin();
    wifiServer.println("Server started");

    // Print the IP address
    
    ipAdress = WiFi.localIP().toString();
    Serial.print("Use this URL to connect: ");
    Serial.print("http://");
    Serial.print(ipAdress);
    Serial.println("/");  //Utiliser cette URL sous Firefox de preference à Chrome
}

//=========================================
//
//          wifiStop
//
//=========================================
void wifiStop(void){
    WiFi.disconnect();
    strcpy(wifiSsid,"");
    ipAdress="";
}

//=========================================
//
//          statusWifi
//
//=========================================
void statusWifi(void){
    if (ipAdress != ""){
        Serial.printf("Wifi is connected on %s ; ipAdress = ", wifiSsid);
        Serial.println(ipAdress);
    } else {
        Serial.println("Wifi is disconnected");
    }
}

//=========================================
//
//          rescan 
//
//=========================================
void rescanWifi(void){
    Serial.print("Rescan Wifi Networks => ");
    wifiInit();
}

//=========================================
//
//          analyseWifi
//
//=========================================
void analyseWifi(String commande){
    if (commande.equals("stop")){
        wifiStop();
        Serial.println("Wifi server stoped");
    } else if (commande.equals("start")){
        wifiServer = WiFiServer(80);
        wifiInit();
        Serial.println("Wifi server started");
    } else if (commande.equals("status")){
        statusWifi();
    } else if (commande.equals("rescan")){
        rescanWifi();
    } else {
        Serial.print("ERREUR => <wifi ");
        Serial.print(commande);
        Serial.println("> => commande inconnue");
        wifiHelp();
    }
}

