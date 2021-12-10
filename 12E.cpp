#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <map>
#include <cmath>


long long lcp(long long i, long long j, const long long& n, const std::vector<std::vector<long long>>& classes) {
	long long ans = 0;
	for (int k = log2(n); k >= 0; --k)
		if (classes[k][i] == classes[k][j]) {
			ans += 1 << k;
			i += 1 << k;
			j += 1 << k;
		}
	return ans;
}

std::pair<std::vector<long long>, std::vector<std::vector<long long>>> suffix_array_classes(const std::string& cstr) {
	std::string str = cstr + '$';
	size_t slen = str.length();
	std::vector<long long> cnt(256, 0);
	std::vector<std::vector<long long>> classes(ceil(log2(slen)) + 1, std::vector<long long>(slen));
	std::vector<std::vector<long long>> part_sort(ceil(log2(slen)) + 1, std::vector<long long>(slen));

	long long num_cl = 1;
	for (size_t i = 0; i < slen; ++i) {
		++cnt[str[i]];
	}
	for (size_t i = 1; i < 256; ++i) {
		cnt[i] += cnt[i - 1];
	}
	for (size_t i = slen; i > 0; --i) {
		part_sort[0][--cnt[str[i - 1]]] = i - 1;
	}

	for (size_t i = 0; i < slen; ++i) {
		if (i == 0) {
			classes[0][part_sort[0][i]] = 0;
		}
		else {
			if (str[part_sort[0][i]] != str[part_sort[0][i - 1]]) {
				classes[0][part_sort[0][i]] = classes[0][part_sort[0][i - 1]] + 1;
				++num_cl;
			}
			else {
				classes[0][part_sort[0][i]] = classes[0][part_sort[0][i - 1]];
			}
		}
	}

	long long deg2 = 1;
	for (size_t i = 1; i <= ceil(log2(slen)); ++i) {
		std::vector<std::vector<long long>> temp_sort(num_cl);
		for (size_t j = 0; j < slen; ++j) {
			part_sort[i][j] = (part_sort[i - 1][j] + slen - deg2) % slen;
		}
		for (long long j = 0; j < slen; ++j) {
			temp_sort[classes[i - 1][(part_sort[i][j])]].push_back(part_sort[i][j]);
		}

		long long count = 0;
		for (size_t j = 0; j < num_cl; ++j) {
			for (size_t l = 0; l < temp_sort[j].size(); ++l) {
				part_sort[i][count] = temp_sort[j][l];
				++count;
			}
		}

		num_cl = 1;
		for (size_t j = 0; j < slen; ++j) {
			if (j == 0) {
				classes[i][part_sort[i][j]] = 0;
			}
			else {
				if (classes[i - 1][part_sort[i][j]] == classes[i - 1][part_sort[i][j - 1]] &&
					classes[i - 1][(part_sort[i][j] + deg2) % slen] == classes[i - 1][(part_sort[i][j - 1] + deg2) % slen]) {
					classes[i][part_sort[i][j]] = classes[i][part_sort[i][j - 1]];
				}
				else {
					classes[i][part_sort[i][j]] = classes[i][part_sort[i][j - 1]] + 1;
					++num_cl;
				}
			}
		}
		deg2 *= 2;
	}

	return { part_sort[ceil(log2(slen))], classes };
}

std::vector<long long> pref_substr_num(const std::string& cstr) {
	std::string str = cstr;
	std::reverse(str.begin(), str.end());
	if (str.length() == 1) {
		return { 1 };
	}
	else {
		std::vector<long long> substr_num;
		size_t slen = str.length() + 1;
		auto temp = suffix_array_classes(str);
		auto suf_arr = temp.first;
		auto classes = temp.second;
		std::map<long long, long long> pref;
		std::vector<long long> ind(slen);
		for (size_t i = 0; i < slen; ++i) {
			ind[suf_arr[i]] = i;
		}

		pref.insert({ ind[slen - 2], slen - 2 });
		long long ans = 1;
		substr_num.push_back(ans);
		for (int i = slen - 3; i >= 0; --i) {
			long long temp = 0;
			auto it = pref.lower_bound(ind[i]);
			if (it != pref.end()) {
				temp = lcp(i, (*it).second, slen, classes);
			}
			if (it != pref.begin()) {
				--it;
				if (ind[i] != 0) {
					temp = std::max(temp, lcp(i, (*it).second, slen, classes));
				}
			}
			ans += (slen - i - temp - 1);
			pref.insert({ ind[i], i });
			substr_num.push_back(ans);
		}
		return substr_num;
	}
}

int main() {
	std::ios_base::sync_with_stdio(false);
	std::cin.tie(nullptr);
	std::cout.tie(nullptr);

	std::string str;
	std::cin >> str;

	std::vector<long long> ans = pref_substr_num(str);
	for (auto i : ans) {
		std::cout << i << std::endl;
	}

	return 0;
}
