/*
Course : Design & Analysis of Algorithms Lab
Assignment : 05
Date :  February 1, 2022
Name : Tapas Ranjan Nayak
Roll No : 20CS01064
*/
#include<bits/stdc++.h>
using namespace std;
#define fast_io                       \
    ios_base::sync_with_stdio(false); \
    cin.tie(NULL)

//Rat object
class Rat{
    public:
    int x, y, dist;
    Rat(int x1,int y1,int dist1){
        x=x1;
        y=y1;
        dist=dist1;
    }
    Rat(){

    }
};

//Hole object
class Hole{
    public:
    int x, y, cap;
    Hole(int x1,int y1,int cap1){
        x=x1;
        y=y1;
        cap=cap1;
    }
    Hole(){

    }
};

//function to calculate distance
double dis(int x1,int y1,int x2,int y2){
    return sqrt(abs(((x1-x2)*(x1-x2))+((y1-y2)*(y1-y2))));
}

//bfs
int bfs(int s,int t,vector<int>&p,vector<vector<int>>&adj,vector<vector<int>>&capacity){
    fill(p.begin(),p.end(),-1);
    p[s]=-2;
    queue<pair<int,int>>q;
    q.push({s,1000000007});
    while(!q.empty()){
        int cur=q.front().first;
        int flow=q.front().second;
        q.pop();
        for(auto it:adj[cur]){
            if(p[it]==-1 && capacity[cur][it]){
                p[it]=cur;
                int f=min(f,capacity[cur][it]);
                if(it==t){
                    return f;
                }
                q.push({it,f});
            }
        }
    }
    return 0;
}

//edmons karp implemntation of Ford-Fulkerson method using bfs
int maxFlow(int s,int t,vector<vector<int>>&adj,vector<vector<int>>&capacity,int n){
    int flow=0;
    vector<int>p(n);
    int f;
    while(f=bfs(s,t,p,adj,capacity)){
        flow+=f;
        int cur=t;
        while(cur!=s){
            int prev=p[cur];
            capacity[prev][cur]-=f;
            capacity[cur][prev]+=f;
            cur=prev;
        }
    }
    return flow;
}
void q1(){
    int rat,hole,time,s,t;
    cin >> rat>> hole>> time;
    s=0;
    t=rat+hole+1;
    vector<vector<int>>capacity(rat+hole+2,vector<int>(rat+hole+2));
    vector<vector<int>>adj(rat+hole+2);
    vector<Rat*>R(rat);
    vector<Hole*>H(hole);
    for(int i=0; i<rat; i++){
        int x,y,dist;
        cin >> x>> y>> dist;
        R[i]=new Rat(x,y,dist);
    }
    for(int i=0; i<hole; i++){
        int x,y,cap;
        cin >> x>> y>> cap;
        H[i]=new Hole(x,y,cap);
    }
    for(int i=1; i<=rat; i++){
        adj[0].push_back(i);
    }
    for(int i=rat+1; i<=rat+hole; i++){
        adj[i].push_back(rat+hole+1);
    }
    for(int i=1; i<=rat; i++){
        capacity[0][i]=1;
    }
    for(int i=rat+1; i<=rat+hole; i++){
        capacity[i][rat+hole+1]=H[i-rat-1]->cap;
    }
    for(int i=0; i<rat; i++){
        for(int j=0; j<hole; j++){
            double distance=dis(R[i]->x,R[i]->y,H[j]->x,H[j]->y);
            
            if (distance-((double)(R[i]->dist * time)) < 0.000001) {
                adj[i+1].push_back(rat+1+j);
                capacity[i+1][rat+1+j]=1;
            }
        }
    }
    cout<<maxFlow(s,t,adj,capacity,rat+hole+2);

    //Debugging codes kindly ignor them
/*
    for(int i=0; i<rat; i++){
        cout<<R[i]->x<<" "<<R[i]->y<<" "<<R[i]->dist<<" | ";
    }
    cout<<"\n";
    for(int i=0; i<hole; i++){
        cout<<H[i]->x<<" "<<H[i]->y<<" "<<H[i]->cap<<" | ";
    }
    cout<<"\n";
    return 0;

    cout<<R[i]->x<<" "<<R[i]->y<<" "<<H[j]->x<<" "<<H[j]->y<<" -- ";
    cout<<i+1<<" "<<j+1<<" "<<distance<<"\n";
    cout<<distance<<" "<<R[i]->dist*time<<" | ";
    cout<<(distance-(double)(R[i]->dist*time))<<" ";

    cout<<"\n";
    return 0;
    for(int i=0; i<adj.size(); i++){
        cout<<i<<"->> ";
        for(auto it:adj[i]){
            cout<<it<<" ";
        }
        cout<<"\n";
    }
    for(int i=0; i<capacity.size(); i++){
        for(int j=0; j<capacity[0].size(); j++){
            cout<<capacity[i][j]<<" ";
        }
        cout<<"\n";
    }
*/

}
int main(){
    fast_io;
    
    q1();

    return 0;
}