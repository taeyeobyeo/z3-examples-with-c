#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//global variable for asterisk cells
int a[9][2];
int ai = 0;
int paint[10][10];
int main(){
	FILE * fp = fopen("formula", "w") ;
	char buf[128];
    //declare instance
    for(int i =1; i<= 9; i++)
        for(int j =1; j<=9; j++)
            fprintf(fp,"(declare-const p%d%d Int)\n", i, j);

    //preset
    fprintf(fp,"; predefined\n");
    FILE * pre = fopen("input", "r" );

    for(int i = 1 ;i<=9;i++){
        for(int j =1; j<=9;j++){
            fscanf(pre,"%s",buf);
            if(strcmp(buf,"*")==0){
                a[ai][0]=i;
                a[ai][1]=j;
                ai++;
            }
            else if (strcmp(buf,"?")!=0){
                fprintf(fp,"(assert (= p%d%d %d))\n", i, j, atoi(buf));
            }
        }
    }

    fclose(pre);

    //range
    for(int i =1; i<= 9; i++)
        for(int j =1; j<=9; j++)
            fprintf(fp,"(assert (and (<= p%d%d 9) (<= 1 p%d%d)))\n", i, j, i, j);

    //row
    for(int i =1; i<=9;i++){
        fprintf(fp,"(assert (and ");
        for(int j =1;j<=8;j++){
            for(int k = j+1;k<=9;k++){
                fprintf(fp,"(not (= p%d%d p%d%d)) ",i,j,i,k);
            }
        }
        fprintf(fp,"))\n");
    }

    //column
    for(int i =1; i<=9;i++){
        fprintf(fp,"(assert (and ");
        for(int j =1;j<=8;j++){
            for(int k = j+1;k<=9;k++){
                fprintf(fp,"(not (= p%d%d p%d%d)) ",j,i,k,i);
            }
        }
        fprintf(fp,"))\n");
    }

    //3x3
    for(int r = 0; r<3; r++){
        for(int s = 0; s<3; s++){
            fprintf(fp,"(assert (and ");
            for(int i = 1; i<=3; i++){
                for(int j =1;j<=3; j++){
                    int x = i, y = j + 1;
                    for(; x<=3;x++){
                        for(;y<=3;y++){
                            fprintf(fp,"(not (= p%d%d p%d%d)) ", 3*r+i, 3*s+j, 3*r+x, 3*s + y);
                        }
                        y=1;
                    }
                }
            }
            fprintf(fp,"))\n");
        }
    }

    //asterisk
    for(int i =0;i<ai - 1;i++){
        fprintf(fp,"(assert (and ");
        for(int j =i+1; j<ai;j++){
            fprintf(fp,"(not (= p%d%d p%d%d)) ",a[i][0],a[i][1],a[j][0],a[j][1]);
        }
        fprintf(fp,"))\n");
    }

    fprintf(fp, "(check-sat)\n(get-model)\n") ;
    fclose(fp);

    //print
    FILE * fin = popen("z3 formula", "r"); //FIXME
	fscanf(fin, "%s", buf);
    if(strcmp(buf,"unsat")==1){
        printf("No Solution\n");
        return -1;
    }
    fscanf(fin, "%s", buf);
	while (!feof(fin)) {
		fscanf(fin, "%s", buf) ; if(strcmp(buf,")") == 0) break;
		fscanf(fin, "%s", buf) ; 
        int first = buf[1] - '0';
        int second = buf[2] - '0';
		fscanf(fin, "%s", buf);
		fscanf(fin, "%s", buf);
		fscanf(fin, "%s", buf);
        paint[first][second] = buf[0] - '0';
	}
	pclose(fin);
    printf("\nA separate output file has been created.\n\n");
    FILE *out = fopen("output","w");
    printf("-------------------------\n");
    for(int i =1; i<=9;i++){
        printf("| ");
        for(int j =1; j<=9;j++){
            fprintf(out, "%d ",paint[i][j]);
            printf("%d ", paint[i][j]);
            if(j%3==0) printf("| ");
        }
        fprintf(out,"\n");
        printf("\n");
        if(i%3==0) printf("-------------------------\n");
    }printf("\n");
    fclose(out);
    return 0;
}
