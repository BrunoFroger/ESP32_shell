


#include <Arduino.h>
#include <string.h>

#include "variables.hpp"

#define NB_VARIABLES    10

StructVariableInt lstVariablesInt[NB_VARIABLES];
StructVariableString lstVariablesString[NB_VARIABLES];

char tmp[100];

//=========================================
//
//          variableHelp 
//
//=========================================
void variableHelp(){
    Serial.println("Syntaxe de la commande variable : ");
    Serial.println(" variable new int <nom> <valeur>            => nouvelle variable de type int");
    Serial.println("              String  <nom> <valeur>        => nouvelle variable de type String");
    Serial.println("          show all                          => visualise toutes les variables");
    Serial.println("                   int                      => visualise tous les int");
    Serial.println("                   String                   => visualise tous les string");
    Serial.println("               int <nom>                    => visualise la variable <nom> de type int");
    Serial.println("               string <nom>                 => visualise la variable <nom> de type string");
    Serial.println("          free int <name>                   => detruit la variables <nom> de type int");
    Serial.println("          free string <name>                => detruit la variables <nom> de type string");
}

//=========================================
//
//          creerVariableInt 
//
//=========================================
int creerVariableInt(String nom, int value){
    int index = 0;
    while (lstVariablesInt[index].used){
        if (index++ >= NB_VARIABLES){
            Serial.println("Plus de place disponible pour une nouvelle variable de type Int");
            return -1;
        }
    }
    //sprintf(tmp, "creation d'une variable de type Int (%d) : nom = %s, valeur = %d", index, nom, value);
    //Serial.println(tmp);
    nom.toCharArray(lstVariablesInt[index].nom,50);
    lstVariablesInt[index].value = value;
    lstVariablesInt[index].used = true;
    visualiseVariableInt(nom);
    return 0;
}

//=========================================
//
//          creerVariableString 
//
//=========================================
int creerVariableString(String nom, String value){
    int index = 0;
    while (lstVariablesString[index].used){
        if (index++ > NB_VARIABLES){
            Serial.println("Plus de place disponible pour une nouvelle variable de type String");
            return -1;
        }
    }
    //sprintf(tmp, "creation 1 d'une variable de type String (%d) : nom = %s, valeur = %s", index, nom, value);
    //Serial.println(tmp);
    nom.toCharArray(lstVariablesString[index].nom,50);
    value.toCharArray(tmp,100);
    strcpy(lstVariablesString[index].value,tmp);
    lstVariablesString[index].used = true;
    //sprintf(tmp, "creation 2 d'une variable de type String (%d) : nom = %s, valeur = %s", index, lstVariablesString[index].nom, lstVariablesString[index].value);
    visualiseVariableString(nom);
    return index;
}

//=========================================
//
//          libereVariableInt 
//
//=========================================
int libereVariableInt(String nom){
    for (int index = 0 ; index < NB_VARIABLES ; index++){
        nom.toCharArray(tmp,50);
        if (strcmp(lstVariablesInt[index].nom, tmp) == 0){
            lstVariablesInt[index].used = false;
            return 0;
        } 
    } 
    Serial.print("ERREUR : Variable ");
    Serial.print(nom);
    Serial.println(" n'existe pas");
    return -1;
}

//=========================================
//
//          libereVariableString 
//
//=========================================
int libereVariableString(String nom){
    for (int index = 0 ; index < NB_VARIABLES ; index++){
        nom.toCharArray(tmp,50);
        if (strcmp(lstVariablesString[index].nom, tmp) == 0){
            lstVariablesString[index].used = false;
            return 0;
        } 
    } 
    Serial.print("ERREUR : Variable ");
    Serial.print(nom);
    Serial.println(" n'existe pas");
    return -1;
}

//=========================================
//
//          modifieVariableInt 
//
//=========================================
int modifieVariableInt(String variable, int valeur){
    for (int index = 0 ; index < NB_VARIABLES ; index++){
        variable.toCharArray(tmp,50);
        if (strcmp(lstVariablesInt[index].nom, tmp) == 0){
            lstVariablesInt[index].value = valeur;
            return 0;
        } 
    } 
    Serial.print("ERREUR : Variable ");
    Serial.print(variable);
    Serial.println(" n'existe pas");
    return -1;
}

//=========================================
//
//          modifieVariableString 
//
//=========================================
int modifieVariableString(String variable, String valeur){
    for (int index = 0 ; index < NB_VARIABLES ; index++){
        variable.toCharArray(tmp,50);
        if (strcmp(lstVariablesString[index].nom, tmp) == 0){
            valeur.toCharArray(tmp,50);
            strcpy(lstVariablesString[index].value,tmp);
            return 0;
        } 
    } 
    Serial.print("ERREUR : Variable ");
    Serial.print(variable);
    Serial.println(" n'existe pas");
    return -1;
}

