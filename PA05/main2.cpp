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

    // for (auto a : inputs) {
    //     cout << a << " ";
    // }
}

pair<bool, int> is_sub_palindrome(string);

pair<string, int> is_palindrome(string s) {
    if (*(s.begin()) != *(s.end() - 1)) { // first != last then false
        // cout << s << " is not palindrome\n";
        return make_pair("is not a palindrome", 0);
    }


    for (int i=0; i<s.size()/2; i++) {
        if (s[i] != *(s.end() - i - 1)) {
            int first_idx = i;
            int last_idx = s.size() - 1 - i;
            int length = last_idx - first_idx;
            if (is_sub_palindrome(s.substr(first_idx, length + 1)).first) {
                return make_pair("is a subpalindrome", s.size() - (length + 1) + is_sub_palindrome(s.substr(first_idx, length + 1)).second);
            } else {
                return make_pair("is a subpalindrome", s.size() - (length + 1) + is_sub_palindrome(s.substr(first_idx, length + 1)).second);
            }
            // return false;
        }
    }
    // cout << s << " is a palindrome\n";
    return make_pair("is a palindrome", s.size());
}
pair<bool, int> is_sub_palindrome(string s) {
    // cout << "sub string : " << s << endl;
    if (is_palindrome(s.substr(1)).first == "is a palindrome") { // except first letter
        // cout << s << " is subpalindrome\n";
        return make_pair(true, s.substr(1).size());
    }
    if (is_palindrome(s.substr(0, s.size() - 1)).first == "is a palindrome") { // except last letter
        // cout << s << " is subpalindrome\n";
        return make_pair(true, s.substr(0, s.size() - 1).size());
    }
    if (is_palindrome(s.substr(1, s.size() - 1 - 1)).first == "is a palindrome") { // except both ends
        // cout << s << " is subpalindrome\n";
        return make_pair(true, s.substr(1, s.size() - 1 - 1).size());
    }
    return make_pair(false, 1);
}


void process() {
    // string s = "veryveryyrev";
    for (auto s : inputs) {
        string answer = is_palindrome(s).first;
        int length = is_palindrome(s).second;
        if (answer == "is a palindrome") {
            cout << length << endl;
        } else if (answer == "is a subpalindrome") {
            cout << length << endl;
        } else {
            cout<< length << endl;
        }
    }
}

void output() {
    
}

int main() {
    input();

    // string s = "bookoob";
    // cout << s[0] << " " << *(s.end() - 1) << endl;
    // cout << s << " " << is_palindrome(s);
    // string s = "hello";
    // cout << s.size() << endl;
    // is_palindrome("summuus");

    process();
    output();

    return 0;
}