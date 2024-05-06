#include <iostream>
#include <map>
#include <vector>

using namespace std;

void createGraph(int m, map<char, vector<char>>& graph) {
    char a, b;
    while (m > 0) {
        cin >> a >> b;
        graph[a].push_back(b);
        m--;
    }
}

bool hasPath(char a, char b, map<char, vector<char>>& graph,
             map<char, bool>& visited) {
    if (a == b) {
        return true;
    }

    visited[a] = true;

    for (char edge : graph[a]) {
        if (!visited[edge] && hasPath(edge, b, graph, visited)) {
            return true;
        }
    }

    return false;
}

bool wordsMatch(map<char, vector<char>>& graph, string word1, string word2) {
    if (word1.length() != word2.length()) {
        return false;
    }

    for (int i = 0; i < word1.length(); i++) {
        map<char, bool> visited;
        if (!hasPath(word1[i], word2[i], graph, visited)) {
            return false;
        }
    }

    return true;
}

int main() {
    int m, n;
    cin >> m >> n;

    map<char, vector<char>> graph;
    createGraph(m, graph);

    string words1[n], words2[n];

    for (int i = 0; i < n; i++) {
        cin >> words1[i] >> words2[i];
    }

    for (int i = 0; i < n; i++) {
        if (wordsMatch(graph, words1[i], words2[i])) {
            cout << "yes" << endl;
        } else {
            cout << "no" << endl;
        }
    }

    return 0;
}
