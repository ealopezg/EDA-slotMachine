#include <stdio.h>
#include <string.h>
#include <stdlib.h>


char ** girarMaquina(char**matriz,int cantidadColumnas,int cantidadFilas){
	char**maquinaGirada = (char**)malloc(sizeof(char*)*(cantidadFilas+cantidadColumnas-1));
	for(int i=0;i<cantidadColumnas;i++){
		char*nuevaFila=(char*)malloc(sizeof(char)*cantidadFilas);
		maquinaGirada[i]=nuevaFila;
	}
	int l=0;
	int k=0;
	for(int i=cantidadColumnas-1;i>0;i--){
		for(int j=0;j<cantidadFilas;j++){
			maquinaGirada[l][k]=matriz[i][j];
			k++;
		}
		l++;
	}
	return maquinaGirada;

}





int main( int argc, const char* argv[] )
{

}


