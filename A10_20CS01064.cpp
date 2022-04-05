/*
Course : Design & Analysis of Algorithms Lab
Assignment : 10
Date :  April 05, 2022
Name : Tapas Ranjan Nayak
Roll No : 20CS01064
*/
#include <bits/stdc++.h>
using namespace std;
#define fast_io ios_base::sync_with_stdio(false); cin.tie(NULL)
vector<int>pour(vector<int>&v,int i,int j,vector<int>&cap){
    vector<int>ret;
    ret=v;
    if(cap[j]<ret[i]+ret[j]){
        ret[i]=(ret[i]+ret[j])-cap[j];
        ret[j]=cap[j];
    }else{
        ret[j]+=ret[i];
        ret[i]=0;
    }
    return ret;
}
bool helper(vector<vector<int>>&ans,set<vector<int>>&s,vector<int>&final,vector<int>&cap,int i){
    //case for return
    if(ans.back()==final){
        return true;
    }

    //for i to end in loop
    for(int k=i; k<ans.size(); k++){
        for(int i=0; i<3; i++){
            for(int j=0; j<3; j++){
                if(i==j)continue;

                //we will pour ith liquid to jth jar
                vector<int>temp=pour(ans[k],i,j,cap);

                //cheking for already visited state
                if(s.find(temp)!=s.end()){
                    continue;
                }

                //inserting to answer vector
                ans.push_back(temp);

                //marking the state as visited
                s.insert(temp);

                //going deep in the recursion tree
                if(helper(ans,s,final,cap,k+1)){
                    return true;
                }

                //backtracking
                ans.pop_back();
            }
        }
    }
    return false;
}
void q1(){
    //final state vector
    vector<int>final(3,0);

    //capacity state vector
    vector<int>cap(3,0);

    //input for capacity and final state
    for(int i=0; i<3; i++)cin >> cap[i];
    for(int i=0; i<3; i++)cin >> final[i];

    //answer vector
    vector<vector<int>>ans;
    ans.push_back({cap[0],0,0});
    set<vector<int>>s;
    s.insert({cap[0],0,0});

    //calling the recursion function
    if(helper(ans,s,final,cap,0)){
        for(int i=0; i<ans.size(); i++){
            cout<<ans[i][0]<<" "<<ans[i][1]<<" "<<ans[i][2]<<"\n";
        }
    }else{
        cout<<"Impossible\n";
    }
    
}
int main(){
    fast_io;
    #ifndef ONLINE_JUDGE
        freopen("input.txt","r", stdin);
        freopen("error.txt","w", stderr);
    #endif
    q1();
    return 0;
}