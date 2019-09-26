#include <stdio.h>
#include <stdlib.h>

int main(){
	FILE * fp = fopen("formula", "w") ;
	char buf[128];

    //declare instance
    for(int i =1; i<= 9; i++)
        for(int j =1; j<=9; j++)
            fprintf(fp,"(declare-const p%d%d Int)\n", i, j);

    //preset
    fprintf(fp,"; predefined\n");
    FILE * pre = fopen("preset", "r" );
    fscanf(pre, "%s", buf);
    while (!feof(pre)) {
        fscanf(pre, "%s", buf);
        int x = buf[0] - '0';
        int y = buf[1] - '0';
        int z = buf[2] - '0';
        if(buf[2] != '*'){
            fprintf(fp,"(assert (= p%d%d %d))\n", x, y, z);
        }
	}
    fclose(pre);

    //range
    for(int i =1; i<= 9; i++)
        for(int j =1; j<=9; j++)
            fprintf(fp,"(assert (and (<= p%d%d 9) (<= 1 p%d%d)))\n", i, j, i, j);
    
    //row
    for(int i =1; i<= 9; i++){
        fprintf(fp,"(assert (= (+ ");
        for(int j =1; j<= 9; j++){
            fprintf(fp,"p%d%d ", i, j);
        }
        fprintf(fp,") 45))\n");
    }

    //column
    for(int i =1; i<= 9; i++){
        fprintf(fp,"(assert (= (+ ");
        for(int j =1; j<= 9; j++){
            fprintf(fp,"p%d%d ", j, i);
        }
        fprintf(fp,") 45))\n");
    }

    //3x3
    for(int r = 0; r<3; r++){
        for(int s = 0; s<3; s++){
            fprintf(fp,"(assert (= (+ ");
            for(int i = 1; i<=3; i++){
                for(int j =1;j<=3; j++){
                    fprintf(fp, "p%d%d ", 3*r+i, 3*s+j);
                }
            }
            fprintf(fp,") 45))\n");
        }
    }
    fprintf(fp, "(check-sat)\n(get-model)\n") ;
    fclose(fp);
    return 0;
}
