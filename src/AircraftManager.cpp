#include "AircraftManager.hpp"

void AircraftManager::move()
{
    std::sort(aircrafts.begin(), aircrafts.end(), [](const std::unique_ptr<Aircraft>& first, const std::unique_ptr<Aircraft>& second) {
                  assert(first != nullptr && second != nullptr);
                  if (second->has_terminal())
                      return false;
                  if (first->has_terminal())
                      return true;
                  return (first->get_fuel() < second->get_fuel());
              });

    std::function<bool(std::unique_ptr<Aircraft>&)> p = [this](const std::unique_ptr<Aircraft>& aircraft){
        assert(aircraft != nullptr);
        try {
            aircraft->move();
        } catch (const AircraftCrash& crash) {
            compteurCrash++;
            std::cerr << "Aircraft crash : " << crash.what() << std::endl;
        }
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
    assert(aircraft != nullptr);
    aircrafts.push_back(std::move(aircraft));
}

int AircraftManager::airline_counting(const std::string_view& x) {
    assert(!x.empty());
    return std::count_if(aircrafts.begin(), aircrafts.end(),
                         [x](const std::unique_ptr<Aircraft>& aircraft_it)
                         { return x == aircraft_it->get_flight_num().substr(0, 2); });
}

float AircraftManager::get_required_fuel() const
{
    return std::accumulate(aircrafts.begin(), aircrafts.end(), 0., [](float accumulate, const std::unique_ptr<Aircraft>& aircraft)
                           {
                               assert(aircraft != nullptr);
                               if (aircraft->is_on_ground() && aircraft->is_low_on_fuel())
                               {
                                   return accumulate + aircraft->missing_fuel_to_max();
                               }
                               return accumulate;
                           });
}