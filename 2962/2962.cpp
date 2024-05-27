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

bool hasOverlap(Sensor& sensor1, Sensor& sensor2) {
    auto [x1, y1] = sensor1.point;
    auto [x2, y2] = sensor2.point;

    double distance = sqrt(pow(x1 - x2, 2) + pow(y1 - y2, 2));
    double radiusSum = sensor1.sensibility + sensor2.sensibility;

    return distance <= radiusSum;
}

vector<Sensor> createSensors(int numSensors, int M, int N) {
    vector<Sensor> sensors;
    Sensor originSensor({0, 0}, 0), destinySensor({M, N}, 0);

    sensors.push_back(originSensor);

    for (int i = 0; i < numSensors; i++) {
        int xSensor, ySensor, sensibility;
        cin >> xSensor >> ySensor >> sensibility;
        sensors.push_back(Sensor({xSensor, ySensor}, sensibility));
    }

    sensors.push_back(destinySensor);

    return sensors;
}

vector<vector<int>> createSensorGraph(vector<Sensor>& sensors) {
    int numSensors = sensors.size();
    vector<vector<int>> sensorGraph(numSensors);

    for (int i = 0; i < numSensors; i++) {
        for (int j = i + 1; j < numSensors; j++) {
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

    vector<Sensor> sensors = createSensors(numSensors, M, N);
    vector<vector<int>> sensorGraph = createSensorGraph(sensors);

    if (hasPath(sensorGraph, 0, sensors.size() - 1)) {
        cout << "N" << endl;
    } else {
        cout << "S" << endl;
    }

    return 0;
}