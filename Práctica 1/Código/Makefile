#-----------------------
# IMPORTANTE: Los valores de los parametros de los ejercicio?_test deben ajustarse.
# Se asume que los ficheros fuente se llaman ejercicio1.c, ejercicio2.c,...,ordenar.h
#-----------------------

CC = gcc -ansi -pedantic
CFLAGS = -Wall
EXE = ejercicio1 ejercicio2 ejercicio3 ejercicio4 ejercicio5 ejercicio5_inv

all : $(EXE)

.PHONY : clean
clean :
	rm -f *.o core $(EXE)

$(EXE) : % : %.o ordenacion.o tiempos.o permutaciones.o
	@echo "#---------------------------"
	@echo "# Generando $@ "
	@echo "# Depende de $^"
	@echo "# Ha cambiado $<"
	$(CC) $(CFLAGS) -o $@ $@.o ordenacion.o tiempos.o permutaciones.o

permutaciones.o : permutaciones.c permutaciones.h
	@echo "#---------------------------"
	@echo "# Generando $@"
	@echo "# Depende de $^"
	@echo "# Ha cambiado $<"
	$(CC) $(CFLAGS) -c $<

 ordenacion.o : ordenacion.c ordenacion.h
	@echo "#---------------------------"
	@echo "# Generando $@"
	@echo "# Depende de $^"
	@echo "# Ha cambiado $<"
	$(CC) $(CFLAGS) -c $<

 tiempos.o : tiempos.c tiempos.h
	@echo "#---------------------------"
	@echo "# Generando $@"
	@echo "# Depende de $^"
	@echo "# Ha cambiado $<"
	$(CC) $(CFLAGS) -c $<

ejercicio1_test:
	@echo Ejecutando ejercicio1
	@./ejercicio1 -limInf 1 -limSup 5 -numN 100000

ejercicio2_test:
	@echo Ejecutando ejercicio2
	@./ejercicio2 -tamanio 5 -numP 10

ejercicio3_test:
	@echo Ejecutando ejercicio3
	@./ejercicio3 -tamanio 5 -numP 10

ejercicio4_test:
	@echo Ejecutando ejercicio4
	@./ejercicio4 -tamanio 100

ejercicio5_test:
	@echo Ejecutando ejercicio5
	@./ejercicio5 -num_min 1000 -num_max 2000 -incr 100 -numP 400 -fichSalida ejercicio5.log

ejercicio5_inv_test:
	@echo Ejecutando ejercicio5_inv
	@./ejercicio5_inv -num_min 1000 -num_max 2000 -incr 100 -numP 400 -fichSalida ejercicio5_inv.log
