#include "tower_sim.hpp"

#include "GL/opengl_interface.hpp"
#include "aircraft.hpp"
#include "airport.hpp"
#include "config.hpp"
#include "img/image.hpp"
#include "img/media_path.hpp"

using namespace std::string_literals;

TowerSimulation::~TowerSimulation()
{
    delete airport;
}

void TowerSimulation::create_aircraft()
{
    std::unique_ptr<Aircraft> aircraft = aircraft_factory.create_random_aircraft(airport);
    auto aircraftSet = aircraft_factory.getAircraftsSet();
    if (aircraftSet.find(aircraft->get_flight_num()) != aircraftSet.end())
    {
        std::cout << "Aircraft already created" << std::endl;
        return;
    }
    aircraft_factory.add_flight_number(aircraft->get_flight_num());
    aircraft_manager.add_aircraft(std::move(aircraft));
}

void TowerSimulation::create_keystrokes()
{
    GL::keystrokes.emplace('x', []() { GL::exit_loop(); });
    GL::keystrokes.emplace('q', []() { GL::exit_loop(); });
    GL::keystrokes.emplace('c', [this]() { create_aircraft(); });
    GL::keystrokes.emplace('+', []() { GL::change_zoom(0.95f); });
    GL::keystrokes.emplace('-', []() { GL::change_zoom(1.05f); });
    GL::keystrokes.emplace('f', []() { GL::toggle_fullscreen(); });
    GL::keystrokes.emplace('i', []() { GL::increase_framerate();});
    GL::keystrokes.emplace('d', []() { GL::decrease_framerate();});
    GL::keystrokes.emplace('p', []() { GL::stop_framerate(); });
    GL::keystrokes.emplace('m', [this]() { std::cout << "Nombre de crash :" << aircraft_manager.get_compteur_crash() << std::endl; });
    GL::keystrokes.emplace('0', [this]() { std::cout << "AF :" << aircraft_manager.airline_counting(aircraft_factory.get_airlines(0)) << std::endl;});
    GL::keystrokes.emplace('1', [this]() { std::cout << "LH :" << aircraft_manager.airline_counting(aircraft_factory.get_airlines(1)) << std::endl;});
    GL::keystrokes.emplace('2', [this]() { std::cout << "EY :" << aircraft_manager.airline_counting(aircraft_factory.get_airlines(2)) << std::endl;});
    GL::keystrokes.emplace('3', [this]() { std::cout << "DL :" << aircraft_manager.airline_counting(aircraft_factory.get_airlines(3)) << std::endl;});
    GL::keystrokes.emplace('4', [this]() { std::cout << "KL :" << aircraft_manager.airline_counting(aircraft_factory.get_airlines(4)) << std::endl;});
    GL::keystrokes.emplace('5', [this]() { std::cout << "BA :" << aircraft_manager.airline_counting(aircraft_factory.get_airlines(5)) << std::endl;});
    GL::keystrokes.emplace('6', [this]() { std::cout << "AY :" << aircraft_manager.airline_counting(aircraft_factory.get_airlines(6)) << std::endl;});
    GL::keystrokes.emplace('7', [this]() { std::cout << "EY :" << aircraft_manager.airline_counting(aircraft_factory.get_airlines(7)) << std::endl;});
}

void TowerSimulation::display_help() const
{
    std::cout << "This is an airport tower simulator" << std::endl
              << "the following keysstrokes have meaning:" << std::endl;

    for (const auto& [first, second] : GL::keystrokes)
    {
        std::cout << first << ' ';
    }

    std::cout << std::endl;
}

void TowerSimulation::init_airport()
{
    airport = new Airport { one_lane_airport, Point3D { 0, 0, 0 },
                            new img::Image { one_lane_airport_sprite_path.get_full_path() }, aircraft_manager };

    GL::move_queue.emplace(airport);
}

void TowerSimulation::init_aircraftManager()
{
    GL::move_queue.emplace(&aircraft_manager);
}

void TowerSimulation::launch()
{
    if (help)
    {
        display_help();
        return;
    }

    init_airport();
    init_aircraftManager();
    assert(airport != nullptr);
    GL::loop();
}