/*
Course : Design & Analysis of Algorithms Lab
Assignment : 04
Date : January 25, 2022
Name : Tapas Ranjan Nayak
Roll No : 20CS01064
*/
#include <bits/stdc++.h>
using namespace std;
#define fast_io                       \
    ios_base::sync_with_stdio(false); \
    cin.tie(NULL)
/*                                      */
enum Type { US, S };
class Node {
   public:
    Type type;
    int val;
    Node(Type s, int i) {
        type = s;
        val = i;
    }
};
class Edge {
   public:
    int from;
    int to;
    Type type;
    Edge(int f, int t, Type ty) {
        from = f;
        to = t;
        type = ty;
    }
};

void debug_print(vector<Node*>& v) {
    for (auto it : v) {
        cout << it->val << " " << it->type << " | ";
    }
    cout << "\n";
}

void debug_print(vector<vector<Edge*>>& adj, map<pair<int, int>, Type>& edges) {
    for (int i = 1; i < adj.size(); i++) {
        cout << i << "-->";
        for (auto it : adj[i]) {
            cout << it->to << " " << edges[{i, it->to}] << " | ";
        }
        cout << "\n";
    }
}

void print(vector<vector<Edge*>>& adj, map<pair<int, int>, Type>& edges,
           int a) {
    vector<pair<int, int>> ans;
    for (int i = 1; i <= a; i++) {
        for (auto it : adj[i]) {
            if (edges[{i, it->to}] == S) {
                ans.push_back({i, it->to-a});
                // cout<<i<<" "<<it->to<<"\n";
            }
        }
    }
    cout << ans.size() << "\n";
    for (auto it : ans) {
        cout << it.first << " " << it.second << "\n";
    }
}

bool dfs(vector<vector<Edge*>>& adj, vector<Node*>& v, vector<bool>& vis,
         map<pair<int, int>, Type>& edges, int u, int a, Type t) {
    if (vis[u]) return false;

    if (u > a && v[u]->type == US) {
        v[u]->type = S;
        // cout << u << "\n ";
        return true;
    }

    vis[u] = true;
    v[u]->type = S;
    // cout << u << " "<<t<<" | \n";
    for (auto& it : adj[u]) {
        if (t == edges[{it->from, it->to}]) Type t2;
        Type t2 = edges[{it->from, it->to}];
        if (t2 == US)
            t2 = S;
        else
            t2 = US;
        if (dfs(adj, v, vis, edges, it->to, a, t2)) {
            if (edges[{it->from, it->to}] == US) {
                edges[{it->from, it->to}] = S;
                edges[{it->to, it->from}] = S;
            } else {
                edges[{it->from, it->to}] = US;
                edges[{it->to, it->from}] = US;
            }
            return true;
        }
    }

    return false;
}

void q2() {
    int a, b, m;
    cout<<"a: "<<"b: "<<"m: \n";
    cin >> a >> b >> m;

    vector<Node*> v(a + b + 1);
    for (int i = 0; i <= a + b; i++) {
        v[i] = new Node(US, i);
    }

    map<pair<int, int>, Type> edges;

    vector<vector<Edge*>> adj(a + b + 1);
    cout<<"Edges:\n";
    for (int i = 0; i < m; i++) {
        int from, to;
        cin >> from >> to;
        to += a;
        edges[{from, to}] = US;
        edges[{to, from}] = US;
        adj[from].push_back(new Edge(from, to, US));
        adj[to].push_back(new Edge(to, from, US));
    }

    for (int i = 1; i <= a; i++) {
        vector<bool> vis(a + b + 1, false);
        if (v[i]->type == US) {
            dfs(adj, v, vis, edges, i, a, US);
            // cout << "\n";
        }
        // cout << "\n";
        // debug_print(v);
        // debug_print(adj,edges);
    }
    // print(adj);
    print(adj, edges, a);
}
void fun(vector<vector<pair<int, int>>>& adj, int s, vector<int>& d) {
    int n = adj.size();
    d[s] = 0;
    set<pair<int, int>> q;
    q.insert({0, s});
    while (!q.empty()) {
        int v = q.begin()->second;
        q.erase(q.begin());
        for (auto edge : adj[v]) {
            int to = edge.first;
            int len = edge.second;

            if (d[v] + len < d[to]) {
                q.erase({d[to], to});
                d[to] = d[v] + len;
                q.insert({d[to], to});
            }
        }
    }
}
void q1() {
    int n, m, k, INF = 1000000;
    cout<<"n :"<<"m: "<<" k:\n";
    cin >> n >> m >> k;
    vector<vector<pair<int, int>>> adj(n + 1);
    cout<<"Edges:\n";
    for (int i = 0; i < m; i++) {
        int a, b, c;
        cin >> a >> b >> c;
        adj[a].push_back({b, c});
    }
    vector<int> d(n + 1, INF);
    fun(adj, k, d);
    int ans = -1;
    for (int i = 1; i <= n; i++) {
        ans = max(ans, d[i]);
    }
    if (ans == INF)
        cout << -1 << "\n";
    else
        cout << ans << "\n";
}
int main() {
    fast_io;
    int input = 1;
    cout << "Question : 1 or 2 or -1 for exit\n";
    while(input!=-1){
        cin >> input;
        if(input==1){
            q1();
        }else if(input==2){
            cout<<"Assuming two partitie numbering from 1 \n";
            q2();
        }else{
            exit(0);
        }
    }
    return 0;
}