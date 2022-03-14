#include "AircraftManager.h"
#include "airport.hpp"

void AircraftManager::move()
{
    std::function<bool(std::unique_ptr<Aircraft>&)> p = [](std::unique_ptr<Aircraft>& aircraft) {
        aircraft->move();
        return aircraft->delete_aircraft();
    };

    auto delete_aircraft = std::remove_if(aircrafts.begin(), aircrafts.end(), p);
    aircrafts.erase(delete_aircraft, aircrafts.end());
    /*
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
     */
}
void AircraftManager::add_aircraft(std::unique_ptr<Aircraft> aircraft)
{
    aircrafts.push_back(std::move(aircraft));
}

void AircraftManager::airline_counting(const unsigned int& x) {
    std::function<bool(std::unique_ptr<Aircraft>&)> count = [x](std::unique_ptr<Aircraft>& aircraft) {
        return aircraft->get_indice() == x;
    };
    auto s = std::count_if(aircrafts.begin(), aircrafts.end(), count);
    std::cout << airlines[x] << ":" << s << std::endl;
}