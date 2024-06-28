#include <bits/stdc++.h>

using namespace std;

#define NUTRITIONS 4

struct Ingredient {
    int protein, fat, sugar, vitamin, price;
};

int N;
vector<int> min_nutrition(NUTRITIONS);

vector<Ingredient> input() {
    cin >> N;

    for (int i=0; i<NUTRITIONS; i++) {
        cin >> min_nutrition[i];
    }

    vector<Ingredient> ingredients(N);
    for (int i=0; i<N; i++) {
        cin >> ingredients[i].protein >> ingredients[i].fat >> ingredients[i].sugar >> ingredients[i].vitamin >> ingredients[i].price;
    }

    return ingredients;
}

vector<int> process(vector<Ingredient> ingredients) {
    int min_price = INT_MAX;
    int max_nutrition_sum = -1;
    vector<int> best_set;

    for (int subset = 1; subset < (1 << N); subset++) {
        int total_protein = 0, total_fat = 0, total_sugar = 0, total_vitamin = 0, total_price = 0;
        vector<int> current_set;

        for (int i=0; i<N; i++) {
            if (subset & (1 << i)) {
                total_protein += ingredients[i].protein;
                total_fat += ingredients[i].fat;
                total_sugar += ingredients[i].sugar;
                total_vitamin += ingredients[i].vitamin;
                total_price += ingredients[i].price;
                current_set.push_back(i+1);
            }
        }

        if (total_protein >= min_nutrition[0] && total_fat >= min_nutrition[1] && total_sugar >= min_nutrition[2] && total_vitamin >= min_nutrition[3]) {
            int nutrition_sum = total_protein + total_fat + total_sugar + total_vitamin;
            if (total_price < min_price ||                                          // check price
                (total_price == min_price && nutrition_sum > max_nutrition_sum) ||  // check nutrition_sum
                (total_price == min_price && nutrition_sum == max_nutrition_sum && current_set < best_set)) { // check low index
                min_price = total_price;
                max_nutrition_sum = nutrition_sum;
                best_set = current_set;
            }
        }
    }

    return best_set;
}

void output(vector<int> best_set) {
    if (best_set.empty()) {
        cout << "0\n";
    } else {
        for (auto index : best_set) {
            cout << index << " ";
        }
        cout << endl;
    }
}

int main() {

    auto ingredients = input();

    auto best_set = process(ingredients);

    output(best_set);

    return 0;
}
