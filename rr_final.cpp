//Author: Shubham Maurya https://github.com/shubhammaurya767/
#include<bits/stdc++.h>
using namespace std;
int tq;
int lastturn;
bool compare(const pair<int, pair<int,int>>&i, const pair<int, pair<int,int>>&j) 
{
    return i.second.second<j.second.second; //arrival time
}
int turn_f(vector<pair<int,pair<int,int>>> &v, int time)
{
    int cnt=0;
    if(lastturn==v.size()-1) lastturn=-1;
    for(int i=lastturn+1;i<v.size();i++)
    {
        if(v[i].second.first==0) continue;
        cnt++;
        if(v[i].second.second<=time)
        {
            lastturn=i;
            return i;
        }
    }
    for(int i=0;i<=lastturn;i++)
    {
        if(v[i].second.first==0) continue;
        cnt++;
        if(v[i].second.second<=time)
        {
            lastturn=i;
            return i;
        }
    }
    if(cnt==0) return -2;
    return -1;
}
vector<pair<int,int>> calc_ct(vector<pair<int,pair<int,int>>> v)
{
    int turn=0;
    lastturn=-1;
    vector<pair<int,int>> arr(v.size());
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
        if(v[turn].second.first>=tq) 
        {   
            v[turn].second.first-=tq;
            time+=tq;
            arr[turn]={turn+1,time};
        }
        else 
        {   
            time+=v[turn].second.first;
            arr[turn]={turn+1,time};
            v[turn].second.first=0;
        }
    }
    return arr;
}
int *calc_tt(const vector<pair<int,pair<int,int>>> &v, vector<pair<int,int>> *ct)
{
    int *tt=new int[v.size()];
    for(int i=0;i<v.size();i++)
        tt[v[i].first-1]=ct->at(i).second-v[i].second.second; // turnaround_time= ct-at
    return tt;
}
int *calc_wait(const vector<pair<int,pair<int,int>>> &v, const int *tt)
{
    int *wait=new int[v.size()];
    for(int i=0;i<v.size();i++)
        wait[v[i].first-1]=tt[v[i].first-1]-v[i].second.first; //waiting time= tt-burst
    return wait;
}

int main(){
	int n;
    cout<<"\n****ROUND ROBIN****\n";
    cout<<"Enter no. of processes: ";
    cin>>n;
    cout<<"Enter time quantum: ";
    cin>>tq;
    cout<<"Enter burst time of processes: \n";
    int *burst=new int[n];
    for(int i=0;i<n;i++)
        {
            cout<<"P"<<i+1<<": ";
            cin>>burst[i];
        }
    cout<<"Enter arrival time of processes: \n";
    int *arrival=new int[n];
    for(int i=0;i<n;i++)
        {
            cout<<"P"<<i+1<<": ";
            cin>>arrival[i];
        }
    vector<pair<int,pair<int,int>>> v; //process_number burst_time arrival_time
    for(int i=0;i<n;i++)
    {
        pair<int,pair<int,int>> temp;
        temp.first=i+1;
        temp.second=make_pair(burst[i],arrival[i]);
        v.push_back(temp);
    }
    sort(v.begin(),v.end(),compare);
    vector<pair<int,int>> ct=calc_ct(v);
    //sort(ct.begin(),ct.end());
    int *tt=calc_tt(v,&ct);
    int *wait=calc_wait(v,tt);
    int totwait=0;
    int tottt=0;
    int tottime=0;
    cout<<"\nProcess\t\tBurst_Time\t\tArrival_Time\t\tTurnaround_Time\t\tWaiting_Time\t\tCompletion Time\n";
    for(int i=0;i<n;i++)
    {
        cout<<"P"<<i+1<<"\t\t\t"<<burst[i]<<"\t\t\t"<<arrival[i]<<"\t\t\t"<<tt[i]<<"\t\t\t"<<wait[i]<<"\t\t\t"<<ct.at(i).second<<"\n";
        tottt+=tt[i];
        totwait+=wait[i];
        if(ct.at(i).second>tottime) tottime=ct.at(i).second;
    }
    cout<<"\nAverage waiting time: "<<(float)totwait/n;
    cout<<"\nAverage turnaround time: "<<(float)tottt/n;
    cout<<"\nThroughput = (no. of processes/total time taken) = "<<(float)n/tottime;
    cout<<"\n\n\n";
    delete burst;
    delete arrival;
}

