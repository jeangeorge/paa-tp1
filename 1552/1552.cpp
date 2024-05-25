#include <algorithm>
#include <cmath>
#include <iomanip>
#include <iostream>
#include <vector>

using namespace std;

class Point {
   public:
    int x, y;
};

double getDistance(Point a, Point b) {
    return sqrt(pow(a.x - b.x, 2) + pow(a.y - b.y, 2));
}

class Edge {
   public:
    int u, v;
    double weight;

    Edge(int u, int v, double weight) {
        this->u = u;
        this->v = v;
        this->weight = weight;
    }

    bool operator<(const Edge& other) const {
        return this->weight < other.weight;
    }
};

class Graph {
   public:
    vector<Edge> edges;

    Graph(vector<Point>& points) {
        int n = points.size();
        for (int i = 0; i < n; i++) {
            for (int j = i + 1; j < n; j++) {
                Edge edge = Edge(i, j, getDistance(points[i], points[j]));
                edges.push_back(edge);
            }
        }
    }

    double minimumSpanningTreeValue() {
        int i = 0, n = this->edges.size();
        vector<Edge> minimumSpanningTree;
        vector<int> parents(n);

        for (int i = 0; i < n; i++) {
            parents[i] = i;
        }

        this->sortEdges();

        while (i < n - 1) {
            int uParent = findParent(this->edges[i].u, parents);
            int vParent = findParent(this->edges[i].v, parents);

            if (uParent != vParent) {
                parents[uParent] = vParent;
                minimumSpanningTree.push_back(this->edges[i]);
            }

            i++;
        }

        double mstValue = 0;

        for (Edge edge : minimumSpanningTree) {
            mstValue += edge.weight;
        }

        return mstValue / 100;
    }

   private:
    void sortEdges() { sort(edges.begin(), edges.end()); }

    int findParent(int node, vector<int>& parent) {
        if (parent[node] == node) {
            return node;
        }
        parent[node] = findParent(parent[node], parent);
        return parent[node];
    }
};

int main() {
    int C;
    cin >> C;

    while (C > 0) {
        int n;
        cin >> n;

        vector<Point> points(n);
        for (int i = 0; i < n; i++) {
            cin >> points[i].x >> points[i].y;
        }

        Graph graph(points);
        cout << fixed << setprecision(2);
        cout << graph.minimumSpanningTreeValue() << endl;

        C--;
    }

    return 0;
}
