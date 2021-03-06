#pragma once

typedef enum {
  PASSIVE_COOLING,
  HI_ACTIVE_COOLING,
  MED_ACTIVE_COOLING
} CoolingType;

#define NO_COOLING_TYPES 3 //Passive,HI active and MED active

#define PASSIVE_COOLING_MIN_LIMIT 0
#define PASSIVE_COOLING_MAX_LIMIT 35
#define HI_ACTIVE_COOLING_MIN_LIMIT 0
#define HI_ACTIVE_COOLING_MAX_LIMIT 45
#define MED_ACTIVE_COOLING_MIN_LIMIT 0
#define MED_ACTIVE_COOLING_MAX_LIMIT 40

typedef struct{
  double Min_Limit;
  double Max_Limit;
} Limits;

typedef enum {
  NORMAL,
  TOO_LOW,
  TOO_HIGH
} BreachType;

#define NO_BREACH_TYPES 3

BreachType inferBreach(double value, double lowerLimit, double upperLimit);
BreachType classifyTemperatureBreach(CoolingType coolingType, double temperatureInC);

typedef enum {
  TO_CONTROLLER,
  TO_EMAIL
} AlertTarget;

typedef struct {
  CoolingType coolingType;
  char brand[48];
} BatteryCharacter;

int checkAndAlert(AlertTarget alertTarget, BatteryCharacter batteryChar, double temperatureInC);

int sendToController(BreachType breachType , void (*FnPtrPrinter) (char *message) );
int sendToEmail(BreachType breachType ,void (*FnPtrPrinter) (char *message) ) ;
void PrintOnConsole(char *message);
