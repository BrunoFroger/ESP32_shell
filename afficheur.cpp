

#include <Arduino.h>
#include <LiquidCrystal_I2C_esp32.h>

// set the LCD number of columns and rows
int lcdColumns = 16;
int lcdRows = 2;

// set LCD address, number of columns and rows
// if you don't know your display address, run an I2C scanner sketch
LiquidCrystal_I2C lcd(0x27, lcdColumns, lcdRows);  
//LiquidCrystal_I2C lcd(0x27, lcdColumns, lcdRows);  

//=========================================
//
//          afficheurHelp 
//
//=========================================
void afficheurHelp(){
    Serial.println("Syntaxe de la commande affiche : ");
    Serial.println(" affiche init                       => initialise l'afficheur");
    Serial.println("         clear                      => efface l'afficheur");
    Serial.println("         <col> <lig> <message>      => affiche <message> sur la ligne <lig> en colonne <col>");
}

//=========================================
//
//          afficheClear 
//
//=========================================
void afficheClear(void){
    lcd.clear();
}

//=========================================
//
//          afficheInit 
//
//=========================================
void afficheInit(void){
    lcd.init();
    lcd.setBacklight(HIGH); 
    lcd.clear();
}

//=========================================
//
//          afficheTexte 
//
//=========================================
void afficheTexte(int colonne, int ligne, String texte){
    if (colonne >= lcdColumns){
        Serial.println("ERREUR : affichage en dehors de l'ecran (colonne)");
        return;
    }
    if (ligne >= lcdRows){
        Serial.println("ERREUR : affichage en dehors de l'ecran (ligne)");
        return;
    }
    lcd.setCursor(colonne,ligne);
    //Serial.print("Afficheur : ");
    //Serial.println(texte);
    lcd.print(texte);
}

//=========================================
//
//          analyseAfficheur 
//
//=========================================
void analyseAfficheur(String commande){
    String param1="";
    String param2="";
    String param3="";
    String subCommand="";
    int index;

    String cde = commande;

    index = cde.indexOf(' ');
    if (index != -1){
        param1 = cde.substring(0,index);
        subCommand = cde.substring(index+1,cde.length());
    } else {
        param1=cde;
    }
    cde=subCommand;

    index = cde.indexOf(' ');
    subCommand="";
    if (index != -1){
        param2 = cde.substring(0,index);
        subCommand = cde.substring(index+1,cde.length());
    } else {
        param2=cde;
    }
    cde=subCommand;

    param3=cde;

    if (param1.equals("help")){
        afficheurHelp();
    } else if (param1.equals("init")){
        afficheInit();
    } else if (param1.equals("clear")){
        afficheClear();
    } else if (param3.length() > 0){
        afficheTexte(param2.toInt(), param1.toInt(), param3);
    } else {
        Serial.print("ERREUR => <affiche ");
        Serial.print(commande);
        Serial.println("> => commande inconnue");
        afficheurHelp();
    }
}