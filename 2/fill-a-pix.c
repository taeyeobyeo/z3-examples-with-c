#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char buf[128];
int val[1001][1001];
int N = 0, M = 0; // represents N*M grid
int** hint;
int** result_table[5];
FILE* fp;
FILE* fin;

int formula(int*** result_table, int** hint, int result);
void exec_z3(int*** result_table, int result);



int main() {
    int c;
    int i = 1, j = 0;
    while((c = getchar()) != EOF){
        switch(c){
            case ' ':
            break;
            case '?':
            j++;
            val[i][j] = 0;
            break;
            case '\n':
            i++; j = 0;
            N++;
            break;
            default:
                j++;
                val[i][j] = c - '0';
        }
        if(j - 1>M) M = j - 1;
    }
    if(j!=0){N++;}
    
    // printf("%d %d %d\n",j,N,M);
    N+=2; M+=2;
    // printf("%d %d\n",N,M);

	hint = (int**)malloc(sizeof(int*) * N);
	for (int i = 0; i < N; i++) {
		hint[i] = (int*)malloc(sizeof(int) * M);
		for (int j = 0; j < M; j++) {
            if(val[i][j]>0)hint[i][j] = val[i][j];
            else hint[i][j] == 0;
        }
	}

	for (int result = 0; result < 5; result++) {
		result_table[result] = (int**)malloc(sizeof(int*) * N);
		for (int i = 0; i < N; i++) {
			result_table[result][i] = (int*)malloc(sizeof(int) * M);
		}

		int check = formula(result_table, hint, result);
		if(check == -1) break;
		else if(check == 0)
			exec_z3(result_table, result);
	}
	return 0;
}


void exec_z3(int*** result_table, int result) {
	fscanf(fin, "%s", buf);
	while (!feof(fin)) {
		fscanf(fin, "%s", buf); if (strcmp(buf, ")") == 0) break;
		fscanf(fin, "%s", buf);
		int num[2] = { 0,0 }, idx = 0;
		int len = strlen(buf);
		for (int i = 1; i < len; i++) {
			if (buf[i] == '_') idx++;
			else {
				num[idx] = num[idx] * 10 + buf[i] - '0';
			}
		}
		fscanf(fin, "%s", buf);
		fscanf(fin, "%s", buf);
		fscanf(fin, "%s", buf);
		if (buf[0] - '0' == 1) result_table[result][num[0]][num[1]] = 1;
	}
	fclose(fin);
	FILE* out = fopen("output", "a");
	printf("\nSolution %d:\n\n", result + 1);
	for (int i = 1; i < N - 1; i++) {
		for (int j = 1; j < M - 1; j++) {
			if(result_table[result][i][j] > 1)
				result_table[result][i][j] = 0;
			else if(result_table[result][i][j] < 0)
				result_table[result][i][j] = 0;
			fprintf(out, "%d ", result_table[result][i][j]);
			printf("%d ", result_table[result][i][j]);
		}
		fprintf(out, "\n");
		printf("\n");
	}printf("\n");
	fclose(out);
}

int formula(int*** result_table, int** hint, int result) {
	fp = fopen("formula", "w");

	//declare instance
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < M; j++) {
			fprintf(fp, "(declare-const p%d_%d Int)\n", i, j);
		}
	}

	//range
	for (int i = 0; i < N; i++)
		for (int j = 0; j < M; j++)
			fprintf(fp, "(assert (and (<= 0 p%d_%d) (>= 1 p%d_%d)))\n", i, j, i, j);


	int **check_arr = (int**)malloc(sizeof(int*)*N);
	for(int i = 0; i < N; i++){
		check_arr[i] = (int*)malloc(sizeof(int)*M);
			for(int j = 0; j < M; j++){
				check_arr[i][j] = 0;
			}
	}
	
	//assert according to hints
	for (int i = 1; i < N; i++) {
		for (int j = 1; j < M; j++) {
			if (hint[i][j] == 0) continue;

			fprintf(fp, "(assert (= (+ ");
			
			for (int x = -1; x < 2; x++) {
				for (int y = -1; y < 2; y++) {
					fprintf(fp, "p%d_%d ", i + x, j + y);
						check_arr[i+x][j+y] = 1;
				}
			}
			fprintf(fp, ") %d))\n", hint[i][j]);	
		}
	}

	//edge setting
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < M; j++) {
			if (i == 0 || i == N - 1 || j == 0 || j == M - 1){
				fprintf(fp, "(assert (= p%d_%d 0))\n", i, j);
				check_arr[i][j] = 0;
			}
		}
	}
	
	//get different solutions
	for (int r = 0; r < result; r++) {
		fprintf(fp, "(assert (not (and ");
		for (int i = 0; i < N; i++)
			for (int j = 0; j < M; j++) {
				if(result_table[r][i][j] > 1)
					result_table[r][i][j] = 0;
					
				else if(result_table[r][i][j] < 0)
					result_table[r][i][j] = 0;

				if (i != 0 && i != N - 1 && j != 0 && j != M - 1){	
					fprintf(fp, "(= p%d_%d %d) ", i, j, result_table[r][i][j]);
				}

			}
		fprintf(fp, ") )) \n");
	}

	fprintf(fp, "(check-sat)\n(get-model)\n");
	fclose(fp);

	fin = popen("z3 formula", "r");
	fscanf(fin, "%s", buf);
	if (strcmp(buf, "unsat") == 0) {
		printf("No Solution\n");
		fclose(fin);
		return -1;
	}

	else
		return 0;
}
