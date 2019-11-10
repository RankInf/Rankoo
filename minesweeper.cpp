#include<iostream>
#include<cstring>
#include<algorithm>
using namespace std;

int dx[8] = {-1, 1, 0, 0, -1, -1, 1, 1}, dy[8] = {0, 0, -1, 1, -1, 1, -1, 1};
int cas, n, m, mine, space;
bool lose, win;
string ss, mod[15];
struct SEQ {
	int x, y, val;
	bool operator <(const SEQ &tmp)const {
		return x < tmp.x ? 1 : (x == tmp.x && y < tmp.y);
	}
}	seq[233333];
int len = 0;
bool info[233][233];
int mp[233][233];
int num[233][233];

void clear() {
	memset(info, 0, sizeof(info));
	memset(mp, 0, sizeof(mp));
	memset(num, 0, sizeof(num));
	mine = 0, space = 0;
}
bool check(int x, int y) {
	if(x <= 0 || x > n) return 0;
	if(y <= 0 || y > m) return 0;
	return 1;
}
void input() {
	for(int i = 0; i <= 8; ++i)
		mod[i][0] = ('0' + i);
	mod[9] = "_";
	mod[10] = "P";
	mod[11] = "?";
	cin >> n >> m;
	for(int i = 1; i <= n; ++i) {
		cin >> ss;
		for(int j = 0; j < m; ++j) {
			if(ss[j] == '_')
				mp[i][j + 1] = 9, info[i][j + 1] = 0;
			if(ss[j] == '*')
				mp[i][j + 1] = 9, info[i][j + 1] = 1, mine++;
		}
	}
	space = n * m;
	for(int i = 1; i <= n; ++i)
		for(int j = 1; j <= m; ++j)
			for(int pos = 0; pos < 8; ++pos) {
				int x1 = i + dx[pos], y1 = j + dy[pos];
				if(!check(x1, y1))
					continue;
				if(info[i][j])
					num[i][j] = -1;
				else
					if(info[x1][y1])
						num[i][j]++;
			}
}
void open(int x, int y) {
	seq[++len] = (SEQ){x, y, num[x][y]};
	mp[x][y] = num[x][y];
	space--;
	if(space == mine)
		win = 1;
	if(num[x][y] == 0)
		for(int i = 0; i < 8; ++i) {
			int x1 = x + dx[i], y1 = y + dy[i];
			if(!check(x1, y1) || mp[x1][y1] == 10 || info[x1][y1] || (mp[x1][y1] >= 0 && mp[x1][y1] <= 8))
				continue;
			open(x1, y1);
		}
}
int o1(int x, int y) {
	if(lose || win)
		return 0;
	len = 0;
	if((mp[x][y] >= 0 && mp[x][y] <= 8) || mp[x][y] == 10)
		return 1;
	if(info[x][y]) {
		lose = 1;
		return -1;
	}
	open(x, y);
	return win ? 2 : 1;	
}
int o2(int x, int y) {
	if(lose || win)
		return 0;
	len = 0;
	if(mp[x] >= 0 && mp[x][y] <= 8)
		return 1;
	if(mp[x][y] == 9) {
		mp[x][y] = 10, seq[++len] = (SEQ){x, y, 10};
		return 1;
	}
	if(mp[x][y] == 10) {
		mp[x][y] = 11, seq[++len] = (SEQ){x, y, 11};
		return 1;
	}
	if(mp[x][y] == 11) {
		mp[x][y] = 9, seq[++len] = (SEQ){x, y, 9};
		return 1;
	}
	return 1;
}
int o3(int x, int y) {
	if(lose || win)
		return 0;
	len = 0;
	if(mp[x][y] == 9)
		return 1;
	int flag = 0;
	for(int i = 0; i < 8; ++i) {
		int x1 = x + dx[i], y1 = y + dy[i];
		if(!check(x1, y1))
			continue;
		if(mp[x1][y1] == 10)
			flag++;
	}
	if(flag != num[x][y])
		return 1;
	for(int i = 0; i < 8; ++i) {
		int x1 = x + dx[i], y1 = y + dy[i];
		if(!check(x1, y1))
			continue;
		if(mp[x1][y1] != 10 && info[x1][y1]) {
			lose = 1;
			return -1;
		}
	}
	for(int i = 0; i < 8; ++i) {
		int x1 = x + dx[i], y1 = y + dy[i];
		if(!check(x1, y1))
			continue;
		if(mp[x1][y1] == 9 || mp[x1][y1] == 11
			open(x1, y1);
	}
	return win ? 2 : 1;
}
void assess(int key) {
	if(key == 0) {
		cout << "INVALID" << endl;
		return ;
	}
	if(key == -1) {
		cout << "LOSE" << endl;
		return ;
	}
	if(!len) {
		cout << "RUNNING: []" << endl;
		return ;
	}
	sort(seq + 1, seq + len + 1);
	cout << "RUNNING: [";
	for(int i = 1; i < len; ++i) {
		if(seq[i].val >= 0 && seq[i].val <= 8)
			cout << "<" << seq[i].x << ", " << seq[i].y << ", " << seq[i].val << ">, ";
		if(seq[i].val == 9)
			cout << "<" << seq[i].x << ", " << seq[i].y << ", " << "_>, ";
		if(seq[i].val == 10)
			cout << "<" << seq[i].x << ", " << seq[i].y << ", " << "P>, ";
		if(seq[i].val == 11)
			cout << "<" << seq[i].x << ", " << seq[i].y << ", " << "?>, ";
	}
	if(seq[len].val >= 0 && seq[len].val <= 8)
		cout << "<" << seq[len].x << ", " << seq[len].y << ", " << seq[len].val << ">]";
	if(seq[len].val == 9)
		cout << "<" << seq[len].x << ", " << seq[len].y << ", " << "_>]";
	if(seq[len].val == 10)
		cout << "<" << seq[len].x << ", " << seq[len].y << ", " << "P>]";
	if(seq[len].val == 11)
		cout << "<" << seq[len].x << ", " << seq[len].y << ", " << "?>]";
	cout << endl;
	if(win)
		cout << "WIN" << endl;
}
void play() {
	int opt, xx, yy, rtr;
	lose = 0, win = 0;
	do {
		cin >> opt;
		if(!opt)
			break;
		cin >> xx >> yy;
		if(opt == 1) {
			rtr = o1(xx, yy);
		}
		if(opt == 2) {
			rtr = o2(xx, yy);
		}
		if(opt == 3) {
			rtr = o3(xx, yy);
		}
		assess(rtr);
	}	while(opt);
	if(!win && !lose)
		cout << "QUIT" << endl;
}
int main() {
	freopen("minesweeper.in", "r", stdin);
	freopen("minesweeper.out", "w", stdout);
	cin >> cas;
	while(cas--) {
		clear();
		input();
		play();
		if(cas)
			cout << "==========" << endl;
	}
	return 0;
}
