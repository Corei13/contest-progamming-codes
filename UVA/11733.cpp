#include <bits/stdc++.h>

using namespace std;

#define x first
#define y second
#define mp make_pair
#define pb push_back
#define sz(a) (int)(a.size())
#define all(a) a.begin(), a.end()
#define R(a) ((a)%mod)

typedef vector<int> VI;
typedef vector<VI> VVI;
typedef long long ll;
typedef vector<ll> VL;
typedef vector<VL> VVL;
typedef vector<VVL> VVVL;
typedef vector<bool> VB;
typedef vector<string> VS;
typedef pair<int, int> PI;
typedef vector<PI> VPI;
typedef vector<VPI> VVPI;
typedef vector<double> VD;
typedef vector<VD> VVD;

struct DisjointSet {
    int n;
    VI rank, parent;

    DisjointSet (int n): n(n), rank(n, 0) {
        for (int i = 0; i < n; i++) {
            parent.push_back(i);
        }
    }

    int Find (int x) {
        return parent[x] == x ? x : (parent[x] = Find(parent[x]));
    }

    bool Union (int x, int y) { // returns false if already connected
        x = Find(x), y = Find(y);
        if (x == y) {
            return false;
        } else if (rank[x] < rank[y]) {
            parent[x] = y;
        } else {
            parent[y] = x;
            rank[x] = max(rank[x], rank[y] + 1);
        }
        return true;
    }
};

template <class T> struct Kruskal {
    int n;
    vector <pair <T, PI>> edges;
    DisjointSet *D;

    Kruskal (int n): n(n) {}

    void addEdge (int s, int t, T d) {
        edges.push_back(make_pair(d, make_pair(s, t)));
    }

    pair<T, int> MST (T A) {
        pair<T, int> ret = make_pair(n, A * n);
        D = new DisjointSet(n);
        sort(all(edges));
        for (auto e : edges) if (e.x < A && D->Union(e.y.x, e.y.y)) {
                ret.x--;
                ret.y -= A - e.x;
            }
        return ret;
    }
};

struct dist : binary_function <int, int, int> {
    int operator() (const int& x, const int& y) const {
        return min (abs(x - y), 10 - abs(x - y));
    }
};

int main(int argc, char const *argv[]) {
    ios::sync_with_stdio(false);

    int t;
    Kruskal<int> *K;
    cin >> t;

    for (int cs = 0; cs < t; ++cs) {
        int n, m, airport;
        cin >> n >> m >> airport;
        K = new Kruskal<int>(n);
        for (int i = 0; i < m; ++i) {
            int a, b, c;
            cin >> a >> b >> c;
            K->addEdge(a - 1, b - 1, c);
        }
        PI res = K->MST(airport);
        cout << "Case #" << cs + 1 << ": " << res.y << ' ' << res.x << endl;
    }

    return 0;
}