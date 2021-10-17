#include<iostream>
#include<map>
#include<cmath>
#include<vector>
#include<string>


using namespace std;


struct Node {
	map<char, int> to;
	vector<int> term;
};


void add(const string& str, vector<Node>& trie, int& cont) {
	int v = 0;
	for (int i = 0; i < str.size(); ++i) {
		if (!trie[v].to.count(str[i])) {
			trie.push_back(Node());
			trie[v].to[str[i]] = int(trie.size()) - 1;
		}
		v = trie[v].to[str[i]];
	}
	trie[v].term.push_back(cont - 1);
}


void bor_sort(const Node& v, const vector<Node>& trie, const vector<string>& s, vector<string>& ss) {
	for (int i = 0; i < v.term.size(); ++i) {
		ss.push_back(s[v.term[i]]);
	}

	for (auto i : v.to) {
		bor_sort(trie[i.second], trie, s, ss);
	}
}


pair<vector<int>, vector<string>> distribution(const string& cstr) {
	string str = cstr;

	vector<int> a;
	vector<string> s;
	string temp = "";

	bool flag = (str[0] == '.');
	bool flagx = flag;
	int cnt = 0;
	for (int i = 0; i < str.length(); ++i) {
		if (str[i] == '.') {
			if (flagx) {
				++cnt;
			}
			else {
				s.push_back(temp);
				temp = "";
				cnt = 1;
				flagx = true;
			}
		}
		else {
			if (flagx) {
				a.push_back(cnt);
				cnt = 0;
				flagx = false;
				temp = str[i];
			}
			else {
				temp += str[i];
			}
		}
	}

	if (flagx) {
		a.push_back(cnt);
	}
	else {
		s.push_back(temp);
	}

	return make_pair(a, s);
}


string linkage(const bool& flag, const vector<int>& a, const vector<string>& ss) {
	string ans = "";

	int i = 0;
	int j = 0;
	bool flagx = true;
	if (flag) {
		for (int l = 0; l < a[0]; ++l) {
			ans += '.';
		}
		j = 1;
	}
	while (true) {
		if (flagx) {
			if (i == ss.size()) {
				break;
			}
			ans += ss[i];
			++i;
			flagx = false;
		}
		else {
			if (j == a.size()) {
				break;
			}
			for (int l = 0; l < a[j]; ++l) {
				ans += '.';
			}
			++j;
			flagx = true;
		}
	}

	return ans;
}


string lex_sort(const string& cstr) {
	auto pairr = distribution(cstr);
	auto a = pairr.first;
	auto s = pairr.second;

	vector<Node> trie;
	trie.push_back(Node());

	int cont = 0;
	for (int i = 0; i < s.size(); ++i) {
		++cont;
		add(s[i], trie, cont);
	}

	vector<string> ss;
	bor_sort(trie[0], trie, s, ss);
	bool flag = (cstr[0] == '.');

	return linkage(flag, a, ss);
}


int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);
	cout.tie(nullptr);

	string str;
	cin >> str;

	cout << lex_sort(str);

	return 0;
}
