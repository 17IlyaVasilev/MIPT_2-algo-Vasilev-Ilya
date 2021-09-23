#include <iostream>
#include <algorithm>
#include <vector>
#include <cmath>


using namespace std;


vector<int> z_function(const vector<int>& mas) {
	int n = mas.size();
	vector<int> z(n);
	int l = -1, r = -1;
	z[0] = 0;
	for (int i = 1; i < n; ++i) {
		if (l <= i && i <= r) {
			z[i] = min(z[i - l], r - i + 1);
		}

		while (z[i] + i < n && mas[z[i]] == mas[i + z[i]]) {
			++z[i];
		}

		if (i + z[i] - 1 > r) {
			l = i;
			r = i + z[i] - 1;
		}
	}

	return z;
}


int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);
	cout.tie(nullptr);

	int n, m;
	cin >> n >> m;

	vector <int> mas(n);
	for (int i = 0; i < n; ++i)
		cin >> mas[i];

	for (int i = n - 1; i >= 0; --i) {
		mas.push_back(mas[i]);
	}

	vector<int> z = z_function(mas);

	for (int i = (n + 1) / 2; i < n; ++i) {
		if (z[2 * i] == 2 * (n - i)) {
			cout << i << " ";
		}
	}
	cout << n;

	return 0;
}