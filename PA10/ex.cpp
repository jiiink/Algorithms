#include <bits/stdc++.h>
using namespace std;
typedef struct {
    int x, y;
    int id;
} Point;


Point init_point = {500, 500, 0};
vector<pair<Point, Point>> orders;
vector<Point> points;
vector<Point> solution;
vector<Point> restaurants;
vector<Point> customers;
int n = 0;
void input() {
    cin >> n;
    
    for (int i=0; i<n; i++) {
        Point restaurant, customer;
        cin >> restaurant.x >> restaurant.y >> customer.x >> customer.y;
        restaurant.id = i + 1;
        customer.id = restaurant.id * (-1);

        orders.push_back(make_pair(restaurant, customer));

        points.push_back(restaurant);
        points.push_back(customer);

        restaurants.push_back(restaurant);
        customers.push_back(customer);
    }
}
int manhattanDistance(Point a, Point b) {
    return abs(a.x - b.x) + abs(a.y - b.y);
}
int main() {
    input();
    for (auto i : orders) {
        cout << "Restaurant: " << i.first.id << " (" << i.first.x << ", " << i.first.y << ")"
             << "\tCustomer: " << i.second.id << " (" << i.second.x << ", " << i.second.y << ")\n";
    }
    int distance = 0;
    int min_distance = INT_MAX;
    vector<Point>::iterator nearest_point;
    // for (auto restaurant : restaurants) {
    //     distance = manhattanDistance(init_point, restaurant);
    //     if (distance < min_distance) {
    //         min_distance = distance;
    //         nearest_point = restaurant;
    //     }
    // }
    for (auto it = restaurants.begin(); it != restaurants.end(); it++) {
        distance = manhattanDistance(init_point, *it);
        if (distance < min_distance) {
            min_distance = distance;
            nearest_point = it;
        }
    }
    solution.push_back(*nearest_point);

    for (auto c : restaurants) {
        cout << c.id << " ";
    }
    cout << endl;

    restaurants.erase(nearest_point);

    for (auto c : restaurants) {
        cout << c.id << " ";
    }
    cout << endl;
}