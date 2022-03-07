#include "AircraftManager.h"
#include "airport.hpp"

void AircraftManager::move()
{
    for (auto item = aircrafts.begin(); item != aircrafts.end();)
    {
        auto& it = **item;
        it.move();
        if (it.delete_aircraft())
        {
            item = aircrafts.erase(item);
        } else {
            item++;
        }
    }
}
void AircraftManager::add_aircraft(std::unique_ptr<Aircraft> aircraft)
{
    aircrafts.push_back(std::move(aircraft));
}