/**
 *
 * Descripcion: Implementacion de funciones de tiempo
 *
 * Fichero: tiempos.c
 * Autor: Carlos Aguirre Maeso
 * Version: 1.0
 * Fecha: 16-09-2017
 *
 */
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <limits.h>
#include "tiempos.h"
#include "ordenacion.h"

/***************************************************/
/* Funcion: tiempo_medio_ordenacion Fecha:         */
/*                                                 */
/* Vuestra documentacion (formato igual            */
/* que en el primer apartado):                     */
/***************************************************/
short tiempo_medio_ordenacion(pfunc_ordena metodo, int n_perms, int N, PTIEMPO ptiempo) {
  int** tablas=NULL;
  int OB=0, OBTOTAL=0, j=0;
  double t1, t2;
  if (metodo==NULL || n_perms<1 || N<1 || ptiempo==NULL)
    return ERR;
  ptiempo->N=N;
  ptiempo->n_elems=n_perms;
  tablas=genera_permutaciones(n_perms, N);
  if (tablas==NULL)
    return ERR;
  t1=clock();
  if (t1==-1) {
    for (j=0; j<n_perms; j++) {
      free(tablas[j]);
      tablas[j]=NULL;
      break;
    }
    free(tablas);
    return ERR;
  }
  for (j=0; j<n_perms; j++) {
    OB=metodo(tablas[j], 0, N-1);
    if (OB==ERR) {
      for (j=0; j<n_perms; j++) {
        free(tablas[j]);
        tablas[j]=NULL;
        break;
      }
      free(tablas);
      return ERR;
    }
    if (j==0) {
      ptiempo->min_ob=OB;
      ptiempo->max_ob=OB;
    }
    if (OB<ptiempo->min_ob)
      ptiempo->min_ob=OB;
    else if (OB>ptiempo->max_ob)
      ptiempo->max_ob=OB;
    OBTOTAL+=OB;
  }
  t2=clock();
  if (t2==-1) {
    for (j=0; j<n_perms; j++) {
      free(tablas[j]);
      tablas[j]=NULL;
      break;
    }
    free(tablas);
    return ERR;
  }
  ptiempo->tiempo=((t2-t1)/n_perms);
  ptiempo->medio_ob=((double)OBTOTAL)/n_perms;
  for (j=0; j<n_perms; j++) {
    free(tablas[j]);
  }
  free(tablas);
  return OK;
}

/***************************************************/
/* Funcion: genera_tiempos_ordenacion Fecha:       */
/*                                                 */
/* Vuestra documentacion                           */
/***************************************************/
short genera_tiempos_ordenacion(pfunc_ordena metodo, char* fichero, int num_min, int num_max, int incr, int n_perms) {
  PTIEMPO tiempos=NULL;
  int j, counter=0;
  if (metodo==NULL || fichero==NULL || num_min<0 || num_max<num_min || incr<1)
    return ERR;
  tiempos=malloc((((num_max-num_min)/incr)+1)*sizeof(TIEMPO));
  if (tiempos==NULL)
    return ERR;
  for(j=num_min; j<=num_max; j+=incr, counter++) {
    if (tiempo_medio_ordenacion(metodo, n_perms, j, &tiempos[counter])==ERR) {
      free(tiempos);
      return ERR;
    }
  }
  if(guarda_tabla_tiempos(fichero, tiempos, counter)==ERR) {
    free(tiempos);
    return ERR;
  }
  free(tiempos);
  return OK;
}

/***************************************************/
/* Funcion: guarda_tabla_tiempos Fecha:            */
/*                                                 */
/* Vuestra documentacion (formato igual            */
/* que en el primer apartado):                     */
/***************************************************/
short guarda_tabla_tiempos(char* fichero, PTIEMPO tiempo, int n_tiempos)
{
  FILE *f=NULL;
  int i;
  if (fichero==NULL || tiempo==NULL || n_tiempos<1)
    return ERR;

  f=fopen(fichero, "w");
  if (f==NULL)
    return ERR;
  for (i=0; i<n_tiempos; i++) {
    if (fprintf(f, "%d %f %f %d %d", tiempo[i].N, tiempo[i].tiempo, tiempo[i].medio_ob, tiempo[i].min_ob, tiempo[i].max_ob)<0) {
      fclose(f);
      return ERR;
    }
    if (fprintf(f, "\n")<0) {
      fclose(f);
      return ERR;
    }
  }
  fclose(f);
  return OK;
}

