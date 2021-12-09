#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

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

std::vector<long long> solve(const std::string& text, const std::string& pattern, const long long& max_dif) {
	size_t tlen = text.length();
	size_t plen = pattern.length();
	std::vector<long long> z_func = z_function(pattern + text);
	std::string t_text = text;
	std::string t_pattern = pattern;
	std::reverse(t_pattern.begin(), t_pattern.end());
	std::reverse(t_text.begin(), t_text.end());
	std::vector<long long> reverse_z_func = z_function(t_pattern + t_text);
	std::vector<long long> ans;
	for (size_t i = 0; i < tlen - plen + 1; ++i) {
		if (z_func[i + plen] + reverse_z_func[tlen - i] + max_dif >= plen) {
			ans.push_back(i);
		}
	}
	return ans;
}


int main() {
	std::ios_base::sync_with_stdio(false);
	std::cin.tie(nullptr);
	std::cout.tie(nullptr);

	std::string text, pattern;
	std::cin >> text;
	std::cin >> pattern;
	long long max_dif;
	std::cin >> max_dif;

	std::vector<long long> ans = solve(text, pattern, max_dif);
	std::cout << ans.size() << std::endl;
	for (auto i : ans) {
		std::cout << i + 1 << ' ';
	}

	return 0;
}
