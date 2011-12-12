#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>
#include<math.h>
#include"kmeans.h"

int main(int argc,char*argv[])
{
    int sum,i,j;
    saved * save;
    ROW=0,COL=0;
    if(argc!=6||(strcmp(argv[1],"-help")==0))
    {
        help_info();
        exit(0);
    }
    how_many_cols(argv[1]);
    read_file(argv[1]);

    if(0==strcmp("random",argv[4]))
    {
        save=random_init(atoi(argv[3]));
    }
    else if(0==strcmp("plus",argv[4]))
    {
        save=plus_init(atoi(argv[3]));
    }
    else
    {
        printf("ERROR:You must specify a method to Initialize tags.\n");
        exit(1);
    }

    if(0==strcmp("means",argv[5]))
    {
        means_cluster(atoi(argv[3]),save);
    }
    else if(0==strcmp("median",argv[5]))
    {
        median_cluster(atoi(argv[3]),save);
    }
    else
    {
        printf("ERROR:You must specify a method to calculate Centers.\n");
        exit(1);
    }

    output(argv[2]);

    /*save=random_init(atoi(argv[3]));
    median_cluster(atoi(argv[3]),save);*/

    return 0;
}


saved* random_init(int clust_num)
{
    int    i,j;
    double center[clust_num][COL];
    int    counter[clust_num];//how many points of each tag
    saved *save;
    srand(time(0));
    for(i=0; i<ROW; i++)
    {
        data[i].tag=(rand()%clust_num);
    }
    //initial center to zero
    for(i=0; i<clust_num; i++)
    {
        for(j=0; j<COL; j++)
        {
            center[i][j]=0;
        }
        counter[i]=0;
    }
    // each tag belongs to a center[i]
    for(i=0; i<ROW; i++)
    {
        for(j=0; j<COL; j++)
        {
            center[data[i].tag][j]+=data[i].val[j];
        }
        counter[data[i].tag]++;//count the numbers of each tag
    }

    for(i=0; i<clust_num; i++)
    {
        for(j=0; j<COL; j++)
        {
            center[i][j]/=counter[i];
            //printf(" center=%f,center_backup=%f",center[i][j],center_backup[i][j]);
        }
    }

    save=(saved *)malloc(sizeof(saved)*clust_num);

    for(i=0;i<clust_num;i++)
    {
        for(j=0;j<COL;j++)
        {
            save[i].val[j]=center[i][j];
        }

    }

    return save;

}

saved* plus_init(int cluster_num)
{
    double dist[ROW],tmp_dist,tmp_sum,sum,total_distance;
    int i,j,first,k,now,flag;
    int *init_center;
    saved *save;

    init_center=(int*)malloc(cluster_num*sizeof(int));

    /*initialize*/
    for(i=0; i<cluster_num; i++)
    {
        init_center[i]=-1;
    }

    srand(time(0));
    first=rand()%ROW;
    init_center[0]=first;
    //printf("first select NO.%d\n",first);
    now=first;
    for(i=1; i<cluster_num; i++)
    {
        total_distance=0;
        for(j=0; j<ROW; j++)
        {
            sum=0;
            for(k=0; k<COL; k++)
            {
                sum+=sqrt(pow(data[now].val[k]-data[j].val[k],2));
            }
            dist[j]=sqrt(sum);
            total_distance+=dist[j];
           // printf("dist=%lf\n",dist[j]);
        }
        //printf("total_dist=%lf\n",total_distance);
        tmp_dist=(rand()/(RAND_MAX+1.0))*total_distance;
        //printf("tmp_dist=%lf\n",tmp_dist);
        tmp_sum=0;
        for(j=0; j<ROW; j++)
        {
            tmp_sum+=dist[j];
            printf("tmp_dist=%lf ? tmp_sum=%lf\n",tmp_dist,tmp_sum);
            if(tmp_dist<=tmp_sum)
            {
                break;
            }
        }

        flag=0;
        for(k=0;k<i;k++)
        {
            if(init_center[k]==j)
            {
                init_center[i]=j+1;
                flag=1;
                break;
            }
        }
        if(flag==0)
        {
            init_center[i]=j;
        }

        now=j;

        for(j=0; j<cluster_num; j++)
        {
            printf("center=%d,",init_center[j]);
        }
    }

    save=(saved *)malloc(sizeof(saved)*cluster_num);

    for(i=0;i<cluster_num;i++)
    {
        for(j=0;j<COL;j++)
        {
            save[i].val[j]=data[init_center[i]].val[j];
        }

    }
    return save;
}

void how_many_cols(char *fname)
{
    char *p,buf[100];
    FILE *fp=fopen(fname,"rt");
    fgets(buf,100,fp);
    p=strtok(buf,",");
    while(p!=NULL)
    {
        p=strtok(NULL,",");
        COL++;
    }
    close(fp);
}

void output(char *fname)
{
    int i,j;
    FILE *fp=fopen(fname,"wt");
    if(fp==NULL)
    {
        printf("fp is NULL\n");
        exit(1);
    }
    for(i=0;i<ROW;i++)
    {
        for(j=0;j<COL;j++)
        {
            if(j==0)
            {
                fprintf(fp,"%lf",data[i].val[j]);
            }
            else
            {
                fprintf(fp,",%lf",data[i].val[j]);
            }
        }
        fprintf(fp," %d",data[i].tag);
        fprintf(fp,"\n");
    }
    fclose(fp);
}

void read_file(char *fname)
{
    int i=0,r=0;
    char *p,buf[100];
    FILE *fp=fopen(fname,"rt");

    if(fp==NULL)
    {
        printf("fp is NULL\n");
        exit(1);
    }
    while(!feof(fp))
    {
        i=0;
        fgets(buf,100,fp);
        p=strtok(buf,",");
        while(p!=NULL)
        {
            data[r].val[i++]=atof(p);
            p=strtok(NULL,",");
        }
        r++;
    }
    ROW=r-1;
    fclose(fp);

}


void help_info()
{
    printf("---------------------Usage--------------------\n");
    printf("./kmeans S D k m i\n");
    printf("S: source file\n");
    printf("D: result file\n");
    printf("k: how many clusters\n");
    printf("m: please use \"means\" or \"median\"(not include the quotation marks)\n");
    printf("i: please use\"random\" or \"plus\"(not include the quotation marks)\n");

}
