#include <bits/stdc++.h>
using namespace std;


// score 86
void print(vector<int> vec) {
    for (auto a : vec) {
        cout << a << " ";
    }
    cout << endl;
}

vector<int> A;
int mode, k;
int N;
void input() {
    cin >> mode >> k;

    cin >> N;

    
    int element;
    for (int i=0; i<N; i++) {
        cin >> element;
        A.push_back(element);
    }

//     fstream cin; // 테스트 시 iostream의 cin 객체 이름을 파일 입출력 객체 이름으로 바꿈

//     // 파일 열기 시도
//     try {
//         cin.open("./sample/8.inp");
//         if (cin.fail()) throw fstream::failure("Could not open file");
//     } catch (const fstream::failure &e) {
//         cerr << e.what();
//     }
// // #endif
    
//     cin >> mode >> k;
//     cin >> N;

//     int element;
//     for (int i=0; i<N; i++) {
//         cin >> element;
//         A.push_back(element);
//     }
// // #ifdef test
//     cin.close(); // 파일 닫기

    
}

void insertion() {
    // cout << "insert " << k << endl;
    int k_value = A[k];
    int count_on_k = 0;

    for (int j=1; j<N; j++) {
        int key = A[j];
        int i = j - 1;
        // if (key == A[k])
        while (i >= 0 and A[i] > key) {
            A[i+1] = A[i];
            i = i - 1;

            // if (key == k_value) {
            //     // cout << "in while\n";
            //     count_on_k++;
            // }
            count_on_k++;
        }
        // count_on_k++;
        if (i != -1 ) count_on_k++;
        if (key == k_value) cout << count_on_k << endl;
        A[i+1] = key;
    }

    // cout << count_on_k << endl;
}

void selection() {
    // cout << "selection " << k << endl;
    int count_on_k = 0;

    for (int j=0; j<N-1; j++) {
        int smallest = j;
        for (int i=j+1; i<N; i++) {
            if (A[i] < A[smallest]) {
                smallest = i;
            }
        }
        swap(A[j], A[smallest]);
        count_on_k++;
        if (k == count_on_k) {
            for (auto item : A) {
                cout << item << endl;
            }
        }
    }
}

int findParentIndex(int index) {
    // if (index == 2) return 0;
    // if (index == 4) return index/2 - 1;

    if (index%2 == 0) return index/2 - 1;
    else              return index/2;
}

void adjust(vector<int>& a, int root, int n) {
    int j;
    int e = a[root];

    for (j=2*root+1; j<n; j = 2*j + 1) {
        if (j < n-1 and a[j] > a[j+1]) j++;
        if (e <= a[j]) break;
        int parentIndex = findParentIndex(j);
        // a[j/2] = a[j]; // !!!!! 2/2 = 1 . so it is not 2's root.
        a[parentIndex] = a[j];
    }
    int parentIndex = findParentIndex(j);
    // a[j/2] = e;
    // cout << "check" ;
    // cout << j << " " << parentIndex << endl;
    a[parentIndex] = e;
} 


void HeapSort(vector<int>& a, const int n) {
    for (int i=n/2; i>=0; i--) {
        adjust(a, i, n);
        // cout << "each sort" << endl;
        // print(A);
    }

    int count_on_k = 0;

    for (int i=n-2; i>=0; i--) {
        swap(a[0], a[i+1]);
        for (int j=i/2; j>=0; j--) {
            adjust(a, j, i+1);
        // cout << "each sort" << endl;
        // print(A);
        }
        // adjust(a, 0, i);
        count_on_k++;
        if (count_on_k == k) {
            for (int j=0; j<=i; j++) {
                cout << a[j] << endl;
            }
        }
    }
}

void heap() {
    // cout << "heap " << k << endl;

    HeapSort(A, N);
}


int partition(vector<int>& a, int low, int high) {
    // int left, right;
    int pivot = low;
    int pivot_item = a[pivot];
    int left = low;
    int right = high;
    while (left < right) {
        while (a[left] <= pivot_item) left++;
        while (a[right] >= pivot_item) right--;
        if (left < right) swap(a[left], a[right]);
    }

    a[low] = a[right];
    a[right] = pivot_item;
    return right;
}

int count_on_k = 0;
void quicksort(vector<int>& a, int low, int high) {
    int pivot;
    if (high > low) {
        pivot = partition(a, low, high);
        count_on_k++;
        if (count_on_k == k) {
            // print(A);
            for (auto item : a) {
                cout << item << endl;
            }
        }
        quicksort(a, low, pivot-1);
        quicksort(a, pivot+1, high);
    }
}

void quick() {
    // cout << "quick " << k << endl;

    quicksort(A, 0, N-1);
}

void process() {
    switch (mode) {
        case 1:
            insertion();
            break;
        case 2:
            selection();
            break;
        case 3:
            heap();
            break;
        case 4:
            quick();
            break;
        default:
            break;
    }
}

void output() {

}



int main() {
    input();

    // cout << 5/2 << endl;
    // if (1 == 2 - 1 and 1 > 0) cout << "and" << endl;
    // cout << "before sorting : ";
    // print(A);
    // cout << "----------input end----------\n";
    process();

    // cout << "after sorting : ";
    // print(A);

    output();

    return 0;
}