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

bool canSteal(const vector<vector<int>>& sensorGraph, int numSensors) {
    int leftIndex = numSensors, bottomIndex = numSensors + 1,
        rightIndex = numSensors + 2, topIndex = numSensors + 3;

    if (hasPath(sensorGraph, leftIndex, bottomIndex)) {
        return false;
    }

    if (hasPath(sensorGraph, leftIndex, rightIndex)) {
        return false;
    }

    if (hasPath(sensorGraph, topIndex, bottomIndex)) {
        return false;
    }

    if (hasPath(sensorGraph, topIndex, rightIndex)) {
        return false;
    }

    return true;
}

bool hasOverlapBetweenSensors(Sensor& sensor1, Sensor& sensor2) {
    auto [x1, y1] = sensor1.point;
    auto [x2, y2] = sensor2.point;

    double distance = sqrt(pow(x1 - x2, 2) + pow(y1 - y2, 2));
    double radiusSum = sensor1.sensibility + sensor2.sensibility;

    return distance <= radiusSum;
}

vector<Sensor> createSensors(int numSensors, int M, int N) {
    vector<Sensor> sensors;

    for (int i = 0; i < numSensors; i++) {
        int xSensor, ySensor, sensibility;
        cin >> xSensor >> ySensor >> sensibility;
        sensors.push_back(Sensor({xSensor, ySensor}, sensibility));
    }

    return sensors;
}

vector<vector<int>> createGraph(vector<Sensor>& sensors, int M, int N) {
    int numSensors = sensors.size();
    vector<vector<int>> sensorGraph(numSensors + 4);

    for (int i = 0; i < numSensors; i++) {
        for (int j = i + 1; j < numSensors; j++) {
            if (hasOverlapBetweenSensors(sensors[i], sensors[j])) {
                sensorGraph[i].push_back(j);
                sensorGraph[j].push_back(i);
            }
        }
    }

    int leftIndex = numSensors, bottomIndex = numSensors + 1,
        rightIndex = numSensors + 2, topIndex = numSensors + 3;

    for (int i = 0; i < numSensors; i++) {
        auto [x, y] = sensors[i].point;
        auto s = sensors[i].sensibility;

        if (x - s <= 0) {
            sensorGraph[i].push_back(leftIndex);
            sensorGraph[leftIndex].push_back(i);
        }

        if (y - s <= 0) {
            sensorGraph[i].push_back(bottomIndex);
            sensorGraph[bottomIndex].push_back(i);
        }

        if (x + s >= M) {
            sensorGraph[i].push_back(rightIndex);
            sensorGraph[rightIndex].push_back(i);
        }

        if (y + s >= N) {
            sensorGraph[i].push_back(topIndex);
            sensorGraph[topIndex].push_back(i);
        }
    }

    return sensorGraph;
}

int main() {
    int M, N, numSensors;
    cin >> M >> N >> numSensors;

    vector<Sensor> sensors = createSensors(numSensors, M, N);
    vector<vector<int>> sensorGraph = createGraph(sensors, M, N);

    if (canSteal(sensorGraph, numSensors)) {
        cout << "S" << endl;
    } else {
        cout << "N" << endl;
    }

    return 0;
}
