/*
Course : Design & Analysis of Algorithms Lab
Assignment : 02
Date : January 11, 2022
Name : Tapas Ranjan Nayak
Roll No : 20CS01064
*/
#include <bits/stdc++.h>
using namespace std;
#define fast_io                       \
    ios_base::sync_with_stdio(false); \
    cin.tie(NULL)
class Node {
   public:
    int val;
    int startTime;
    int endTime;
    Node(int i) { val = i; }
};
class Graph {
   public:
    vector<Node*> nodes;
    vector<vector<int>> adj;
    vector<int> degree;

    Graph(int v, vector<pair<int, int>>& edges) {
        nodes.resize(v + 1);
        adj.resize(v + 1);
        degree.assign(v + 1, 0);
        for (int i = 0; i < nodes.size(); i++) {
            nodes[i] = new Node(i);
        }
        for (auto it : edges) {
            degree[it.second]++;
            adj[it.first].push_back(it.second);
        }
    }

    void dfs(int v, vector<bool>& visited, int& time) {
        visited[v] = true;
        nodes[v]->startTime = time++;
        for (auto it : adj[v]) {
            if (visited[it] == false) {
                dfs(it, visited, time);
            }
        }
        nodes[v]->endTime = time++;
    }

    void dfs() {
        vector<bool> vistited(nodes.size(), false);
        int time = 1;
        for (int i = 1; i < degree.size(); i++) {
            if (vistited[i] == false) {
                dfs(i, vistited, time);
            }
        }
    }
    void dfs(vector<bool>& visited, int v, vector<int>& c) {
        visited[v] = true;
        c.push_back(v);
        for (auto it : adj[v]) {
            if (visited[it] == false) {
                dfs(visited, it, c);
            }
        }
    }
    void printComponent(vector<vector<int>>& comp, vector<int>& parent) {
        vector<bool> vistied(nodes.size(), false);
        vector<pair<int, int>> visitTime;
        for (int i = 1; i < nodes.size(); i++) {
            visitTime.push_back({nodes[i]->endTime, nodes[i]->val});
        }
        sort(visitTime.begin(), visitTime.end(), greater<pair<int, int>>());
        int asg = 0;
        for (int i = 0; i < visitTime.size(); i++) {
            if (vistied[visitTime[i].second] == false) {
                vector<int> v;
                dfs(vistied, visitTime[i].second, v);
                comp.push_back(v);
                asg++;
                for (int j = 0; j < v.size(); j++) {
                    parent[v[j]] = asg;
                }
            }
        }
        cout << "Printing Components :\n";
        for (int i = 1; i < comp.size(); i++) {
            if (comp.size() > 0) {
                cout << "Component " << i << " : ";
                for (int it : comp[i]) {
                    cout << it << " ";
                }
                cout << "\n";
            }
        }
        cout << "\n";
    }

    void dfs1(stack<int>& s, vector<bool>& visited, int& vis, int u) {
        visited[u] = true;
        vis++;
        for (auto it : adj[u]) {
            if (visited[it] == false) {
                degree[it]--;
                dfs1(s, visited, vis, nodes[it]->val);
            }
        }
        s.push(u);
    }

    void topSort(vector<int>& v) {
        int vis = 1;
        stack<int> s;
        vector<bool> visited(nodes.size(), false);
        while (vis < nodes.size()) {
            for (int i = 1; i < nodes.size(); i++) {
                if (degree[i] == 0 && visited[i] == false) {
                    dfs1(s, visited, vis, nodes[i]->val);
                }
            }
        }
        while (!s.empty()) {
            v.push_back(s.top());
            s.pop();
        }
    }

    void print() {
        for (int i = 0; i < adj.size(); i++) {
            if (adj[i].size() > 0) {
                cout << i << "-> ";
                for (auto it : adj[i]) {
                    cout << nodes[it]->val << " " << nodes[it]->startTime << " "
                         << nodes[it]->endTime << "-- ";
                }
                cout << "\n";
            }
        }
    }
};
int main() {
    fast_io;
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("error.txt", "w", stderr);
#endif
    int v;
    cin >> v;
    vector<pair<int, int>> edges;
    while (1) {
        int a, b;
        cin >> a;
        if (a == -1) {
            break;
        }
        cin >> b;
        edges.push_back({a, b});
    }
    Graph* g1 = new Graph(v, edges);
    g1->dfs();
    vector<pair<int, int>> edges2;
    for (auto it : edges) {
        edges2.push_back({it.second, it.first});
    }
    Graph* g2 = new Graph(v, edges2);
    g2->nodes = g1->nodes;
    vector<vector<int>> comp;
    vector<int> par(g2->nodes.size(), -1);
    comp.push_back({});
    g2->printComponent(comp, par);

    set<pair<int, int>> um;
    for (auto it : edges) {
        if (par[it.first] != par[it.second]) {
            um.insert({par[it.first], par[it.second]});
        }
    }
    vector<pair<int, int>> newEdge;
    for (auto it : um) {
        newEdge.push_back({it.first, it.second});
    }
    Graph* g3 = new Graph(comp.size() - 1, newEdge);
    vector<int> arr;
    g3->topSort(arr);
    cout << "Printing Topological Sort:\n";
    cout << "(";
    for (auto it : arr) {
        cout << "(";
        for (auto it1 : comp[it]) {
            cout << it1 << ",";
        }
        cout << "),";
    }
    cout << ")";
    cout << "\n";
    return 0;
}