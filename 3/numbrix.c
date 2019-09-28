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
    int** hint = (int**) malloc(sizeof(int*)*N);
    for(int i =0;i<N;i++){
        hint[i] = (int*) malloc(sizeof(int)*M);
        for(int j = 0; j<M;j++) hint[i][j] = 0;
    }
    rewind(in);
    for(int i =0; i<N-2;i++){
        for(int j =0; j<M-2;j++){
            fscanf(in,"%s",buf);
            if(strcmp(buf,"?")!=0){
                hint[i+1][j+1] = atoi(buf);
            }
        }
    }
    fclose(in);
    int nxm = (N-2)*(M-2), exp = 0;

    while(nxm>0){
        nxm/=10;    //10000 1000 100 10 1
        exp++;      //1 2 3 4 5
    }
    // printf("%d\n", exp);

    FILE *fp = fopen("formula","w");
    //declare instance
    for(int i =0; i<N;i++){
        for(int j =0; j<M;j++){
            fprintf(fp,"(declare-const p%d_%d Int)\n", i, j);
        }
    }
    
    //range
    for(int i =1; i<N-1;i++)
        for(int j =1; j<M-1;j++)
            fprintf(fp,"(assert (and (<= 1 p%d_%d) (>= %d p%d_%d)))\n", i, j, (N-2)*(M-2), i,j);

    //predefine
    for(int i = 1;i<N-1;i++){
        for(int j =1;j<M-1;j++){
            if(hint[i][j]!=0) fprintf(fp,"(assert (= p%d_%d %d))\n", i,j,hint[i][j]);
        }
    }
    //edge
    for(int i =0; i<N;i++){
        for(int j =0; j<M;j++){
            if(i==0||i==N-1||j==0||j==M-1)
                fprintf(fp,"(assert (= p%d_%d 0))\n",i,j);
        }
    }

    //diff setting
    for(int i =1; i<N -1;i++){
        for(int j =1;j<M-1;j++){
            int x = i, y = j+1;
            for(;x<N-1;x++){
                for(;y<M-1;y++){
                    fprintf(fp,"(assert (not (= p%d_%d p%d_%d)))\n",i,j,x,y);
                }
                y=1;
            }
        }
    }

    //assert + 1
    for(int i = 1; i< N-1;i++){
        for (int j =1; j<M-1;j++){
            fprintf(fp,"(assert (or (= p%d_%d %d) ", i, j, (N-2)*(M-2));
            fprintf(fp,"(= (+ p%d_%d 1) p%d_%d) ", i, j, i,j-1);
            fprintf(fp,"(= (+ p%d_%d 1) p%d_%d) ", i, j, i-1, j);
            fprintf(fp,"(= (+ p%d_%d 1) p%d_%d) ", i, j, i, j+1);
            fprintf(fp,"(= (+ p%d_%d 1) p%d_%d) ", i, j, i+1,j);
            fprintf(fp,"))\n");
        }
    }

    for(int i = 1; i< N-1;i++){
        for (int j =1; j<M-1;j++){
            fprintf(fp,"(assert (or (= p%d_%d 1) ", i, j);
            fprintf(fp,"(= (- p%d_%d 1) p%d_%d) ", i, j, i,j-1);
            fprintf(fp,"(= (- p%d_%d 1) p%d_%d) ", i, j, i-1, j);
            fprintf(fp,"(= (- p%d_%d 1) p%d_%d) ", i, j, i, j+1);
            fprintf(fp,"(= (- p%d_%d 1) p%d_%d) ", i, j, i+1,j);
            fprintf(fp,"))\n");
        }
    }
    fprintf(fp, "(check-sat)\n(get-model)\n") ;
    fclose(fp);

    FILE *fin = popen("z3 formula", "r");
    int** dp = (int**) malloc(sizeof(int*)*N);
    for(int i =0;i<N;i++){
        dp[i] = (int*) malloc(sizeof(int)*M);
        for(int j = 0; j<M;j++) dp[i][j] = 0;
    }
    fscanf(fp, "%s", buf);
    if(strcmp(buf,"unsat")==0){
        printf("\nNo solution\n");
        return -1;
    }
    fscanf(fp, "%s", buf);
    while (!feof(fp)) {
        fscanf(fp, "%s", buf); if(strcmp(buf,")") == 0) break; 
        // printf("%s ",buf1);
		fscanf(fp, "%s", buf); if(strcmp(buf,")") == 0) break; 
        // printf("%s ",buf2);
        // int len = strlen(buf2) - 1;
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
		fscanf(fp, "%s", buf); 
        // printf("%s ",buf3);
		fscanf(fp, "%s", buf); 
        // printf("%s ",buf4);
		fscanf(fp, "%s", buf); 
        // printf("%s \n",buf);
        dp[num[0]][num[1]] = atoi(buf);
        // printf("%d %d %d\n",num[0],num[1], atoi(buf));
	}
    pclose(fin);

    FILE *out = fopen("output", "w");
    printf("\nA separate output file has been created\n\n");
    for(int i = 1;i<N-1;i++){
        for(int j = 1; j<M-1;j++){
            switch(exp){
                case 2:
                    fprintf(out,"%2d ", dp[i][j]);
                    printf("%2d ", dp[i][j]);
                    break;
                case 3:
                    fprintf(out,"%3d ", dp[i][j]);
                    printf("%3d ", dp[i][j]);
                    break;
                case 4:
                    fprintf(out,"%4d ", dp[i][j]);
                    printf("%4d ", dp[i][j]);
                    break;
                case 5:
                    fprintf(out,"%5d ", dp[i][j]);
                    printf("%5d ", dp[i][j]);
                    break;
                default:
                    fprintf(out,"%d ", dp[i][j]);
                    printf("%d ", dp[i][j]);
            }
        }
        fprintf(out,"\n");
        printf("\n");
    }printf("\n");
    fclose(out);
    return 0;
}