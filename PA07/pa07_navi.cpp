#include <bits/stdc++.h>
using namespace std;

typedef pair<int, int> Pair;

class Node {
	public:
		int h;
		int g;
		int f;
		Pair position;
		Node *parent;
	
		bool operator==(const Node &node);

		bool operator<(const Node& other) const {
			return position < other.position;
		}

		Node(int h=0, int g=0, int f=0, Pair position=make_pair(-1, -1), Node* parent=nullptr) {
			this->h = h;
			this->g = g;
			this->f = f;
			this->position = position;
			this->parent = parent;
		}
};

bool Node::operator==(const Node &node) {
	return (node.position.first  == this->position.first &&
		node.position.second == this->position.second);
}

class AStar {
	private:	
		int x; // grid size 
		int y;
		int x_0; // start position
		int y_0;
		int x_f; // end position
		int y_f;

		char **grid;
		
		int move[4][2] = { // directions for node
			{1,	0}, 		
			{-1,0}, 
			{0,	1}, 
			{0,	-1},
		};

		struct comp {
			bool operator()(const Node& a, const Node& b) {
				return a.f >= b.f;
			}
		};
		priority_queue<Node, vector<Node>, comp> open_pq; // for fast getting minimum f
		set<Pair> open_set;								  // for fast searching
		set<Node> closed_list;	
		
		
	public:
		AStar(); // draw a grid
		~AStar();
		
		void BeginPathSearch();
		int costH(Pair pos);
		int costG(Pair pos);
		void moveNode(int pos_x, int pos_y, Node curr_node);
		bool checkTarget(Node);
};

AStar::AStar() {
	// fstream cin;
	// cin.open("./sample_data/9.inp");

    cin >> x >> y;
    grid = new char*[x];

	for (int i = 0; i < y; i++) {
		grid[i] = new char[y];
		for (int j = 0; j < x; j++) {
			grid[i][j] =  '.'; 
		}
	}

    int flag, row1, col1, row2, col2;
    int number_of_zero;
    cin >> number_of_zero;
    for (int i=0; i<number_of_zero; i++) {
        cin >> flag >> row1 >> col1;
        grid[row1][col1] = 'o';
    }

    char sourceFlag;
    cin >> sourceFlag >> x_0 >> y_0;

    char targetFlag;
    cin >> targetFlag >> x_f >> y_f;

    int number_of_obstacle;
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
                    grid[j][k] = 'o';
                }
            }
        }
    }

	grid[x_0][y_0]  = '*'; //start
	grid[x_f][y_f] 	= 'x'; //finish
}

AStar::~AStar() {
	delete *grid;
}


int AStar::costG(Pair pos) {
    return (abs(x_0 - pos.first) + abs(y_0 - pos.second)) * 3;
}

int AStar::costH(Pair pos) {
    return (int)sqrt(pow(pos.first - x_f, 2) + pow(pos.second - y_f, 2));
}

void AStar::moveNode(int pos_x, int pos_y, Node curr_node) {
	for (int direction = 0; direction < 4; direction++) {
			pos_x = curr_node.position.first  + move[direction][0];
			pos_y = curr_node.position.second + move[direction][1];
			
			if (pos_x < 0 || pos_x > x - 1 || pos_y < 0 || pos_y > y - 1)
				continue;
			else if (grid[pos_x][pos_y] == 'o')
				continue;
			

			int h = costH(curr_node.position);
			int g = costG(curr_node.position);
			int f = h + g;
			Node new_node(h, g, f, make_pair(pos_x, pos_y), &curr_node);
			
			if (closed_list.find(new_node) != closed_list.end()) { // new_node is in the closed_list
				continue;
			} else if(open_set.find(new_node.position) == open_set.end()) {	// new_node is not in the open_set
				open_pq.push(new_node);
                open_set.insert(new_node.position);
			}
		}
}

bool AStar::checkTarget(Node end_node) {
	auto target = closed_list.find(end_node);
	if (target != closed_list.end()) { // found target in the closed_list
        cout << target->f + 2 << endl;
		return true;
	}
	return false;
}

void AStar::BeginPathSearch() {
	int pos_x;
	int pos_y;

	Node start_node(0, 0, 0, make_pair(x_0, y_0), nullptr);
	Node end_node(0, 0, 0, make_pair(x_f, y_f), nullptr);
	Node curr_node;

	open_pq.push(start_node);
    open_set.insert(start_node.position);
	
	while(!open_pq.empty()) {
        curr_node = open_pq.top();
        open_pq.pop();
        open_set.erase(open_set.find(curr_node.position));
		closed_list.insert(curr_node);

		moveNode(pos_x, pos_y, curr_node);

		if (checkTarget(end_node)) { // arrive at the end_node
			return;
		}
	}
	return;
}

int main() {
	AStar path_finding = AStar();

	path_finding.BeginPathSearch();

	return(0);
}