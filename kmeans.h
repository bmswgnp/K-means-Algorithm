#ifndef _KMEANS_H_
#define _KMEANS_H_


#define MAX_NUM 4096
typedef struct
{
    double val[30];

}saved;

typedef struct
{
    int tag;
    double val[30];// at most 30 dimensions
} point;

point data[MAX_NUM];
int   ROW,COL;

void  how_many_cols(char *fname);
void  help_info();
void  read_file(char *fname);
saved* random_init(int clust_num);
void  means_cluster(int clust_num,saved* save);
saved*  plus_init(int clust_num);
void  median_cluster(int clust_num,saved* save);
void  output(char *fname);

#endif
