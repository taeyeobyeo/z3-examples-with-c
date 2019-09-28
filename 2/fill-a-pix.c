#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(){
    char buf[128];
    FILE *in = fopen("input", "r");
    int N = 0, M = 0; // represents N*M grid
    fgets(buf,128,in);
    int len = strlen(buf);
    for(int i =0; i<len;i++){
        if(buf[i]==' ')M++;
    }M+=3;
    rewind(in);
    while(!feof(in)){
        fgets(buf,128,in);
        N++;
    }N+=2;
    // printf("\nN:%d M:%d\n",N,M);
    int** hint = (int**) malloc(sizeof(int*)*N);
    for(int i =0;i<N;i++){
        hint[i] = (int*) malloc(sizeof(int)*M);
        for(int j = 0; j<M;j++) hint[i][j] = 0;
    }
    //dp
    int** dp = (int**) malloc(sizeof(int*)*N);
    for(int i =0;i<N;i++){
        dp[i] = (int*) malloc(sizeof(int)*M);
        for(int j = 0; j<M;j++) dp[i][j] = 0;
    }
    rewind(in);
    for(int i =0;i<N-2;i++){
        for(int j =0;j<M-2;j++){
            fscanf(in,"%s", buf);
            if(strcmp(buf,"?")!=0){
                hint[i+1][j+1] = atoi(buf);
            }
        }
    }
    fclose(in);
    FILE *fp = fopen("formula","w");
    
    //declare instance
    for(int i =0; i<N;i++){
        for(int j =0; j<M;j++){
            fprintf(fp,"(declare-const p%d_%d Int)\n", i, j);
        }
    }

    for(int i =0; i<N;i++)
        for(int j =0; j<M;j++)
            fprintf(fp,"(assert (and (<= 0 p%d_%d) (>= 1 p%d_%d)))\n", i, j,i,j);

    //edge
    for(int i =0; i<N;i++){
        for(int j =0; j<M;j++){
            if(i==0||i==N-1||j==0||j==M-1)
                fprintf(fp,"(assert (= p%d_%d 0))\n",i,j);
        }
    }

    //assert
    for(int i = 1; i< N-1;i++){
        for (int j =1; j<M-1;j++){
            if(hint[i][j]==0) continue;
            fprintf(fp,"(assert (= (+ ");
            for(int x = -1; x<2;x++){
                for(int y = -1; y<2;y++){
                    fprintf(fp,"p%d_%d ", i+x,j+y);
                }
            }
            fprintf(fp,") %d))\n", hint[i][j]);
        }
    }

    fprintf(fp, "(check-sat)\n(get-model)\n") ;
    fclose(fp);

    FILE *fin = popen("z3 formula", "r");
    fscanf(fin, "%s", buf);
    if(strcmp(buf,"unsat")==1){
        printf("No Solution\n");
        return -1;
    }
    fscanf(fin, "%s", buf);
    while (!feof(fin)) {
        fscanf(fin, "%s", buf); if(strcmp(buf,")") == 0) break; 
        // printf("%s ",buf1);
		fscanf(fin, "%s", buf);
        // printf("%s ",buf);
        int num[2] = {0,0}, idx = 0;
        int len = strlen(buf);
        for(int i = 1; i < len; i++){
            // printf("%c\n", buf[i]);
            if(buf[i]=='_') idx++;
            else{
                num[idx] = num[idx]*10 + buf[i] - '0';
                // printf("%d\n",num[idx]);
            }
        }
		fscanf(fin, "%s", buf); 
        // printf("%s ",buf3);
		fscanf(fin, "%s", buf); 
        // printf("%s ",buf4);
		fscanf(fin, "%s", buf); 
        // printf("%s \n",buf5);
        if(buf[0] - '0' == 1) dp[num[0]][num[1]] = 1;
        // printf("%d\n",buf5[0] - '0');
	}
    pclose(fin);
    
    for(int i = 1;i<N-1;i++){
        for(int j = 1; j<M-1;j++){
            printf("%d ",dp[i][j]);
        }
        printf("\n");
    }
    return 0;
}
