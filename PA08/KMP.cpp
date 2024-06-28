#include <iostream>
#include <vector>
#include <string>

using namespace std;

// Function to compute the prefix function (LPS array)
void computeLPSArray(const string& pattern, vector<int>& lps, int& comparisons) {
    int length = 0;
    lps[0] = 0;
    int i = 1;
    int m = pattern.size();

    while (i < m) {
        comparisons++; // Increment comparison count
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
            cout << "Pattern found at index " << i - j << endl;
            j = lps[j - 1];
        } else if (i < n && pattern[j] != text[i]) {
            if (j != 0) {
                j = lps[j - 1];
            } else {
                i++;
            }
        }
    }

    return comparisons;
}

int main() {
    string text = "FAFEDFDBEF";
    string pattern = "FDBEF";

    int comparisonCount = KMPComparisons(text, pattern);
    cout << "Total number of comparisons: " << comparisonCount << endl;

    return 0;
}
