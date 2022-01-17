/*
Course : Design & Analysis of Algorithms Lab
Assignment : 01
Date : January 04, 2022
Name : Tapas Ranjan Nayak
Roll No : 20CS01064
*/
#include <bits/stdc++.h>
using namespace std;
class Node {
   private:
    int val;
    int startTime;
    int endTime;
    int parent;

   public:
    Node() {}

    Node(int v) {
        val = v;
        startTime = 0;
        endTime = 0;
        parent = -1;
    }

    Node(int v, int st, int et) {
        val = v;
        startTime = st;
        endTime = et;
    }

    void setVal(int v) { val = v; }

    void setStartTime(int t) { startTime = t; }

    void setEndTime(int t) { endTime = t; }

    int getVal() { return val; }

    int getStartTime() { return startTime; }

    int getEndTime() { return endTime; }

    int getParent() { return parent; }

    void setParent(int p) { parent = p; }
};
class Graph {
   private:
    vector<Node*> g;
    vector<vector<int>> adj;
    vector<bool> visited;
    vector<pair<int, int>> edge;

    void __dfs(int u, int& t) {
        if (visited[u]) {
            return;
        }
        visited[u] = true;
        g[u]->setStartTime(t++);
        for (int x : adj[u]) {
            if (!visited[x]) {
                __dfs(x, t);
                g[x]->setParent(u);
            }
        }
        g[u]->setEndTime(t++);
        return;
    }

    void printTime() {
        for (int i = 1; i < g.size(); i++) {
            if (g[i]) {
                cout << i << " " << g[i]->getStartTime() << " "
                     << g[i]->getEndTime() << " " << g[i]->getParent() << "\n";
            }
        }
    }

    void printEdge() {
        for (auto it : edge) {
            int u = it.first;
            int v = it.second;
            if (g[v]->getParent() == u &&
                g[u]->getStartTime() < g[v]->getStartTime() &&
                g[v]->getEndTime() < g[u]->getEndTime() &&
                g[v]->getStartTime() < g[v]->getEndTime()) {
                cout << u << " " << v << " Tree Edge\n";

            } else if (g[v]->getStartTime() < g[u]->getStartTime() &&
                       g[u]->getEndTime() < g[v]->getEndTime() &&
                       g[u]->getStartTime() < g[u]->getEndTime()) {
                cout << u << " " << v << " Back Edge\n";

            } else if (g[v]->getParent() != u &&
                       g[u]->getStartTime() < g[v]->getStartTime() &&
                       g[v]->getEndTime() < g[u]->getEndTime() &&
                       g[v]->getStartTime() < g[v]->getEndTime()) {
                cout << u << " " << v << " Forward Edge\n";

            } else if (g[v]->getStartTime() < g[v]->getEndTime() &&
                       g[u]->getStartTime() < g[u]->getEndTime() &&
                       g[v]->getEndTime() < g[u]->getStartTime()) {
                cout << u << " " << v << " Cross Edge\n";
            }
        }
    }

    void _dfs(int u) {
        visited.assign(adj.size() + 1, false);
        int t = 1;
        __dfs(u, t);
        g[u]->setEndTime(t);
        printTime();
        printEdge();
    }

   public:
    Graph(int v) {
        adj.resize(v + 1);
        g.resize(v + 1);
    }

    void add(int u, int v) {
        adj[u].push_back(v);
        if (g[u] == NULL) g[u] = new Node(u);
        if (g[v] == NULL) g[v] = new Node(v);
        edge.push_back({u, v});
    }

    void dfs() {
        for (int i = 0; i < adj.size(); i++) {
            if (adj[i].size() > 0) {
                _dfs(i);
                break;
            }
        }
    }

    void dfs(int v) { _dfs(v); }

    void print() {
        for (int i = 0; i < adj.size(); i++) {
            if (adj[i].size() > 0) {
                cout << i << " --> ";
                for (int j = 0; j < adj[i].size(); j++) {
                    cout << g[adj[i][j]]->getVal() << " ";
                }
                cout << "\n";
            }
        }
    }
};
int main() {
    int v, e;
    cin >> v >> e;

    Graph* g = new Graph(v);

    for (int i = 0; i < e; i++) {
        int a, b;
        cin >> a >> b;
        g->add(a, b);
    }

    g->print();

    g->dfs();

    return 0;
}