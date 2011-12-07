#ifndef _KMEANS_H_
#define _KMEANS_H_


#define MAX_NUM 1024
typedef struct
{
    int tag;
    double val[10];// at most 10 dimensions
} point;

point data[MAX_NUM];
int   ROW,COL;

void  how_many_cols(char *fname);
void  help_info();
void  read_file(char *fname);
void  random_tag(int mod);
void  means_cluster(int clust_num);

#endif 
