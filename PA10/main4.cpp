#include <bits/stdc++.h>
// score 80
using namespace std;

struct Point {
    int x, y;
    int id;
    Point(int x, int y, int id) : x(x), y(y), id(id) {}
};

int manhattanDistance(Point a, Point b) {
    return abs(a.x - b.x) + abs(a.y - b.y);
}

void findBestRoute(int orderCount, vector<Point> &pickups, vector<Point> &deliveries, vector<int> &bestRoute, int &bestDistance) {
    vector<int> route;
    for (int i = 1; i <= orderCount; ++i) {
        route.push_back(i);
        route.push_back(-i);
    }
    
    sort(route.begin(), route.end());
    do {
        int distance = 0;
        int carried = 0;
        Point current(500, 500, 0);
        bool valid = true;
        vector<bool> picked(orderCount + 1, false);

        for (int id : route) {
            Point next = (id > 0) ? pickups[id - 1] : deliveries[-id - 1];
            distance += manhattanDistance(current, next);
            current = next;

            if (id > 0) {
                carried++;
                picked[id] = true;
            } else {
                if (!picked[-id]) {
                    valid = false;
                    break;
                }
                carried--;
            }

            if (carried < 0 || carried > 2) {
                valid = false;
                break;
            }
        }

        if (valid && distance < bestDistance) {
            bestDistance = distance;
            bestRoute = route;
        }
    } while (next_permutation(route.begin(), route.end()));
}

int main() {
    // fstream cin;
    // cin.open("./13_sample/05.inp");
    int orderCount;
    cin >> orderCount;
    
    vector<Point> pickups, deliveries;
    for (int i = 1; i <= orderCount; ++i) {
        int px, py, dx, dy;
        cin >> px >> py >> dx >> dy;
        pickups.push_back(Point(px, py, i));
        deliveries.push_back(Point(dx, dy, -i));
    }
    
    vector<int> bestRoute;
    int bestDistance = INT_MAX;
    
    findBestRoute(orderCount, pickups, deliveries, bestRoute, bestDistance);
    
    for (int id : bestRoute) {
        cout << id << " ";
    }
    cout << endl;
    cout << bestDistance << endl;

    return 0;
}
