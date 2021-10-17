#include <iostream>
#include <algorithm>
#include <vector>
#include <cmath>
#include <string>
#include <set>


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

long long sum_all_subwords(const string& cstr) {
	string str = cstr;
	long long ans = 0;

	set<string> s;
	vector<int> num;
	string nstr = "";
	vector<int> maxx(str.length(), 0);

	for (int i = 1; i <= str.length(); ++i) {
		ans += i * (str.length() - i + 1);
	}

	for (int i = str.length() - 1; i >= 0; --i) {
		nstr = str[i] + nstr;
		vector<int> z = z_function(nstr);

		for (int j = 0; j < z.size(); ++j) {
			if (z[j] > 0 && maxx[str.length() - nstr.length() + j] < z[j]) {
				ans -= (z[j] * (z[j] + 1) / 2 - maxx[str.length() - nstr.length() + j] * (maxx[str.length() - nstr.length() + j] + 1) / 2);
				maxx[str.length() - nstr.length() + j] = max(maxx[str.length() - nstr.length() + j], z[j]);
			}
		}
	}

	return ans;
}


int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);
	cout.tie(nullptr);

	string str;
	cin >> str;

	cout << sum_all_subwords(str);

	return 0;
}