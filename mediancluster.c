#include<stdio.h>
#include<math.h>
#include<stdlib.h>
#include"kmeans.h"

typedef struct
{
    double a;
    int index;
} Array;

int cmp(const void*x,const void *y)
{
    return ((Array*)x)->a > ((Array*)y)->a ?1:-1;
}

void median_cluster(int clust_num,saved* save)
{
    double center[clust_num][COL];
    double center_backup[clust_num][COL];
    int    count=0,median;//how many points of each tag
    int    i,j,k,t,p,flag=1,modified_count;
    double sum,pick_max[clust_num];
    Array arr[MAX_NUM];

    for(i=0; i<clust_num; i++)
    {
        for(j=0; j<COL; j++)
        {
            center[i][j]=save[i].val[j];
            center_backup[i][j]=save[i].val[j];
        }

    }

    do
    {
        for(i=0; i<ROW; i++)
        {
            for(j=0; j<clust_num; j++)
            {
                sum=0;
                for(k=0; k<COL; k++)
                {
                    sum+=pow(center[j][k]-data[i].val[k],2);
                }
                pick_max[j]=sqrt(sum);
            }
            for(p=0,t=1; t<clust_num; t++)
            {
                if(pick_max[p]>pick_max[t])
                {
                    p=t;
                }
            }
            data[i].tag=p;

        }


        //for each tag,sort the elements
        for(i=0; i<clust_num; i++)
        {
            count=0;
            for(j=0; j<ROW; j++)
            {
                if(data[j].tag==i)
                {
                    arr[count].a=data[j].val[0];
                    arr[count].index=j;
                    count++;
                }
            }

            //sort them!

            qsort(&arr,count,sizeof(Array),cmp);
            for(j=0;j<count;j++)
            {
             //   printf("arr[%d].a=%lf,index=%d\n",j,arr[j].a,arr[j].index);
            }

            median=(count-1)/2;
          //  printf("count=%d,median=%d\n",count,median);

            for(k=0; k<COL; k++)
            {
                center[i][k]=data[arr[median].index].val[k];
            }
        }
        //end


        // if each element in center_backup equals to center,
        // it means the center point is no longer change,
        // then finish the while loop
        modified_count=0;
        for(i=0; i<clust_num; i++)
        {
            for(j=0; j<COL; j++)
            {
                if(center[i][j]!=center_backup[i][j])
                {
                    center_backup[i][j]=center[i][j];
                    modified_count++;
                }
            }
        }
        if(modified_count==0)
        {
            flag=0;
        }
    }
    while(flag);

    /*
    //debug info
    for(i=0; i<ROW; i++)
    {
        for(j=0; j<COL; j++)
        {
            //printf("ROW=%d,COL=%d,center[%d][%d]=%f ",ROW,COL,i,j,center[i][j]);
            printf("data[%d].val %f,tag=%d,",i,data[i].val[j],data[i].tag);
        }
        printf("\n");
        //printf(",count=%d\n\n",counter[i]);
    }
    //end debuf info

    */

}
