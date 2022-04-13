#pragma once

#include <vector>
#include <memory>
#include "aircraft.hpp"

class aircraftManager : public GL::DynamicObject
{
private:
    std::vector<std::unique_ptr<Aircraft>> aircrafts;
    int compteurCrash = 0;

public:
    void move() override;
    void add_aircraft(std::unique_ptr<Aircraft> aircraft);
    int airline_counting(const std::string_view& x);
    unsigned int get_required_fuel() const;
    int get_compteur_crash() const { return compteurCrash; }
};

