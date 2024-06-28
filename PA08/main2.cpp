#include <bits/stdc++.h>
using namespace std;

#define d 256
#define NO_OF_CHARS 256

// int rabin_karp_counter = 0;
// int KMP_counter = 0;
// int Boyer_Moore_counter = 0;

class Counter {
    public:
        string name;
        int counter;
        Counter(string n, int c) : name(n), counter(c) {}
};
Counter RK("RK", 0);
Counter KMP("KMP", 0);
Counter BM("BM", 0);


string pattern;
string text;
void input() {
    int pattern_line, text_line;

    cin >> pattern_line;

    while (pattern_line--) {
        cin >> pattern;
    }

    cin >> text_line;
    while (text_line--) {
        cin >> text;
    }
}


void Rabin_Karp(string pat, string txt, int q) {
    int M = pat.size();
    int N = txt.size();
    int i, j;
    int p = 0; // hash value for pattern
    int t = 0; // hash value for txt
    int h = 1;
 
    // The value of h would be "pow(d, M-1)%q"
    for (i = 0; i < M - 1; i++)
        h = (h * d) % q;
 
    // Calculate the hash value of pattern and first
    // window of text
    for (i = 0; i < M; i++) {
        p = (d * p + pat[i]) % q;
        t = (d * t + txt[i]) % q;
    }
 
    // Slide the pattern over text one by one
    for (i = 0; i <= N - M; i++) {
 
        // Check the hash values of current window of text
        // and pattern. If the hash values match then only
        // check for characters one by one
        RK.counter++;
        if (p == t) {
            /* Check for characters one by one */
            for (j = 0; j < M; j++) {
                RK.counter++;
                if (txt[i + j] != pat[j]) {
                    break;
                }
            }
 
            // if p == t and pat[0...M-1] = txt[i, i+1,
            // ...i+M-1]
 
            // if (j == M)
                // cout << "Pattern found at index " << i
                //      << endl;
        }
 
        // Calculate hash value for next window of text:
        // Remove leading digit, add trailing digit
        if (i < N - M) {
            t = (d * (t - txt[i] * h) + txt[i + M]) % q;
 
            // We might get negative value of t, converting
            // it to positive
            if (t < 0)
                t = (t + q);
        }
    }
}


void computeLPSArray(string pat, int M, int* lps);

// Prints occurrences of pat[] in txt[]
void KMPSearch(string pat, string txt)
{
    int M = pat.size();
    int N = txt.size();

    // create lps[] that will hold the longest prefix suffix values for pattern
    int lps[M];
    // int compareCount = 0; // Initialize the comparison counter

    // Preprocess the pattern (calculate lps[] array)
    computeLPSArray(pat, M, lps);

    int i = 0; // index for txt[]
    int j = 0; // index for pat[]
    while (i < N) {
        KMP.counter++; // Increment comparison counter for the comparison pat[j] == txt[i]
        if (pat[j] == txt[i]) {
            j++;
            i++;
        }

        if (j == M) {
            // printf("Found pattern at index %d\n", i - j);
            j = lps[j - 1];
        } else if (i < N && pat[j] != txt[i]) {
            // Mismatch after j matches
            if (j != 0)
                j = lps[j - 1];
            else
                i++;
        }
    }
    // printf("Total comparisons: %d\n", compareCount);
}

// Fills lps[] for given pattern pat[0..M-1]
void computeLPSArray(string pat, int M, int* lps)
{
    // length of the previous longest prefix suffix
    int len = 0;

    lps[0] = 0; // lps[0] is always 0

    // the loop calculates lps[i] for i = 1 to M-1
    int i = 1;
    while (i < M) {
        // compareCount++; // Increment comparison counter for the comparison pat[i] == pat[len]
        if (pat[i] == pat[len]) {
            len++;
            lps[i] = len;
            i++;
        } else {
            if (len != 0) {
                len = lps[len - 1];
            } else {
                lps[i] = 0;
                i++;
            }
        }
    }
}

// The preprocessing function for Boyer Moore's bad character heuristic
void badCharHeuristic(string str, int size, int badchar[NO_OF_CHARS]) {
    int i;

    // Initialize all occurrences as -1
    for (i = 0; i < NO_OF_CHARS; i++)
        badchar[i] = -1;

    // Fill the actual value of last occurrence of a character
    for (i = 0; i < size; i++)
        badchar[(int)str[i]] = i;
}

/* A pattern searching function that uses Bad Character Heuristic of Boyer Moore Algorithm */
void Boyer_Moore(string pat, string txt) {
    int m = pat.size();
    int n = txt.size();

    int badchar[NO_OF_CHARS];

    /* Fill the bad character array by calling the preprocessing function badCharHeuristic() for given pattern */
    badCharHeuristic(pat, m, badchar);

    int s = 0; // s is shift of the pattern with respect to text
    // int compareCount = 0; // Initialize the comparison counter

    while (s <= (n - m)) {
        int j = m - 1;

        /* Keep reducing index j of pattern while characters of pattern and text are matching at this shift s */
        while (j >= 0 && pat[j] == txt[s + j]) {
            BM.counter++; // Increment comparison counter
            j--;
        }

        // Increment comparison counter for the mismatch or the last comparison that breaks the loop
        if (j >= 0) {
            BM.counter++;
        }

        /* If the pattern is present at current shift, then index j will become -1 after the above loop */
        if (j < 0) {
            // cout << "Pattern occurs at shift = " << s << endl;

            /* Shift the pattern so that the next character in text aligns with the last occurrence of it in pattern.
            The condition s+m < n is necessary for the case when pattern occurs at the end of text */
            s += (s + m < n) ? m - badchar[txt[s + m]] : 1;
        } else {
            /* Shift the pattern so that the bad character in text aligns with the last occurrence of it in pattern.
            The max function is used to make sure that we get a positive shift.
            We may get a negative shift if the last occurrence of bad character in pattern
            is on the right side of the current character. */
            s += max(1, j - badchar[txt[s + j]]);
        }
    }
    // cout << "Total comparisons: " << compareCount << endl;
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

    // input();
    pattern = "GAEAE";
    text = "EEGAEAEDDC";

    // cout << pattern << "\n" << text;
    int q = INT_MAX;

    Rabin_Karp(pattern, text, q);

    KMPSearch(pattern, text);

    Boyer_Moore(pattern, text);

    cout << "RK\t: " << RK.counter << endl;
    cout << "KMP\t: " << KMP.counter << endl;
    cout << "BM\t: " << BM.counter << endl;

    output();

    return 0;
}