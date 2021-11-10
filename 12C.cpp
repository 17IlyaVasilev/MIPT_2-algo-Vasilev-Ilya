#include <iostream>
#include <algorithm>
#include <vector>


using namespace std;


class SuffAuto {
private:
	struct Node {
		long long end = 0;
		long long len = 0;
		long long link = -1;
		bool term = false;
		vector <long long> to;

		long long count = 0;
		bool used = false;

		Node(const long long& m) {
			to.assign(m, -1);
		}

		//Node operator= (const Node& node) = delete;

		//~Node() {};
	};

	long long n = 0;
	long long m = 0;
	long long last = 0;
	long long maxx = -1;
	long long ind = -1;
	vector<Node> t;

public:
	SuffAuto(const long long&, const long long&);
	//SuffAuto operator= (const SuffAuto& suffauto) = delete;
	long long dfs(const long long&);
	void add(const long long&, long long&);
	vector<long long> answer();
	//~SuffAuto() {};
};


SuffAuto::SuffAuto(const long long& num, const long long& dif) {
	m = dif;
	n = num;
	t.push_back(Node(dif));
	t.back().term = true;
}


long long SuffAuto::dfs(const long long& v) {
	if (t[v].used) {
		return t[v].count;
	}
	else {
		t[v].used = true;
	}

	if (t[v].term) {
		t[v].count = 1;
	}
	else {
		t[v].count = 0;
	}


	for (long long i = 0; i < t[v].to.size(); ++i) {
		if (t[v].to[i] > 0) {
			t[v].count += dfs(t[v].to[i]);
		}
	}

	if (maxx < t[v].len * t[v].count) {
		ind = v;
		maxx = max(maxx, t[v].len * t[v].count);
	}

	return t[v].count;
}


void SuffAuto::add(const long long& c, long long& index) {
	t.push_back(Node(m));

	auto curr = t.size() - 1;
	auto p = last;
	while (p != -1 && t[p].to[c] == -1) {
		t[p].to[c] = curr;
		p = t[p].link;
	}

	t[curr].end = index;
	t[curr].len = t[curr].end + 1;
	if (p == -1) {
		t[curr].link = 0;
		last = curr;
		return;
	}

	auto q = t[p].to[c];
	if (t[q].len == t[p].len + 1) {
		t[curr].link = q;
		last = curr;
		return;
	}

	t.push_back(Node(m));
	auto clone = t.size() - 1;
	t[clone].len = t[p].len + 1;
	t[clone].end = t[q].end;
	while (p != -1 && t[p].to[c] == q) {
		t[p].to[c] = clone;
		p = t[p].link;
	}
	t[clone].to = t[q].to;
	t[clone].link = t[q].link;
	t[q].link = clone;
	t[curr].link = clone;
	last = curr;
}


vector<long long> SuffAuto::answer() {
	vector<long long> ans(3, 0);

	long long v = last;
	while (v != -1) {
		t[v].term = true;
		v = t[v].link;
	}

	dfs(0);

	ans[0] = maxx;
	ans[1] = t[ind].end;
	ans[2] = t[ind].len;

	return ans;
}



int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);
	cout.tie(nullptr);

	long long n, m;
	cin >> n >> m;

	SuffAuto suffauto(n, m);
	vector<long long> s(n, 0);

	for (long long i = 0; i < n; ++i) {
		cin >> s[i];
		suffauto.add(s[i] - 1, i);
	}

	vector<long long> ans = suffauto.answer();
	cout << ans[0] << endl;
	cout << ans[2] << endl;

	for (long long i = ans[1] - ans[2]; i < ans[1]; ++i) {
		cout << s[i + 1] << ' ';
	}

	return 0;
}