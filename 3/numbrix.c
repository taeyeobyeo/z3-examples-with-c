#include <stdio.h>
#include <stdlib.h>


int main(){
    char buf1[128];
    char buf2[128];
    char buf3[128];
    char buf4[128];
    char buf5[128];
    FILE *pre = fopen("preset","r");
    fscanf(pre, "%s ", buf1); //n
    int n = atoi(buf1) + 2;
    fscanf(pre, "%s\n", buf2); //m
    int m = atoi(buf2) + 2;

    //hint
    int** hint = (int**) malloc(sizeof(int*)*n);
    for(int i =0;i<n;i++){
        hint[i] = (int*) malloc(sizeof(int)*m);
        for(int j = 0; j<m;j++) hint[i][j] = 0;
    }
    while (!feof(pre)) {
        fscanf(pre, "%s", buf3);
        int a = atoi(buf3);
        // printf("%d\n",a);
        fscanf(pre, "%s", buf4);
        int b = atoi(buf4);
        fscanf(pre, "%s", buf5);
        int c = atoi(buf5);
        // printf("%d %d %d\n", a,b,c);
        hint[a][b] = c;
	}
    fclose(pre);

    FILE *fp = fopen("formula","w");
    //declare instance
    for(int i =0; i<n;i++){
        for(int j =0; j<m;j++){
            fprintf(fp,"(declare-const p%d%d Int)\n", i, j);
        }
    }
    
    //range
    for(int i =1; i<n-1;i++)
        for(int j =1; j<m-1;j++)
            fprintf(fp,"(assert (and (<= 1 p%d%d) (>= %d p%d%d)))\n", i, j, (n-2)*(m-2), i,j);

    //predefine
    for(int i = 1;i<n-1;i++){
        for(int j =1;j<m-1;j++){
            if(hint[i][j]!=0) fprintf(fp,"(assert (= p%d%d %d))\n", i,j,hint[i][j]);
        }
    }
    //edge
    for(int i =0; i<n;i++){
        for(int j =0; j<m;j++){
            if(i==0||i==n-1||j==0||j==m-1)
                fprintf(fp,"(assert (= p%d%d 0))\n",i,j);
        }
    }

    //diff setting
    for(int i =1; i<n -1;i++){
        for(int j =1;j<m-1;j++){
            int x = i, y = j+1;
            for(;x<n-1;x++){
                for(;y<m-1;y++){
                    fprintf(fp,"(assert (not (= p%d%d p%d%d)))\n",i,j,x,y);
                }
                y=1;
            }
        }
    }

    //assert + 1
    for(int i = 1; i< n-1;i++){
        for (int j =1; j<m-1;j++){
            fprintf(fp,"(assert (or (= p%d%d %d) ", i, j, (n-2)*(m-2));
            fprintf(fp,"(= (+ p%d%d 1) p%d%d) ", i, j, i,j-1);
            fprintf(fp,"(= (+ p%d%d 1) p%d%d) ", i, j, i-1, j);
            fprintf(fp,"(= (+ p%d%d 1) p%d%d) ", i, j, i, j+1);
            fprintf(fp,"(= (+ p%d%d 1) p%d%d) ", i, j, i+1,j);
            fprintf(fp,"))\n");
        }
    }

    for(int i = 1; i< n-1;i++){
        for (int j =1; j<m-1;j++){
            fprintf(fp,"(assert (or (= p%d%d 1) ", i, j);
            fprintf(fp,"(= (- p%d%d 1) p%d%d) ", i, j, i,j-1);
            fprintf(fp,"(= (- p%d%d 1) p%d%d) ", i, j, i-1, j);
            fprintf(fp,"(= (- p%d%d 1) p%d%d) ", i, j, i, j+1);
            fprintf(fp,"(= (- p%d%d 1) p%d%d) ", i, j, i+1,j);
            fprintf(fp,"))\n");
        }
    }

    fprintf(fp, "(check-sat)\n(get-model)\n") ;
    fclose(fp);
    return 0;
}