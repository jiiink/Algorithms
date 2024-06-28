#include <bits/stdc++.h>
using namespace std;
#define COORDINATES 4

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
    fstream cin;
    cin.open("./13_sample/05.inp");
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


vector<Point>::iterator find_nearest_point(Point from, vector<Point>& vec) {
    int distance = 0;
    int min_distance = INT_MAX;
    vector<Point>::iterator nearest_point = vec.end();
    for (auto it = vec.begin(); it != vec.end(); it++) {
        distance = manhattanDistance(from, *it);
        if (distance < min_distance) {
            min_distance = distance;
            nearest_point = it;
        }
    }
    return nearest_point;
}

vector<Point>::iterator find_customer_by_food(Point from, vector<Point>& vec, set<int>& foods) {
    // Point current_point = solution.back();
    int distance = 0;
    int min_distance = INT_MAX;
    vector<Point>::iterator nearest_customer = vec.end();
          
    for (auto it = customers.begin(); it != customers.end(); it++) {
        if (foods.find(it->id * (-1)) != foods.end()) { // correct customer
            distance = manhattanDistance(from, *it);
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
    solution.push_back(*nearest_point);
    restaurants.erase(nearest_point);


    // cout << "Nearest : " << solution[0].id << endl;
    while (solution.size() != n * 2) {
        // int food_count = 0;
        set<int> foods;
        for (auto i : solution) { // check food count
            if (i.id > 0) {
                // food_count++;
                foods.insert(i.id);
            }
            else if (i.id < 0) {
                // food_count--;
                foods.erase(i.id * (-1));
            }
        }
        
        if (foods.size() == 2) { // max food
            Point current_point = solution.back();

            vector<Point>::iterator nearest_customer = find_customer_by_food(current_point, customers, foods);

            solution.push_back(*nearest_customer);
            customers.erase(nearest_customer);
        }
        else { // restaurant or customer
            Point current_point = solution.back();
            vector<Point>::iterator nearest_restaurant = find_nearest_point(current_point, restaurants);

            if (foods.size() == 0) {
                solution.push_back(*nearest_restaurant);
                restaurants.erase(nearest_restaurant);
            }
            else {
                vector<Point>::iterator nearest_customer = find_customer_by_food(current_point, customers, foods);

                int distance = 0;
                int min_distance = INT_MAX;

                vector<Point>::iterator nearest_point;
                vector<vector<Point>::iterator> next_points;

                if (nearest_customer != customers.end()) {
                    next_points.push_back(nearest_customer);
                }
                if (nearest_restaurant != restaurants.end()) {
                    next_points.push_back(nearest_restaurant);
                }
                
                for (auto it = next_points.begin(); it != next_points.end(); it++) {
                    distance = manhattanDistance(current_point, *(*it));
                    if (distance < min_distance) {
                        min_distance = distance;
                        nearest_point = *it;
                    }
                }

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
    for (int i=0; i<solution.size() - 1; i++) {
        distance += manhattanDistance(solution[i], solution[i+1]);
    }
    for (auto i : solution) {
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