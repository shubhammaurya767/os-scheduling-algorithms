//Author: Shubham Maurya https://github.com/shubhammaurya767/
#include<bits/stdc++.h>
using namespace std;
class process{
    public:
    int arrival;
    int burst;
    int pn;
    int priority;
    process(){
        arrival=0;
        burst=0;
        pn=0;
        priority=0;
    }
};
bool compare(const process&i, const process&j) 
{
    return i.priority<j.priority; //priority
}
bool comparepn(const process&i, const process&j) 
{
    return i.pn<j.pn; //priority
}
int turn_f(vector<process> &v, int time)
{
    int cnt=0;
    int highp=INT_MAX;
    int highpi=-1;
    for(int i=0;i<v.size();i++)
    {
        if(v[i].burst==0) continue;
        cnt++;
        if(v[i].arrival<=time)
        {
            if(v[i].priority<highp) {
                highpi=i;
                highp=v[i].priority;
            }
        }
    }
    if(cnt==0) return -2;
    return highpi;
}
vector<pair<int,int>> calc_ct(vector<process> v)
{
    int turn=0;
    vector<pair<int,int>> arr(v.size()); //process no. completion time
    int time=0;
    for(;;)
    {
        int turn=turn_f(v,time);
        if(turn==-2) break;
        while(turn==-1)
        {
            time++;
            turn=turn_f(v,time);
        }
        int x=v[turn].arrival+1;
        if(v[turn].arrival<=time)
            x=time+1;
        arr[v[turn].pn-1]={v[turn].pn,x};
        v[turn].burst--;
        time=x;
    }
    return arr;
}
int *calc_tt(const vector<process> &v, vector<pair<int,int>> *ct)
{
    int *tt=new int[v.size()];
    for(int i=0;i<v.size();i++)
        tt[v[i].pn-1]=ct->at(i).second-v[i].arrival; // turnaround_time= ct-at
    return tt;
}
int *calc_wait(const vector<process> &v, const int *tt)
{
    int *wait=new int[v.size()];
    for(int i=0;i<v.size();i++)
        wait[v[i].pn-1]=tt[v[i].pn-1]-v[i].burst; //waiting time= tt-burst
    return wait;
}

int main(){
	int n;
    cout<<"\n****ROUND ROBIN****\n";
    cout<<"Enter no. of processes: ";
    cin>>n;
    cout<<"Enter burst time of processes: \n";
    vector<process> v(n);
    for(int i=0;i<n;i++)
        {
            cout<<"P"<<i+1<<": ";
            cin>>v[i].burst;
            v[i].pn=i+1;
        }
    cout<<"Enter arrival time of processes: \n";
    for(int i=0;i<n;i++)
        {
            cout<<"P"<<i+1<<": ";
            cin>>v[i].arrival;
        }
    cout<<"Assuming lower the no., higher the priority,\nEnter Priority of processes: \n";
    for(int i=0;i<n;i++)
        {
            cout<<"P"<<i+1<<": ";
            cin>>v[i].priority;
        }
    sort(v.begin(),v.end(),compare);
    vector<pair<int,int>> ct=calc_ct(v);
    sort(v.begin(),v.end(),comparepn);
    int *tt=calc_tt(v,&ct);
    int *wait=calc_wait(v,tt);
    int totwait=0;
    int tottt=0;
    int tottime=0;
    cout<<"\nProcess\t\tBurst_Time\t\tArrival_Time\t\tPriority\t\tTurnaround_Time\t\tWaiting_Time\t\tCompletion Time\n";
    for(int i=0;i<n;i++)
    {
        cout<<"P"<<i+1<<"\t\t\t"<<v[i].burst<<"\t\t\t"<<v[i].arrival<<"\t\t\t"<<v[i].priority<<"\t\t\t"<<tt[i]<<"\t\t\t"<<wait[i]<<"\t\t\t"<<ct.at(i).second<<"\n";
        tottt+=tt[i];
        totwait+=wait[i];
        if(ct.at(i).second>tottime) tottime=ct.at(i).second;
    }
    cout<<"\nAverage waiting time: "<<(float)totwait/n;
    cout<<"\nAverage turnaround time: "<<(float)tottt/n;
    cout<<"\nThroughput = (no. of processes/total time taken) = "<<(float)n/tottime;
    cout<<"\n\n\n";
}

