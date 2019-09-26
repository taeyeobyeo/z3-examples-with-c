#include <stdio.h>
#include <stdlib.h>
#include <string.h>
int paint[10][10];

int main(){
    FILE *fp = fopen("result","r");
    char buf1[128];
    char buf2[128];
    char buf3[128];
    char buf4[128];
    char buf5[128];
    int i = 0, j = 0, n = 0;
    fscanf(fp, "%s\n %s", buf3, buf4) ;
    while (!feof(fp)) {
		fscanf(fp, "%s", buf1) ; if(strcmp(buf1,")") == 0) break;
		fscanf(fp, "%s", buf2) ;
        i = buf2[1] - '0';
        j = buf2[2] - '0';
		fscanf(fp, "%s", buf3) ; NULL;
		fscanf(fp, "%s", buf4) ; NULL;
		fscanf(fp, "%s", buf5) ;
        n = buf5[0] - '0';
        paint[i][j] = n;
	}
    fclose(fp);
    
    printf("-------------------------\n");
    for(int i =1; i<=9;i++){
        printf("| ");
        for(int j =1; j<=9;j++){
            printf("%d ", paint[i][j]);
            if(j%3==0) printf("| ");
        }
        printf("\n");
        if(i%3==0) printf("-------------------------\n");
    }
    return 0;
}