//=========================================
//
//          visualiseVariableInt
//
//=========================================
void visualiseVariableInt(String variable){
    for (int index = 0 ; index < NB_VARIABLES ; index++){
        variable.toCharArray(tmp,50);
        if (strcmp(lstVariablesInt[index].nom, tmp) == 0){
            /*
            Serial.print("visualisation de la variable <");
            Serial.print(variable);
            Serial.print("> = ");
            Serial.print(lstVariablesInt[index].value);
            Serial.println();
            */
            sprintf(tmp,"|  %2d |  oui |  %12s  |  %10d  |",index, lstVariablesInt[index].nom, lstVariablesInt[index].value);
            Serial.println(tmp);
            return;
        } 
    } 
    Serial.print("ERREUR : Variable ");
    Serial.print(variable);
    Serial.println(" n'existe pas");
}

//=========================================
//
//          visualiseVariableString 
//
//=========================================
void visualiseVariableString(String variable){
    for (int index = 0 ; index < NB_VARIABLES ; index++){
        variable.toCharArray(tmp,50);
        if (strcmp(lstVariablesString[index].nom, tmp) == 0){
            sprintf(tmp,"|  %2d |  oui |  %12s  |  %10s  |",index, lstVariablesString[index].nom, lstVariablesString[index].value);
            Serial.println(tmp);
            return;
        } 
    } 
    Serial.print("ERREUR : Variable ");
    Serial.print(variable);
    Serial.println(" n'existe pas");
}

//=========================================
//
//          visualiseAllVariableInt 
//
//=========================================
void visualiseAllVariableInt(void){
    Serial.println("+--------------------------------------------+");
    Serial.println("|        Variable de type Int                |");
    Serial.println("+-----+------+----------------+--------------+");
    Serial.println("| idx | used |    Nom         |  Valeur      |");
    Serial.println("+-----+------+----------------+--------------+");
    for (int index = 0 ; index < NB_VARIABLES ; index++){
        if (lstVariablesInt[index].used){
            sprintf(tmp,"|  %2d |  oui |  %12s  |  %10s  |",index, lstVariablesInt[index].nom, lstVariablesInt[index].value);
        } else {
            sprintf(tmp,"|  %2d |  non |  %12s  |  %10s  |",index, "", "");
        }
        Serial.println(tmp);
    } 
    Serial.println("+-----+------+----------------+--------------+");
    Serial.println();
}

//=========================================
//
//          visualiseAllVariableString 
//
//=========================================
void visualiseAllVariableString(void){
    Serial.println("+--------------------------------------------+");
    Serial.println("|        Variable de type String             |");
    Serial.println("+-----+------+----------------+--------------+");
    Serial.println("| idx | used |    Nom         |  Valeur      |");
    Serial.println("+-----+------+----------------+--------------+");
    for (int index = 0 ; index < NB_VARIABLES ; index++){
        if (lstVariablesString[index].used){
            sprintf(tmp,"|  %2d |  oui |  %12s  |  %10s  |",index, lstVariablesString[index].nom, lstVariablesString[index].value);
        } else {
            sprintf(tmp,"|  %2d |  non |  %12s  |  %10s  |",index, "", "");
        }
        Serial.println(tmp);
    } 
    Serial.println("+-----+------+----------------+--------------+");
    Serial.println();
}

//=========================================
//
//          analyseCreationVariable 
//
//=========================================
void analyseCreationVariable(String cde){
    String typeVariable="";
    String nomVariable="";
    String valeurVariable="";
    String subCommand="";
    int index;

    /*
    Serial.print("Creation d'une variable <");
    Serial.print(cde);
    Serial.print(">");
    Serial.println();
    */

    index = cde.indexOf(' ');
    if (index != -1){
        typeVariable = cde.substring(0,index);
        subCommand = cde.substring(index+1,cde.length());
    }
    /*
    Serial.print("type : <");
    Serial.print(typeVariable);
    Serial.println(">");
    */
    cde=subCommand;

    index = cde.indexOf(' ');
    subCommand="";
    if (index != -1){
        nomVariable = cde.substring(0,index);
        subCommand = cde.substring(index+1,cde.length());
    }
    /*
    Serial.print("Nom : <");
    Serial.print(nomVariable);
    Serial.println(">");
    */
    cde=subCommand;

    valeurVariable = subCommand;
    /*
    Serial.print("Valeur : <");
    Serial.print(valeurVariable);
    Serial.println(">");
    */
    if (typeVariable.equals("int")){
        creerVariableInt(nomVariable,valeurVariable.toInt());
    } else if (typeVariable.equals("string")){
        creerVariableString(nomVariable,valeurVariable);
    } else {
        Serial.println("ERREUR : erreur de syntaxe");
        variableHelp();
    }
}

