#include<stdio.h>


int FINDLRU(int time[],int n)
{
    int minimum=time[0],i,pos=0;
    for(i=1;i<n;++i)
    {
        if(time[i]<minimum)
        {
            minimum=time[i];
            pos=i;
        }
    }
    return pos;
}


int main()
{
    int frames[10],pages[30],time[10],i,j,k,noframes,nopages,count=0,pagefault=0,pos;

    printf("Enter number of frames");
    scanf("%d",&noframes);

    printf("Enter number of pages");
    scanf("%d",&nopages);

    printf("Enter Pages Sequences");
    for(i=0;i<nopages;i++)
    {
        scanf("%d",&pages[i]);
    }

    for(i=0;i<noframes;i++)
    {
        frames[i]=-1;
        time[i]=0;
    }

    for(i=0;i<nopages;i++)
    {
        int found=0;

        for(j=0;j<noframes;j++)
        {
            if(frames[j]==pages[i])
            {
                found=1;
                time[j]=++count;
                break;
            }
        }

        if(!found)
        {
            if(frames[j]==-1)
            {
                pos=j;
            }

            else
            {
                pos=FINDLRU(time,noframes);
            }

            frames[pos]=pages[i];
            time[pos]=++count;
            pagefault++;
        }

        printf("\n %d|",pages[i]);
        for(k=0;k<noframes;k++)
        {
            if(frames[k]!=-1)
            {
                printf("%d",frames[k]);
            }

            else
            {
                printf("-");
            }
        }
    }

    return 0;
}