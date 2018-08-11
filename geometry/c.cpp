#include <bits/stdc++.h>
using namespace std;

#include <bits/stdc++.h>
using namespace std;


struct node {
	int x, y, vx, vy;
	node () {}
	node (int _x,  int _y, int _vx, int _vy) {
		x = _x; y = _y; vx = _vx; vy = _vy;
	}

	node getNext (int i, int j) const {
		return node (x + vx + i, y + vy + j, vx + i, vy + j);
	}

	bool operator == (const node & nd) const {
		if (x == nd.x && y == nd.y && vx == nd.vx && vy == nd.vy) return true;
		return false;
	}

	void prnt () const {
		cout << x << " " << y << " " << vx << " " << vy;
	}
};

struct dnode {
	double x, y, vx, vy;
	dnode () {}
	dnode (double _x, double _y, double _vx, double _vy) {
		x = _x; y = _y; vx = _vx; vy = _vy;
	}
	
	bool operator == (const node & nd) const {
		if ((int) x == nd.x && (int) y == nd.y && (int) vx == nd.vx && (int) vy == nd.vy) return true;
		return false;
	}
};

struct Wall {
	int x1, y1, x2, y2;
	Wall () {}
	Wall (int _x1, int _y1, int _x2, int _y2){
		x1 = _x1; x2 = _x2; y1 = _y1; y2 = _y2;
	}
	Wall (node n1, node n2){
		x1 = n1.x; y1 = n1.y;
		x2 = n2.x; y2 = n2.y;
	}
};

struct Line {
	double a, b, c;
	Line() {}
	Line(Wall w){
		a = w.y1 - w.y2;
		b = w.x2 - w.x1;
		c = w.x1 * w.y2 - w.x2 * w.y1;
	}

};

vector <Wall> v;
int dist[64][64][25][25];

inline int getDist (const node nd) {
	return dist[nd.x][nd.y][nd.vx + 12][nd.vy + 12];
}

inline void setDist (const node & nd, int d) {
	dist[nd.x][nd.y][nd.vx + 12][nd.vy + 12] = d;
}

int n, m;

bool IsInside(Wall w, node p){
	//printf("#");
	if((p.x >= w.x1 && p.x <= w.x2) || (p.x >= w.x2 && p.x <= w.x1))
		if((p.y >= w.y1 && p.y <= w.y2) || (p.y >= w.y2 && p.y <= w.y1)){
			//printf("okok\n");
			return true;
		}
	return false;
}

bool IsInside(Wall w, dnode p){
	if((p.x >= w.x1 && p.x <= w.x2) || (p.x >= w.x2 && p.x <= w.x1))
		if((p.y >= w.y1 && p.y <= w.y2) || (p.y >= w.y2 && p.y <= w.y1)){
			//printf("okok\n");
			return true;
		}
	return false;
}

bool parallel(Line a, Line b){ return fabs(a.a * b.b - a.b * b.a) < eps; }

dnode Intersect(Line a, Line b){
	double determinant = a.b * b.a - a.a * b.b;
	double x = (a.c * b.b - a.b * b.c) / determinant;
	double y = (a.a * b.c - a.c * b.a) / determinant;
	dnode sol = dnode(x,y,0,0);
	return sol;
}

bool intersect(Wall w1, Wall w2){
	dnode sol;
	Line a = Line(w1);
	Line b = Line(w2);
	
	node w1n1 = node(w1.x1,w1.y1, 0, 0);
	node w1n2 = node(w1.x2, w1.y2, 0, 0);
	node w2n1 = node(w2.x1, w2.y1, 0 , 0);
	node w2n2 = node(w2.x2, w2.y2, 0 , 0);
	
	if(parallel(a, b)){
		if(a.c != b.c) return false;
		return !(!IsInside(w2, w1n1) && !IsInside(w2, w1n2) && !IsInside(w1, w2n1) && !IsInside(w1, w2n2));
	}
	
	sol = Intersect(a, b);
	
	if(IsInside(w1,sol) && IsInside(w2,sol)){
		return true;
	}
	return false;
}


int main () {

	node v[4];
	node t[4];

	wall s1[4];
	wall s2[4];

	for (int i = 0; i < 4; ++i) {
		int x, y;
		scanf ("%d %d", &x, &y);
		v[i].x = x;
		v[i].y = y;
	}

	for (int i = 0; i < 4; ++i) {
		int x, y;
		scanf ("%d %d", &x, &y);
		t[i].x = x;
		t[i].y = y;
	}

	for (int i = 0; i < 4; ++i) {
		s1[i] = wall (v[i], v[(i + 1) % 4]);
		s2[i] = wall (t[i], t[(i + 1) % 4]);
	}

	for (int i = 0; i < 4; ++i) {
		for (int j = 0; j < 4; ++j) {
			if (intersect (s1[i], s2[j])) {
				cout << "YES" << endl;
				return 0;
			}
		}
	}

	for (int i = 0; i < 4; ++i) {
		if (t[i].x >= min (v[0].x, v[2].x) && t[i].x <= max (v[0].x, v[2].x))
			if (t[i].y >= min (v[0].y, v[2].y) && t[i].y <= max (v[0].y, v[2].y)) {
				cout << "YES" << endl;
				return 0;
			}
	}

	cout << "NO" << endl;

	return 0;
}