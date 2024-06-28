#include <bits/stdc++.h>
using namespace std;

int k;
vector< vector<int> > input() {

    cin >> k;
    vector< vector<int> > vec;

    for (int i=0; i<5; i++) {
        vector<int> v(k, 0);
        vec.push_back(v);
        for (int j=0; j<k; j++) {
            cin >> vec[i][j];
        }
        auto it = vec[i].begin();
        vec[i].insert(it, 0);
        vec[i].push_back(k+1);
    }
    return vec;
}  


void flip(vector<int>& vec, int start, int end) {
    for (int i=start; i<end; i++) {
        vec[i] *= -1;
    }

    if (start + 1 == end) {
        return;
    } else {
        float mid = (start + end - 1) / 2.0;
        for (int i=start; i < mid; i++) {
            swap(vec[i], vec[2*mid - i]);
        }
    }
}

bool isOne(vector<int> vec) {
    // just one thing
    int flag = 0;
    for (int i=1; i<k+1; i++) {
        if (i != vec[i]) {
            flag++;
        }
    }

    if (flag == 1) return true;

    else { // one part
        int start=0, end=0;
        for (int i=1; i<k+1; i++) {
            if (i != vec[i]) {
                start = i;
                end = abs(vec[i]) + 1;
                break;
            }
        }
        flip(vec, start, end);
        for (int i=1; i<k+1; i++) {
            if (vec[i] != i) return false;
        }
        return true;
    }

}

bool isTwo(vector<int> vec) {
    // vector<int> subtracted;
    // for (int i=0; i<vec.size(); i++) {
    //     subtracted.push_back(vec[i] - i);
    // }
    // subtracted.push_back(k+1);

    int start = -1;
    int end = k + 1;
    int front; 
    // int back = end;
    for (int i=1; i<k+2; i++) {
        if (i != vec[i] and start < 0) {
            start = i;
            front = i-1;
        } else if (i == vec[i] and start >= 0) {
            end = i;
            // back = end;
            break;
        }
    } 

    for (int i=start; i<end; i++) {
        if ( vec[i]*(-1) == vec[front] + 1 ) {
            flip(vec, start, i+1);
            break;
        } else if ( vec[i]*(-1) == vec[end] -1 ) {
            flip(vec, i, end);
            break;
        }
    }

    if (isOne(vec)) return true;
    else            return false;
}

vector<string> process(vector< vector<int> > vec) {
    vector<string> answers;

    for (auto i : vec) {
        if (isOne(i)) {
            answers.push_back("one");
        } else if (isTwo(i)) {
            answers.push_back("two");
        } else {
            answers.push_back("over");
        }
    }

    return answers;

}

void output(vector<string> answers) {
    for (auto i : answers) {
        cout << i << endl;
    }
}


int main() {

    vector< vector<int> > vec = input();

    vector<string> answers = process(vec);

    output(answers);

    return 0;
}