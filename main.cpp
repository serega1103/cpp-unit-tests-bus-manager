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
istream& operator>>(istream& is, Query& q) {
    // Тип
    string type;
    is >> type;

    // ТИПЫ ЗАПРОСОВ
    // Добавление автобуса
    if (type == "NEW_BUS"s) {
        // Тип запроса
        q.type = QueryType::NewBus;

        // Автобус
        string bus;
        cin >> q.bus;

        // Количество остановок
        int stop_count;
        cin >> stop_count;

        // Ввод остановок
        q.stops.resize(stop_count);
        for (string& stop : q.stops) {
            cin >> stop;
        }

    // Автобусы на конкретной остановке
    } else if (type == "BUSES_FOR_STOP"s) {
        // Тип запроса
        q.type = QueryType::BusesForStop;

        // Остановка
        string stop;
        cin >> q.stop;
        
    // Остановки автобуса
    } else if (type == "STOPS_FOR_BUS"s) {
        // Тип запроса
        q.type = QueryType::StopsForBus;

        string bus;
        cin >> q.bus;

    // Все автобусы
    } else if (type == "ALL_BUSES"s) {
        // Тип запроса
        q.type = QueryType::AllBuses;
    }
    
    return is;
}

struct BusesForStopResponse {
    // Наполните полями эту структуру
};

ostream& operator<<(ostream& os, const BusesForStopResponse& r) {
    // Реализуйте эту функцию
    return os;
}

struct StopsForBusResponse {
    // Наполните полями эту структуру
};

ostream& operator<<(ostream& os, const StopsForBusResponse& r) {
    // Реализуйте эту функцию
    return os;
}

struct AllBusesResponse {
    // Наполните полями эту структуру
};

ostream& operator<<(ostream& os, const AllBusesResponse& r) {
    // Реализуйте эту функцию
    return os;
}

class BusManager {
public:
    void AddBus(const string& bus, const vector<string>& stops) {
        // Реализуйте этот метод
    }

    BusesForStopResponse GetBusesForStop(const string& stop) const {
        // Реализуйте этот метод
    }

    StopsForBusResponse GetStopsForBus(const string& bus) const {
        // Реализуйте этот метод
    }

    AllBusesResponse GetAllBuses() const {
        // Реализуйте этот метод
    }
};

// Реализуйте функции и классы, объявленные выше, чтобы эта функция main
// решала задачу "Автобусные остановки"

int main() {
    // Менеджер автобусов
    BusManager bm;

    // Количество запросов
    int query_count;
    cout << "Query count input: ";
    cin >> query_count;

    // Запрос
    Query q;
    for (int i = 0; i < query_count; ++i) {
        // Ввод запроса
        cout << "Query input: ";
        cin >> q;
        cout << endl;

        // switch (q.type) {
        //     case QueryType::NewBus:
        //         bm.AddBus(q.bus, q.stops);
        //         break;
        //     case QueryType::BusesForStop:
        //         cout << bm.GetBusesForStop(q.stop) << endl;
        //         break;
        //     case QueryType::StopsForBus:
        //         cout << bm.GetStopsForBus(q.bus) << endl;
        //         break;
        //     case QueryType::AllBuses:
        //         cout << bm.GetAllBuses() << endl;
        //         break;
        // }
    }
}