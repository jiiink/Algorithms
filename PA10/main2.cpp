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
    ifstream cin("./13_sample/04.inp");
    if (!cin) {
        cerr << "File not found" << endl;
        exit(1);
    }
    
    cin >> n;
    for (int i = 0; i < n; i++) {
        Point restaurant, customer;
        cin >> restaurant.x >> restaurant.y >> customer.x >> customer.y;
        restaurant.id = i + 1;
        customer.id = -1 * (i + 1);

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

vector<Point>::iterator find_nearest_point(Point from, vector<Point>& vec) {
    int min_distance = INT_MAX;
    vector<Point>::iterator nearest_point = vec.end();
    for (auto it = vec.begin(); it != vec.end(); it++) {
        int distance = manhattanDistance(from, *it);
        if (distance < min_distance) {
            min_distance = distance;
            nearest_point = it;
        }
    }
    return nearest_point;
}

vector<Point>::iterator find_customer_by_food(Point from, vector<Point>& vec, set<int>& foods) {
    int min_distance = INT_MAX;
    vector<Point>::iterator nearest_customer = vec.end();
    for (auto it = vec.begin(); it != vec.end(); it++) {
        if (foods.find(-it->id) != foods.end()) { // correct customer
            int distance = manhattanDistance(from, *it);
            if (distance < min_distance) {
                min_distance = distance;
                nearest_customer = it;
            }
        }
    }
    return nearest_customer;
}

void process() {
    vector<Point>::iterator nearest_point = find_nearest_point(init_point, restaurants);
    if (nearest_point != restaurants.end()) {
        solution.push_back(*nearest_point);
        restaurants.erase(nearest_point);
    }

    while (solution.size() != n * 2) {
        set<int> foods;
        for (auto& i : solution) {
            if (i.id > 0) {
                foods.insert(i.id);
            } else if (i.id < 0) {
                foods.erase(-i.id);
            }
        }

        Point current_point = solution.back();
        if (foods.size() == 2) { // max food
            vector<Point>::iterator nearest_customer = find_customer_by_food(current_point, customers, foods);
            if (nearest_customer != customers.end()) {
                solution.push_back(*nearest_customer);
                customers.erase(nearest_customer);
            }
        } else { // restaurant or customer
            vector<Point>::iterator nearest_restaurant = find_nearest_point(current_point, restaurants);
            vector<Point>::iterator nearest_customer = find_customer_by_food(current_point, customers, foods);

            int min_distance = INT_MAX;
            vector<Point>::iterator nearest_point = restaurants.end();
            if (nearest_restaurant != restaurants.end() && manhattanDistance(current_point, *nearest_restaurant) < min_distance) {
                nearest_point = nearest_restaurant;
                min_distance = manhattanDistance(current_point, *nearest_restaurant);
            }
            if (nearest_customer != customers.end() && manhattanDistance(current_point, *nearest_customer) < min_distance) {
                nearest_point = nearest_customer;
            }

            if (nearest_point != restaurants.end()) {
                solution.push_back(*nearest_point);
                if (nearest_point->id < 0) {
                    customers.erase(nearest_customer);
                } else {
                    restaurants.erase(nearest_restaurant);
                }
            }
        }
    }
}

void output() {
    int distance = manhattanDistance(init_point, solution.front());
    for (int i = 0; i < solution.size() - 1; i++) {
        distance += manhattanDistance(solution[i], solution[i + 1]);
    }
    for (auto& i : solution) {
        cout << i.id << " ";
    }
    cout << endl;
    cout << distance << endl;
}

int main() {
    input();
    process();
    output();
    return 0;
}
