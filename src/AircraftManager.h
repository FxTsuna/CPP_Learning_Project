#pragma once

#include <vector>
#include <memory>
#include "aircraft.hpp"
#include "AircraftFactory.h"

class AircraftManager : public GL::DynamicObject
{
private:
    std::vector<std::unique_ptr<Aircraft>> aircrafts;
    const std::string airlines[8] = { "AF", "LH", "EY", "DL", "KL", "BA", "AY", "EY" };

public:
    void move() override;
    void add_aircraft(std::unique_ptr<Aircraft> aircraft);
    void airline_counting(const unsigned int& x);
};

