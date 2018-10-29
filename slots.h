#include <stdio.h>
#include <stdlib.h>


char *abrirArchivo(char nombreArchivo[],int n){
  	char *salida = (char*)malloc(sizeof(n));
	FILE *punteroFile;

	if ((punteroFile = fopen(nombreArchivo,"r")) == NULL){
	   printf("Error! archivo no encontrado");

	   // Program exits if the file pointer returns NULL.
	   exit(1);
	}

	fgets( salida, n, punteroFile );
	fclose(punteroFile); 

	return salida;
}



char **generarColumnas(char entrada[]){
 	if(entrada==NULL){
 		return NULL;
 	}
 	else{
 		if

 	}
 }





void run(int semilla){
	char *entrada = abrirArchivo("maquina.in",20);
// 	int filas = numeroFilas(entrada);
// 	int columnas = numeroColumnas(entrada);
// 	char entrada2[] = limpiarEntrada(entrada);
	printf("%s",entrada);



}

// char createMatrix(char[] entrada,int m,int n){
// 	char 
// }


