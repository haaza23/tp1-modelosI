#include <stdio.h>
#include <iostream>
#include <vector>
#include <array>
#include <bits/stdc++.h>

#define CANT_MAX 500
#define CANT_MAX_PRENDAS 385

struct prenda
{
  int index;
  int time;
  int nro_lavado;
};


//Lista de prendas
std::vector<std::vector<int>> matrix(CANT_MAX_PRENDAS, std::vector<int>(CANT_MAX_PRENDAS));
std::vector<prenda> prendas;
int numero_lavado = 1;
bool termino = false;

void load_prendas() {
  char line[CANT_MAX];
  FILE *lavados = fopen("problema_2.txt", "r");
  while (fgets(line, sizeof(line), lavados)) {
    char flag_from_input;
    int x1 = 0, x2 = 0;
    sscanf(line, "%c %d %d", &flag_from_input, &x1, &x2);
    if (flag_from_input == 'e') {
      matrix[x1-1][x2-1] = 1;
      matrix[x2-1][x1-1] = 1;
    }
    if (flag_from_input == 'n') {
      prendas.push_back({x1-1, x2, 0});
    }

  }
  fclose(lavados);
}

bool compareByLength(const prenda &a, const prenda &b)
{
    return a.time > b.time;
}

int main() {
  load_prendas();

  std::sort(prendas.begin(), prendas.end(), compareByLength);

  // printf("   ");
  // for (int i = 0; i < matrix.size(); i++){
  //   printf("%d  ", i);
  // }
  // printf("\n");
  // for (int i = 0; i < 10; i++){
  //   printf("%d: ", i);
  //   for (int j = 0; j < matrix.size(); j++)
  //   {
  //     if(j > 9){
  //       printf("%d   ",matrix[i][j]);
  //     } else {
  //       printf("%d  ",matrix[i][j]);
  //     }
  //   }
  //   printf("\n");
  // }
  
  for(int j = 0; j < CANT_MAX_PRENDAS; j++) {
    if(prendas[j].nro_lavado == 0) {
      printf("lavado %d con tiempo %d\n", prendas[j].index+1, prendas[j].time);
      prendas[j].nro_lavado = numero_lavado;
      for(int k = 0; k < CANT_MAX_PRENDAS; k++) {
        if(matrix[prendas[j].index][prendas[k].index] != 1 && prendas[k].nro_lavado == 0) {
          bool no_cumple = false;
          for(int a = 0; a < k; a++) {
            if (matrix[prendas[k].index][prendas[a].index] == 1 && prendas[a].nro_lavado == numero_lavado) {
              no_cumple = true;
            }
          }
          if(!no_cumple) {
            prendas[k].nro_lavado = numero_lavado;
          }
        }
      }
      numero_lavado++;
    }
  }

  FILE *salida = fopen("salida.txt", "w");
  for(int i = 0; i < CANT_MAX_PRENDAS; i++) {
    fprintf(salida, "%d %d\n", prendas[i].index+1, prendas[i].nro_lavado);
  }

  return 0;
}