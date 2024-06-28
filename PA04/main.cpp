#include <bits/stdc++.h>
using namespace std;
#define INF 1000000 // 1,000,000

// score 100

class Graph {
    private:
        int V; // vertices
        vector< vector< pair<int, int> > > adj; // (vertex, distance)

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
        vector<vector<pair<int, int>>> getAdj() { return adj; }
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
    // cout << g.getV() << endl;
    vector<int> dists(g.getV()+1, INF);
    priority_queue< pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;

    dists[start] = 0;
    pq.push(make_pair(0, start)); // (distance, vertex)

    while (!pq.empty()) {
        int u = pq.top().second;
        pq.pop();


        auto adj = g.getAdj();

        for (auto neighbor : adj[u]) {
            int v = neighbor.first;
            int weight = neighbor.second;
            if (dists[v] > dists[u] + weight) {
                dists[v] = dists[u] + weight;
                pq.push(make_pair(dists[v], v));
            }
        }
    }

    return dists;
}



// struct myComparison {
//     bool operator() (const int& a, const int& b) {

//     }
// };


int main() {
    
    // cout << INF;
    input();

    // g.print();

    auto dists_from_c1 = shortestDistances(c1);
    auto dists_from_c2 = shortestDistances(c2);

    // cout << "\nfrom c1 : ";
    // for (auto i : dists_from_c1) {
    //     cout << i << " ";
    // }
    // cout << "\nfrom c2 : ";
    // for (auto i : dists_from_c2) {
    //     cout << i << " ";
    // }
    // cout << endl;

    vector<pair<int, int>> fin; // (distance, vertex)
    for (int i=1; i<dists_from_c1.size(); i++) {
        fin.push_back(make_pair(min(dists_from_c1[i], dists_from_c2[i]), i));
    }

    sort(fin.begin(), fin.end());
    // for (auto i : fin) {
    //     cout << i.second << " ";
    // }
    auto it = fin.begin();
    advance(it, 2);
    for (it; it<fin.end(); it++) {
        cout << (*it).second << endl;
    }
    // cout << endl;
    // priority_queue<int, vector<int>, greater<int>> pq; 
    // process();        

    // output();

    return 0;
}