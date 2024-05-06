#include <iostream>
#include <vector>

using namespace std;

int main() {
    int N, M, K, A, start, destination;
    double P;
    vector<int> positions;

    while (cin >> N >> M >> K >> P) {
        for (int i = 0; i < M; i++) {
            int u, v;
            cin >> u >> v;
        }

        cin >> A;
        for (int i = 0; i < A; i++) {
            int position;
            cin >> position;
            positions.push_back(position);
        }

        cin >> start >> destination;
    }
}
