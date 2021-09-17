#include <stdio.h>
#include <iostream>
#include <vector>

#define CANT_MAX 100
#define CANT_MAX_PRENDAS 20

//Lista de prendas
std::vector<std::vector<int>> matrix(CANT_MAX_PRENDAS, std::vector<int>(CANT_MAX_PRENDAS));
int* tiempos = new int[CANT_MAX_PRENDAS];
int numero_lavado = 1;
int* prendas_lavado = new int[CANT_MAX_PRENDAS];
bool termino = false;

void load_prendas() {
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
}

int main() {
  load_prendas();

  for(int i = 0; i < CANT_MAX_PRENDAS; i++){
    prendas_lavado[i] = 0;
  }

  while(!termino) {
    int cont = 0;
    for(int i = 0; i < CANT_MAX_PRENDAS; i++) {
      if(prendas_lavado[i] != 0) {
        cont++;
      }
      if (cont == 20) termino = true;
    }

    for(int j = 0; j < CANT_MAX_PRENDAS; j++) {
      if(prendas_lavado[j] == 0) {
        if(tiempos[j] < 5) {
          prendas_lavado[j] = numero_lavado;
          for(int k = 0; k < CANT_MAX_PRENDAS; k++) {
            if(matrix[j][k] != 1 && j != k && tiempos[k] < 5) {
              prendas_lavado[k] = numero_lavado;
            }
          }
        } else {
          prendas_lavado[j] = numero_lavado;
          for(int k = 0; k < CANT_MAX_PRENDAS; k++) {
            if(matrix[j][k] != 1 && j != k && tiempos[k] >= 5) {
              prendas_lavado[k] = numero_lavado;
            }
          }
        }
      }
      numero_lavado++;
    }
  }

  FILE *salida = fopen("salida.txt", "w");
  for(int i = 0; i < CANT_MAX_PRENDAS; i++) {
    fprintf(salida, "%d %d\n", i+1, prendas_lavado[i]);
  }

  // for (int i = 0; i < matrix.size(); i++){
  //   for (int j = 0; j < matrix[i].size(); j++)
  //   {
  //       printf("%d ", matrix[i][j]);
  //   }
  //   printf("\n");
  // }
  // for (int i = 0; i < CANT_MAX_PRENDAS; i++) {
  //   printf("%d\n", prendas_lavado[i]);
  // }
  return 0;
}
