#include <bits/stdc++.h>
using namespace std;

typedef struct {
    int x, y;
    int id;
} Point;

Point init_point = {500, 500, 0};
vector<Point> points;
vector<Point> restaurants;
vector<Point> customers;
int n = 0;

void input() {
    ifstream cin("./13_sample/05.inp");
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

        points.push_back(restaurant);
        points.push_back(customer);
        restaurants.push_back(restaurant);
        customers.push_back(customer);
    }
}

int manhattanDistance(Point a, Point b) {
    return abs(a.x - b.x) + abs(a.y - b.y);
}

struct Individual {
    vector<int> chromosome;
    int fitness;
};

int calculate_fitness(vector<int>& chromosome) {
    vector<Point> route;
    route.push_back(init_point);
    for (int idx : chromosome) {
        route.push_back(points[idx]);
    }

    int total_distance = 0;
    for (int i = 0; i < route.size() - 1; i++) {
        total_distance += manhattanDistance(route[i], route[i + 1]);
    }
    return total_distance;
}

vector<int> create_chromosome() {
    vector<int> chromosome(points.size());
    iota(chromosome.begin(), chromosome.end(), 0);
    random_shuffle(chromosome.begin(), chromosome.end());
    return chromosome;
}

Individual create_individual() {
    Individual ind;
    ind.chromosome = create_chromosome();
    ind.fitness = calculate_fitness(ind.chromosome);
    return ind;
}

bool compare_individuals(const Individual& a, const Individual& b) {
    return a.fitness < b.fitness;
}

vector<Individual> selection(vector<Individual>& population) {
    sort(population.begin(), population.end(), compare_individuals);
    return vector<Individual>(population.begin(), population.begin() + population.size() / 2);
}

pair<Individual, Individual> crossover(const Individual& parent1, const Individual& parent2) {
    int size = parent1.chromosome.size();
    int crossover_point = rand() % size;

    Individual offspring1, offspring2;
    offspring1.chromosome = parent1.chromosome;
    offspring2.chromosome = parent2.chromosome;

    for (int i = crossover_point; i < size; i++) {
        swap(offspring1.chromosome[i], offspring2.chromosome[i]);
    }

    offspring1.fitness = calculate_fitness(offspring1.chromosome);
    offspring2.fitness = calculate_fitness(offspring2.chromosome);

    return {offspring1, offspring2};
}

void mutate(Individual& ind, double mutation_rate) {
    for (int i = 0; i < ind.chromosome.size(); i++) {
        if ((double)rand() / RAND_MAX < mutation_rate) {
            int swap_idx = rand() % ind.chromosome.size();
            swap(ind.chromosome[i], ind.chromosome[swap_idx]);
        }
    }
    ind.fitness = calculate_fitness(ind.chromosome);
}

void genetic_algorithm(int population_size, int generations, double mutation_rate) {
    srand(time(0));
    vector<Individual> population(population_size);
    for (int i = 0; i < population_size; i++) {
        population[i] = create_individual();
    }

    for (int generation = 0; generation < generations; generation++) {
        vector<Individual> selected = selection(population);

        while (selected.size() < population_size) {
            int parent1_idx = rand() % selected.size();
            int parent2_idx = rand() % selected.size();
            auto [offspring1, offspring2] = crossover(selected[parent1_idx], selected[parent2_idx]);
            selected.push_back(offspring1);
            selected.push_back(offspring2);
        }

        for (int i = 0; i < selected.size(); i++) {
            mutate(selected[i], mutation_rate);
        }

        population = selected;
    }

    sort(population.begin(), population.end(), compare_individuals);
    Individual best = population[0];

    vector<Point> best_route;
    best_route.push_back(init_point);
    for (int idx : best.chromosome) {
        best_route.push_back(points[idx]);
    }

    cout << "Best route order (point indices): ";
    for (int idx : best.chromosome) {
        cout << idx << " ";
    }
    cout << endl;

    int total_distance = calculate_fitness(best.chromosome);
    cout << "Total distance: " << total_distance << endl;
}

int main() {
    input();
    int population_size = 100;
    int generations = 1000;
    double mutation_rate = 0.01;

    genetic_algorithm(population_size, generations, mutation_rate);

    return 0;
}
