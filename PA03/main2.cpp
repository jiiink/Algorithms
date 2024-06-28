#include <bits/stdc++.h>
using namespace std;


// score 60
int k;
vector< vector<int> > input() {

    fstream cin;
    try {
        cin.open("./sample/6.inp");
        if (cin.fail()) throw fstream::failure("Could not open file");
    } catch (const fstream::failure &e) {
        cerr << e.what();
    }


    cin >> k;
    vector< vector<int> > vec;

    for (int i=0; i<5; i++) {
        vector<int> v(k, 0);
        vec.push_back(v);
        for (int j=0; j<k; j++) {
            cin >> vec[i][j];
        }
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
    for (int i=0; i<vec.size(); i++) {
        if (i+1 != vec[i]) {
            flag++;
        }
    }

    if (flag == 1) return true;

    else { // one part
        int start, end;
        for (int i=0; i<vec.size(); i++) {
            if (i+1 != vec[i]) {
                start = i;
                end = abs(vec[i]);
                break;
            }
        }
        flip(vec, start, end);
        vector<int> init(k);
        iota(init.begin(), init.end(), 1);
        if (vec == init) {
            return true;
        }
    }

    return false;
}

bool isTwo(vector<int> vec) {
    int start, end;
    for (int i=0; i<vec.size(); i++) {
        // flip one thing
        if (i+1 == vec[i]*(-1)) { // only sign diff
            start = i;
            end = i + 1;
            break;
        } else if (i+1 != vec[i] and vec[i] > 0) {
            start = i;
            int index = start;
            while (vec[index++] > 0) {
            } 
            end = index;
            break;
        } else if (i+1 != vec[i]) { // flip part 
            start = i;
            end = abs(vec[i]);
            break;
        }
    }
    
    flip(vec, start, end);
    if (isOne(vec)) {
        return true;
    } else {
        return false;
    }
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