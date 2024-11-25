#include<stdio.h>

#define MAXPROCESSES 5
#define MAXRESOURCES 3

int available[MAXRESOURCES];
int maximum[MAXPROCESSES][MAXRESOURCES];
int allocation[MAXPROCESSES][MAXRESOURCES];
int need[MAXPROCESSES][MAXRESOURCES];

int checksafestate()
{
    int work[MAXRESOURCES];
    int finish[MAXPROCESSES]={0};
    int seq[MAXPROCESSES];
    int count=0;

    for(int i=0;i<MAXPROCESSES;i++)
    {
        work[i]=available[i];
    }

    while(count<MAXPROCESSES)
    {
        int found=0;
        for(int p=0;p<MAXPROCESSES;p++)
        {
            if(!finish[p])
            {
                int canallocate=1;
                for(int r=0;r<MAXRESOURCES;r++)
                {
                    if(need[p][r]>work[r])
                    {
                        canallocate=0;
                        break;
                    }
                }

                if(canallocate)
                {
                    for(int r=0;r<MAXRESOURCES;r++)
                    {
                        work[r]+=allocation[p][r];
                    }

                    finish[p]=1;
                    seq[count++]=p;
                    found=1;
                    break;
                }
            }


        }
        if(!found)
        {
            return 0;
        }
    }


    
}


for(int i=0;i<MAXPROCESSES;i++)
    {
        for(int j=0;j<MAXRESOURCES;j++)
        {
            need[i][j]=maximum[i][j]-allocation[i][j];
        }
    }