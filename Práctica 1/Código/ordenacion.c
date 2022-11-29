/**
 *
 * Descripcion: Implementacion de funciones de ordenacion
 *
 * Fichero: ordenacion.c
 * Autor: Carlos Aguirre
 * Version: 1.0
 * Fecha: 16-09-2019
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include "ordenacion.h"

/***************************************************/
/* Funcion: SelectSort    Fecha:                   */
/* Vuestro comentario                              */
/***************************************************/
int InsertSort(int* tabla, int ip, int iu)
{
  int i, j, pos, OB=0;
  if (tabla==NULL || ip<0 || iu<ip)
    return ERR;
  for (i=ip; i<=iu; i++) {
    pos=tabla[i];
    j=i-1;
    while (j>=ip && ++OB && tabla[j]>=pos) {
      tabla[j+1]=tabla[j];
      j--;
    }
    tabla[j+1]=pos;
  }
  return OB;
}

int InsertSortInv(int* tabla, int ip, int iu)
{
  int i, j, pos, OB=0;
  if (tabla==NULL || ip<0 || iu<ip)
    return ERR;
  for (i=ip; i<=iu; i++) {
    pos=tabla[i];
    j=i-1;
    while (j>=ip && ++OB && tabla[j]<=pos) {
      tabla[j+1]=tabla[j];
      j--;
    }
    tabla[j+1]=pos;
  }
  return OB;
}
