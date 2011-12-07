#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>
#include<math.h>
#include"kmeans.h"

int main(int argc,char*argv[])
{
    int sum,i,j;
    ROW=0,COL=0;
    if(argc!=6||(strcmp(argv[1],"-help")==0))
    {
        help_info();
        exit(0);
    }
    how_many_cols(argv[1]);
    read_file(argv[1]);
    random_tag(atoi(argv[3]));
    //debug info
    for(i=0; i<ROW; i++)
    {
        for(j=0; j<COL; j++)
        {
            printf("data[%d].val %f,tag=%d,",i,data[i].val[j],data[i].tag);
        }
        printf("\n");
    }
    means_cluster(atoi(argv[3]));

    return 0;
}


void random_tag(int mod)
{
    int i;
    srand(time(0));
    for(i=0; i<ROW; i++)
    {
        data[i].tag=(rand()%mod);
    }

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
    
}
