#include <bits/stdc++.h>
using namespace std;

class Counter {
    public:
        string name;
        int counter;
        Counter(string n, int c) : name(n), counter(c) {}
};
Counter RK("RK", 0);
Counter KMP("KMP", 0);
Counter BM("BM", 0);
#define d 256 
#define q 101 
#define NO_OF_CHARS 256
string pattern;
string text;
void input() {

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
    return comparisons;
}
void computeLPSArray(vector<int>& lps, int m) {
    int length = 0;
    lps[0] = 0;
    int i = 1;

    while (i < m) {
        if (pattern[i] == pattern[length]) {
            length++;
            lps[i] = length;
            i++;
        } else {
            if (length != 0)
                length = lps[length - 1];
            else {
                lps[i] = 0;
                i++;
            }
        }
    }
}

int KMPComparisons(int n, int m) {
    vector<int> lps(m);
    int comparisons = 0;

    computeLPSArray(lps, m);

    int i = 0;
    int j = 0;
    while (i < n) {
        comparisons++; 
        if (pattern[j] == text[i]) {
            i++;
            j++;
        }

        if (j == m) {
            return comparisons;
            j = lps[j - 1];
        } else if (i < n && pattern[j] != text[i]) {
            if (j != 0) {
                comparisons++;
                j = lps[j - 1];
            } else {
                i++;
            }
        }
    }

    return comparisons;
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

    RK.counter = RabinKarp(n, m);
    KMP.counter = KMPComparisons(n, m);
    BM.counter = BoyerMoore(n, m);

    output();
    return 0;
}