/**
 *
 * Descripcion: Funciones de cabecera para ordenacion
 *
 * Fichero: ordenacion.h
 * Autor: Carlos Aguirre
 * Version: 1.0
 * Fecha: 16-09-2019
 *
 */

#ifndef ORDENACION_H
#define ORDENACION_H

/* constantes */

#ifndef ERR
#define ERR -1
#define OK (!(ERR))
#endif

/* definiciones de tipos */
typedef int (* pfunc_ordena)(int*, int, int);

/* Funciones */

int InsertSort(int* tabla, int ip, int iu);
int InsertSortInv(int* tabla, int ip, int iu);


#endif