/***************************************************/
/* Funcion: tiempo_medio_busqueda Fecha:           */
/*                                                 */
/* Vuestra documentacion                           */
/***************************************************/
short tiempo_medio_busqueda(pfunc_busqueda metodo, pfunc_generador_claves generador, int orden, int N, int n_veces, PTIEMPO ptiempo) {
  PDICC pdicc;
  int *claves=NULL;
  int *perm=NULL;
  int pos, obs_sol, j;
  double t1, t2;


  pdicc=ini_diccionario(N,orden);
  if (pdicc==NULL)
    return ERR;

  perm=genera_perm(N);
  if (perm==NULL) {
    libera_diccionario(pdicc);
    return ERR;
  }

  if(insercion_masiva_diccionario(pdicc,perm,N)==ERR) {
    libera_diccionario(pdicc);
    free(perm);
    return ERR;
  }

  claves=malloc(N*n_veces*sizeof(int));
  if (claves==NULL) {
    libera_diccionario(pdicc);
    free(perm);
    return ERR;
  }

  generador(claves, (N*n_veces), N); /*o exponencial dependiendo del algoritmo de ordenacion q usemos*/

  t1=clock();
  if (t1==-1) {
    libera_diccionario(pdicc);
    free(perm);
    free(claves);
    return ERR;
  }

  ptiempo->N=N;
  ptiempo->n_elems=N*n_veces;
  ptiempo->tiempo=0;
  ptiempo->medio_ob=0;
  ptiempo->min_ob=INT_MAX;
  ptiempo->max_ob=-1;

  for(j=0;j<=N*n_veces;j++) {
    obs_sol=busca_diccionario(pdicc, claves[j],&pos,metodo);
    if (obs_sol==ERR){
      libera_diccionario(pdicc);
      free(perm);
      free(claves);
      return ERR;
    }
    if (obs_sol<ptiempo->min_ob)
      ptiempo->min_ob=obs_sol;
    if (obs_sol>ptiempo->max_ob)
      ptiempo->max_ob=obs_sol;
    ptiempo->medio_ob+=((double)obs_sol/(n_veces*N));
  }

  t2=clock();
  if (t2==-1) {
    libera_diccionario(pdicc);
    free(perm);
    free(claves);
    return ERR;
  }

  ptiempo->tiempo=((double)(t2-t1)/(n_veces*N));


  libera_diccionario(pdicc);
  free(perm);
  free(claves);

  return OK;
}

/***************************************************/
/* Funcion: genera_tiempos_busqueada Fecha:        */
/*                                                 */
/* Vuestra documentacion                           */
/***************************************************/
short genera_tiempos_busqueda(pfunc_busqueda metodo, pfunc_generador_claves generador, int orden, char* fichero, int num_min, int num_max, int incr, int n_veces) {
  PTIEMPO tiempos=NULL;
  int i, counter=0;
  if (metodo==NULL || generador==NULL || fichero==NULL || num_min<0 || num_max<num_min || incr<1)
    return ERR;
  tiempos=malloc((((num_max-num_min)/incr)+1)*sizeof(TIEMPO));
  if (tiempos==NULL)
    return ERR;
  for(i=num_min; i<=num_max; i+=incr, counter++) {
    if (tiempo_medio_busqueda(metodo, generador, orden, i, n_veces, &tiempos[counter])==ERR) {
      free(tiempos);
      return ERR;
    }
  }
  if(guarda_tabla_tiempos(fichero, tiempos, counter)==ERR) {
    free(tiempos);
    return ERR;
  }
  free(tiempos);
  return OK;
}
