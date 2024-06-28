#include <bits/stdc++.h>

using namespace std;

struct Ingredient {
    int protein, fat, sugar, vitamin, price;
};

int main() {
    int N;
    cin >> N;
    
    vector<int> min_nutrition(4);
    for (int i = 0; i < 4; ++i) {
        cin >> min_nutrition[i];
    }
    
    vector<Ingredient> ingredients(N);
    for (int i = 0; i < N; ++i) {
        cin >> ingredients[i].protein >> ingredients[i].fat >> ingredients[i].sugar >> ingredients[i].vitamin >> ingredients[i].price;
    }
    
    int min_price = INT_MAX;
    int max_nutrition_sum = -1;
    vector<int> best_combination;

    // Iterate through all subsets
    for (int subset = 1; subset < (1 << N); ++subset) {
        int total_protein = 0, total_fat = 0, total_sugar = 0, total_vitamin = 0, total_price = 0;
        vector<int> current_combination;

        for (int i = 0; i < N; ++i) {
            if (subset & (1 << i)) {
                cout << "subset: " << subset << "\t i: " << i << "\t1 << i: " << (1 << i) << endl;
                total_protein += ingredients[i].protein;
                total_fat += ingredients[i].fat;
                total_sugar += ingredients[i].sugar;
                total_vitamin += ingredients[i].vitamin;
                total_price += ingredients[i].price;
                current_combination.push_back(i + 1);
            }
        }

        if (total_protein >= min_nutrition[0] && total_fat >= min_nutrition[1] && total_sugar >= min_nutrition[2] && total_vitamin >= min_nutrition[3]) {
            int nutrition_sum = total_protein + total_fat + total_sugar + total_vitamin;
            if (total_price < min_price || (total_price == min_price && nutrition_sum > max_nutrition_sum) || 
                (total_price == min_price && nutrition_sum == max_nutrition_sum && current_combination < best_combination)) {
                min_price = total_price;
                max_nutrition_sum = nutrition_sum;
                best_combination = current_combination;
            }
        }
    }

    if (best_combination.empty()) {
        cout << 0 << endl;
    } else {
        for (int idx : best_combination) {
            cout << idx << " ";
        }
        cout << endl;
    }

    return 0;
}
