#include <stdio.h>
#include <iostream>
#include <vector>

#define CANT_MAX 100
#define CANT_MAX_PRENDAS 20

//Lista de prendas
std::vector<std::vector<int>> matrix(CANT_MAX_PRENDAS, std::vector<int>(CANT_MAX_PRENDAS));
int* tiempos = new int[CANT_MAX_PRENDAS];

int main() {
  char line[CANT_MAX];
  FILE *lavados = fopen("problema_1.txt", "r");
  while (fgets(line, sizeof(line), lavados)) {
    char flag = fgetc(lavados);
    char flag_from_input;
    int x1 = 0, x2 = 0;
    if (flag == 'e') {
      sscanf(line, "%c %d %d", &flag_from_input, &x1, &x2);
      if (x1 != 0 || x2 != 0) {
        matrix[x1-1][x2-1] = 1;
      }
    }
    if (flag == 'n') {
      sscanf(line, "%c %d %d", &flag_from_input, &x1, &x2);
      if (x1 != 0 || x2 != 0) {
        tiempos[x1-1] = x2;
      }
    }
  }
  fclose(lavados);

  // for (int i = 0; i < matrix.size(); i++){
  //   for (int j = 0; j < matrix[i].size(); j++)
  //   {
  //       printf("%d", matrix[i][j]);
  //   }
  //   printf("\n");
  // }
  for (int i = 0; i < 20; i++) {
    printf("%d\n", tiempos[i]);
  }
  return 0;
}
