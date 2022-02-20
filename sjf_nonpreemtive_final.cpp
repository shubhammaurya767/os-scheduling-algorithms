#include<bits/stdc++.h>
using namespace std;
int sj(const vector<pair<int,pair<int,int>>> &v, int time)
{
    int lb=INT_MAX; //least burst
    int sjpi=-1; //shortest job process index
    for(int i=0;i<v.size();i++)
    {

        if(v[i].second.first==0) continue;
        if(v[i].second.second<=time) {
            if(v[i].second.first<lb)
            {   
                sjpi=v[i].first-1; //index = process number - 1
                lb=v[i].second.first;
            }
            else if(v[i].second.first==lb)
            {
                if(v[i].second.second<v[sjpi].second.second)
                        sjpi=v[i].first-1;
            }
        }
    }
    return sjpi;
}
vector<pair<int,int>> calc_ct(vector<pair<int,pair<int,int>>> v)
{
    vector<pair<int,int>> arr;
    int time=0;
    for(int i=0;i<v.size();i++)
    {
        int x=0;
        int ind=sj(v,time);
        while(ind==-1)
        {
            time++;
            ind=sj(v,time);
        }
        if(time>=v[ind].second.second) x=time+v[ind].second.first; //curr_time+burst_time
        else x=v[ind].second.first+v[ind].second.second;
        pair<int,int> tp={v[ind].first,x};
        arr.push_back(tp);
        v[ind].second.first=0;
        time=x;
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
    cout<<"\n****SHORTEST JOB FIRST - NON PREEMPTIVE****\n";
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
    vector<pair<int,int>> ct=calc_ct(v);
    sort(ct.begin(),ct.end());
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







