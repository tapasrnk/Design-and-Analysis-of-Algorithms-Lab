/*
Course : Design & Analysis of Algorithms Lab
Assignment : 03
Date : January 18, 2022
Name : Tapas Ranjan Nayak
Roll No : 20CS01064
*/
#include <bits/stdc++.h>
using namespace std;
#define fast_io                       \
    ios_base::sync_with_stdio(false); \
    cin.tie(NULL)
//Union find data structure
struct DSU{
    //parent vector
    vector<int>par;
    //size vector
    vector<int>s;


    //constructor
    DSU(int n){
        par.resize(n+1);
        s.resize(n+1);
        for(int i=0; i<=n; i++){
            par[i]=i;
            s[i]=1;
        }
    }

    //path compression
    int find(int v){
        return par[v]=(par[v]==v)?v:find(par[v]);
    }

    //union by size
    void merge(int u,int v){
        int a=find(u);
        int b=find(v);
        if(a<b) swap(a,b);
        par[b]=a;
        s[a]+=s[b];
    }

};
void q1(){
    //size of matrix
    int n;
    cin >> n;

    //input for matrix
    vector<vector<int>>mat(n,vector<int>(n,0));
    for(int i=0; i<n; i++){
        for(int j=0; j<n; j++){
            cin >> mat[i][j];
        }
    }

    //dsu of size n
    DSU d(n);

    //number of reasearch community
    int ans=n;

    //mergering two community
    for(int i=0; i<n; i++){
        for(int j=i+1; j<n; j++){
            if(mat[i][j]==1){
                if (d.find(i) != d.find(j)) {
                    d.merge(i, j);
                    ans--;
                }
            }
        }
    }

    //printng the answer
    cout<<ans<<"\n";
}
void dfs(vector<vector<int>>&mat,vector<int>&cols,int i,int j){
    //out of bound check
    if(i<0 || i>=mat.size() || j<0 || j>=cols[i]){
        return ;
    }

    //invalid acess check
    if(mat[i][j]==0){
        return ;
    }

    //turing unvisited to vistied
    mat[i][j]=0;

    //reusion call on nebouring cells
    dfs(mat,cols,i+1,j);
    dfs(mat,cols,i-1,j);
    dfs(mat,cols,i,j+1);
    dfs(mat,cols,i,j-1);
}
void q2(){
    //number of rows
    int row;
    cin >> row;

    //number of columns in each row
    vector<int>cols(row);

    //martix and input
    vector<vector<int>>mat(row);
    for(int i=0; i<row; i++){
        cin >> cols[i];
        mat[i].resize(cols[i]);
    }
    for(int i=0; i<row; i++){
        for(int j=0; j<cols[i]; j++){
            cin >> mat[i][j];
        }
    }

    //number of groups
    int ans=0;

    //calling dfs
    for(int i=0; i<row; i++){
        for(int j=0; j<cols[i]; j++){
            if(mat[i][j]==1){
                ans++;
                dfs(mat,cols,i,j);
            }
        }
    }

    //printing the answer
    cout<<ans<<"\n";
}

int main(){
    /*
    fast_io;
    #ifndef ONLINE_JUDGE
        freopen("input.txt", "r", stdin);
        freopen("error.txt", "w", stderr);
    #endif
    */
    q1();
    q2();
    return 0;
}