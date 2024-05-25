#include <iostream>
#include <map>
#include <queue>
#include <string>
#include <vector>

using namespace std;

const int MAX_LENGTH = 51;

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
    vector<vector<int>> graph;

    Graph(int numWords) {
        this->numWords = numWords;
        this->createNodes();
        this->createGraph();
    }

    int calculateShortestSequence(string sourceLanguage,
                                  string targetLanguage) {
        int minLength = MAX_LENGTH;
        queue<pair<Node, int>> queue;
        vector<bool> visited(numWords, false);

        for (int i = 0; i < this->numWords; i++) {
            if (nodeContainsLanguage(nodes[i], sourceLanguage)) {
                queue.push({nodes[i], nodes[i].wordLength});
                visited[i] = true;
            }
        }

        while (!queue.empty()) {
            auto [node, currentLength] = queue.front();
            queue.pop();

            if (nodeContainsLanguage(node, targetLanguage)) {
                minLength = min(minLength, currentLength);
                continue;
            }

            for (int neighborId : graph[node.id]) {
                Node &neighbor = nodes[neighborId];
                if (!visited[neighborId]) {
                    visited[neighborId] = true;
                    queue.push({neighbor, currentLength + neighbor.wordLength});
                }
            }
        }

        return minLength;
    }

   private:
    void createNodes() {
        for (int i = 0; i < numWords; i++) {
            string language1, language2, word;
            cin >> language1 >> language2 >> word;
            nodes.push_back(Node(i, language1, language2, word));
        }
    }

    void createGraph() {
        graph.resize(this->numWords);

        for (int i = 0; i < nodes.size(); i++) {
            for (int j = 0; j < nodes.size(); j++) {
                if (nodesHaveSameLanguage(nodes[i], nodes[j])) {
                    graph[i].push_back(j);
                    graph[j].push_back(i);
                }
            }
        }
    }

    bool nodeContainsLanguage(Node &node, string language) {
        return node.language1 == language || node.language2 == language;
    }

    bool nodesHaveSameLanguage(Node node1, Node node2) {
        return node1.language1 == node2.language1 ||
               node1.language1 == node2.language2 ||
               node1.language2 == node2.language2 ||
               node1.language2 == node2.language1;
    }
};

void printSolution(vector<int> &shortestSequences) {
    for (int i = 0; i < shortestSequences.size(); i++) {
        int shortestSequence = shortestSequences[i];
        if (shortestSequence < MAX_LENGTH) {
            cout << shortestSequence;
        } else {
            cout << "impossivel";
        }
        if (i < shortestSequences.size() - 1) {
            cout << endl;
        }
    }
}

int main() {
    int numWords;
    string sourceLanguage, targetLanguage;
    vector<int> shortestSequences;

    while (cin >> numWords && numWords != 0) {
        cin >> sourceLanguage >> targetLanguage;
        Graph graph = Graph(numWords);
        shortestSequences.push_back(
            graph.calculateShortestSequence(sourceLanguage, targetLanguage));
    }

    printSolution(shortestSequences);

    return 0;
}