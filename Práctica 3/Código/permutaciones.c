/**
 *
 * Descripcion: Implementacion de funciones de generacion de permutaciones
 *
 * Fichero: permutaciones.c
 * Autor: Carlos Aguirre
 * Version: 1.0
 * Fecha: 16-09-2017
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include "permutaciones.h"

/***************************************************/
/* Funcion: aleat_num Fecha: 21/09/2019            */
/* Autores: Rubén García y Elena Cano              */
/*                                                 */
/* Rutina que genera un numero aleatorio           */
/* entre dos numeros dados                         */
/*                                                 */
/* Entrada:                                        */
/* int inf: limite inferior                        */
/* int sup: limite superior                        */
/* Salida:                                         */
/* int: numero aleatorio                           */
/***************************************************/
int aleat_num(int inf, int sup)
{
  return (rand()/(RAND_MAX+1.))*(sup-inf+1)+inf;
}

/***************************************************/
/* Funcion: genera_perm Fecha: 21/09/2019          */
/* Autores: Rubén García y Elena Cano              */
/*                                                 */
/* Rutina que genera una permutacion               */
/* aleatoria                                       */
/*                                                 */
/* Entrada:                                        */
/* int n: Numero de elementos de la                */
/* permutacion                                     */
/* Salida:                                         */
/* int *: puntero a un array de enteros            */
/* que contiene a la permutacion                   */
/* o NULL en caso de error                         */
/***************************************************/
void swap(int* x, int* y) {
  int aux;
  aux=*x;
  *x=*y;
  *y=aux;
}

int* genera_perm(int N)
{
  int* p=NULL;
  int i;
  p=(int*)malloc(N*sizeof(int));
  if (p==NULL)
    return NULL;
  for (i=0; i<N; i++) {
    p[i]=i+1;
  }
  for (i=0; i<N; i++) {
    swap(&(p[i]), &(p[aleat_num(i, N-1)]));
  }
  return p;
}

/***************************************************/
/* Funcion: genera_permutaciones Fecha: 21/09/2019 */
/* Autores: Rubén García y Elena Cano              */
/*                                                 */
/* Funcion que genera n_perms permutaciones        */
/* aleatorias de tamanio elementos                 */
/*                                                 */
/* Entrada:                                        */
/* int n_perms: Numero de permutaciones            */
/* int N: Numero de elementos de cada              */
/* permutacion                                     */
/* Salida:                                         */
/* int**: Array de punteros a enteros              */
/* que apuntan a cada una de las                   */
/* permutaciones                                   */
/* NULL en caso de error                           */
/***************************************************/
int** genera_permutaciones(int n_perms, int N)
{
  int** perms=NULL;
  int i;
  int j;
  perms=malloc(n_perms*sizeof(int*));
  if (perms==NULL)
    return NULL;
  for (i=0; i<n_perms; i++) {
    perms[i]=genera_perm(N);
    if (perms[i]==NULL) {
      for (j=0; j<i; j++) {
        free(perms[j]);
        perms[j]=NULL;
        break;
      }
    free(perms);  
    return NULL;
    }
  }
  return perms;
}
