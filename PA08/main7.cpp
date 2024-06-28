#include <bits/stdc++.h>
using namespace std;

int n;
string p, t;
int p_len, t_len;
vector<int> jump;

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
            cout << "RK\t: " << cnt << endl;
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
            cout << "KMP\t: " << cnt << endl;
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
    cout << "BM\t: " << cnt << endl;
    return cnt;
}

void print_ans(vector<pair<int, int>> ans) {
    if (ans[0].first == ans[1].first) {
        ans[0].second = 0;
        ans[1].second = 0;
    }
    if (ans[1].first == ans[2].first) {
        ans[1].second = 0;
        ans[2].second = 0;
    }
    if (ans[0].first == ans[1].first) {
        ans[0].second = 0;
        ans[1].second = 0;
    }
    if (ans[0].first == ans[2].first) {
        ans[0].second = 0;
        ans[2].second = 0;
    }

    for (int i=0; i<3; i++) {
        cout << ans[i].second << " ";
    }
}






string pattern;
string text;
void input() {

    string filename = "./sample/7.inp";
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


int main() {
    // cin >> n;
    // cin.ignore();
    // for (int i=0; i<n; i++) {
    //     string input;
    //     getline(cin, input);
    //     t += input;
    // }
    input();
    cout << p << endl;
    cout << t << endl;
    p_len = p.length();
    t_len = t.length();
    vector<pair<int, int>> ans;
    ans.push_back(make_pair(RK(), 1));
    ans.push_back(make_pair(KMP(), 2));
    ans.push_back(make_pair(BM(), 3));
    sort(ans.begin(), ans.end());
    print_ans(ans);
    return 0;
}