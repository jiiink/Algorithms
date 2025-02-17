#include <bits/stdc++.h>
using namespace std;
class Counter {
    public:
        string name;
        int counter;
        Counter(string n, int c) : name(n), counter(c) {}
};
Counter RK_("RK", 0);
Counter KMP_("KMP", 0);
Counter BM_("BM", 0);
int n;
string p, t;
int p_len, t_len;
vector<int> jump;
#define d 256 
#define q 101 
#define NO_OF_CHARS 256

int calculateHash(const string& str, int length, int prime, int base) {
    int hash = 0;
    for (int i = 0; i < length; i++) 
        hash = (base * hash + str[i]) % prime;
    return hash;
}

int RK(int n, int m) {
    int patternHash = calculateHash(p, m, q, d);
    int textHash = calculateHash(t, m, q, d);
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
                if (t[i + j] != p[j]) {
                    match = false;
                    break;
                }
            }
            if (match)
                return comparisons;
        }

        if (i < n - m) {
            textHash = (d * (textHash - t[i] * h) + t[i + m]) % q;
            if (textHash < 0)
                textHash = (textHash + q);
        }
    }
    // return comparisons;
}


int RK() {
    int power = 1, cnt = 0, t_hash = 0, p_hash = 0;
    for (int j=0; j<p_hash; j++) {
        t_hash += static_cast<int>(t[p_len -1 -j]) * power;
        p_hash += static_cast<int>(p[p_len -1 -j]) * power;
        if (j < p_len - 1) {
            power = power * 2;
        }
    }
    cnt++;
    for (int i=1; i<t_len -p_len + 1; i++) {
        cnt++;
        t_hash = 2 * (t_hash - static_cast<int>(t[i-1]) * (power)) + (static_cast<int>(t[p_len - 1 + i]));
        if (t_hash == p_hash) {
            for (int j=0; j<p_len; j++) {
                cnt ++;
                if (p[j] != t[i + j]) {
                    break;
                }
            }
            return cnt;
        }
    }
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

int KMP() {
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

int BM() {
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




bool compareCounter(const Counter &a, const Counter &b) {
    return a.counter < b.counter;
}
void output() {
    vector<Counter> counters = {RK_, KMP_, BM_};
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
    cin >> n;
    cin.ignore();
    for (int i=0; i<n; i++) {
        string input;
        getline(cin, input);
        p += input;
    }
    cin >> n;
    cin.ignore();
    for (int i=0; i<n; i++) {
        string input;
        getline(cin, input);
        t += input;
    }
    // cout << p << endl;
    // cout << t << endl;
    p_len = p.size();
    t_len = t.size();

    RK_.counter = RK(t_len, p_len);
    KMP_.counter = KMP();
    BM_.counter = BM();
    // cout << "RK\t: " << RK(t_len, p_len) << endl;
    // cout << "KMP\t: " << KMP_.counter << endl;
    // cout << "BM\t: " << BM_.counter << endl;
    output();
   
    return 0;
}