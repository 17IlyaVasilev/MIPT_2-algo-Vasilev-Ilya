#include <iostream>
#include <algorithm>
#include <vector>

class SuffAuto {
private:
	struct Node {
		long long end = 0;
		long long len = 0;
		long long link = -1;
		bool term = false;
		std::vector <long long> to;

		long long count = 0;
		bool used = false;

		Node(const long long& m) {
			to.assign(m, -1);
		}
	};

	long long num = 0;
	long long alpha_num = 0;
	long long last = 0;
	long long max = -1;
	long long ind = -1;
	std::vector<Node> nodes;

public:
	SuffAuto(const long long&, const long long&);
	long long dfs(const long long&);
	void add(const long long&, const size_t&);
	std::vector<long long> answer();
};


SuffAuto::SuffAuto(const long long& num, const long long& dif): num(num), alpha_num(dif){
	nodes.push_back(Node(dif));
	nodes.back().term = true;
}


long long SuffAuto::dfs(const long long& vert) {
	if (nodes[vert].used) {
		return nodes[vert].count;
	}
	else {
		nodes[vert].used = true;
	}

	if (nodes[vert].term) {
		nodes[vert].count = 1;
	}
	else {
		nodes[vert].count = 0;
	}
	for (size_t i = 0; i < nodes[vert].to.size(); ++i) {
		if (nodes[vert].to[i] > 0) {
			nodes[vert].count += dfs(nodes[vert].to[i]);
		}
	}
	if (max < nodes[vert].len * nodes[vert].count) {
		ind = vert;
		max = std::max(max, nodes[vert].len * nodes[vert].count);
	}
	return nodes[vert].count;
}


void SuffAuto::add(const long long& c, const size_t& index) {
	nodes.push_back(Node(alpha_num));
	auto curr = nodes.size() - 1;
	auto vert = last;

	while (vert != -1 && nodes[vert].to[c] == -1) {
		nodes[vert].to[c] = curr;
		vert = nodes[vert].link;
	}
	nodes[curr].end = index;
	nodes[curr].len = nodes[curr].end + 1;
	if (vert == -1) {
		nodes[curr].link = 0;
		last = curr;
		return;
	}

	auto new_vert = nodes[vert].to[c];
	if (nodes[new_vert].len == nodes[vert].len + 1) {
		nodes[curr].link = new_vert;
		last = curr;
		return;
	}
	nodes.push_back(Node(alpha_num));
	auto clone = nodes.size() - 1;
	nodes[clone].len = nodes[vert].len + 1;
	nodes[clone].end = nodes[new_vert].end;
	while (vert != -1 && nodes[vert].to[c] == new_vert) {
		nodes[vert].to[c] = clone;
		vert = nodes[vert].link;
	}
	nodes[clone].to = nodes[new_vert].to;
	nodes[clone].link = nodes[new_vert].link;
	nodes[new_vert].link = clone;
	nodes[curr].link = clone;
	last = curr;
}


std::vector<long long> SuffAuto::answer() {
	std::vector<long long> ans(3, 0);
	long long vert = last;
	while (vert != -1) {
		nodes[vert].term = true;
		vert = nodes[vert].link;
	}
	dfs(0);
	ans[0] = max;
	ans[1] = nodes[ind].end;
	ans[2] = nodes[ind].len;
	return ans;
}



int main() {
	std::ios_base::sync_with_stdio(false);
	std::cin.tie(nullptr);
	std::cout.tie(nullptr);

	long long n, m;
	std::cin >> n >> m;

	SuffAuto suffauto(n, m);
	std::vector<long long> seq(n, 0);
	for (size_t i = 0; i < n; ++i) {
		std::cin >> seq[i];
		suffauto.add(seq[i] - 1, i);
	}

	std::vector<long long> ans = suffauto.answer();
	std::cout << ans[0] << std::endl;
	std::cout << ans[2] << std::endl;
	for (int i = ans[1] - ans[2]; i < ans[1]; ++i) {
		std::cout << seq[i + 1] << ' ';
	}

	return 0;
}
