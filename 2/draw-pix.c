#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char buf[128];

int main(){
    FILE *pre = fopen("preset","r");
    fscanf(pre, "%s ", buf); //n
    int n = atoi(buf) + 2;
    fscanf(pre, "%s\n", buf); //m
    int m = atoi(buf) + 2;
    fclose(pre);
    // printf("%d%d\n",n,m);
    int** dp = (int**) malloc(sizeof(int*)*n);
    for(int i =0;i<n;i++){
        dp[i] = (int*) malloc(sizeof(int)*m);
        for(int j = 0; j<m;j++) dp[i][j] = 0;
    }

    FILE *fp = fopen("result","r");
    char buf1[128];
    char buf2[128];
    char buf3[128];
    char buf4[128];
    char buf5[128];
    int x = 0, y = 0;
    fscanf(fp, "%s\n %s", buf1, buf2);
    if(strcmp(buf1,"unsat")==0) {
        printf("Unsatisfiable preset\n\n");
        fclose(fp);
        return -1;
    }
    while (!feof(fp)) {
        fscanf(fp, "%s", buf1); if(strcmp(buf1,")") == 0) break; 
        // printf("%s ",buf1);
		fscanf(fp, "%s", buf2);
        // printf("%s ",buf2);
        x = buf2[1] - '0';
        y = buf2[2] - '0';
		fscanf(fp, "%s", buf3); 
        // printf("%s ",buf3);
		fscanf(fp, "%s", buf4); 
        // printf("%s ",buf4);
		fscanf(fp, "%s", buf5); 
        // printf("%s \n",buf5);
        if(buf5[0] - '0' == 1) dp[x][y] = 1;
        // printf("%d\n",buf5[0] - '0');
	}
    fclose(fp);
    for(int i = 1;i<n-1;i++){
        for(int j = 1; j<m-1;j++){
            printf("%d ",dp[i][j]);
        }
        printf("\n");
    }
    return 0;
}