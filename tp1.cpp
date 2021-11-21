#include <stdio.h>
#include <iostream>
#include <vector>

#define CANT_MAX 500
#define CANT_MAX_PRENDAS 385

//Lista de prendas
std::vector<std::vector<int>> matrix(CANT_MAX_PRENDAS, std::vector<int>(CANT_MAX_PRENDAS));
int* tiempos = new int[CANT_MAX_PRENDAS];
int numero_lavado = 1;
int* prendas_lavado = new int[CANT_MAX_PRENDAS];
bool termino = false;

void load_prendas() {
  char line[CANT_MAX];
  FILE *lavados = fopen("problema_2.txt", "r");
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

bool isInRange(int num1, int num2) {
  return (abs(num1 - num2) <= 2);
}

int main() {
  load_prendas();

  for(int i = 0; i < CANT_MAX_PRENDAS; i++){
    prendas_lavado[i] = 0;
  }

  for(int j = 0; j < CANT_MAX_PRENDAS; j++) {
    if(prendas_lavado[j] == 0 && tiempos[j] > 8) {
      printf("%d  \n", j);
      prendas_lavado[j] = numero_lavado;
      for(int k = 0; k < CANT_MAX_PRENDAS; k++) {
        if(matrix[j][k] != 1 && j != k && prendas_lavado[k] == 0 && tiempos[k] > 8) {
          bool no_cumple = false;
          for(int a = 0; a < CANT_MAX_PRENDAS; a++) {
            if (matrix[a][k] == 1 && prendas_lavado[a] == numero_lavado) no_cumple = true;
          }
          if(!isInRange(tiempos[j], tiempos[k])) no_cumple = true;
          if(!no_cumple) {
            prendas_lavado[k] = numero_lavado;
          }
        }
      }
      numero_lavado++;  
    }
  }

  for(int j = 0; j < CANT_MAX_PRENDAS; j++) {
    if(prendas_lavado[j] == 0 && tiempos[j] <= 8) {
      printf("%d  \n", j);
      prendas_lavado[j] = numero_lavado;
      for(int k = 0; k < CANT_MAX_PRENDAS; k++) {
        if(matrix[j][k] != 1 && j != k && prendas_lavado[k] == 0 && tiempos[k] <= 8) {
          bool no_cumple = false;
          for(int a = 0; a < CANT_MAX_PRENDAS; a++) {
            if (matrix[a][k] == 1 && prendas_lavado[a] == numero_lavado) no_cumple = true;
          }
          if(!isInRange(tiempos[j], tiempos[k])) no_cumple = true;
          if(!no_cumple) {
            prendas_lavado[k] = numero_lavado;
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

  return 0;
}