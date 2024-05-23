#include <cmath>
#include <iomanip>
#include <iostream>
#include <queue>
#include <vector>

using namespace std;

class Node {
   public:
    int index;
    int availableBullets;

    Node(int index, int availableBullets) {
        this->index = index;
        this->availableBullets = availableBullets;
    }

    bool operator<(const Node& other) const {
        return availableBullets < other.availableBullets;
    }
};

vector<vector<int>> createGraph(int numberOfNodes, int numberOfEdges) {
    vector<vector<int>> graph(numberOfNodes);
    for (int i = 0; i < numberOfEdges; i++) {
        int u, v;
        cin >> u >> v;

        // Estou usando 'u - 1' e 'v - 1' porque desejo mapear a entrada '1'
        // para a posição '0', '2' para '1' e assim sucetivamente
        graph[u - 1].push_back(v - 1);
        graph[v - 1].push_back(u - 1);
    }
    return graph;
}

vector<int> createShootersPerNode(int numberOfNodes) {
    vector<int> shootersPerNode(numberOfNodes, 0);
    int numberOfShooters;

    cin >> numberOfShooters;
    for (int i = 0; i < numberOfShooters; i++) {
        int pos;
        cin >> pos;
        shootersPerNode[pos - 1]++;
    }
    return shootersPerNode;
}

double calculateSuccessProbability(vector<vector<int>>& graph,
                                   vector<int>& shootersPerNode,
                                   int numberOfNodes, int numberOfBullets,
                                   double killProbability, int start, int end) {
    int requiredBullets = shootersPerNode[start];
    if (requiredBullets > numberOfBullets) {
        return 0;
    }

    vector<bool> visited(numberOfNodes, false);
    priority_queue<pair<double, Node>> priorityQueue;

    priorityQueue.push({pow(killProbability, requiredBullets),
                        Node(start, numberOfBullets - requiredBullets)});

    while (!priorityQueue.empty()) {
        auto [currentProbability, currentNode] = priorityQueue.top();
        priorityQueue.pop();

        if (currentNode.index == end) {
            return currentProbability;
        }

        bool wasVisited = visited[currentNode.index];
        if (wasVisited) {
            continue;
        }

        visited[currentNode.index] = true;

        for (int neighbor : graph[currentNode.index]) {
            int requiredBullets = shootersPerNode[neighbor];
            if (requiredBullets <= currentNode.availableBullets) {
                double newProb =
                    currentProbability * pow(killProbability, requiredBullets);
                int newAvailableBullets =
                    currentNode.availableBullets - requiredBullets;
                priorityQueue.push(
                    {newProb, Node(neighbor, newAvailableBullets)});
            }
        }
    }
    return 0;
}

int main() {
    int numberOfNodes, numberOfEdges, numberOfBullets, start, end;
    double killProbability;
    vector<double> successProbabilities;

    while (cin >> numberOfNodes >> numberOfEdges >> numberOfBullets >>
           killProbability) {
        vector<vector<int>> graph = createGraph(numberOfNodes, numberOfEdges);

        vector<int> shootersPerNode = createShootersPerNode(numberOfNodes);

        cin >> start >> end;

        // Estou usando 'start - 1' e 'end - 1' por praticidade porque as
        // entradas se iniciam em 1 e em C++ arrays sao indexados em 0
        double successProbability = calculateSuccessProbability(
            graph, shootersPerNode, numberOfNodes, numberOfBullets,
            killProbability, start - 1, end - 1);

        successProbabilities.push_back(successProbability);
    }

    cout << fixed << setprecision(3);
    for (double successProbability : successProbabilities) {
        cout << successProbability << endl;
    }

    return 0;
}