//=========================================
//
//          analyseSuppressionVariable 
//
//=========================================
void analyseSuppressionVariable(String cde){
    String typeVariable="";
    String nomVariable="";
    String valeurVariable="";
    String subCommand="";
    int index;

    /*
    Serial.print("suppression d'une variable <");
    Serial.print(cde);
    Serial.print(">");
    Serial.println();
    */

    index = cde.indexOf(' ');
    if (index != -1){
        typeVariable = cde.substring(0,index);
        subCommand = cde.substring(index+1,cde.length());
    }
    /*
    Serial.print("type : <");
    Serial.print(typeVariable);
    Serial.println(">");
    */
    cde=subCommand;

    index = cde.indexOf(' ');
    subCommand="";
    if (index != -1){
        nomVariable = cde.substring(0,index);
        subCommand = cde.substring(index+1,cde.length());
    } else {
        nomVariable=cde;
    }

    /*
    Serial.print("Nom : <");
    Serial.print(nomVariable);
    Serial.println(">");
    */

    cde=subCommand;

    if (typeVariable.equals("int")){
        libereVariableInt(nomVariable);
    } else if (typeVariable.equals("string")){
        libereVariableString(nomVariable);
    } else {
        Serial.println("ERREUR : erreur de syntaxe");
        variableHelp();
    }
}

//=========================================
//
//          analyseVisualisationVariable 
//
//=========================================
void analyseVisualisationVariable(String cde){
    String param1="";
    String param2="";
    String param3="";
    String subCommand="";
    int index;

    /*
    Serial.print("visualisation de variable(s) <");
    Serial.print(cde);
    Serial.print(">");
    Serial.println();
    */

    index = cde.indexOf(' ');
    if (index != -1){
        param1 = cde.substring(0,index);
        subCommand = cde.substring(index+1,cde.length());
    } else {
        param1=cde;
    }
    /*
    Serial.print("param1 : <");
    Serial.print(param1);
    Serial.println(">");
    */
    cde=subCommand;
    

    index = cde.indexOf(' ');
    subCommand="";
    if (index != -1){
        param2 = cde.substring(0,index);
        subCommand = cde.substring(index+1,cde.length());
    } else {
        param2=cde;
    }

    /*
    Serial.print("param2 : <");
    Serial.print(param2);
    Serial.println(">");
    */
    cde=subCommand;

    param3=cde;
    /*
    Serial.print("param3 : <");
    Serial.print(param3);
    Serial.println(">");
    */
    if (param1.equals("all")){
        if (param2.equals("int")){
            visualiseAllVariableInt();
        } else if (param2.equals("string")){
            visualiseAllVariableString();
        } else if (param2.equals("")){
            visualiseAllVariableInt();
            visualiseAllVariableString();
        } else {
            Serial.println("ERREUR : syntaxe incorrecte");
            variableHelp();
        }
    } else if(param1.equals("int")){
        visualiseVariableInt(param2);
    } else if(param1.equals("string")){
        visualiseVariableString(param2);
    } else {
        Serial.println("ERREUR : erreur de syntaxe");
        variableHelp();
    }
}


//=========================================
//
//          analyseSet 
//
//=========================================
void analyseVariable(String cde){
    int index = cde.indexOf(' ');
    String subCommand = cde.substring(index+1,cde.length());

    //Serial.print("variable commande => <");
    //Serial.print(cde);
    //Serial.print(">");
    //Serial.println();
    
    if (cde.equals("")){
        Serial.println("Pas de parametres => display all");
        visualiseAllVariableInt();
        visualiseAllVariableString();
    } else if (cde.startsWith("new ")){
        Serial.print("creation d'une nouvelle variable");
        Serial.println();
        analyseCreationVariable(cde.substring(4,cde.length()));
    } else if (cde.startsWith("free ")){
        Serial.print("suppresssion d'une variable");
        Serial.println();
        analyseSuppressionVariable(cde.substring(5,cde.length()));
    } else if (cde.startsWith("show ")){
        Serial.print("visualisation de variable(s)");
        Serial.println();
        analyseVisualisationVariable(cde.substring(5,cde.length()));
    } else {
        Serial.print("ERREUR => <variable ");
        Serial.print(cde);
        Serial.println("> => commande inconnue");
        variableHelp();
    }
}
