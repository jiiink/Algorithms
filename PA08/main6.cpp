#include <bits/stdc++.h>
using namespace std;

#define d 256 
#define q 101 
#define NO_OF_CHARS 256

class Counter {
    public:
        string name;
        int counter;
        Counter(string n, int c) : name(n), counter(c) {}
};
Counter RK("RK", 0);
Counter KMP("KMP", 0);
Counter BM("BM", 0);


int n;
string p, t;
int p_len, t_len;
vector<int> jump;

string pattern;
string text;
void input() {

    string filename = "./sample/9.inp";
    cout << filename << endl;
    fstream cin;
    cin.open(filename);

    int pattern_line, text_line;

    cin >> pattern_line;

    if (pattern_line == 1) {
        cin >> pattern;
    } else {
        while (pattern_line--) {
            string line;
            getline(cin, line);
            pattern += line;
        }
    }
    p = pattern;


    cin >> text_line;
    if (text_line == 1) {
        cin >> text;
    } else {
        while (text_line--) {
            string line;
            getline(cin, line);
            text += line;
        }
    }

    t = text;
}


int calculateHash(const string& str, int length, int prime, int base) {
    int hash = 0;
    for (int i = 0; i < length; i++) 
        hash = (base * hash + str[i]) % prime;
    return hash;
}

int RabinKarp(int n, int m) {
    int patternHash = calculateHash(pattern, m, q, d);
    int textHash = calculateHash(text, m, q, d);
    int h = 1;
    int comparisons = 0;

    for (int i = 0; i < m - 1; i++)
        h = (h * d) % q;

    for (int i = 0; i <= n - m; i++) {
        comparisons++;
        if (patternHash == textHash) {
            bool match = true;
            for (int j = 0; j < m; j++) {
                comparisons++;
                if (text[i + j] != pattern[j]) {
                    match = false;
                    break;
                }
            }
            if (match)
                return comparisons;
        }

        if (i < n - m) {
            textHash = (d * (textHash - text[i] * h) + text[i + m]) % q;
            if (textHash < 0)
                textHash = (textHash + q);
        }
    }
    // return comparisons;
}



vector<int> getPi() {
    int m = p.size(), j = 0;
    vector<int> pi(m, 0);
    for (int i=1; i<m; i++) {
        while (j > 0 and p[i] != p[j]) {
            j = pi[j-1];
        }
        if (p[i] == p[j]) {
            pi[i] = j++;
        }
    }
    return pi;
}

int KMP_() {
    int cnt = 0, i=0, j=0;
    vector<int> pi = getPi();
    while (i < t_len) {
        if (p[j] == t[i]) {
            i++;
            j++;
            cnt++;
        }
        else if (p[j] != t[i]) {
            cnt++;
            if (j != 0) j = pi[j-1];
            else i++;
        }
        if (j == p_len) {
            return cnt;
        }
    }
}

int BM_() {
    jump.resize(t_len);
    for (int i=0; i<t_len; i++) {
        jump[i] = p_len;
    }
    for (int i=0; i<p_len; i++) {
        int idx = p[i] - 'A';
        jump[idx] = p_len - i - 1;
    }

    int i = p_len - 1, j = p_len - 1, cnt = 0;
    while (j >= 0) {
        cnt++;
        while (t[i] != p[j]) {
            cnt++;
            int idx = t[i] - 'A';
            int k = jump[idx];
            if (p_len - j > k) {
                i = i + p_len - j;
            }
            else {
                i = i + k;
            }
            j = p_len - 1;
        }
        i--;
        j--;
    }
    return cnt;
}





void badCharHeuristic(int size, vector<int>& badChar) {
    for (int i = 0; i < NO_OF_CHARS; i++)
        badChar[i] = -1;
    for (int i = 0; i < size; i++)
        badChar[(int)pattern[i]] = i;
}

void preprocessGoodSuffix(int size, vector<int>& goodSuffix) {
    vector<int> border(size + 1, 0);
    int i = size, j = size + 1;
    border[i] = j;

    while (i > 0) {
        while (j <= size && pattern[i - 1] != pattern[j - 1]) {
            if (goodSuffix[j] == 0) goodSuffix[j] = j - i;
            j = border[j];
        }
        i--;
        j--;
        border[i] = j;
    }
    j = border[0];
    for (i = 0; i <= size; i++) {
        if (goodSuffix[i] == 0) goodSuffix[i] = j;
        if (i == j) j = border[j];
    }
}

int BoyerMoore(int n, int m) {
    vector<int> badChar(NO_OF_CHARS);
    vector<int> goodSuffix(m + 1, 0);
    int comparisons = 0;
    
    badCharHeuristic(m, badChar);
    preprocessGoodSuffix(m, goodSuffix);

    int s = 0;
    while (s <= (n - m)) {
        int j = m - 1;

        while (j >= 0 && pattern[j] == text[s + j]) {
            comparisons++;
            j--;
        }
        if (j < 0) {
            // comparisons++;
            s += (s + m < n) ? goodSuffix[0] : 1;
            return comparisons;
        } else {
            comparisons++;
            s += max(goodSuffix[j + 1], j - badChar[text[s + j]]);
        }
    }
    return comparisons;
}




bool compareCounter(const Counter &a, const Counter &b) {
    return a.counter < b.counter;
}
void output() {
    vector<Counter> counters = {RK, KMP, BM};
    sort(counters.begin(), counters.end(), compareCounter);

    for (int i=0; i < 3; i++) {
        if (i != 2 and counters[i].counter == counters[i+1].counter) {
            counters[i].name = "0";
            counters[i+1].name = "0";
        }
    }

    for (auto c : counters) {
        cout << c.name << " ";
    }
}

int main() {
    input();
    int n = text.size();
    int m = pattern.size();
    t_len = text.size();
    p_len = pattern.size();

    cout << "Text\t: " << t << endl;
    cout << "Pattern\t: " << p << endl;


    RK.counter = RabinKarp(n, m);
    cout << "RK done\n";
    // RK.counter = RK_(n, m);
    KMP.counter = KMP_();
    cout << "KMP done \n";
    BM.counter = BM_();
    // BM.counter = BoyerMoore(n, m);
    cout << "BM done \n";

    cout << "RK\t: " << RK.counter << endl;
    cout << "KMP\t: " << KMP.counter << endl;
    cout << "BM\t: " << BM.counter << endl;

    output();
    return 0;
}