#include <stdio.h>
#include <stdlib.h>

char buf[128];

int main(){
    //preset
    FILE * pre = fopen("preset", "r" );
    fscanf(pre, "%s ", buf); //n
    int n = buf[0] - '0' + 2;
    fscanf(pre, "%s\n", buf); //m
    int m = buf[0] - '0' + 2;

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
        fscanf(pre, "%s", buf);
        int x = buf[0] - '0';
        int y = buf[1] - '0';
        int z = buf[2] - '0';
        hint[x][y] = z;
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
