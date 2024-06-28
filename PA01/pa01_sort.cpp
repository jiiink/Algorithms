#include <bits/stdc++.h>
using namespace std;



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

    
}

void insertion() {
    int k_value = A[k];
    int count_on_k = 0;

    for (int j=1; j<N; j++) {
        int key = A[j];
        int i = j - 1;

        while (i >= 0 and A[i] > key) {
            A[i+1] = A[i];
            i = i - 1;

            count_on_k++;
        }

        if (i != -1 ) count_on_k++;
        if (key == k_value) cout << count_on_k << endl;
        A[i+1] = key;
    }
}

void selection() {
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
    
        a[parentIndex] = a[j];
    }
    int parentIndex = findParentIndex(j);
    
    a[parentIndex] = e;
} 


void HeapSort(vector<int>& a, const int n) {
    for (int i=n/2; i>=0; i--) {
        adjust(a, i, n);
        
    }

    int count_on_k = 0;

    for (int i=n-2; i>=0; i--) {
        swap(a[0], a[i+1]);
        for (int j=i/2; j>=0; j--) {
            adjust(a, j, i+1);
        }
        count_on_k++;
        if (count_on_k == k) {
            for (int j=0; j<=i; j++) {
                cout << a[j] << endl;
            }
        }
    }
}

void heap() {
    HeapSort(A, N);
}

int count_on_k = 0;

int partition(vector<int>& a, int low, int high) {
    int pivot = a[low];
    int count = 0;
    for (int i=low + 1; i<=high; i++) {
        if (a[i] <= pivot) count++;
    }

    int pivotIndex = low + count;
    swap(a[pivotIndex], a[low]);

    int i = low, j = high;
    while (i < pivotIndex && j > pivotIndex) {
        while (a[i] <= pivot) i++;
        while (a[j] > pivot) j--;
        if (i < pivotIndex && j > pivotIndex) {
            swap(a[i++], a[j--]);
        }
    }
    count_on_k++;
    return pivotIndex;
}


void quicksort(vector<int>& a, int low, int high) {
    int pivot;
    if (high > low) {
        pivot = partition(a, low, high);

        if (count_on_k == k) {

            for (auto item : a) {
                cout << item << endl;
            }
        }
        quicksort(a, low, pivot-1);
        quicksort(a, pivot+1, high);
    }
}

void quick() {
    quicksort(A, 0, N-1);
    if (count_on_k < k) {
        for (auto item : A) {
            cout << item << endl;
        } 
    }
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


int main() {
    input();

    process();

    return 0;
}