#include <stdio.h>
#include <stdlib.h>
#include <queue>
#include <string>
#include<iostream>
#include<array>
#include <algorithm>
#include <string.h>
#include<bits/stdc++.h>
#include<bits/stdc++.h>

using namespace std;
float meanTA=0;
float meanTRTS=0;
int quantum;
int quantumA;
struct process
{
    char name;
    int arrivalt;
    int servicet;
    int remainingt;
    int waitingt=0;
    int Qnum=0;
    int realP=0;
    int VP=0;
    int Turnt=0;
    float trts;
};
typedef struct process process;
process initprocess(char name,int arrivalt,int servicet,int remainingt,int prior)
{
    process x;
    x.name=name;
    x.arrivalt=arrivalt;
    x.servicet=servicet;
    x.remainingt=remainingt;
    x.realP=prior;
    x.VP=x.realP;
    return x;
}
bool compare( process a, process b)
{
    if(a.arrivalt < b.arrivalt)
        return 1;
    else
        return 0;
}
struct compareST
{
    bool operator()(process const& p1, process const& p2)
    {
        return p1.servicet > p2.servicet;
    }
};
struct compareRT
{
    bool operator()(process const& p1, process const& p2)
    {
        if(p1.remainingt == p2.remainingt)
        {
            return p1.arrivalt>p2.arrivalt;
        }
        else
        {
            return p1.remainingt > p2.remainingt;
        }
    }
};
struct compareVP
{
    bool operator()(process const& p1, process const& p2)
    {
        if(p1.VP == p2.VP)
        {
            return p1.arrivalt>p2.arrivalt;
        }
        else
        {
            return p1.VP < p2.VP;
        }
    }
};
struct compareAT
{
    bool operator()(process const& p1, process const& p2)
    {
            return p1.arrivalt > p2.arrivalt;
    }
};
struct compareRatio
{
    bool operator()(process const& p1, process const& p2)
    {
        return (p1.waitingt+p1.servicet)/p1.servicet < (p2.waitingt+p2.servicet)/p2.servicet;
    }
};
void trace (string schname,int interval,process processes[],int size,char **time)
{
    printf("%s",schname.c_str());
    for(int i=0; i<=interval; i++)
    {
        printf("%d ",i%10);
    }
    printf(" \n------------------------------------------------\n");
    for(int i=0; i<size; i++)
    {
        printf("%c     |",processes[i].name);
        for(int j=0; j<interval; j++)
        {
            printf("%c|",time[i][j]);
        }
        printf(" \n");
    }
    printf("------------------------------------------------\n\n");
}
void stats (string schname,int interval,process processes[],int size,char **time)
{
    printf("%s\n",schname.c_str());
    printf("Process    ");
    int nod;
    for(int i=0;i<size;i++){
        printf("|%*c%*s",int(ceil(float((5+1))/2)),processes[i].name,int(ceil(float((5-1))/2)),"");
    }
    printf("|\n");
    printf("Arrival    ");
    for(int i=0;i<size;i++){
        if(processes[i].arrivalt!=0)
            nod=floor(log10(processes[i].arrivalt)+1);
        else
            nod=1;
        printf("|%*d%*s",int(ceil(float((5+nod)))/2),processes[i].arrivalt
               ,int(ceil(float((5-nod))/2)),"");
    }
    printf("|\n");
    printf("Service    ");
    for(int i=0;i<size;i++){
        if(processes[i].servicet!=0)
            nod=floor(log10(processes[i].servicet)+1);
        else
            nod=1;
        printf("|%*d%*s",int(ceil(float((5+nod)))/2),processes[i].servicet
               ,int(ceil(float((5-nod))/2)),"");
    }
    printf("| Mean|\n");
    printf("Finish     ");
    for(int i=0;i<size;i++){
        if(processes[i].servicet!=0)
            nod=floor(log10(processes[i].arrivalt+processes[i].Turnt)+1);
        else
            nod=1;
        printf("|%*d%*s",int(ceil(float((5+nod)))/2),processes[i].arrivalt+processes[i].Turnt
               ,int(ceil(float((5-nod))/2)),"");
    }
    printf("|-----|\n");
    printf("Turnaround ");
    for(int i=0;i<size;i++){
        if(processes[i].Turnt!=0)
            nod=floor(log10(processes[i].Turnt)+1);
        else
            nod=1;
        printf("|%*d%*s",int(ceil(float((5+nod)))/2),processes[i].Turnt
               ,int(ceil(float((5-nod))/2)),"");
    }

    printf("|%*.2f|\n",5,meanTA);
    printf("NormTurn   ");
    for(int i=0;i<size;i++){
        printf("|%*.2f",5,processes[i].trts);
    }
    printf("|%*.2f|\n",5,meanTRTS);

}
string typeofalg(int type)
{
    if(type==1)
    {
        return "FCFS  ";
    }
    else if(type==2)
    {
        return "RR-"+to_string(quantum)+"  ";
    }
    else if(type==3)
    {
        return "SPN   ";
    }
    else if(type==4)
    {
        return "SRT   ";
    }
    else if(type==5)
    {
        return "HRRN  ";
    }
    else if(type==6)
    {
        return "FB-1  ";
    }
    else if(type==7)
    {
        return "FB-2i ";
    }
    else if(type==8)
    {
        return "Aging ";
    }
}
int main()
{
    string SorT;
    cin >> SorT;
    string algorithms;
    cin >> algorithms;
    vector<string> scheduling;
    stringstream check1(algorithms);
    string token;
    while(getline(check1, token, ','))
    {
        string oneS=token;
        stringstream check2(oneS);
        vector<string> w;
        string token2;
        while(getline(check2, token2, '-'))
        {
            w.push_back(token2);
        }
        scheduling.push_back(w[0]);
        if(w[0].compare("2")==0){
            quantum=stoi(w[1]);

        }
        if(w[0].compare("8")==0){
            quantumA=stoi(w[1]);
        }
    }
    int interval;
    cin >> interval;
    int n;
    cin >> n;
    process sorted[n];
    for(int i=0;i<n;i++){
        string PP;
        cin >> PP;
        string token2;
        stringstream check1(PP);
        vector<string> processinfo;
        while(getline(check1, token2, ','))
        {
            processinfo.push_back(token2);
        }

        sorted[i].name=processinfo[0][0];
        sorted[i].arrivalt=stoi(processinfo[1]);
        sorted[i].servicet=stoi(processinfo[2]);
        sorted[i].realP=stoi(processinfo[2]);
        sorted[i].VP=sorted[i].realP;
        sorted[i].remainingt=sorted[i].servicet;
        sorted[i].trts=0;
        sorted[i].Turnt=0;
        sorted[i].Qnum=0;
        sorted[i].waitingt=0;
    }
    char** time = new char*[n];
    sort(sorted,sorted+n,compare);
    for(int nos=0;nos<scheduling.size();nos++){
        for(int i = 0; i < n; i++)
        {
            sorted[i].Turnt=0;
            sorted[i].trts=0;
            sorted[i].waitingt=0;
            time[i] = new char[interval];
            for(int j=0; j<interval; j++)
            {
                time[i][j]=' ';
            }
        }
        string type=typeofalg(stoi(scheduling[nos]));
        switch(stoi(scheduling[nos]))
        {
        case 1:
        {
            priority_queue<process, vector<process>, compareAT > prQ;
            prQ.push(sorted[0]);
            int endt=0;
            process x;
            endt+=prQ.top().arrivalt;
            int temp;
            while(!prQ.empty())
            {
                x=prQ.top();
                prQ.pop();
                for(int j=0; j<n; j++)
                {
                    if(x.name==sorted[j].name)
                    {
                        temp=j;
                    }
                }
                int endtemp=endt;
                for(int k=endtemp; k<(endtemp+x.servicet); k++)
                {
                    for(int mm=endt;mm>=x.arrivalt;mm--){
                                if(time[temp][mm] != '*')
                                {
                                    time[temp][mm]='.';
                                }
                    }
                    time[temp][k]='*';
                    endt=endt+1;
                    for(int y=1; y<n; y++)
                    {
                        if(sorted[y].arrivalt==endt)
                        {
                            prQ.push(sorted[y]);
                        }
                    }

                }
                int flag=1;
                if(prQ.empty()){
                    for(int nn=endt; nn<interval; nn++)
                            {
                                for(int h=1; h<n; h++)
                                {
                                    if(sorted[h].arrivalt==nn)
                                    {
                                        prQ.push(sorted[h]);
                                        endt=nn;
                                        flag=0;
                                    }
                                }
                                if(flag==0) break;
                            }
                }
            }
            break;
        }
        case(2):
        {
            int t=sorted[0].arrivalt;
            queue<process> b;
            b.push(sorted[0]);
            while(!b.empty())
            {
                process x=b.front();
                b.pop();
                for(int i=0; i<n; i++)
                {
                    if(x.name==sorted[i].name)
                    {
                        for(int j=quantum; j!=0; j--)
                        {
                            for(int mm=t;mm>=x.arrivalt;mm--){
                                if(time[i][mm] != '*')
                                {
                                    time[i][mm]='.';
                                }
                            }
                            time[i][t]='*';
                            t+=1;
                            x.remainingt=x.remainingt-1;
                            for(int h=1; h<n; h++)
                            {
                                if(sorted[h].arrivalt==t)
                                {
                                    b.push(sorted[h]);
                                    break;
                                }
                            }
                            if(x.remainingt==0)
                            {
                                break;
                            }

                        }
                    }
                }
                if(x.remainingt!=0)
                {
                    b.push(x);
                }
                int flag=1;
                if(b.empty()){
                    for(int nn=t; nn<interval; nn++)
                    {
                        for(int h=1; h<n; h++)
                        {
                            if(sorted[h].arrivalt==nn)
                            {
                                b.push(sorted[h]);
                                t=nn;
                                flag=0;
                            }
                        }
                        if(flag==0) break;
                    }
                }

            }
            break;
        }
        case 3:
        {
            priority_queue<process, vector<process>, compareST > prQ;
            prQ.push(sorted[0]);
            int endt=0;
            process x;
            endt+=prQ.top().arrivalt;
            int temp;
            while(!prQ.empty())
            {
                x=prQ.top();
                prQ.pop();
                for(int j=0; j<n; j++)
                {
                    if(x.name==sorted[j].name)
                    {
                        temp=j;
                    }
                }
                int endtemp=endt;
                for(int k=endtemp; k<(endtemp+x.servicet); k++)
                {
                    for(int mm=endt;mm>=x.arrivalt;mm--){
                                if(time[temp][mm] != '*')
                                {
                                    time[temp][mm]='.';
                                }
                    }
                    time[temp][k]='*';
                    endt=endt+1;
                    for(int y=1; y<n; y++)
                    {
                        if(sorted[y].arrivalt==endt)
                        {
                            prQ.push(sorted[y]);
                        }
                    }
                }
                int flag=1;
                if(prQ.empty()){
                    for(int nn=endt; nn<interval; nn++)
                            {
                                for(int h=1; h<n; h++)
                                {
                                    if(sorted[h].arrivalt==nn)
                                    {
                                        prQ.push(sorted[h]);
                                        endt=nn;
                                        flag=0;
                                    }
                                }
                                if(flag==0) break;
                            }
                }
            }
            break;
        }
        case 4:
        {
            priority_queue<process, vector<process>, compareRT > prQ;
            prQ.push(sorted[0]);
            int endt=0;
            process x;
            endt+=prQ.top().arrivalt;
            int temp;
            while(!prQ.empty())
            {
                for(int y=1; y<n; y++)
                {
                    if(sorted[y].arrivalt==endt)
                    {
                        prQ.push(sorted[y]);
                    }
                }
                x=prQ.top();
                prQ.pop();
                for(int j=0; j<n; j++)
                {
                    if(x.name==sorted[j].name)
                    {
                        temp=j;
                    }
                }
                for(int mm=endt;mm>=x.arrivalt;mm--){
                                if(time[temp][mm] != '*')
                                {
                                    time[temp][mm]='.';
                                }
                    }
                time[temp][endt]='*';
                endt+=1;
                x.remainingt-=1;
                if(x.remainingt!=0)
                {
                    prQ.push(x);
                }
                int flag=1;
                if(prQ.empty()){
                    for(int nn=endt; nn<interval; nn++)
                            {
                                for(int h=1; h<n; h++)
                                {
                                    if(sorted[h].arrivalt==nn)
                                    {
                                        prQ.push(sorted[h]);
                                        endt=nn;
                                        flag=0;
                                    }
                                }
                                if(flag==0) break;
                            }
                }
            }
            break;
        }
        case(5):
        {
            priority_queue<process, vector<process>, compareRatio > prQ;
            priority_queue<process, vector<process>, compareRatio > tempPrQ;
            int endt=0;
            process x;
            prQ.push(sorted[0]);
            endt+=prQ.top().arrivalt;
            int temp;
            for(int i=0; i<n; i++)
            {
                x=prQ.top();
                prQ.pop();
                for(int j=0; j<n; j++)
                {
                    if(x.name==sorted[j].name)
                    {
                        temp=j;
                    }
                }
                time[temp][x.arrivalt]='.';
                int endtemp=endt;
                for(int k=endtemp; k<(endtemp+x.servicet); k++)
                {
                    for(int mm=endt;mm>=x.arrivalt;mm--){
                                if(time[temp][mm] != '*')
                                {
                                    time[temp][mm]='.';
                                }
                    }
                    time[temp][k]='*';
                    for(int y=1; y<n; y++)
                    {
                        if(sorted[y].arrivalt==k)
                        {
                            prQ.push(sorted[y]);
                        }
                    }
                    endt=endt+1;
                }
                while(!prQ.empty())
                {
                    process y=prQ.top();
                    prQ.pop();
                    y.waitingt=endt-y.arrivalt;
                    tempPrQ.push(y);
                }
                while(!tempPrQ.empty())
                {
                    process y=tempPrQ.top();
                    tempPrQ.pop();
                    prQ.push(y);
                }
                int flag=1;
                if(prQ.empty()){
                    for(int nn=endt; nn<interval; nn++)
                            {
                                for(int h=1; h<n; h++)
                                {
                                    if(sorted[h].arrivalt==nn)
                                    {
                                        prQ.push(sorted[h]);
                                        endt=nn;
                                        flag=0;
                                    }
                                }
                                if(flag==0) break;
                            }
                }
            }
            break;
        }
        case(6):
        {
            queue<process> Q[5];
            int endt=0;
            process x;
            endt+=sorted[0].arrivalt;
            int temp;
            x=sorted[0];
            Q[0].push(x);
            for(int h=0; h<5; h++)
            {
                while(!Q[h].empty())
                {
                    x=Q[h].front();
                    for(int j=0; j<n; j++)
                    {
                        if(x.name==sorted[j].name)
                        {
                            temp=j;
                        }
                    }
                    for(int mm=endt;mm>=x.arrivalt;mm--){
                                if(time[temp][mm] != '*')
                                {
                                    time[temp][mm]='.';
                                }
                    }
                    time[temp][endt]='*';
                    x.remainingt-=1;
                    Q[x.Qnum].pop();
                    endt++;
                    for(int y=1; y<n; y++)
                    {
                        if(sorted[y].arrivalt==endt)
                        {
                            Q[0].push(sorted[y]);
                        }
                    }
                    if(x.remainingt!=0)
                    {

                        if((Q[0].empty() && Q[1].empty() && Q[2].empty() && Q[3].empty() && Q[4].empty() ))
                        {
                            Q[x.Qnum].push(x);
                        }
                        else
                        {
                            if(x.Qnum==4)   Q[x.Qnum].push(x);
                            else
                            {
                                x.Qnum+=1;
                                Q[x.Qnum].push(x);
                            }
                        }
                    }
                    h=0;
                }
                int flag=1;
                if(h==4 && Q[0].empty() && Q[1].empty() && Q[2].empty() && Q[3].empty() && Q[4].empty()){
                        for(int l=endt;l<interval;l++){
                            for(int y=1; y<n; y++)
                            {
                                if(sorted[y].arrivalt==l)
                                {
                                    Q[0].push(sorted[y]);
                                    flag=0;
                                    h=-1;
                                    endt=l;
                                    break;
                                }
                            }
                            if(flag==0) break;
                        }
                    }
            }
            break;
        }
        case(7):
        {
            queue<process> Q[5];
            int endt=0;
            process x;
            endt+=sorted[0].arrivalt;
            int temp;
            x=sorted[0];
            Q[0].push(x);
            for(int h=0; h<5; h++)
            {
                while(!Q[h].empty())
                {
                    x=Q[h].front();
                    for(int j=0; j<n; j++)
                    {
                        if(x.name==sorted[j].name)
                        {
                            temp=j;
                        }
                    }
                    for(int mm=endt;mm>=x.arrivalt;mm--){
                                if(time[temp][mm] != '*')
                                {
                                    time[temp][mm]='.';
                                }
                    }
                    for(int u=0; u<pow(2,x.Qnum); u++)
                    {
                        time[temp][endt]='*';
                        x.remainingt-=1;
                        endt++;
                        for(int y=1; y<n; y++)
                        {
                            if(sorted[y].arrivalt==endt)
                            {
                                Q[0].push(sorted[y]);
                            }
                        }
                        if(x.remainingt==0) break;
                    }
                    Q[x.Qnum].pop();
                    if(x.remainingt!=0)
                    {

                        if((Q[0].empty() && Q[1].empty() && Q[2].empty() && Q[3].empty() && Q[4].empty() ))
                        {
                            Q[x.Qnum].push(x);
                        }
                        else
                        {
                            if(x.Qnum==4)   Q[x.Qnum].push(x);
                            else
                            {
                                x.Qnum+=1;
                                Q[x.Qnum].push(x);
                            }
                        }
                    }
                    h=0;
                }
                int flag=1;
                if(h==4 && Q[0].empty() && Q[1].empty() && Q[2].empty() && Q[3].empty() && Q[4].empty()){
                        for(int l=endt;l<interval;l++){
                            for(int y=1; y<n; y++)
                            {
                                if(sorted[y].arrivalt==l)
                                {
                                    Q[0].push(sorted[y]);
                                    flag=0;
                                    h=-1;
                                    endt=l;
                                    break;
                                }
                            }
                            if(flag==0) break;
                        }
                    }
            }
            break;
        }
        case(8):
        {
            priority_queue<process, vector<process>, compareVP > prQ;
            priority_queue<process, vector<process>, compareVP > tempPrQ;
            int endt=0;
            process x;
            prQ.push(sorted[0]);
            endt+=prQ.top().arrivalt;
            int temp;
            while(endt<interval)
            {
                x=prQ.top();
                prQ.pop();
                for(int i=0; i<n; i++)
                {
                    for(int j=0; j<n; j++)
                    {
                        if(x.name==sorted[j].name)
                        {
                            temp=j;
                        }
                    }
                }
                for(int qu=quantumA;qu!=0;qu--){
                    for(int mm=endt;mm>=x.arrivalt;mm--){
                            if(time[temp][mm] != '*')
                            {
                                time[temp][mm]='.';
                            }
                        }
                    time[temp][endt]='*';
                    endt++;
                    for(int y=1; y<n; y++)
                    {
                        if(sorted[y].arrivalt==endt)
                        {
                            process tempproc=sorted[y];
                            prQ.push(tempproc);
                        }
                    }
                }
                x.VP=x.realP;
                while(!prQ.empty())
                {
                    process y=prQ.top();
                    prQ.pop();
                    y.VP++;
                    tempPrQ.push(y);
                }
                while(!tempPrQ.empty())
                {
                    process y=tempPrQ.top();
                    tempPrQ.pop();
                    prQ.push(y);
                }
                prQ.push(x);
            }
            break;
        }
        }
    int flag=1;
    for(int i=0;i<n;i++){
        for(int t=sorted[i].arrivalt;t<interval;t++){
            if(time[i][t]!=' ')
                sorted[i].Turnt++;
            else if(time[i][t]=' ')
                {sorted[i].trts=float(sorted[i].Turnt)/sorted[i].servicet;
                break;}
            if(t==interval-1){
                sorted[i].trts=float(sorted[i].Turnt)/sorted[i].servicet;
            }
        }
    meanTA+=sorted[i].Turnt;
    meanTRTS+=sorted[i].trts;
    }
    meanTA/=n;
    meanTRTS/=n;
    if(SorT.compare("trace")==0)
        trace(type,interval,sorted,n,time);
    else if(SorT.compare("stats")==0)
        stats(type,interval,sorted,n,time);
    }
}

