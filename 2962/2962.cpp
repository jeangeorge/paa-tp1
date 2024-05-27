#include <iostream>
#include <map>
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

bool isCoveredBySensor(int x, int y, const vector<Sensor>& sensors) {
    for (Sensor sensor : sensors) {
        int distanceX = x - sensor.point.first;
        int distanceY = y - sensor.point.second;
        if (distanceX * distanceX + distanceY * distanceY <=
            sensor.sensibility * sensor.sensibility) {
            return true;
        }
    }
    return false;
}

bool canMoveTo(int x, int y, const vector<Sensor>& sensors, int M, int N,
               const vector<vector<bool>>& visited) {
    return x >= 0 && x <= M && y >= 0 && y <= N && !visited[x][y] &&
           !isCoveredBySensor(x, y, sensors);
}

void moveTo(int x, int y, queue<Point>& queue, vector<vector<bool>>& visited) {
    queue.push({x, y});
    visited[x][y] = true;
}

bool hasPath(int M, int N, const vector<Sensor>& sensors) {
    if (isCoveredBySensor(0, 0, sensors)) {
        return false;
    }

    if (isCoveredBySensor(M, N, sensors)) {
        return false;
    }

    queue<Point> queue;
    vector<vector<bool>> visited(M + 1, vector<bool>(N + 1, false));

    moveTo(0, 0, queue, visited);

    while (!queue.empty()) {
        auto [x, y] = queue.front();
        queue.pop();

        if (x == M && y == N) {
            return true;
        }

        if (canMoveTo(x - 1, y - 1, sensors, M, N, visited)) {
            moveTo(x - 1, y - 1, queue, visited);
        }

        if (canMoveTo(x - 1, y, sensors, M, N, visited)) {
            moveTo(x - 1, y, queue, visited);
        }

        if (canMoveTo(x - 1, y + 1, sensors, M, N, visited)) {
            moveTo(x - 1, y + 1, queue, visited);
        }

        if (canMoveTo(x, y - 1, sensors, M, N, visited)) {
            moveTo(x, y - 1, queue, visited);
        }

        if (canMoveTo(x, y + 1, sensors, M, N, visited)) {
            moveTo(x, y + 1, queue, visited);
        }

        if (canMoveTo(x + 1, y - 1, sensors, M, N, visited)) {
            moveTo(x + 1, y - 1, queue, visited);
        }

        if (canMoveTo(x + 1, y, sensors, M, N, visited)) {
            moveTo(x + 1, y, queue, visited);
        }

        if (canMoveTo(x + 1, y + 1, sensors, M, N, visited)) {
            moveTo(x + 1, y + 1, queue, visited);
        }
    }

    return false;
}

int main() {
    int M, N, numSensors;
    cin >> M >> N >> numSensors;

    vector<Sensor> sensors;

    for (int i = 0; i < numSensors; i++) {
        int xSensor, ySensor, sensibility;
        cin >> xSensor >> ySensor >> sensibility;
        sensors.push_back(Sensor({xSensor, ySensor}, sensibility));
    }

    if (hasPath(M, N, sensors)) {
        cout << "S" << endl;
    } else {
        cout << "N" << endl;
    }

    return 0;
}
