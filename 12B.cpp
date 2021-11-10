﻿#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <cmath>


using namespace std;


long long lcp(long long i, long long j, const long long& n, const vector<vector<long long>>& classes) {
	long long ans = 0;
	for (long long k = log2(n); k >= 0; --k)
		if (classes[k][i] == classes[k][j]) {
			ans += 1 << k;
			i += 1 << k;
			j += 1 << k;
		}
	return ans;
}


int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);
	cout.tie(nullptr);

	string s;
	cin >> s;
	long long num;
	cin >> num;

	s += '$';
	size_t slen = s.length();
	vector<long long> cnt(256, 0);
	vector<vector<long long>> classes(ceil(log2(slen)) + 1, vector<long long>(slen));
	vector<vector<long long>> part_sort(ceil(log2(slen)) + 1, vector<long long>(slen));
	long long num_cl = 1;

	for (long long i = 0; i < slen; ++i) {
		++cnt[s[i]];
	}

	for (long long i = 1; i < 256; ++i) {
		cnt[i] += cnt[i - 1];
	}

	for (long long i = slen - 1; i >= 0; --i) {
		part_sort[0][--cnt[s[i]]] = i;
	}

	for (long long i = 0; i < slen; ++i) {
		if (i == 0) classes[0][part_sort[0][i]] = 0; else
			if (s[part_sort[0][i]] != s[part_sort[0][i - 1]]) {
				classes[0][part_sort[0][i]] = classes[0][part_sort[0][i - 1]] + 1;
				++num_cl;
			}
			else classes[0][part_sort[0][i]] = classes[0][part_sort[0][i - 1]];
	}

	long long k = ceil(log2(slen));
	long long deg2 = 1;
	for (long long i = 1; i <= k; ++i) {
		vector<vector<long long>> temp_sort(num_cl);

		for (long long j = 0; j < slen; ++j) {
			part_sort[i][j] = (part_sort[i - 1][j] + slen - deg2) % slen;
		}

		for (long long j = 0; j < slen; ++j) {
			temp_sort[classes[i - 1][(part_sort[i][j])]].push_back(part_sort[i][j]);
		}
		long long count = 0;
		for (long long j = 0; j < num_cl; ++j) {
			for (long long l = 0; l < temp_sort[j].size(); ++l) {
				part_sort[i][count] = temp_sort[j][l];
				++count;
			}
		}

		num_cl = 1;
		for (long long j = 0; j < slen; ++j) {
			if (j == 0) classes[i][part_sort[i][j]] = 0; else
				if (classes[i - 1][part_sort[i][j]] == classes[i - 1][part_sort[i][j - 1]] &&
					classes[i - 1][(part_sort[i][j] + deg2) % slen] == classes[i - 1][(part_sort[i][j - 1] + deg2) % slen])
					classes[i][part_sort[i][j]] = classes[i][part_sort[i][j - 1]]; else {
					classes[i][part_sort[i][j]] = classes[i][part_sort[i][j - 1]] + 1;
					++num_cl;
				}
		}

		deg2 *= 2;
	}

	long long count = 1;
	--slen;
	num -= (slen - part_sort[k][1]);
	while (num > 0 && count < slen) {
		++count;
		num -= (slen - part_sort[k][count] - lcp(part_sort[k][count - 1], part_sort[k][count], slen, classes));
	}

	if (num > 0) {
		for (long long i = part_sort[k][slen]; i < slen; ++i) {
			cout << s[i];
		}
	}
	else {
		for (long long i = part_sort[k][count]; i < slen + num; ++i) {
			cout << s[i];
		}
	}


	return 0;
}