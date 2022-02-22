#define CATCH_CONFIG_MAIN  // This tells Catch to provide a main() - only do this in one cpp file

#include "test/catch.hpp"
#include "typewise-alert.h"

TEST_CASE("infers the breach according to limits") {
  REQUIRE(inferBreach(12, 20, 30) == TOO_LOW);
  REQUIRE(inferBreach(60, 20, 30) == TOO_HIGH);
  REQUIRE(inferBreach(27, 20, 30) == NORMAL);
}


TEST_CASE("infers breach according to cooling type") {
  Limits TempLimit[NO_COOLING_TYPES]= {{PASSIVE_COOLING_MIN_LIMIT,PASSIVE_COOLING_MAX_LIMIT},
                                 {HI_ACTIVE_COOLING_MIN_LIMIT,HI_ACTIVE_COOLING_MAX_LIMIT},
                                 {MED_ACTIVE_COOLING_MIN_LIMIT,MED_ACTIVE_COOLING_MAX_LIMIT}};
  
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
