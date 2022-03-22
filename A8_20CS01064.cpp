/*
Course : Design & Analysis of Algorithms Lab
Assignment : 08
Date :  March 15, 2022
Name : Tapas Ranjan Nayak
Roll No : 20CS01064
*/
#include <bits/stdc++.h>
using namespace std;
void Q1(){
    //input string. we have to make string s to string t
    string s,t;
    cin >> s>> t;

    //size of s is n and t is m
    int n=s.size(),m=t.size();

    //dp table
    vector<vector<int>>dp(n+1,vector<int>(m+1,INT_MAX));

    //base case
    // if s is empty and t is length i then we need i operation
    // if t is empty and s is length i then we need i operation 
    for(int i=1; i<=m; i++)dp[0][i]=i;
    for(int i=1; i<=n; i++)dp[i][0]=i;

    //dp state dp[i][j] is minimum distance to conver string s form i to end to string t form j to end 
    //dp relation . if s[i]==s[j] then dp[i][j]=dp[i-1][j-1]
    //if s[i]!=s[j] then we have two option 1.delete -> dp[i][j]=dp[i-1][j]+1 
    //2. insert -> dp[i][j]=dp[i][j-1]+1
    //3. replace is equivalent to delete and insert
    for(int i=1; i<=n; i++){
        for(int j=1; j<=m; j++){
            if(s[i-1]==t[j-1]){
                dp[i][j]=dp[i-1][j-1];
            }else{
                dp[i][j]=min(dp[i][j-1]+1,dp[i-1][j]+1);
            }
        }
    }

    //answer is dp[n][m]
    cout<<dp[n][m]<<"\n";
}
void Q2(){
    //size of input 
    int n;
    cin >> n;

    //matrix size
    vector<int>v(n,0);
    for(int i=0; i<n; i++)cin >> v[i];

    //dp tabulation 
    vector<vector<int>>dp(n+1,vector<int>(n+1,INT_MAX));

    //base case
    for(int i=1; i<n; i++)dp[i][i]=0;

    //recuse relation 
    for(int i=2; i<n; i++){
        for(int j=1; j<n-i+1; j++){
            int k=i+j-1;
            for(int l=j; l<k; l++){
                int temp=0;
                temp+=dp[j][l]+dp[l+1][k]+v[j-1]*v[l]*v[k];
                dp[j][k]=min(dp[j][k],temp);
            }
        }
    }

    //answer
    cout<<dp[1][n-1]<<"\n";
}
void Q3(){
    //n=> no. of eggs , k=> no. of floor
    int n,k;
    cin >> n>> k;

    //dp tabulation
    vector<vector<int>>dp(n+1,vector<int>(k+1,INT_MAX));

    //base case 1.if floor is 1 we need 1 trail 2.if floor is 0 we need 0 trail
    for(int i=1; i<=n; i++){
        dp[i][1]=1;
        dp[i][0]=0;
    }

    //if we have one egg then we need n trail for n floor
    for(int j=1; j<=k; j++){
        dp[1][j]=j;
    }

    //recurse realtion
    for(int i=2; i<=n; i++){
        for(int j=2; j<=k; j++){
            for(int x=1; x<=j; x++){
                int temp=0;
                temp+=1+max(dp[i-1][x-1],dp[i][j-x]);
                dp[i][j]=min(dp[i][j],temp);
            }
        }
    }

    //answer
    cout<<dp[n][k]<<"\n";
}
void Q4(){
    //size of array
    int n;
    cin >> n;

    //input array
    vector<int>v(n,0);
    for(int i=0; i<n; i++)cin >> v[i];
    //vector<int>dp(n,0);
    // dp[0]=v[0];
    // dp[1]=max(dp[0],v[1]);
    // dp[2]=max(dp[1],v[2]);
    // for(int i=3; i<n; i++){
    //     dp[i]=max({v[i]+dp[i-1],v[i-1]+dp[i-2],v[i-2]+dp[i-3]});
    // }
    // cout<<dp[n-1]<<"\n";
    int ans=0;
    for(int i=0; i<n; i++){
        int sum=0;
        for(int j=i; j<n; j+=3){
            sum+=v[j];
        }
        ans=max(ans,sum);
    }
    cout<<ans<<"\n";
}
int main() {
    int input=0;
    while(1){
        cin >> input;
        switch (input)
        {
        case 1:
            Q1();
            break;
        case 2:
            Q2();
            break;
        case 3:
            Q3();
            break;
        case 4:
            Q4();
            break;
        
        default:
            break;
        }
    }
    return 0;
}