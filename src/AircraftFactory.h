#pragma once

#include "airport.hpp"
#include "AircraftManager.h"

class AircraftFactory
{
private:
    const std::string airlines[8] = { "AF", "LH", "EY", "DL", "KL", "BA", "AY", "EY" };
    AircraftType* aircraftType[NUM_AIRCRAFT_TYPES] {};
    std::unique_ptr<Aircraft> create_aircraft(const AircraftType& type, Airport* airport);
    std::set<std::string> setAircrafts;
    void init_aircraft_types();

public:
    AircraftFactory()
    {
        init_aircraft_types();
    }
    std::unique_ptr<Aircraft> create_random_aircraft(Airport* airport);
    void add_flight_number(const std::string& str);
    std::set<std::string> getAircraftsSet() {return  setAircrafts;}
};

