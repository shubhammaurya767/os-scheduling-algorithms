#include<bits/stdc++.h>
using namespace std;
bool compare(const pair<int, pair<int,int>>&i, const pair<int, pair<int,int>>&j) 
{
    return i.second.second<j.second.second; //arrival time
}
vector<pair<int,int>> *calc_ct(const vector<pair<int,pair<int,int>>> &v)
{
    vector<pair<int,int>> *arr;
    int time=0;
    for(int i=0;i<v.size();i++)
    {
        int x=0;
        if(time>=v[i].second.second) x=time+v[i].second.first; //curr_time+burst_time
        else x=v[i].second.first+v[i].second.second;
        arr->push_back(make_pair(v[i].first,x));
        time=x;
    }
    return arr;
}
int *calc_tt(const vector<pair<int,pair<int,int>>> &v, const vector<pair<int,int>> *ct)
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
    cout<<"\n****FIRST COME FIRST SERVE****\n";
	int n;
    cout<<"Enter no. of processes: ";
    cin>>n;
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
    vector<pair<int,int>> *ct=calc_ct(v);
    int *tt=calc_tt(v,ct);
    int *wait=calc_wait(v,tt);
    sort(v.begin(),v.end());
    sort(ct->begin(),ct->end());
    int totwait=0;
    int tottt=0;
    int tottime=0;
    cout<<"Process\t\tBurst_Time\t\tArrival_Time\t\tTurnaround_Time\t\tWaiting_Time\t\tCompletion Time\n";
    for(int i=0;i<n;i++)
    {
        cout<<"P"<<i+1<<"\t\t\t"<<v[i].second.first<<"\t\t\t"<<v[i].second.second<<"\t\t\t"<<tt[i]<<"\t\t\t"<<wait[i]<<"\t\t\t"<<ct->at(i).second<<"\n";
        tottt+=tt[i];
        totwait+=wait[i];
        if(ct->at(i).second>tottime) tottime=ct->at(i).second;
    }
    cout<<"\nAverage waiting time: "<<(float)totwait/n;
    cout<<"\nAverage turnaround time: "<<(float)tottt/n;
    cout<<"\nThroughput = (no. of processes/total time taken) = "<<(float)n/tottime;
    cout<<"\n\n\n";
    delete burst;
    delete arrival;
    delete ct;
}
