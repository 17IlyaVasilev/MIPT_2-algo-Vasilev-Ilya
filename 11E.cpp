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


void add(const string& str, vector<Node>& trie, const int& cnt) {
	int v = 0;
	for (int i = 0; i < str.size(); ++i) {
		if (!trie[v].to.count(str[i])) {
			trie.push_back(Node());
			trie[v].to[str[i]] = int(trie.size()) - 1;
		}
		v = trie[v].to[str[i]];
	}
	trie[v].term.push_back(cnt - 1);
}


void find_ingoes(const string& text, vector<Node>& trie, vector<vector<int>>& ans) {
	for (int j = 0; j < text.size(); ++j) {
		int v = 0;
		for (int i = j; i < text.size(); ++i) {
			if (!trie[v].to.count(text[i])) {
				break;
			}
			v = trie[v].to[text[i]];
			for (int l = 0; l < trie[v].term.size(); ++l) {
				++ans[trie[v].term[l]][0];
				ans[trie[v].term[l]].push_back(j + 1);
			}
		}
	}
}


int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);
	cout.tie(nullptr);

	string text;
	cin >> text;
	int n;
	cin >> n;

	vector<Node> trie;
	trie.push_back(Node());
	vector<vector<int>> ans;
	vector<int> a(1, 0);
	int cnt = 0;

	for (int i = 0; i < n; ++i) {
		string pattern;
		cin >> pattern;

		++cnt;
		ans.push_back(a);
		add(pattern, trie, cnt);
	}

	find_ingoes(text, trie, ans);

	for (int i = 0; i < cnt; ++i) {
		cout << ans[i][0];
		for (int j = 1; j < ans[i].size(); ++j) {
			cout << " " << ans[i][j];
		}
		cout << endl;
	}

	return 0;
}
