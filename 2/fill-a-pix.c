#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(){
    char buf1[128];
    char buf2[128];
    char buf3[128];
    char buf4[128];
    char buf5[128];
    //preset
    FILE * pre = fopen("preset", "r" );
    fscanf(pre, "%s ", buf1); //n
    int n = atoi(buf1) + 2;
    fscanf(pre, "%s\n", buf2); //m
    int m = atoi(buf2) + 2;
    // printf("%d %d\n",n,m);
    //hint
    int** hint = (int**) malloc(sizeof(int*)*n);
    for(int i =0;i<n;i++){
        hint[i] = (int*) malloc(sizeof(int)*m);
        for(int j = 0; j<m;j++) hint[i][j] = 0;
    }
    //dp
    int** dp = (int**) malloc(sizeof(int*)*n);
    for(int i =0;i<n;i++){
        dp[i] = (int*) malloc(sizeof(int)*m);
        for(int j = 0; j<m;j++) dp[i][j] = 0;
    }

    while (!feof(pre)) {
        fscanf(pre, "%s", buf3);
        fscanf(pre, "%s", buf4);
        fscanf(pre, "%s", buf5);
        int a = atoi(buf3);
        int b = atoi(buf4);
        int c = atoi(buf5);
        // printf("%d %d %d\n",x,y,z);
        if(1<=a&&a<n&&1<=b&&b<m&&0<=c&&c<=9)
            hint[a][b] = c;
	}
    fclose(pre);

	FILE * fp = fopen("formula", "w") ;
    
    //declare instance
    for(int i =0; i<n;i++){
        for(int j =0; j<m;j++){
            fprintf(fp,"(declare-const p%d%d Int)\n", i, j);
        }
    }

    for(int i =0; i<n;i++)
        for(int j =0; j<m;j++)
            fprintf(fp,"(assert (and (<= 0 p%d%d) (>= 1 p%d%d)))\n", i, j,i,j);

    //edge
    for(int i =0; i<n;i++){
        for(int j =0; j<m;j++){
            if(i==0||i==n-1||j==0||j==m-1)
                fprintf(fp,"(assert (= p%d%d 0))\n",i,j);
        }
    }

    //assert
    for(int i = 1; i< n-1;i++){
        for (int j =1; j<m-1;j++){
            if(hint[i][j]==0) continue;
            fprintf(fp,"(assert (= (+ ");
            for(int x = -1; x<2;x++){
                for(int y = -1; y<2;y++){
                    fprintf(fp,"p%d%d ", i+x,j+y);
                }
            }
            fprintf(fp,") %d))\n", hint[i][j]);
        }
    }

    fprintf(fp, "(check-sat)\n(get-model)\n") ;
    fclose(fp);
    return 0;
}
