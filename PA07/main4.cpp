#include <bits/stdc++.h>
using namespace std;

// 66

class Node {
    public:
        int is_unblocked = 1;
        int f = 0;
        int g = 0;
        int h = 0;
        int row = 0;
        int col = 0;
        int parent_row = 0;
        int parent_col = 0;
};

vector< vector<Node> > Grid;
vector<Node> open_list;
vector<Node> close_list;

// vector< vector<int> > Grid;
int m, n;
int number_of_zero;
int row1, col1, row2, col2;
int number_of_obstacle;
int flag;

Node source, target;

void put_open_list(Node);
void printF();

void input() {

    fstream cin;
    cin.open("./sample_data/9.inp");


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
        cin >> flag >> row1 >> col1;
        Grid[row1][col1].is_unblocked = 0;
    }

    // cout << "Enter source : ";
    char sourceFlag;
    cin >> sourceFlag >> row1 >> col1;
    if (sourceFlag == 's') {
        source.row = row1;
        source.col = col1;
        Grid[row1][col1].is_unblocked = 5;
    }

    // cout << "Enter target : ";
    char targetFlag;
    cin >> targetFlag >> row1 >> col1;
    if (targetFlag == 't') {
        target.row = row1;
        target.col = col1;
        Grid[row1][col1].is_unblocked = 9;
    }

    string obFlag;
    cin >> obFlag >> number_of_obstacle;
    if (obFlag == "ob") {
        for (int i=0; i<number_of_obstacle; i++) {
            cin >> row1 >> col1 >> row2 >> col2;
            int top_row = min(row1, row2);
            int bottom_row = max(row1, row2);
            int left_col = min(col1, col2);
            int right_col = max(col1, col2);
            for (int j=top_row; j<=bottom_row; j++) {
                for (int k=left_col; k<=right_col; k++) {
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

    for (auto i : open_list) {
        if (node.row == i.row and node.col == i.col) return false;
    }

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


void update_node(Node& node, Node& src) {
    node.parent_row = src.row;
    node.parent_col = src.col;
    node.g = calculate_g(node);
    node.h = calculate_h(node);
    node.f = node.g + node.h;
    open_list.push_back(node);
}

void put_open_list(Node src) {
    // printF();
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

    {
    if (is_valid(up)) {
        update_node(up, src);
    }
    if (is_valid(right)) {
        update_node(right, src);
    }
    if (is_valid(down)) {
        update_node(down, src);
    }
    if (is_valid(left)) {
        update_node(left, src);
    }
    }

    find_min_f();
    
}

void output() {
    cout << Grid[target.row][target.col].f << endl;
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

    // printGrid();

    // cout << "Source : " << source.row << ", " << source.col << endl;
    // cout << "Target : " << target.row << ", " << target.col << endl;

    close_list.push_back(source);
    put_open_list(source);

    output();
// 
    // printF();

    return 0;
}