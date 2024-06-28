#include <bits/stdc++.h>

using namespace std;

struct Point {
    int x, y;
    int id;
    Point(int x, int y, int id) : x(x), y(y), id(id) {}
};



Point start = {500, 500, 0};
int orderCount;
vector<Point> pickups, deliveries;
void input() {
    // fstream cin;
    // cin.open("./13_sample/05.inp");
    cin >> orderCount;

    for (int i = 1; i <= orderCount; ++i) {
        int px, py, dx, dy;
        cin >> px >> py >> dx >> dy;
        pickups.emplace_back(px, py, i);
        deliveries.emplace_back(dx, dy, -i);
    }
}

int manhattanDistance(Point a, Point b) {
    return abs(a.x - b.x) + abs(a.y - b.y);
}

void process(Point current, int foods, int distance, int orderCount,
               vector<Point> &pickups, vector<Point> &deliveries,
               vector<bool> &picked, vector<bool> &delivered,
               vector<int> &currentRoute, vector<int> &bestRoute, int &bestDistance) {
    if (distance > bestDistance) return; 

    if (currentRoute.size() == orderCount * 2) { 
        if (distance < bestDistance || (distance == bestDistance && currentRoute < bestRoute)) {
            bestDistance = distance;
            bestRoute = currentRoute;
        }
        return;
    }

    for (int i = 0; i < orderCount; ++i) {
        if (!picked[i]) { 
            if (foods < 2) {  // 2 foods at a time
                picked[i] = true;
                currentRoute.push_back(i + 1);
                process(pickups[i], foods + 1, distance + manhattanDistance(current, pickups[i]),
                          orderCount, pickups, deliveries, picked, delivered, currentRoute, bestRoute, bestDistance);
                picked[i] = false;
                currentRoute.pop_back();
            }
        } 
        if (picked[i] && !delivered[i]) { 
            delivered[i] = true;
            currentRoute.push_back(-(i + 1));
            process(deliveries[i], foods - 1, distance + manhattanDistance(current, deliveries[i]),
                      orderCount, pickups, deliveries, picked, delivered, currentRoute, bestRoute, bestDistance);
            delivered[i] = false;
            currentRoute.pop_back();
        }
    }
}

void output(vector<int> bestRoute, int bestDistance) {
    for (int id : bestRoute) {
            cout << id << " ";
    }
    cout << endl;
    cout << bestDistance << endl;
}

int main() {

    input();

    vector<int> currentRoute;
    vector<int> bestRoute(orderCount * 2);
    int bestDistance = INT_MAX;
    vector<bool> picked(orderCount, false);
    vector<bool> delivered(orderCount, false);
    
    process(start, 0, 0, orderCount, pickups, deliveries, picked, delivered, currentRoute, bestRoute, bestDistance);


    output(bestRoute, bestDistance);
    

    return 0;
}
