#include <bits/stdc++.h>
using namespace std;


typedef pair<int, int> Pair;

typedef struct {
    int is_unblocked = 1;
    int f = 0;
    int g = 0;
    int h = 0;
    int row = 0;
    int col = 0;
    int parent_row = 0;
    int parent_col = 0;
} Node;

vector< vector<Node> > Grid;
vector<Node> open_list;
vector<Node> close_list;

// vector< vector<int> > Grid;
int m, n;
int number_of_zero;
int row, col, row2, col2;
int number_of_obstacle;
int flag;

Node source, target;

void put_open_list(Node);

void input() {
    cin >> m >> n;
    for (int i=0; i<m; i++) {
        vector<Node> vect(n, Node());
        for (int j=0; j<n; j++) {
            vect[j].row = i;
            vect[j].col = j;
            vect[j].is_unblocked = 1;
        }
        Grid.push_back(vect);
    }

    cin >> number_of_zero;
    for (int i=0; i<number_of_zero; i++) {
        cin >> flag >> row >> col;
        Grid[row][col].is_unblocked = 0;
    }

    // cout << "Enter source : ";
    char sourceFlag;
    cin >> sourceFlag >> row >> col;
    if (sourceFlag == 's') {
        source.row = row;
        source.col = col;
        Grid[row][col].is_unblocked = 5;
    }

    // cout << "Enter target : ";
    char targetFlag;
    cin >> targetFlag >> row >> col;
    if (targetFlag == 't') {
        target.row = row;
        target.col = col;
        Grid[row][col].is_unblocked = 9;
    }

    string obFlag;
    cin >> obFlag >> number_of_obstacle;
    if (obFlag == "ob") {
        for (int i=0; i<number_of_obstacle; i++) {
        cin >> row >> col >> row2 >> col2;
        for (int j=row; j<=row2; j++) {
            for (int k=col; k<=col2; k++) {
                Grid[j][k].is_unblocked = 0;
            }
        }
    }
    }

    
}

bool is_valid(Node node) {
    if (!node.is_unblocked) return false;
    if (node.row < 0 or node.row >= m) return false;
    if (node.col < 0 or node.col >= n) return false;

    for (auto i : close_list) {
        if (node.row == i.row and node.col == i.col) {
            return false;
        }
    }

    return true;
}

int calculate_g(Node& cur) { // Manhatton
    return (abs(source.row - cur.row) + abs(source.col - cur.col)) * 3;
}

int calculate_h(Node& cur) { // Euclid
    return (int)sqrt(pow(cur.row - target.row, 2) + pow(cur.col - target.col, 2));
}

void find_min_f() {
    // cout << "find_min_f\n";
    int min_f = 1000000;
    auto erase_it = open_list.end();
    // Node* node = nullptr;
    for (auto it=open_list.begin(); it<open_list.end(); it++) {
        if (it->row == target.row and it->col == target.col) return; // target is in the open_list

        if (it->f <= min_f) {
            min_f = it->f;
            erase_it = it;
        }
    }

    if (erase_it != open_list.end()) {
        // cout << "erase\n";
        open_list.erase(erase_it);
        close_list.push_back(*erase_it);
        put_open_list(*erase_it);
    }
    
}

bool is_target(Node& node) {
    if (node.row == target.row and node.col == target.col) return true;
    
    return false;
}

bool is_dup(Node& node) {
    for (auto it : open_list) {
        if (node.row == it.row and node.col == it.col) return true;
    }

    return false;
}

void put_open_list(Node src) {
    int adj_row, adj_col;
    if (src.row - 1 < 0) adj_row = src.row;
    else adj_row = src.row - 1;
    Node& up = Grid[adj_row][src.col];

    if (src.row + 1 >= m) adj_row = src.row;
    else adj_row = src.row + 1;
    Node& down = Grid[adj_row][src.col];

    if (src.col - 1 < 0) adj_col = src.col;
    else adj_col = src.col - 1;
    Node& left = Grid[src.row][adj_col];

    if (src.col + 1 >= n) adj_col = src.col;
    else adj_col = src.col + 1;
    Node& right = Grid[src.row][adj_col];
    

    // {
    // if (is_dup(up)) {
    //     Node& old = Grid[up.row][up.col];
    //     if (calculate_g(up) < up.g) {
    //         up.parent_row = src.row;
    //         up.parent_col = src.col;
    //         up.g = calculate_g(up);
    //         up.h = calculate_h(up);
    //         up.f = up.g + up.h;
    //     }
    // }
    // if (is_dup(right)) {
    //     if (calculate_g(right) < right.g) {
    //         right.parent_row = src.row;
    //         right.parent_col = src.col;
    //         right.g = calculate_g(right);
    //         right.h = calculate_h(right);
    //         right.f = right.g + right.h;
    //     }
    // }
    // if (is_dup(down)) {
    //     if (calculate_g(down) < down.g) {
    //         down.parent_row = src.row;
    //         down.parent_col = src.col;
    //         down.g = calculate_g(down);
    //         down.h = calculate_h(down);
    //         down.f = down.g + down.h;
    //     }
    // }
    // if (is_dup(left)) {
    //     if (calculate_g(left) < left.g) {
    //         left.parent_row = src.row;
    //         left.parent_col = src.col;
    //         left.g = calculate_g(left);
    //         left.h = calculate_h(left);
    //         left.f = left.g + left.h;
    //     }
    // }
    // }

    {
    if (is_valid(up)) {
        up.parent_row = src.row;
        up.parent_col = src.col;
        up.g = calculate_g(up);
        up.h = calculate_h(up);
        up.f = up.g + up.h;
        open_list.push_back(up);
    }
    if (is_valid(right)) {
        right.parent_row = src.row;
        right.parent_col = src.col;
        right.g = calculate_g(right);
        right.h = calculate_h(right);
        right.f = right.g + right.h;
        open_list.push_back(right);
    }
    if (is_valid(down)) {
        down.parent_row = src.row;
        down.parent_col = src.col;
        down.g = calculate_g(down);
        down.h = calculate_h(down);
        down.f = down.g + down.h;
        open_list.push_back(down);
    }
    if (is_valid(left)) {
        left.parent_row = src.row;
        left.parent_col = src.col;
        left.g = calculate_g(left);
        left.h = calculate_h(left);
        left.f = left.g + left.h;
        open_list.push_back(left);
    }
    }

    find_min_f();
    
}

void output() {
    cout << Grid[target.row][target.col].f << endl;
}

void printGrid() {
    cout << endl;
    for (auto row : Grid) {
        for (auto col : row) {
            cout << col.is_unblocked << " ";
        }
        cout << endl;
    }
    cout << endl;
}

void printF() {
    cout << endl;
    for (auto row : Grid) {
        for (auto col : row) {
            cout << col.f << " ";
        }
        cout << endl;
    }
    cout << endl;
}

int main() {

    input();


    cout << "Source : " << source.row << ", " << source.col << endl;
    cout << "Target : " << target.row << ", " << target.col << endl;

    close_list.push_back(source);
    put_open_list(source);

    output();

    // printGrid();
    // printF();

    return 0;
}