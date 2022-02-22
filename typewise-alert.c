#include "typewise-alert.h"
#include <stdio.h>
#include <string.h>

BreachType inferBreach(double value, double lowerLimit, double upperLimit) {
  if(value < lowerLimit) {
    return TOO_LOW;
  }
  if(value > upperLimit) {
    return TOO_HIGH;
  }
  return NORMAL;
}

BreachType classifyTemperatureBreach(CoolingType coolingType, double temperatureInC) {
  int lowerLimit = TempLimit[coolingType].Min_Limit;
  int upperLimit = TempLimit[coolingType].Max_Limit;
  return inferBreach(temperatureInC, lowerLimit, upperLimit);
}

void PrintOnConsole(char *message){
  printf(" %s!\n", message); 
  return;
}

void checkAndAlert(AlertTarget alertTarget, BatteryCharacter batteryChar, double temperatureInC) {
  BreachType breachType = classifyTemperatureBreach(batteryChar.coolingType, temperatureInC);
  void (*FnPtrPrinter) (char *message) ;
  FnPtrPrinter = &PrintOnConsole;
  switch(alertTarget) {
    case TO_CONTROLLER:
      sendToController(breachType, FnPtrPrinter);
      break;
    case TO_EMAIL:
      sendToEmail(breachType , FnPtrPrinter);
      break;
  }
}

void sendToController(BreachType breachType,void (*FnPtrPrinter) (char *message)) {
  const unsigned short header = 0xfeed;
  char *PrintMessage;
  sprintf(PrintMessage,"%x : %x\n", header, breachType);
  FnPtrPrinter(PrintMessage);
}

void sendToEmail(BreachType breachType , void (*FnPtrPrinter) (char *message) ) {
  const char *recepientEmail = "a.b@c.com";
  char *PrintMessage;
  sprintf(PrintMessage,"To : %s\n", recepientEmail);
  FnPtrPrinter(PrintMessage);
}
