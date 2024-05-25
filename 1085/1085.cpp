#include <iostream>
#include <map>
#include <queue>
#include <vector>

using namespace std;

class Node {
   public:
    string key;

    Node(string language, string word) { this->key = language + " " + word; }
};

int calculateShortestSequence(map<string, vector<pair<string, string>>> &graph,
                              string sourceLanguage, string targetLanguage) {
    // queue for bfs
    queue<pair<string, int>> queue;

    map<string, bool> visited;

    for (auto [language1, language2word] : graph) {
        for (auto [language2, word] : language2word) {
            visited[language1 + " - " + language2 + " - " + word] = false;
        }
    }

    queue.push({sourceLanguage, 0});
    visited[sourceLanguage] = true;

    while (!queue.empty()) {
        string currentLanguage = queue.front().first;
        int size = queue.front().second;

        queue.pop();

        if (currentLanguage == targetLanguage) {
            return size;
        }

        for (pair<string, string> word : graph[currentLanguage]) {
            if (word.second[0] != currentLanguage[0] && !visited[word.first]) {
                queue.push({word.first, size + 1});
                visited[word.first] = true;
            }
        }
    }

    return -1;
}

int main() {
    while (true) {
        int M;
        cin >> M;

        if (M == 0) {
            break;
        }

        string sourceLanguage, targetLanguage;
        map<string, vector<pair<string, string>>> graph;

        cin >> sourceLanguage >> targetLanguage;

        for (int i = 0; i < M; i++) {
            string language1, language2, word;
            cin >> language1 >> language2 >> word;
            graph[language1].push_back({language2, word});
            graph[language2].push_back({language1, word});
        }

        int shortestSequence =
            calculateShortestSequence(graph, sourceLanguage, targetLanguage);

        if (shortestSequence >= 0) {
            cout << shortestSequence << endl;
        } else {
            cout << "impossivel" << endl;
        }
    }
    return 0;
}
