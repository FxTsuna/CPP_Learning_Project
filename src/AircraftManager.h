#pragma once

#include <vector>
#include <memory>
#include "aircraft.hpp"

class AircraftManager : public GL::DynamicObject
{
private:
    std::vector<std::unique_ptr<Aircraft>> aircrafts;

public:
    void move() override;
    void add_aircraft(std::unique_ptr<Aircraft> aircraft);
};

