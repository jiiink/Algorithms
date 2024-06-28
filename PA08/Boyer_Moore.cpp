#include <iostream>
#include <vector>
#include <string>

using namespace std;

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
            cout << "Pattern found at index " << s << endl;
            s += (s + m < n) ? goodSuffix[0] : 1;
        } else {
            comparisons++;
            s += max(goodSuffix[j + 1], j - badChar[text[s + j]]);
        }
    }

    return comparisons;
}

int main() {
    string text = "EGFEAGCCGC";
    string pattern = "GCCGC";

    int comparisonCount = BoyerMooreComparisons(text, pattern);
    cout << "Total number of comparisons: " << comparisonCount << endl;

    return 0;
}
