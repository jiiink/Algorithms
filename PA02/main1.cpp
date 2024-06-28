#include <iostream>
#include <vector>
using namespace std;
#define myout(v) {for (auto i : v) cout << i << " ";} cout << endl;

int P, N, M;
vector<int> input() {
    cin >> P >> N;

    vector<int> vec(N, 0);
    // myout(vec);    

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

    // myout(vec);
    return vec;
}

int process(vector<int> vec) {
    int sum = 0;

    for (auto& i : vec) {
        i += P;
        if (i > 0) {
            sum += i;
        }
    }

    return sum;
}

void output(int result) {
    cout << result << endl;
}

int main() {
    
    int result = process(input());

    output(result);

    return 0;
}