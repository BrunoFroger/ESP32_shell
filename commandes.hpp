

#include <Arduino.h>

#ifndef __COMMANDES
#define __COMMANDES

#include "help.hpp"
#include "setGet.hpp"
#include "wifi.hpp"
#include "afficheur.hpp"
#include "variables.hpp"

#define NB_COMMANDES 10
extern String ListeCommandes[NB_COMMANDES];

extern void analyseCommande(String commande);

#endif
