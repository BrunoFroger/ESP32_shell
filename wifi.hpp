





#ifndef __WIFISHELL
#define __WIFISHELL

#include <Arduino.h>
#include <WiFi.h>


extern String ipAdress;
extern char *wifiSsid;
extern char *wifiPassword;
extern WiFiClient wifiClient;
extern WiFiServer wifiServer;

extern void initWifi(void);
extern void stopWifi(void);
extern void statusWifi(void);
extern void analyseWifi(String commande);
extern void wifiHelp(void);
extern void rescanWifi(void);

#endif
