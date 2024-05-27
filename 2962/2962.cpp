#include <cmath>
#include <iostream>
#include <queue>
#include <vector>

using namespace std;

using Point = pair<int, int>;

class Sensor {
   public:
    Point point;
    int sensibility;

    Sensor(Point point, int sensibility)
        : point(point), sensibility(sensibility) {}
};

// BFS
bool hasPath(const vector<vector<int>>& sensorGraph, int originIndex,
             int destinyIndex) {
    queue<int> queue;
    vector<bool> visited(sensorGraph.size(), false);

    queue.push(originIndex);
    visited[originIndex] = true;

    while (!queue.empty()) {
        int currentIndex = queue.front();
        queue.pop();

        if (currentIndex == destinyIndex) {
            return true;
        }

        for (int neighborIndex : sensorGraph[currentIndex]) {
            if (!visited[neighborIndex]) {
                visited[neighborIndex] = true;
                queue.push(neighborIndex);
            }
        }
    }

    return false;
}

bool hasOverlap(const Sensor& sensor1, const Sensor& sensor2) {
    auto [x1, y1] = sensor1.point;
    auto [x2, y2] = sensor2.point;

    double distance = sqrt(pow(x1 - x2, 2) + pow(y1 - y2, 2));
    double radiusSum = sensor1.sensibility + sensor2.sensibility;

    return distance <= radiusSum;
}

vector<vector<int>> createSensorGraph(const vector<Sensor>& sensors,
                                      Sensor& originSensor,
                                      Sensor& destinySensor, int originIndex,
                                      int destinyIndex) {
    int numSensors = sensors.size();
    vector<vector<int>> sensorGraph(numSensors + 2);

    // Itera em todos os sensores
    for (int i = 0; i < numSensors; i++) {
        // Verifico se existe interseção entre algum sensor e o sensor de origem
        if (hasOverlap(sensors[i], originSensor)) {
            // Se houver, adiciona aresta no grafo
            sensorGraph[originIndex].push_back(i);
            sensorGraph[i].push_back(originIndex);
        }

        // Verifico se existe interseção entre algum sensor e o sensor de
        // destino
        if (hasOverlap(sensors[i], destinySensor)) {
            // Se houver, adiciona aresta no grafo
            sensorGraph[destinyIndex].push_back(i);
            sensorGraph[i].push_back(destinyIndex);
        }

        // Novo loop para pegar cada sensor 2 a 2
        for (int j = i + 1; j < numSensors; j++) {
            // Verifico se os sensores (exceto origem e destino) se intersectam.
            // Se sim, cria aresta entre eles no grafo
            if (hasOverlap(sensors[i], sensors[j])) {
                sensorGraph[i].push_back(j);
                sensorGraph[j].push_back(i);
            }
        }
    }

    return sensorGraph;
}

int main() {
    int M, N, numSensors;
    cin >> M >> N >> numSensors;

    // Faz a leitura dos sensores
    vector<Sensor> sensors;
    for (int i = 0; i < numSensors; i++) {
        int xSensor, ySensor, sensibility;
        cin >> xSensor >> ySensor >> sensibility;
        sensors.push_back(Sensor({xSensor, ySensor}, sensibility));
    }

    // Dois sensores auxiliares
    // A ideia é que eles sirvam somente para marcar a origem e destino
    Sensor originSensor({0, 0}, 0), destinySensor({M, N}, 0);

    int originIndex = numSensors,
        destinyIndex = numSensors + 1;  // vamos armazenar a origem e destino no
                                        // fim da lista de adjacencia

    vector<vector<int>> sensorGraph = createSensorGraph(
        sensors, originSensor, destinySensor, originIndex, destinyIndex);

    // Verifico se existe caminho saindo do sensor de origem e chegando no
    // sensor de destino. Se houver significa que o ladrão não conseguirá
    // alcançar a obra
    if (!hasPath(sensorGraph, originIndex, destinyIndex)) {
        cout << "S" << endl;
    } else {
        cout << "N" << endl;
    }

    return 0;
}
