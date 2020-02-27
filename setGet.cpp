


#include "commandes.hpp"


//=========================================
//
//          variableHelp 
//
//=========================================
void setGetHelp(){
    Serial.println("Syntaxe des commandes set / get : ");
    Serial.println(" set analog <numPin> <valeur>           => set valeur sur broche numPin");
    Serial.println("     digital <numPin> <valeur>          => set valeur sur broche numPin");
    Serial.println(" get analog <numPin>                    => get valeur sur broche numPin");
    Serial.println("     digital <numPin>                   => get valeur sur broche numPin");
}

//=========================================
//
//          analyseGet 
//
//=========================================
void analyseGet(String cde){
    int index = cde.indexOf(' ');
    String subCommand= cde.substring(index+1,cde.length());
    int numPin=subCommand.toInt();
    int valeur;
    if (cde.startsWith("analog ")){
        Serial.print("Valeur entree analogique n° <");
        Serial.print(numPin);
        Serial.print("> = ");
        Serial.print(analogRead(numPin));
        Serial.println();
    } else if (cde.startsWith("digital ")){
        Serial.print("Valeur entree digitale n° ");
        Serial.print(numPin);
        Serial.print(" = ");
        pinMode(numPin,INPUT);
        Serial.print(digitalRead(numPin));
        Serial.println();
    } else {
        Serial.print("ERREUR => <get ");
        Serial.print(cde);
        Serial.println("> => commande inconnue");
        afficheurHelp();
    }
}

//=========================================
//
//          analyseSet 
//
//=========================================
void analyseSet(String cde){
    int index = cde.indexOf(' ');
    int valeur = 0;
    int numPin = 0;
    String subCommand= cde.substring(index+1,cde.length());
    Serial.print("subCommand = ");
    Serial.println(subCommand);
    index = subCommand.indexOf(' ');
    numPin = subCommand.substring(0,index).toInt();
    Serial.print("numPin = ");
    Serial.println(numPin);
    valeur = subCommand.substring(index+1,subCommand.length()).toInt();
    if (cde.startsWith("analog ")){
        Serial.print("Ecriture sur entree analogique n° <");
        Serial.print(numPin);
        Serial.print("> = ");
        Serial.print(valeur);
        //analogWrite(numPin, valeur);
        Serial.println();
    } else if (cde.startsWith("digital ")){
        Serial.print("Ecriture sur entree digitale n° ");
        Serial.print(numPin);
        Serial.print(" = ");
        Serial.print(valeur);
        pinMode(numPin,OUTPUT);
        digitalWrite(numPin, valeur);
        Serial.println();
    } else {
        Serial.print("ERREUR => <set ");
        Serial.print(cde);
        Serial.println("> => commande inconnue");
        setGetHelp();
    }
}
