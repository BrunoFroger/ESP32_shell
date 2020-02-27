

#ifndef __VARIABLES
#define __VARIABLES

#include <Arduino.h>

typedef struct {
    boolean used;
    char nom[50];
    char value[50];
} StructVariableString;


typedef struct {
    boolean used;
    char nom[50];
    int value;
} StructVariableInt;


extern int creerVariableInt(String nom, int value);
extern int creerVariableString(String nom, String value);

extern int libereVariableInt(String nom);
extern int libereVariableString(String nom);

extern int modifieVariableInt(String variable, int valeur);
extern int modifieVariableString(String variable, String valeur);

extern void visualiseVariableInt(String variable);
extern void visualiseVariableString(String variable);

extern void visualiseAllVariableInt(void);
extern void visualiseAllVariableString(void);

extern void analyseVariable(String commande);
extern void variableHelp(void);

#endif
