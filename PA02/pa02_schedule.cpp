#include <bits/stdc++.h>
using namespace std;
#define myout(v) {for (auto i : v) cout << i << " ";} cout << endl;

vector<int> input() {
    int N, M, P;
    cin >> P >> N;

    vector<int> vec(N, P);

    cin >> M;

    while (M--) {
        int i;
        cin >> i;
        while(i--) {
            int start, end, noise;
            cin >> start >> end >> noise;
            while (start < end) {
                vec[start++] += noise;
            }
        }
    }

    return vec;
}

int max_sum(vector<int> vec) {
    vector<int> sums(vec.size(), 0);

    // i == 0
    sums[0] = vec[0];

    // either
    for (int i=1; i<vec.size(); i++) {
        sums[i] = max(0, sums[i-1]) + vec[i];
    }

    return *(max_element(sums.begin(), sums.end()));
}

void output(int result) {
    cout << result << endl;
}

int main() {
    
    int result = max_sum(input());

    output(result);

    return 0;
}