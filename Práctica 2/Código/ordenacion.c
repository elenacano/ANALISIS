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
/* Funcion: InserttSort    Fecha:                  */
/* Algoritmo de ordenacion InsertSort              */
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

/***************************************************/
/* Funcion: MergeSort    Fecha:                    */
/* Algoritmo de ordenacion MergeSort               */
/***************************************************/

int merge(int* tabla, int ip, int iu, int im) {
  int OBS=0;
  int i, j, k;
  int* tablaAux=NULL;

  if (tabla==NULL || ip>iu)
    return ERR;
  tablaAux=malloc((iu-ip+1)*sizeof(int));
  if (tablaAux==NULL)
    return ERR;
  i=ip;
  j=im+1;
  k=0;

  while(i<=im && j<=iu) {
    if (tabla[i]<tabla[j]) {
      tablaAux[k]=tabla[i];
      i++;
    }
    else {
      tablaAux[k]=tabla[j];
      j++;
    }
    k++;
    OBS++;
  }

  if (i>im) {
    while (j<=iu) {
      tablaAux[k]=tabla[j];
      j++;
      k++;
    }
  }
  else if (j>iu) {
    while (i<=im) {
      tablaAux[k]=tabla[i];
      i++;
      k++;
    }
  }
  for(i=ip; i<=iu; i++) {
    tabla[i]=tablaAux[i-ip];
  }
  free(tablaAux);
  return OBS;
}

int MergeSort(int* tabla, int ip, int iu) {
  int im, flag, OBS=0;
  if (tabla==NULL || ip>iu)
    return ERR;
  if (ip==iu)
    return OBS;
  im=(ip+iu)/2;
  flag=MergeSort(tabla, ip, im);
  if (flag==ERR)
    return ERR;
  OBS+=flag;
  flag=MergeSort(tabla, im+1, iu);
  if (flag==ERR)
    return ERR;
  OBS+=flag;
  flag=merge(tabla, ip, iu, im);
  if (flag==ERR)
    return ERR;
  OBS+=flag;
  return OBS;
}

/***************************************************/
/* Funcion: QuickSort    Fecha:                    */
/* Algoritmo de ordenacion QuickSort               */
/***************************************************/

int medio(int* tabla, int ip, int iu, int* pos) {
  int OBS=0;
  if (tabla==NULL || ip<0 || ip>iu || !pos)
    return ERR;
  (*pos)=ip;
  return OBS;
}

int medio_avg(int* tabla, int ip, int iu, int* pos) {
  int OBS=0;
  if (tabla==NULL || ip<0 || ip>iu || !pos)
    return ERR;
  (*pos)=(ip+iu)/2;
  return OBS;
}

int medio_stat(int* tabla, int ip, int iu, int* pos) {
  int avg, im, OBS=0;
  if (tabla==NULL || ip<0 || ip>iu || !pos)
    return ERR;
  im=(ip+iu)/2;
  avg=tabla[im];
  if ((tabla[im]>tabla[ip] && tabla[im]<tabla[iu]) || (tabla[im]>tabla[iu] && tabla[im]<tabla[ip]))
    (*pos)=im;
  else if ((tabla[ip]>avg && tabla[ip]<tabla[iu]) || (tabla[ip]>tabla[iu] && tabla[ip]<avg))
    (*pos)=ip;
  else
    (*pos)=iu;
  return OBS;
}

int partir(int* tabla, int ip, int iu, int* pos) {
  int OBS=0;
  int i, aux, swap;
  if (tabla==NULL || ip<0 || ip>iu || !pos)
    return ERR;
  OBS=medio_stat(tabla, ip, iu, pos);
  if (OBS==ERR)
    return ERR;
  aux=tabla[*pos];
  tabla[*pos]=tabla[ip];
  tabla[ip]=aux;
  *pos=ip;
  for (i=ip+1; i<=iu; i++) {
    if (tabla[i]<aux) {
      (*pos)++;
      swap=tabla[i];
      tabla[i]=tabla[*pos];
      tabla[*pos]=swap;
    }
    OBS++;
  }
  swap=tabla[ip];
  tabla[ip]=tabla[*pos];
  tabla[*pos]=swap;
  return OBS;
}

int QuickSort(int* tabla, int ip, int iu) {
  int im, flag, OBS=0;
  if (tabla==NULL || ip<0 || ip>iu)
    return ERR;
  if (ip==iu)
    return OBS;
  else {
    flag=partir(tabla, ip, iu, &im);
    if (flag==ERR)
      return ERR;
    OBS+=flag;
    if (ip<im-1) {
      flag=QuickSort(tabla, ip, im-1);
      if (flag==ERR)
        return ERR;
      OBS+=flag;
    }
    if (im+1<iu) {
      flag=QuickSort(tabla, im+1, iu);
      if (flag==ERR)
        return ERR;
      OBS+=flag;
    }
  }
  return OBS;
}
