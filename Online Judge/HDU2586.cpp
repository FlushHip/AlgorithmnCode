#include <bits/stdc++.h>

using namespace std;

#define MAXSIZE (40000 + 5)
#define NUM_PARENT 0

#define BITOFBINARY(x) ((int)(log((x) * 1.0) / log(2.0)))

typedef struct Edge Edge;

struct Edge {
    int to, val;
    int next;
    Edge() {};
    Edge(int to, int val, int next = -1) :
        to(to), val(val), next(next) {}
};

int n, m;
Edge edges[MAXSIZE * 2];
int head[MAXSIZE];

int lowbit(int x)
{
    return x & -x;
}

void add_edge(int x, int y, int val, int i)
{
    edges[i] = Edge(y, val, head[x]);
    head[x] = i;
}

const int MAXDEP = BITOFBINARY(MAXSIZE);

int dep[MAXSIZE], dis[MAXSIZE];
int pd[MAXSIZE][MAXDEP + 1];

void init_dfs(int src)
{
    for (int i = head[src]; i + 1; i = edges[i].next) {
        int to = edges[i].to;
        if (to == pd[src][NUM_PARENT])
            continue;
        dep[to] = dep[src] + 1;
        dis[to] = dis[src] + edges[i].val;
        pd[to][NUM_PARENT] = src;
        init_dfs(to);
    }
}

void init_redouble()
{
    for (int power = 1; power <= MAXDEP; ++power)
        for (int i = 1; i <= n; i++)
            pd[i][power] = pd[pd[i][power - 1]][power - 1];
}

int lca(int x, int y)
{
    if (dep[x] < dep[y])
        swap(x, y);

    int diff = dep[x] - dep[y];
    // do {
    //     x = pd[x][BITOFBINARY(lowbit(diff))];
    // } while (diff -= lowbit(diff) > 0);
    for (; diff; diff -= lowbit(diff))
	    x = pd[x][BITOFBINARY(lowbit(diff))];

    if (x == y)
        return x;

    for (int i = MAXDEP; i >= 0; --i)
        if (pd[x][i] != pd[y][i])
            x = pd[x][i],
            y = pd[y][i];
    return pd[x][NUM_PARENT];
}

int main()
{
    int T;
    for (scanf("%d", &T); T--; ) {
        int x, y, val;
        scanf("%d%d", &n, &m);

	// any num
        int root = 1;

        memset(head, -1, sizeof(head));
        memset(pd, 0, sizeof(pd));
        dis[root] = 0;
        dep[root] = 1;

        for (int i = 0; i < 2 * (n - 1); i += 2) {
            scanf("%d%d%d", &x, &y, &val);
            add_edge(x, y, val, i);
            add_edge(y, x, val, i + 1);
        }

        init_dfs(root);
        init_redouble();

        for (; m--; ) {
            scanf("%d%d", &x, &y);
            printf("%d\n", dis[x] + dis[y] - 2 * dis[lca(x, y)]);
        }
    }
    return 0;
}
