#include <bits/stdc++.h>

using namespace std;

typedef pair<int, int> Pair;

class Node
{
	public:
	
	int h;
	int g;
	int f;
	
	Pair position;
	
	
	Node *parent;
	
	bool operator== (const Node &node);

    bool operator<(const Node& other) const {
        return position < other.position;
    }
};

bool Node::operator== (const Node &node)
{
	return (node.position.first  == this->position.first &&
		node.position.second == this->position.second);
}

class AStar
{

private:	

	int 	  x;
	int 	  y;

	int 	x_0;
	int 	y_0;

	int x_f;
	int y_f;

	
	char **grid;
    // vector<vector<char> > grid;
	
	int move[4][2] ={{1 ,	0}, 		
			{-1,	0}, 
			{0,	1}, 
			{0,	-1},
			 };
	
	
public:
	AStar();
	~AStar();
	
	void BeginPathSearch();

	void costF(Node new_node, Node curr_node);

	int costH(Pair pos);
	int costG(Node node, Pair pos);
};

AStar::AStar()
{

    // fstream cin;
    // cin.open("./sample_data/10.inp");

    cin >> x >> y;
    grid = new char*[x];

	for (int i = 0; i < y; i++)
	{
		grid[i] = new char[y];
		for (int j = 0; j < x; j++)
		{
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

AStar::~AStar()
{
	delete *grid;
}


int AStar::costG(Node node, Pair pos)
{
    return (abs(x_0 - pos.first) + abs(y_0 - pos.second)) * 3;
}

int AStar::costH(Pair pos)
{
    return (int)sqrt(pow(pos.first - x_f, 2) + pow(pos.second - y_f, 2));
}





void AStar::costF(Node new_node, Node curr_node)
{
	new_node.h = costH(new_node.position);
	new_node.g = costG(new_node, curr_node.position);
	new_node.f = new_node.h + new_node.g;
}



struct comp {
    bool operator()(const Node& a, const Node& b) {
        return a.f >= b.f;
    }
};

void AStar::BeginPathSearch()
{
	int pos_x;
	int pos_y;
	// int index;
	int curr_pos;

	Node start_node;
	Node curr_node;
	Node end_node;

	Node *new_node;

	priority_queue<Node, vector<Node>, comp>	open_pq;
    set<Pair> open_set;
	set<Node>	closed_list;

    start_node.position = make_pair(x_0, y_0);
    end_node.position =   make_pair(x_f, y_f);

	start_node.g = 	0;
	start_node.h = 	0;
	start_node.f = 	0;

	end_node.g = 	0;
	end_node.h = 	0;
	end_node.f = 	0;

	start_node.parent = nullptr;
	end_node.parent	  = nullptr;

	
	open_pq.push(start_node);
    open_set.insert(start_node.position);
	
	while(!open_pq.empty())
	{
        curr_node = open_pq.top();
        open_pq.pop();
        open_set.erase(open_set.find(curr_node.position));
		// open_list.erase(open_list.begin() + index);
		closed_list.insert(curr_node);

		for (curr_pos = 0; curr_pos < 4; curr_pos++)
		{
			
			pos_x = curr_node.position.first  + move[curr_pos][0];
			pos_y = curr_node.position.second + move[curr_pos][1];

			
			if (pos_x < 0 || pos_x > x - 1 || pos_y < 0 || pos_y > y - 1)
				continue;
			else if (grid[pos_x][pos_y] == 'o')
				continue;
			
			new_node = new Node;
            new_node->position = make_pair(pos_x, pos_y);
            new_node->parent = &curr_node;
			new_node->g = costG(*new_node, curr_node.position);
            new_node->h = costH(curr_node.position);
			new_node->f = new_node->g + new_node->h;
			
			if (closed_list.find(*new_node) != closed_list.end()) // is in a closed
				continue;

			else if(open_set.find(new_node->position) == open_set.end()) // is not in a open
			{	
				open_pq.push(*new_node);
                open_set.insert(new_node->position);
			}
		}

        // Node target = getFromList(end_node, closed_list);
        auto it = closed_list.find(end_node);
        
		if (it != closed_list.end())
		{
            cout << it->f + 2 << endl;
			return;
		}
	}
	cout << "There is no path !" << endl;
	return;
}

int main()
{
	AStar path_finding = AStar();

	path_finding.BeginPathSearch();


	return(0);
}