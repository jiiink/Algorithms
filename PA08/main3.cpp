#include <iostream>
#include <string>
#include <vector>

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

#define d 256 // Number of characters in the input alphabet
#define q 101 // A prime number




string pattern;
// vector<string> patterns;
string text;
void input() {
    int pattern_line, text_line;

    cin >> pattern_line;

    // while (pattern_line--) {
    //     cin >> pattern;
    // }
    if (pattern_line == 1) {
        cin >> pattern;
    } else {
        while (pattern_line--) {
            string line;
            getline(cin, line);
            // patterns.push_back(line);
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
            // patterns.push_back(line);
            text += line;
        }
    }

    // cin >> text_line;
    // while (text_line--) {
    //     cin >> text;
    // }
}


// Function to calculate hash value
int calculateHash(const string& str, int length, int prime, int base) {
    int hash = 0;
    for (int i = 0; i < length; i++) {
        hash = (base * hash + str[i]) % prime;
    }
    return hash;
}

// Rabin-Karp algorithm to find the pattern in the text and count the comparisons
int RabinKarpComparisons(const string& text, const string& pattern) {
    int n = text.size();
    int m = pattern.size();
    int patternHash = calculateHash(pattern, m, q, d);
    int textHash = calculateHash(text, m, q, d);
    int h = 1;
    int comparisons = 0;

    // The value of h would be "pow(d, M-1)%q"
    for (int i = 0; i < m - 1; i++) {
        h = (h * d) % q;
    }

    // Slide the pattern over the text
    for (int i = 0; i <= n - m; i++) {
        // Check if the hash values of the current window of text matches with the pattern's hash value
        comparisons++;
        if (patternHash == textHash) {
            // If the hash values match, check the characters one by one
            bool match = true;
            for (int j = 0; j < m; j++) {
                comparisons++;
                if (text[i + j] != pattern[j]) {
                    match = false;
                    break;
                }
            }
            // If all characters match, we found a pattern match
            if (match) {
                cout << "Pattern found at index " << i << endl;
                return comparisons;
            }
        } else {
            // comparisons++; // Increment comparison count when hash values are compared and do not match
        }

        // Calculate hash value for the next window of text
        if (i < n - m) {
            textHash = (d * (textHash - text[i] * h) + text[i + m]) % q;
            if (textHash < 0) {
                textHash = (textHash + q);
            }
        }
    }

    return comparisons;
}

// Function to compute the prefix function (LPS array)
void computeLPSArray(const string& pattern, vector<int>& lps, int& comparisons) {
    int length = 0;
    lps[0] = 0;
    int i = 1;
    int m = pattern.size();

    while (i < m) {
        // comparisons++; // Increment comparison count
        if (pattern[i] == pattern[length]) {
            length++;
            lps[i] = length;
            i++;
        } else {
            if (length != 0) {
                length = lps[length - 1];
            } else {
                lps[i] = 0;
                i++;
            }
        }
    }
}

// KMP algorithm to find the pattern in the text and count the comparisons
int KMPComparisons(const string& text, const string& pattern) {
    int n = text.size();
    int m = pattern.size();
    vector<int> lps(m);
    int comparisons = 0;

    // Preprocess the pattern to create the LPS array
    computeLPSArray(pattern, lps, comparisons);

    int i = 0; // Index for text
    int j = 0; // Index for pattern
    while (i < n) {
        comparisons++; // Increment comparison count
        if (pattern[j] == text[i]) {
            i++;
            j++;
        }

        if (j == m) {
            return comparisons;
            cout << "Pattern found at index " << i - j << endl;
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

#define NO_OF_CHARS 256

// Preprocessing for bad character heuristic
void badCharHeuristic(const string& pattern, int size, vector<int>& badChar) {
    for (int i = 0; i < NO_OF_CHARS; i++) {
        badChar[i] = -1;
    }
    for (int i = 0; i < size; i++) {
        badChar[(int)pattern[i]] = i;
    }
}

// Preprocessing for good suffix heuristic
void preprocessGoodSuffix(const string& pattern, int size, vector<int>& goodSuffix) {
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

// Boyer-Moore algorithm to find the pattern in the text and count the comparisons
int BoyerMooreComparisons(const string& text, const string& pattern) {
    int n = text.size();
    int m = pattern.size();
    vector<int> badChar(NO_OF_CHARS);
    vector<int> goodSuffix(m + 1, 0);
    int comparisons = 0;

    // Preprocess the pattern for bad character heuristic
    badCharHeuristic(pattern, m, badChar);

    // Preprocess the pattern for good suffix heuristic
    preprocessGoodSuffix(pattern, m, goodSuffix);

    int s = 0; // s is the shift of the pattern with respect to the text
    while (s <= (n - m)) {
        int j = m - 1;

        while (j >= 0 && pattern[j] == text[s + j]) {
            comparisons++;
            j--;
        }

        if (j < 0) {
            return comparisons;
            cout << "Pattern found at index " << s << endl;
            s += (s + m < n) ? goodSuffix[0] : 1;
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

    for (int i=0; i<counters.size(); i++) {
        if (i != counters.size() - 1 and counters[i].counter == counters[i+1].counter) {
            counters[i].name = "0";
            counters[i+1].name = "0";
        }
    }

    for (auto c : counters) {
        cout << c.name << " ";
    }
}


int main() {
    // string text = "EEGAEAEDDC";
    // string pattern = "GAEAE";
    input();
    cout << "Text\t: "    << text << endl;
    cout << "Pattern\t: " << pattern << endl;

    RK.counter = RabinKarpComparisons(text, pattern);
    KMP.counter = KMPComparisons(text, pattern);
    BM.counter = BoyerMooreComparisons(text, pattern);
    cout << "RK\t: " << RK.counter << endl;
    cout << "KMP\t: " << KMP.counter << endl;
    cout << "BM\t: " << BM.counter << endl;

    output();

    return 0;
}