#include <stdio.h>
#include <stdlib.h>

int main(){
	FILE * fp = fopen("formula", "w") ;
	char buf[128];

    //declare instance
    for(int i =1; i<= 9; i++)
        for(int j =1; j<=9; j++){
            for(int n = 1; n<= 9; n++){
                fprintf(fp,"(declare-const p%d%d%d Bool)\n", i, j, n);
            }
            // fprintf(fp,"(declare-const p%d%d* Bool)\n", i, j);
        }

    //cells
    fprintf(fp,"; predefined\n");
    FILE * pre = fopen("preset", "r" );
    fscanf(pre, "%s", buf);
    while (!feof(pre)) {
        fscanf(pre, "%s", buf);
        int x = buf[0] - '0';
        int y = buf[1] - '0';
        int z = buf[2] - '0';
        if(buf[2] != '*'){
            fprintf(fp,"(assert(= p%d%d%d true))\n", x, y, z);
        }
        // else {
        //     fprintf(fp,"(assert(= p%d%d%d true))\n", x, y, z);
        // }
	}
    fclose(pre);

    fprintf(fp,"; Q0\n");
    fprintf(fp,"(assert (and ");
	for (int i = 1; i <= 9 ; i++){
        fprintf(fp,"(and ");
        for (int j =1; j<=9;j++){
            fprintf(fp,"(and ");
            for(int n = 1; n<=9; n++){
                fprintf(fp,"(and ");
                for(int m = 1; m<=9; m++){
                    if(m!=n)fprintf(fp,"(not (and p%d%d%d p%d%d%d)) ",i,j,n,i,j,m);
                }fprintf(fp,")");
            }fprintf(fp,")");
        } fprintf(fp,")");
    }fprintf(fp,"))\n");
    
    fprintf(fp,"; Q0-2\n");
    fprintf(fp,"(assert (and ");
	for (int i = 1; i <= 9 ; i++){
        fprintf(fp,"(and ");
        for (int j =1; j<=9;j++){
            fprintf(fp,"(or ");
            for(int n = 1; n<=9; n++){
                fprintf(fp,"p%d%d%d ",i,j,n);
            }fprintf(fp,")");
        } fprintf(fp,")");
    }fprintf(fp,"))\n");

    //row
    fprintf(fp,"; Q1\n");
    fprintf(fp,"(assert (and ");
	for (int i = 1; i <= 9 ; i++){
        fprintf(fp,"(and ");
        for (int n =1; n<=9;n++){
            fprintf(fp,"(or ");
            for(int j = 1; j<=9; j++){
                fprintf(fp,"p%d%d%d ",i,j,n);
            }fprintf(fp,")");
        } fprintf(fp,")");
    }fprintf(fp,"))\n");

    //column
    fprintf(fp,"; Q2\n");
    fprintf(fp, "(assert (and ");
	for (int j = 1; j <= 9 ; j++){
        fprintf(fp,"(and ");
        for (int n =1; n<=9;n++){
            fprintf(fp,"(or ");
            for(int i = 1; i<=9; i++){
                fprintf(fp,"p%d%d%d ",i,j,n);
            } fprintf(fp,")");
        }fprintf(fp,")");
    }fprintf(fp,"))\n");
    //3x3
    fprintf(fp,"; Q3\n");
    // (and (or (or 
    fprintf(fp,"(assert (and ");
    for( int r = 0; r<=2; r++){
        fprintf(fp,"(and ");
        for(int s = 0; s<=2; s++){
            fprintf(fp,"(and ");
            for(int n = 1; n<=9;n++){
                fprintf(fp,"(or ");
                for(int i =1; i<=3;i++){
                    fprintf(fp,"(or ");
                    for(int j =1; j<=3;j++){
                        fprintf(fp, "p%d%d%d ",3*r + i, 3*s + j, n);
                    }fprintf(fp,")");
                }fprintf(fp,")");
            } fprintf(fp,")");
        }fprintf(fp,")");
    }fprintf(fp,"))\n");

    // fprintf(fp,"; asterisk\n");
    // // (and (or (or 
    // fprintf(fp,"(assert (and ");
    // for( int i = 1; i<=9; i++){
    //     fprintf(fp,"(and ");
    //     for(int j =1; j<=9;j++){
    //         fprintf(fp,"(and ");
    //         for(int n = 1; n<=9;n++){
    //             fprintf(fp,"(or ");
    //             for(int m = 1; m<=9;m++){
    //                 if(n==m) continue;
    //                 fprintf(fp,"(not p%d%d%d) p%d%d%d",i,j,n,i,j,m);
    //             }fprintf(fp,")");
    //         }fprintf(fp,")");
    //     }fprintf(fp,")");
    // }fprintf(fp,"))\n");

    fprintf(fp, "(check-sat)\n(get-model)\n") ;
    fclose(fp);
    
	FILE * fin = popen("z3 formula", "r") ; //FIXME
	fscanf(fin, "%s %s", buf, buf) ;
	while (!feof(fin)) {
		fscanf(fin, "%s", buf) ; printf("%s ", buf) ;
		fscanf(fin, "%s", buf) ; printf("%s ", buf) ;
		fscanf(fin, "%s", buf) ; printf("%s ", buf) ;
		fscanf(fin, "%s", buf) ; printf("%s ", buf) ;
		fscanf(fin, "%s", buf) ; printf("%s\n", buf) ;
	}
    pclose(fin);
    return 0;
}
