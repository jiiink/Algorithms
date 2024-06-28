#include <bits/stdc++.h>
using namespace std;
#define vvb vector<vector<bool>>

int n = 0;
int m = 0;
int search_count = 0;
vector<vector<int>> solutions;

vector<int> vcolor;
vvb graph;
void input() {

    cin >> n >> m;

    for (int i=0; i<n; i++) {
        vector<bool> row;
        bool unit;
        vcolor.push_back(0);
        for (int j=0; j<n; j++) {
            cin >> unit;
            row.push_back(unit); 
        }
        graph.push_back(row);
    }
}


bool promising(int i, int color) {
    for (int j=0; j<n; j++) {
        if (graph[i][j] and vcolor[i] == vcolor[j]) {
            return false;
        }
    }
    return true;
}


void is_max_color(vector<int> vcolor) {
    set<int> s(vcolor.begin(), vcolor.end());
    if (s.size() == m) {
        solutions.push_back(vcolor);
    }
}

void m_coloring(int i) {
    if (i >= n) return;

    for (int color=1; color<=m; color++) {

        for (int j=i+1; j<n; j++) {
            vcolor[j] = 0;
        }

        search_count++;

        vcolor[i] = color;
        
        if (promising(i, color)) {
            if (i + 1 == n) { // check the solution is max color
                is_max_color(vcolor);
            }
            m_coloring(i+1);
        } else {
            continue;
        }
    }
}


void output() {
    if (solutions.empty()) {
        cout << "no\n";
    } else {
        cout << solutions.size() << endl;
        cout << search_count << endl;
    }
}

int main() {

    input();

    m_coloring(0);

    output();    

    return 0;
}