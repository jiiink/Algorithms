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

	
	// bool isOnList(Node node, vector<Node> list);
    Node* getFromList(Node node, vector<Node> list);

	int costH(Pair pos);
	int costG(Node node, Pair pos);
};

AStar::AStar()
{

    fstream cin;
    cin.open("./sample_data/9.inp");

    cin >> x >> y;
    grid = new char*[x];

    // vector<vector<char>> grid(x, vector<char>(y, '.'));
    // this->grid = grid;

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



// bool AStar::isOnList(Node node, vector<Node> list)
// {
//     // int mid = list.size() / 2;


// 	for (int i = 0; i < list.size(); i++)
// 	{
// 		if (node == list[i])
// 			return true;
// 	}
// 	return false;
// }

Node* AStar::getFromList(Node node, vector<Node> list) {
    for (int i=0; i<list.size(); i++) {
        if (node == list[i])
            return &list[i];
    }
    return nullptr;
}



void AStar::costF(Node new_node, Node curr_node)
{
	new_node.h = costH(new_node.position);
	new_node.g = costG(new_node, curr_node.position);
	new_node.f = new_node.h + new_node.g;
}

void AStar::BeginPathSearch()
{
	int pos_x;
	int pos_y;
	int index;
	int curr_pos;

	Node start_node;
	Node curr_node;
	Node end_node;

	Node *new_node;

	vector<Node>	open_list;
	vector<Node>	closed_list;

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

	
	open_list.push_back(start_node);
	
	while(!open_list.empty())
	{
		index 		= 0;
		curr_node 	= open_list[0];
		for (int i = 0; i < open_list.size(); i++) 	
		{	
			if (open_list[i].f < curr_node.f)
			{	
				index 	  = i;
				curr_node = open_list[i];
			}
		}
		open_list.erase(open_list.begin() + index);
		closed_list.push_back(curr_node);

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
			
			if (getFromList(*new_node, closed_list) != nullptr)
				continue;

			else if(getFromList(*new_node, open_list) == nullptr)
			{	
				open_list.push_back(*new_node);
			}
		}

        Node* target = getFromList(end_node, open_list);
		if (target != nullptr)
		{
            // Node* target = getFromList(end_node, closed_list);
            cout << target->f + 2 << endl;
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