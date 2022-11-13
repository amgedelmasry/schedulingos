#include <stdio.h>
#include <stdlib.h>
#include <queue>
#include <string>
#include<iostream>
#include<array>
#include <algorithm>
#include <string.h>
using namespace std;

struct process{
    char name;
    int arrivalt;
    int servicet;
    int remainingt;
};
typedef struct process process;
process initprocess(char name,int arrivalt,int servicet,int remainingt){
    process x;
    x.name=name;
    x.arrivalt=arrivalt;
    x.servicet=servicet;
    x.remainingt=remainingt;
    return x;
}
bool compare( process a, process b){
	if(a.arrivalt < b.arrivalt)
		return 1;
	else
		return 0;
}
void trace (string schname,int interval,process processes[],int size,char **time){
    printf("%s  ",schname.c_str());
    for(int i=0;i<=interval;i++){
        printf("%d ",i%10);
    }
    printf("\n------------------------------------------------\n");
    for(int i=0;i<size;i++){
        printf("%c     |" ,processes[i].name);
        for(int j=0;j<interval;j++){
            printf("%c|",time[i][j]);
        }
        printf("\n");
    }
    printf("------------------------------------------------");
}
int returnnum(char* type){
    if(strcmp(type,"FCFS")==0){
        return 1;
    }
}
int main()
{
    process sorted[3];
    int interval=15;
    char* type="FCFS";
    int typeint=returnnum(type);
    sorted[0]=initprocess('A',2,3,4);
    sorted[1]=initprocess('B',3,3,4);
    sorted[2]=initprocess('C',1,3,4);
    int n=sizeof(sorted)/sizeof(process);
    char** time = new char*[n];
    for(int i = 0; i < n; i++){
        time[i] = new char[interval];
        for(int j=0;j<interval;j++){
            time[i][j]=' ';
        }
    }
    switch(typeint){
        case(1):
            sort(sorted,sorted+n,compare);
            int endt=0;
            for(int i=0;i<n;i++){
                time[i][sorted[i].arrivalt]='.';
                for(int j=endt;j<(endt+sorted[i].servicet);j++){
                    time[i][j]='*';
                }
                endt=endt+sorted[i].servicet;
            }
            trace(type,interval,sorted,n,time);
            break;
    }
}
