#include <iostream>
#include <vector>

using namespace std;

class Route {
   public:
    int source, destination, ticketPrice;

    Route(int source, int destination, int ticketPrice)
        : source(source), destination(destination), ticketPrice(ticketPrice) {}
};

vector<Route> createRoutes(int numberOfRoutes) {
    int source, destination, ticketPrice;
    vector<Route> routes;

    for (int i = 0; i < numberOfRoutes; i++) {
        cin >> source >> destination >> ticketPrice;
        routes.push_back(Route(source - 1, destination - 1, ticketPrice));
    }

    return routes;
}

vector<vector<int>> createGraph(vector<Route> routes, int numberOfRoutes) {
    vector<vector<int>> graph(numberOfRoutes);

    for (Route route : routes) {
        graph[route.source].push_back(route.destination);
        graph[route.destination].push_back(route.source);
    }

    return graph;
}

int calculateMoney() { return -1; }

int main() {
    int numberOfCities, numberOfRoutes, source, destination, ticketPrice,
        numberOfFriends, freeSeats, i = 0;

    while (cin >> numberOfCities >> numberOfRoutes) {
        vector<Route> routes = createRoutes(numberOfRoutes);
        vector<vector<int>> graph = createGraph(routes, numberOfRoutes);

        cin >> numberOfFriends >> freeSeats;

        cout << "Instancia " << ++i << endl;
        int money = calculateMoney();
        if (money >= 0) {
            cout << money << endl;
        } else {
            cout << "impossivel" << endl;
        }

        cout << endl;
    }

    return 0;
}