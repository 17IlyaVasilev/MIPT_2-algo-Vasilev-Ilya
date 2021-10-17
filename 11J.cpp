#include <iostream>
#include <algorithm>
#include <vector>
#include <cmath>
#include <string>


using namespace std;


vector<long long> z_function(const string& str) {
	long long n = str.length();
	vector<long long> z(n);
	long long l = -1, r = -1;
	z[0] = 0;
	for (long long i = 1; i < n; ++i) {
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

vector<long long> solve(const string& text, const string& pattern, const long long& k) {
	long long tl = text.length();
	long long pl = pattern.length();
	vector<long long> z = z_function(pattern + text);
	string t_text = text;
	string t_pattern = pattern;
	reverse(t_pattern.begin(), t_pattern.end());
	reverse(t_text.begin(), t_text.end());
	vector<long long> rz = z_function(t_pattern + t_text);

	vector <long long> ans;
	for (long long i = 0; i < tl - pl + 1; ++i) {
		if (z[i + pl] + rz[tl - i] + k >= pl) {
			ans.push_back(i);
		}
	}

	return ans;
}


int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);
	cout.tie(nullptr);

	string text, pattern;
	cin >> text;
	cin >> pattern;
	long long k;
	cin >> k;

	vector<long long> ans = solve(text, pattern, k);

	cout << ans.size() << endl;
	for (auto i : ans) {
		cout << i + 1 << ' ';
	}

	return 0;
}