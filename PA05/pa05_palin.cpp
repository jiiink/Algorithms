#include <bits/stdc++.h>
using namespace std;

vector<string> inputs;
void input() {
    int N = 0;
    cin >> N;

    while (N--) {
        string i;
        cin >> i;
        inputs.push_back(i);
    }
}

pair<bool, int> is_quasi_palindrome(string);

pair<string, int> is_palindrome(string s) {
    char first_letter = *(s.begin());
    char last_letter = *(s.end() - 1);
    if (first_letter != last_letter) {
        return make_pair("is not a palindrome", 0);
    }

    for (int i=0; i<s.size()/2; i++) {
        if (s[i] != *(s.end() - i - 1)) {
            int first_idx = i;
            int last_idx = s.size() - 1 - i;
            int length = last_idx - first_idx;
            auto result = is_quasi_palindrome(s.substr(first_idx, length + 1));
            if (result.first) { // sub string can be a palindrome
                return make_pair("is a quasipalindrome", s.size() - (length + 1) + result.second);
            } else { // one char between palindrome pair
                return make_pair("is a quasipalindrome", s.size() - (length + 1) + result.second);
            }
        }
    }
    
    return make_pair("is a palindrome", s.size()); // complete palindrome
}
pair<bool, int> is_quasi_palindrome(string s) {
    string substr = s.substr(1);
    if (is_palindrome(substr).first == "is a palindrome") { // except first letter
        return make_pair(true, substr.size());
    }

    substr = s.substr(0, s.size() - 1);
    if (is_palindrome(substr).first == "is a palindrome") { // except last letter
        return make_pair(true, substr.size());
    }

    substr = s.substr(1, s.size() - 1 - 1);
    if (is_palindrome(substr).first == "is a palindrome") { // except both ends
        return make_pair(true, substr.size());
    }

    return make_pair(false, 1); // accepted one char between palindrome pair
}

vector<pair<string, int>> answer_pair;
void test_is_palindrome() {
    for (auto s : inputs) {
        answer_pair.push_back(is_palindrome(s));
    }
}

void output() {
    for (auto i : answer_pair) {
        string answer = i.first;
        int length = i.second;
        if (answer == "is a palindrome") {
            cout << length << endl;
        } else if (answer == "is a quasipalindrome") {
            cout << length << endl;
        } else {
            cout<< length << endl;
        }
    }
}

int main() {
    input();
    test_is_palindrome();
    output();

    return 0;
}