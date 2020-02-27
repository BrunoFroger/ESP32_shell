

#include <Arduino.h>

#ifndef __AFFICHEUR
#define __AFFICHEUR

extern void afficheInit(void);
extern void afficheTexte(int ligne, int colonne, String texte);
extern void afficheClear(void);
extern void afficheurHelp(void);
extern void analyseAfficheur(String commande);

#endif