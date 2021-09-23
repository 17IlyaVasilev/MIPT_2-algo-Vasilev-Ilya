#include <iostream>
#include <algorithm>
#include <vector>
#include <cmath>
#include <string>


using namespace std;


vector<int> z_function(const string& str) {
	int n = str.length();
	vector<int> z(n);
	int l = -1, r = -1;
	z[0] = 0;
	for (int i = 1; i < n; ++i) {
		if (l <= i && i <= r) {
			z[i] = min(z[i - l], r - i + 1);
		}

		while (z[i] + i < n && str[z[i]] == str[i + z[i]]) {
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

	string text, pattern;
	cin >> text;
	cin >> pattern;

	string str = pattern + "#" + text;
	vector<int> z = z_function(str);

	for (int i = pattern.length() + 1; i < str.length(); ++i) {
		if (z[i] == pattern.length()) {
			cout << i - pattern.length() - 1 << " ";
		}
	}

	return 0;
}