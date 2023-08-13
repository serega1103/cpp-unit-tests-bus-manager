#include <cassert>
#include <iostream>
#include <sstream>
#include <map>
#include <string>
#include <vector>

using namespace std;

// Типы запросов
enum class QueryType {
    NewBus,
    BusesForStop,
    StopsForBus,
    AllBuses,
};

// Запрос
struct Query {
    QueryType type;
    string bus;
    string stop;
    vector<string> stops;
};

// Ввод запроса
istream& operator>>(istream& is, Query& query) {
    // Тип
    string type;
    is >> type;

    // ТИПЫ ЗАПРОСОВ
    // Добавление автобуса
    if (type == "NEW_BUS"s) {
        // Тип запроса
        query.type = QueryType::NewBus;
        // Автобус
        is >> query.bus;
        // Количество остановок
        int stop_count;
        is >> stop_count;

        // Ввод остановок
        query.stops.resize(stop_count);
        for (string& stop : query.stops) {
            is >> stop;
        }

    // Автобусы на конкретной остановке
    } else if (type == "BUSES_FOR_STOP"s) {
        // Тип запроса
        query.type = QueryType::BusesForStop;
        // Остановка
        is >> query.stop;
        
    // Остановки автобуса
    } else if (type == "STOPS_FOR_BUS"s) {
        // Тип запроса
        query.type = QueryType::StopsForBus;
        // Автобус
        is >> query.bus;

    // Все автобусы
    } else if (type == "ALL_BUSES"s) {
        // Тип запроса
        query.type = QueryType::AllBuses;
    }
    
    return is;
}

// Автобусы на конкретной остановке
struct BusesForStopResponse {
    // Остановка
    string stop = ""s;
    // Автобусы
    vector<string> buses;
};

// Вывод автобусов на конкретной остановке
ostream& operator<<(ostream& os, const BusesForStopResponse& r) {
    // Реализуйте эту функцию
    return os;
}


// Остановки автобуса
struct StopsForBusResponse {
    // Автобус
    string bus = ""s;
    // Остановки
    vector<string> stops;
};

// Вывод остановок автобуса
ostream& operator<<(ostream& os, const StopsForBusResponse& r) {
    // Реализуйте эту функцию
    return os;
}


// Все автобусы
struct AllBusesResponse {
    // Автобусы и их остановки
    map<string, vector<string>> buses_to_stops;
};

// Вывод всех автобусов
ostream& operator<<(ostream& os, const AllBusesResponse& r) {
    // Если автобусов нет
    if (r.buses_to_stops.empty()) {
        os << "No buses"s << endl;
    } 
    else {
        // Проход по автобусам
        for (const auto& [bus, stops] : r.buses_to_stops) {
            // Вывод автобуса
            os << "Bus "s << bus << ":"s;
            // Проход по остановкам автобуса
            for (const string& stop : stops) {
                // Вывод остановки
                os << " "s << stop;
            }
            os << endl;
        }
    }
    return os;
}

class BusManager {
public:
    // Добавление автобуса
    void AddBus(const string& bus, const vector<string>& stops) {
        // Автобус и его остановки
        buses_to_stops[bus] = stops;
        // Остановки с этим автобусом
        for (const string& stop : stops) {
            stops_to_buses[stop].push_back(bus);
        }
    }

    // Автобусы на конкретной остановке
    BusesForStopResponse GetBusesForStop(const string& stop) const {
        // Если есть автобусы для остановки
        if (stops_to_buses.count(stop) != 0) {
            return BusesForStopResponse({stop, stops_to_buses.at(stop)});
        } 
        return BusesForStopResponse({stop, vector<string>(0)});
    }

    // Остановки автобуса
    StopsForBusResponse GetStopsForBus(const string& bus) const {
        if (buses_to_stops.count(bus) != 0) {
            for (const string& stop : buses_to_stops.at(bus)) {
                cout << "Stop "s << stop << ": "s;
                if (stops_to_buses.at(stop).size() == 1) {
                    cout << "no interchange"s;
                } else {
                    for (const string& other_bus : stops_to_buses.at(stop)) {
                        if (bus != other_bus) {
                            cout << other_bus << " "s;
                        }
                    }
                }
                cout << endl;
            }
        } 
        return StopsForBusResponse({bus, vector<string>(0)});
    }

    // Все автобусы
    AllBusesResponse GetAllBuses() const {
        return AllBusesResponse({buses_to_stops});
    }
private:
    // Автобусы в остановки
    map<string, vector<string>> buses_to_stops;
    // Остановки в автобусы
    map<string, vector<string>> stops_to_buses;
};

// Тест запросов
void TestQueries() {
    // Запрос
    Query query;

    // Ввод
    istringstream input;

    // Добавление автобуса
    input.str("NEW_BUS 32 3 Tolstopaltsevo Marushkino Vnukovo"s);
    // Ввод запроса
    input >> query;
    // Тип запроса
    assert(query.type == QueryType::NewBus);
    // Автобус
    assert(query.bus == "32"s);
    // Остановки
    string stops;
    for (const string& stop : query.stops) {
        stops += stop;
        stops += " "s;
    }
    assert(stops == "Tolstopaltsevo Marushkino Vnukovo "s);
    input.clear();

    // Автобусы на конкретной остановке
    input.str("BUSES_FOR_STOP Vnukovo"s);
    // Ввод запроса
    input >> query;
    // Тип запроса
    assert(query.type == QueryType::BusesForStop);
    // Остановка
    assert(query.stop == "Vnukovo"s);
    input.clear();

    // Остановки автобуса
    input.str("STOPS_FOR_BUS 32K"s);
    // Ввод запроса
    input >> query;
    // Тип запроса
    assert(query.type == QueryType::StopsForBus);
    // Автобус
    assert(query.bus == "32K"s);
    input.clear();

    // Все автобусы
    input.str("ALL_BUSES"s);
    // Ввод запроса
    input >> query;
    // Тип запроса
    assert(query.type == QueryType::AllBuses);
    input.clear();

    cout << "Test Queries is OK" << endl;
}

int main() {
    // Тест запросов
    TestQueries();

    // Менеджер автобусов
    BusManager bus_manager;

    // Количество запросов
    int query_count;
    cout << "Query count input: ";
    cin >> query_count;

    // Запрос
    Query query;
    for (int i = 0; i < query_count; ++i) {
        // Ввод запроса
        cout << "Query input: ";
        cin >> query;
        cout << endl;

        switch (query.type) {
            case QueryType::NewBus:
                bus_manager.AddBus(query.bus, query.stops);
                break;
            case QueryType::BusesForStop:
                cout << bus_manager.GetBusesForStop(query.stop) << endl;
                break;
            case QueryType::StopsForBus:
                cout << bus_manager.GetStopsForBus(query.bus) << endl;
                break;
            case QueryType::AllBuses:
                cout << bus_manager.GetAllBuses() << endl;
                break;
        }
    }
}