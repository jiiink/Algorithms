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

    // fstream cin; // 테스트 시 iostream의 cin 객체 이름을 파일 입출력 객체 이름으로 바꿈

    // // 파일 열기 시도
    // try {
    //     cin.open("./sample/6.inp");
    //     if (cin.fail()) throw fstream::failure("Could not open file");
    // } catch (const fstream::failure &e) {
    //     cerr << e.what();
    // }

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



void printGraph(vvb graph) {
    for (auto row : graph) {
        for (auto col : row) {
            cout << col << " ";
        }
        cout << endl;
    }
}


bool promising(int i, int color) {
    for (int j=0; j<n; j++) {
        if (graph[i][j] and vcolor[i] == vcolor[j]) {
            // search_count++;
            return false;
        }
    }
    // search_count++;
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
            if (i + 1 == n) {
                // set s(vcolor);
                is_max_color(vcolor);
                // solutions.push_back(vcolor);
                // return;
            }
            m_coloring(i+1);
        } else {
            continue;
        }
    }
}


void output() {
    // cout << endl;
    if (solutions.empty()) {
        cout << "no\n";
        return;
    } 
    // else {
    //     for (auto sol : solutions) {
    //         for (auto s : sol) {
    //             cout << s << " ";
    //         }
    //     cout << endl;
    //     }
    // }

    // cout << endl;
    cout << solutions.size() << endl;
    cout << search_count << endl;
}

int main() {

    input();
    // printGraph(graph);
    m_coloring(0);

    output();
    
    

    return 0;
}