#para ejecutar este makefile ingrese en terminal
#make programa
#programa: main 
#		gcc main.c LectorArchivos.c listaData.c readdir.c Recorredor.c -o a.out
main: main.c LectorArchivos.c listaData.c Recorredor.c
	gcc -g -o rastreo main.c LectorArchivos.c listaData.c Recorredor.c