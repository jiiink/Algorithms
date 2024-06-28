#include <bits/stdc++.h>
using namespace std;
#define myout(v) {for (auto i : v) cout << i << " ";} cout << endl;

int P, N, M;
vector<int> input() {


    // fstream cin; // 테스트 시 iostream의 cin 객체 이름을 파일 입출력 객체 이름으로 바꿈

    // // 파일 열기 시도
    // try {
    //     cin.open("./sample/8.inp");
    //     if (cin.fail()) throw fstream::failure("Could not open file");
    // } catch (const fstream::failure &e) {
    //     cerr << e.what();
    // }



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
    // cin.close(); // 파일 닫기

    // myout(vec);
    return vec;
}

int dynamic_programming(vector<int> vec) {
    vector<int> cache(vec.size(), 0);

    // i == 0
    cache[0] = vec[0];

    // either
    for (int i=1; i<vec.size(); i++) {
        cache[i] = max(0, cache[i-1]) + vec[i];
    }

    return *(max_element(cache.begin(), cache.end()));
}


int process(vector<int> vec) {
    int sum = 0;

    for (auto& i : vec) {
        i += P;
        if (i > 0) {
            sum += i;
        }
    }
    // myout(vec);
    return dynamic_programming(vec);

    // return sum;
}

void output(int result) {
    cout << result << endl;
}

int main() {
    
    int result = process(input());

    output(result);

    return 0;
}