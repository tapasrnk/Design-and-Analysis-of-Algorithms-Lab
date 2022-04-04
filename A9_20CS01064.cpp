/*
Course : Design & Analysis of Algorithms Lab
Assignment : 09
Date :  March 22, 2022
Name : Tapas Ranjan Nayak
Roll No : 20CS01064
*/
#include <bits/stdc++.h>
using namespace std;
void q1(){
    //size of input vector
    int n;
    cin >> n;

    //input vector
    vector<int>v(n,0);
    for(int i=0; i<n; i++){
        cin >> v[i];
    }

    //answer
    int res = 0;

    //using vector as stack
    vector<int> s = {INT_MAX};

    for (int i=0; i<n; i++) {
        while (s.back() <= v[i]) {
            int t = s.back();
            s.pop_back();
            res += t * min(s.back(), v[i]);
        }
        s.push_back(v[i]);
    }
    for (int i = 2; i < s.size(); ++i) {
        res += s[i] * s[i - 1];
    }

    //output the answer
    cout<<res<<"\n";
}

//class for job
class Job{
    public:
    int start;
    int finish;
    int profit;
    Job(int a,int b,int c){
        start=a;
        finish=b;
        profit=c;
    }
    Job(){

    }
};

//comparator function
bool comp(Job s1, Job s2){
    return (s1.finish < s2.finish);
}

//binary search
int bs(vector<Job>&jobs, int index){
    int lo = 0, hi = index - 1;
   
    while (lo <= hi){
        int mid = (lo + hi) / 2;
        if (jobs[mid].finish <= jobs[index].start){
            if (jobs[mid + 1].finish <= jobs[index].start)
                lo = mid + 1;
            else
                return mid;
        }
        else
            hi = mid - 1;
    }
    return -1;
}

void q2(){
    //size of job vector
    int n;
    cin >> n;

    //job vector
    vector<Job>v(n);
    for(int i=0; i<n; i++){
        int a,b,c;
        cin >> a>> b>> c;
        v[i]={a,b,c};
    }

    //sorting by end time
    sort(v.begin(),v.end(), comp);

    //dp table
    vector<int>dp(n,0);
    dp[0] = v[0].profit;
   
    for (int i=1; i<n; i++){

        //option 1 if we include the ith job
        int op1=v[i].profit;
        int pivot=bs(v,i);
        if(pivot!=-1){
            op1+=dp[pivot];
        }

        //option 2 if we not include the ith job
        int op2=dp[i-1];

        //dp[i] is maximum of if we include or not include the ith job
        dp[i]=max(op1,op2);
    }

    //output the answer
    cout<<dp[n-1]<<"\n";
}
int main(){
    // q1();
    q2();
    return 0;
}