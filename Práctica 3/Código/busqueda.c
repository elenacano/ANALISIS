/**
 *
 * Descripcion: Implementacion funciones para busqueda
 *
 * Fichero: busqueda.c
 * Autor: Carlos Aguirre
 * Version: 1.0
 * Fecha: 11-11-2016
 *
 */

#include "busqueda.h"

#include <stdlib.h>
#include <math.h>

/**
 *  Funciones de geracion de claves
 *
 *  Descripcion: Recibe el numero de claves que hay que generar
 *               en el parametro n_claves. Las claves generadas
 *               iran de 1 a max. Las claves se devuelven en
 *               el parametro claves que se debe reservar externamente
 *               a la funcion.
 */

/**
 *  Funcion: generador_claves_uniforme
 *               Esta fucnion genera todas las claves de 1 a max de forma
 *               secuencial. Si n_claves==max entonces se generan cada clave
 *               una unica vez.
 */
void generador_claves_uniforme(int *claves, int n_claves, int max)
{
  int i;

  for(i = 0; i < n_claves; i++) claves[i] = 1 + (i % max);

  return;
}

/**
 *  Funcion: generador_claves_potencial
 *               Esta funcion genera siguiendo una distribucion aproximadamente
 *               potencial. Siendo los valores mas pequenos mucho mas probables
 *               que los mas grandes. El valor 1 tiene una probabilidad del 50%,
 *               el dos del 17%, el tres el 9%, etc.
 */
void generador_claves_potencial(int *claves, int n_claves, int max)
{
  int i;

  for(i = 0; i < n_claves; i++) {
    claves[i] = .5+max/(1 + max*((double)rand()/(RAND_MAX)));
  }

  return;
}

PDICC ini_diccionario (int tamanio, char orden)
{
  PDICC pdicc=NULL;
  if(tamanio<0 || (orden!=ORDENADO && orden!=NO_ORDENADO)){
    return NULL;
  }
    pdicc=malloc(sizeof(PDICC));
    if(pdicc==NULL)
      return NULL;

    pdicc->tabla=malloc(tamanio*sizeof(int));
    if (pdicc->tabla==NULL){
      free(pdicc);
      return NULL;
    }
    pdicc->tamanio=tamanio;
    pdicc->n_datos=0;
    pdicc->orden=orden;

    return pdicc;
}

void libera_diccionario(PDICC pdicc)
{
  if (pdicc!=NULL) {
    if (pdicc->tabla!=NULL)
      free(pdicc->tabla);
    free(pdicc);
  }
  return;
}

int inserta_diccionario(PDICC pdicc, int clave)
{
  int i, OBS=0;

  if(pdicc==NULL)
    return ERR;
  if (pdicc->n_datos>=pdicc->tamanio)
    return ERR;

  pdicc->tabla[pdicc->n_datos]=clave;

  if (pdicc->orden==ORDENADO) {
    i=pdicc->n_datos-1;
    while (i>=0 && ++OBS && pdicc->tabla[i]>=clave) {
      pdicc->tabla[i+1]=pdicc->tabla[i];
      i--;
    }
    pdicc->tabla[i+1]=clave;
  }
  pdicc->n_datos++;

  return OBS;
}

int insercion_masiva_diccionario (PDICC pdicc, int *claves, int n_claves)
{
  int i, flag, OBS=0;
  if (pdicc==NULL || claves==NULL || n_claves<0)
    return ERR;
  for (i=0; i<n_claves; i++)
  {
    flag=inserta_diccionario(pdicc, claves[i]);
    if (flag==ERR)
      return ERR;
    OBS+=flag;
  }
  return OK;
}

int busca_diccionario(PDICC pdicc, int clave, int *ppos, pfunc_busqueda metodo)
{
  int OBS=0;

  if (pdicc==NULL || ppos==NULL || metodo==NULL)
    return ERR;
  OBS=metodo(pdicc->tabla, 0, pdicc->n_datos-1, clave, ppos);
  if (OBS==ERR)
    return ERR;
  return OBS;
}


/* Funciones de busqueda del TAD Diccionario */
int bbin(int *tabla, int P, int U, int clave, int *ppos)
{
  int medio, OBS=0;

	if (tabla==NULL || P>U)
    return ERR;

  while(P<=U) {
    medio=(P+U)/2;
    OBS++;
    if (tabla[medio]==clave){
      *ppos=medio;
      return OBS;
    }
    else if (clave<tabla[medio]) {
      U=medio-1;
    }
    else if (clave>tabla[medio]) {
      P=medio+1;
    }
  }

  *ppos=NO_ENCONTRADO;
  return OBS;
}

int blin(int *tabla, int P, int U, int clave, int *ppos)
{
  int OBS=0, i;
  if (tabla==NULL || P<0 || U<P || ppos==NULL)
    return ERR;
  for (i=P; i<=U; i++) {
    OBS++;
    if (tabla[i]==clave) {
      (*ppos)=i;
      return OBS;
    }
  }
  (*ppos)=NO_ENCONTRADO;
  return OBS;
}

int blin_auto(int *tabla,int P,int U,int clave,int *ppos)
{
  int OBS=0, i, aux;
  if (tabla==NULL || P<0 || U<P || ppos==NULL)
    return ERR;
  for (i=P; i<=U; i++) {
    OBS++;
    if (tabla[i]==clave) {
      (*ppos)=i;
      if (i!=0) {
        aux=tabla[i-1];
        tabla[i-1]=tabla[i];
        tabla[i]=aux;
      }
      return OBS;
    }
  }
  (*ppos)=NO_ENCONTRADO;
  return OBS;
}
