#include "typewise-alert.h"
#include <stdio.h>
#include <string.h>

Limits TempLimit[NO_COOLING_TYPES]= {{PASSIVE_COOLING_MIN_LIMIT,PASSIVE_COOLING_MAX_LIMIT},
                                 {HI_ACTIVE_COOLING_MIN_LIMIT,HI_ACTIVE_COOLING_MAX_LIMIT},
                                 {MED_ACTIVE_COOLING_MIN_LIMIT,MED_ACTIVE_COOLING_MAX_LIMIT}};

char AlertMessage[NO_BREACH_TYPES][50] = {"","HI, Temperature is Too Low!!!" ,"Hi, Temperature is Too High!!!" };

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
  sprintf(PrintMessage,"To : %s\n  %s\n", recepientEmail, AlertMessage[breachType]);
  FnPtrPrinter(PrintMessage);
}
