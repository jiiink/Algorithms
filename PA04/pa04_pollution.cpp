#include <bits/stdc++.h>
using namespace std;
#define INF 1000000 // 1,000,000
#define vvp vector<vector<pair<int, int>>> // 2D vector with pair
#define pii pair<int, int>

class Graph {
    private:
        int V; // vertices
        vvp adj; // (vertex, distance)

    public:
        Graph() {}
        Graph(int vertices) : V(vertices) {
            adj.resize(V+1); // for correcting index and value. so there is 0 vertex in index 0
        }

        void addEdge(int u, int v, int distance) {
            // For undirected
            adj[u].push_back(make_pair(v, distance));
            adj[v].push_back(make_pair(u, distance));
        }

        void print() {
            int i = 1;
            auto it = adj.begin();
            it++;
            for (it ; it < adj.end(); it++) {
                for (auto v : *it) {
                    printf("(%d : %d) distance : %d\n", i, v.first, v.second);
                }
                i++;
            }
        }

        int getV() { return V; }
        vvp getAdj() { return adj; }
};



int N, c1, c2;
Graph g;
void input() {
    cin >> N >> c1 >> c2;

    g = Graph(N);
    
    while (N-- > 1) {
        int u, v, distance;
        cin >> u >> v >> distance;

        g.addEdge(u, v, distance);
    }
    
}

vector<int> shortestDistances(int start) {
    vector<int> dists(g.getV()+1, INF);
    priority_queue< pii, vector<pii>, greater<pii>> pq;

    dists[start] = 0;
    pq.push(make_pair(0, start)); // (distance, vertex)

    while (!pq.empty()) { // until visit all vertices
        int u = pq.top().second;
        pq.pop();


        auto adj = g.getAdj();

        for (auto neighbor : adj[u]) {
            int v = neighbor.first;
            int weight = neighbor.second;
            if (dists[v] > dists[u] + weight) { // from start to v > from start to v via u
                dists[v] = dists[u] + weight;   // update dists
                pq.push(make_pair(dists[v], v)); // will be visited
            }
        }
    }

    return dists;
}

vector<pii> spread(vector<int> dists_from_c1, vector<int> dists_from_c2) {
    vector<pii> spreadedOrder; // (distance, vertex)
    for (int i=1; i<dists_from_c1.size(); i++) { // take minimum value between from c1 and from c2
        spreadedOrder.push_back(make_pair(min(dists_from_c1[i], dists_from_c2[i]), i));
    }

    sort(spreadedOrder.begin(), spreadedOrder.end());

    return spreadedOrder;
}

void output(vector<pii> spreadedOrder) {
    auto it = spreadedOrder.begin();
    advance(it, 2); // for excepting c1, c2
    for (it; it<spreadedOrder.end(); it++) {
        cout << (*it).second << endl;
    }        
}

int main() {
    input();

    auto dists_from_c1 = shortestDistances(c1);
    auto dists_from_c2 = shortestDistances(c2);

    auto spreadedOrder = spread(dists_from_c1, dists_from_c2);

    output(spreadedOrder);

    return 0;
}