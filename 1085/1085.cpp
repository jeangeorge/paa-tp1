#include <climits>
#include <iostream>
#include <map>
#include <queue>
#include <string>
#include <vector>

using namespace std;

using IntVector = vector<int>;
using PairIntInt = pair<int, int>;
using PriorityQueue =
    priority_queue<PairIntInt, vector<PairIntInt>, greater<PairIntInt>>;
using IntMatrix = vector<IntVector>;

class Node {
   public:
    int id;
    string language1, language2, word;
    char firstLetter;
    int wordLength;

    Node(int id, string language1, string language2, string word) {
        this->id = id;
        this->language1 = language1;
        this->language2 = language2;
        this->word = word;
        this->firstLetter = word[0];
        this->wordLength = word.length();
    }
};

class Graph {
   public:
    int numWords;
    vector<Node> nodes;
    map<string, IntVector> adjacencyList;

    Graph(int numWords) {
        this->numWords = numWords;
        this->createNodes();
        this->createAdjacencyList();
    }

    // Dijkstra
    int calculateShortestSequence(string sourceLanguage,
                                  string targetLanguage) {
        PriorityQueue priorityQueue;
        IntMatrix minDistances(numWords, IntVector(26, INT_MAX));

        for (int i = 0; i < numWords; i++) {
            Node &node = nodes[i];
            if (nodeContainsLanguage(node, sourceLanguage)) {
                int initialDistance = node.wordLength;
                char initialLetter = node.firstLetter;

                priorityQueue.push({initialDistance, i});
                minDistances[i][node.firstLetter - 'a'] = initialDistance;
            }
        }

        while (!priorityQueue.empty()) {
            auto [currentLength, nodeIndex] = priorityQueue.top();
            priorityQueue.pop();

            Node &node = nodes[nodeIndex];

            if (nodeContainsLanguage(node, targetLanguage)) {
                return currentLength;
            }

            processNeighbors(node, node.language1, currentLength, minDistances,
                             priorityQueue);

            processNeighbors(node, node.language2, currentLength, minDistances,
                             priorityQueue);
        }

        return -1;
    }

   private:
    void createNodes() {
        for (int i = 0; i < numWords; i++) {
            string language1, language2, word;
            cin >> language1 >> language2 >> word;
            nodes.push_back(Node(i, language1, language2, word));
        }
    }

    void createAdjacencyList() {
        for (int i = 0; i < numWords; i++) {
            adjacencyList[nodes[i].language1].push_back(i);
            adjacencyList[nodes[i].language2].push_back(i);
        }
    }

    bool nodeContainsLanguage(Node &node, string &language) {
        return node.language1 == language || node.language2 == language;
    }

    void processNeighbors(Node &node, string language, int currentLength,
                          IntMatrix &minDistances,
                          PriorityQueue &priorityQueue) {
        for (int neighborIndex : adjacencyList[language]) {
            Node &neighbor = nodes[neighborIndex];
            if (node.firstLetter != neighbor.firstLetter) {
                int newDistance = currentLength + neighbor.wordLength;
                int &currentMinDistance =
                    minDistances[neighbor.id][neighbor.firstLetter - 'a'];

                if (newDistance < currentMinDistance) {
                    currentMinDistance = newDistance;
                    priorityQueue.push({newDistance, neighbor.id});
                }
            }
        }
    }
};

void printSolution(IntVector &shortestSequences) {
    for (int shortestSequence : shortestSequences) {
        if (shortestSequence != -1) {
            cout << shortestSequence << endl;
        } else {
            cout << "impossivel" << endl;
        }
    }
}

int main() {
    int numWords;
    string sourceLanguage, targetLanguage;
    IntVector shortestSequences;

    while (cin >> numWords && numWords != 0) {
        cin >> sourceLanguage >> targetLanguage;
        Graph graph = Graph(numWords);

        shortestSequences.push_back(
            graph.calculateShortestSequence(sourceLanguage, targetLanguage));
    }

    printSolution(shortestSequences);

    return 0;
}
