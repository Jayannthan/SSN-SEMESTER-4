#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ld = long double;
const ll MOD = 1e+9 + 7;

struct DSU
{
private:
    vector<int> parent, size;
    int N;

public:
    DSU(int n)
    {
        N = n;
        size.resize(N + 1, 1);
        parent.resize(N + 1);
        for (int i = 0; i <= N; i++)
        {
            parent[i] = i;
        }
    }

    void Union(int a, int b)
    {
        a = find(a);
        b = find(b);
        if (a != b)
        {
            if (size[a] < size[b])
            {
                swap(a, b);
            }
            parent[b] = a;
            size[a] += size[b];
        }
    }

    int find(int a)
    {
        if (parent[a] == a)
            return a;
        return parent[a] = find(parent[a]);
    }
};

int main()
{
    int n, m;
    cin >> n >> m; // no of vertices and edges;
    vector<array<int, 3>> v;
    for (int i = 0; i < m; i++)
    {
        int x, y, c;
        cin >> x >> y >> c; // edge betweeen x and y with cost c
        v.push_back({c, x, y});
    }

    sort(v.begin(), v.end());

    DSU ds(n);
    vector<pair<int, int>> g[n + 1];

    int cost = 0;
    for (int i = 0; i < m; i++)
    {
        int x = v[i][1], y = v[i][2];
        if (ds.find(x) != ds.find(y))
        {
            ds.Union(x, y);
            g[x].push_back({y, v[i][0]});
            g[y].push_back({x, v[i][0]});
            cost += v[i][0];
        }
    }
    cout << cost << '\n';
}
