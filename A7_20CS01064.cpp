/*
Course : Design & Analysis of Algorithms Lab
Assignment : 07
Date :  February 15, 2022
Name : Tapas Ranjan Nayak
Roll No : 20CS01064
*/
#include <bits/stdc++.h>
using namespace std;
#define fast_io                       \
    ios_base::sync_with_stdio(false); \
    cin.tie(NULL)
#define INF 10000000
class Graph{
    public:
    int size;
    vector<vector<int>>capacity;
    vector<vector<int>>adj;
    Graph(int n){
        size=n;
        adj.resize(n);
        capacity.resize(n);
        for(int i=0; i<n; i++){
            capacity[i].resize(n);
        }
    }
    void add(int a,int b){
        adj[a].push_back(b);
    }
};
int bfs(int s, int t, vector<int>& parent,Graph* g) {
    fill(parent.begin(), parent.end(), -1);
    parent[s] = -2;
    queue<pair<int, int>> q;
    q.push({s, INF});

    while (!q.empty()) {
        int cur = q.front().first;
        int flow = q.front().second;
        q.pop();

        for (int next : g->adj[cur]) {
            if (parent[next] == -1 && g->capacity[cur][next]) {
                parent[next] = cur;
                int new_flow = min(flow, g->capacity[cur][next]);
                if (next == t)
                    return new_flow;
                q.push({next, new_flow});
            }
        }
    }

    return 0;
}

int maxflow(Graph* g,int s, int t) {
    int flow = 0;
    vector<int> parent(g->size);
    int new_flow;

    while (new_flow = bfs(s, t, parent,g)) {
        flow += new_flow;
        int cur = t;
        while (cur != s) {
            int prev = parent[cur];
            g->capacity[prev][cur] -= new_flow;
            g->capacity[cur][prev] += new_flow;
            cur = prev;
        }
    }

    return flow;
}
void q1(){
    int n,m;
    cin >> n>> m;
    Graph* g;
    g = new Graph(2*n+1);
    vector<int>nodes(n+1);
    for(int i=1; i<=n; i++){
        cin >> nodes[i];
    }
    for(int i=1; i<=n; i++){
        g->add(i,i+n);
        g->capacity[i][i+n]=nodes[i];
    }
    for(int i=0; i<m; i++){
        int a,b,c;
        cin >> a>> b>> c;
        g->add(a+n,b);
        g->capacity[a+n][b]=c;
    }

    int ans=0;
    ans=maxflow(g,1,2*n);
    cout<<ans<<"\n";

}
int main() {
    fast_io;

    q1();

    return 0;
}