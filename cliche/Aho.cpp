//163E
#include<bits/stdc++.h>

using namespace std;

typedef long long ll;

const int MAXN = 1e6 + 10;
const int XX = 1e6 + 10;

int n, q, ind[MAXN], nxt[26][XX], f[XX], que[MAXN], sz;
string s[MAXN];
int s_t[MAXN], f_t[MAXN], tm;
vector<int>	adj[MAXN];
int fen[MAXN];
char ch[XX];
bool on[MAXN];

string read_string(){
	scanf("%s", ch);
	string temp;
	return ch;
}

int insert(string t){
	int cur = 0;
	for (char c:t)
		if (nxt[c - 'a'][cur])
			cur = nxt[c - 'a'][cur];
		else
			cur = nxt[c - 'a'][cur] = ++sz;
	return cur;
}

void build(){
	int h = 0, t = 0;
	for (int i = 0; i < 26; i++)
		if (nxt[i][0])
			que[t++] = nxt[i][0];

	while (h < t){
		int v = que[h++];
		if (v)	
			adj[f[v]].push_back(v);
		for (int i = 0; i < 26; i++)
			if (nxt[i][v]){
				f[nxt[i][v]] = nxt[i][f[v]];
				que[t++] = nxt[i][v];
			}
			else
				nxt[i][v] = nxt[i][f[v]];
	}
}

void dfs(int v = 0){
	s_t[v] = tm++;
	for (int u:adj[v])
		dfs(u);
	f_t[v] = tm;
}

void add(int l, int r, int val){
	for (l++; l < MAXN; l+=l&-l)	fen[l] += val;
	for (r++; r < MAXN; r += r&-r)	fen[r] -= val;
}

ll get(int v){
	ll ret = 0;
	for (v++; v; v -= v&-v)
		ret += fen[v];
	return ret;
}

ll ans(string t){
	int cur = 0;
	ll ret = 0;
	for (char c:t){
		cur = nxt[c - 'a'][cur];
		ret += get(s_t[cur]);
	}
	return ret;
}	

int main(){
	scanf("%d %d", &q, &n);
	for (int i = 0; i < n; i++){
		s[i] = read_string();
		ind[i] = insert(s[i]);
	}
	build();
	dfs();
	for (int i = 0; i < n; i++)
		on[ind[i]] = 1, add(s_t[ind[i]], f_t[ind[i]], 1);
	
	while (q--){
		char type;	scanf("%1s", &type);
		if (type == '-'){
			int id;	scanf("%d", &id), id--;	id = ind[id];
			if (on[id]){
				on[id] = 0;
				add(s_t[id], f_t[id], -1);
			}
		}
		else if (type == '+'){
			int id;	scanf("%d", &id), id--;	id = ind[id];
			if (!on[id]){
				on[id] = 1;
				add(s_t[id], f_t[id], 1);
			}
		}
		else{
			string t = read_string();
			printf("%I64d\n", ans(t));
		}
	}
	return 0;
}
