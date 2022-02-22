#define CATCH_CONFIG_MAIN  // This tells Catch to provide a main() - only do this in one cpp file

#include "test/catch.hpp"
#include "typewise-alert.h"

TEST_CASE("infers the breach according to limits") {
  REQUIRE(inferBreach(12, 20, 30) == TOO_LOW);
  REQUIRE(inferBreach(60, 20, 30) == TOO_HIGH);
  REQUIRE(inferBreach(27, 20, 30) == NORMAL);
}


TEST_CASE("infers breach according to cooling type") {
  REQUIRE(classifyTemperatureBreach(PASSIVE_COOLING, -5) == TOO_LOW);
  REQUIRE(classifyTemperatureBreach(PASSIVE_COOLING, 27) == NORMAL);
  REQUIRE(classifyTemperatureBreach(PASSIVE_COOLING, 37) == TOO_HIGH);
  REQUIRE(classifyTemperatureBreach(HI_ACTIVE_COOLING, -5) == TOO_LOW);
  REQUIRE(classifyTemperatureBreach(HI_ACTIVE_COOLING,27) == NORMAL);
  REQUIRE(classifyTemperatureBreach(HI_ACTIVE_COOLING, 47) == TOO_HIGH); 
  REQUIRE(classifyTemperatureBreach(MED_ACTIVE_COOLING, -5) == TOO_LOW);
  REQUIRE(classifyTemperatureBreach(MED_ACTIVE_COOLING, 27) == NORMAL);
  REQUIRE(classifyTemperatureBreach(MED_ACTIVE_COOLING, 42) == TOO_HIGH);
}


TEST_CASE("alerts breachtype") {
  BatteryCharacter batteryChar;
  batteryChar.coolingType =  PASSIVE_COOLING;
  REQUIRE(checkAndAlert(TO_CONTROLLER, batteryChar, 37) == 0);
  //REQUIRE(checkAndAlert(TO_CONTROLLER, batteryChar, 27) == 0);
  //REQUIRE(checkAndAlert(TO_CONTROLLER, batteryChar, -10) == 0);
  
  //REQUIRE(checkAndAlert(TO_EMAIL, batteryChar, 37) == 1);
 // REQUIRE(checkAndAlert(TO_EMAIL, batteryChar, 27) == 1);
 // REQUIRE(checkAndAlert(TO_EMAIL, batteryChar, -10) == 1);
  
  //batteryChar.coolingType =  HI_ACTIVE_COOLING;
  //REQUIRE(checkAndAlert(TO_CONTROLLER, batteryChar, 47) == 0);
 // REQUIRE(checkAndAlert(TO_CONTROLLER, batteryChar, 27) == 0);
 // REQUIRE(checkAndAlert(TO_CONTROLLER, batteryChar, -10) == 0);
  
 // REQUIRE(checkAndAlert(TO_EMAIL, batteryChar, 47) == 1);
 // REQUIRE(checkAndAlert(TO_EMAIL, batteryChar, 27) == 1);
 // REQUIRE(checkAndAlert(TO_EMAIL, batteryChar, -10) == 1);
  
 // batteryChar.coolingType =  MED_ACTIVE_COOLING;
 // REQUIRE(checkAndAlert(TO_CONTROLLER, batteryChar, 42) == 0);
 // REQUIRE(checkAndAlert(TO_CONTROLLER, batteryChar, 27) == 0);
 // REQUIRE(checkAndAlert(TO_CONTROLLER, batteryChar, -10) == 0);
  
 // REQUIRE(checkAndAlert(TO_EMAIL, batteryChar, 42) == 1);
 // REQUIRE(checkAndAlert(TO_EMAIL, batteryChar, 27) == 1);
 // REQUIRE(checkAndAlert(TO_EMAIL, batteryChar, -10) == 1);
  
}
