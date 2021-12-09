#include <iostream>
#include <vector>
#include <string>
#include <set>


std::vector<long long> z_function(const std::string& str) {
	size_t num = str.length();
	std::vector<long long> z_func(num);
	long long left = -1;
	long long right = -1;
	z_func[0] = 0;
	for (size_t i = 1; i < num; ++i) {
		if (left <= i && i <= right) {
			z_func[i] = std::min(z_func[i - left], right - i + 1);
		}

		while (z_func[i] + i < num && str[z_func[i]] == str[i + z_func[i]]) {
			++z_func[i];
		}

		if (i + z_func[i] - 1 > right) {
			left = i;
			right = i + z_func[i] - 1;
		}
	}
	return z_func;
}

long long sum_all_subwords(const std::string& cstr) {
	std::string str = cstr;
	long long ans = 0;
	std::string new_str = "";
	std::vector<long long> max(str.length(), 0);
	for (size_t i = 1; i <= str.length(); ++i) {
		ans += i * (str.length() - i + 1);
	}

	for (int i = str.length() - 1; i >= 0; --i) {
		new_str = str[i] + new_str;
		std::vector<long long> z_func = z_function(new_str);
		for (size_t j = 0; j < z_func.size(); ++j) {
			if (z_func[j] > 0 && max[str.length() - new_str.length() + j] < z_func[j]) {
				ans -= (z_func[j] * (z_func[j] + 1) / 2 - max[str.length() - new_str.length() + j] * (max[str.length() - new_str.length() + j] + 1) / 2);
				max[str.length() - new_str.length() + j] = std::max(max[str.length() - new_str.length() + j], z_func[j]);
			}
		}
	}
	return ans;
}


int main() {
	std::ios_base::sync_with_stdio(false);
	std::cin.tie(nullptr);
	std::cout.tie(nullptr);

	std::string str;
	std::cin >> str;

	std::cout << sum_all_subwords(str);

	return 0;
}
