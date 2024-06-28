#include <bits/stdc++.h>
using namespace std;

int main() {
	vector<int> v = {0, 0, 1, 4, 3};
	set<int> s(v.begin(), v.end());

	for (auto i : s) {
		cout << i << " ";
	}
	return 0;
}
