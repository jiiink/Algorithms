#include <iostream>
#include <string>
#include <vector>

using namespace std;

#define d 256 // Number of characters in the input alphabet
#define q 101 // A prime number

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
            }
        } else {
            comparisons++; // Increment comparison count when hash values are compared and do not match
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

int main() {
    string text = "FAFEDFDBEF";
    string pattern = "FDBEF";

    int comparisonCount = RabinKarpComparisons(text, pattern);
    cout << "Total number of comparisons: " << comparisonCount << endl;

    return 0;
}
