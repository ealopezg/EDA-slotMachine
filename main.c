#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

/**
 * Definición de la Estructura
 * Par
 */
typedef struct par{
	char*texto;
	int nCaract;
	int numero;

}par;


/**
 * Funcion que devuelve el indice del
 * primer espacio ' ' que encuentre					
 * 
 * @param  entrada String de entrada	
 * @param  largo   Largo del string de
 *                 entrada
 * @return         Posición del primer
 *                 espacio
 */
int encontrarEspacio(char entrada[],int largo){
	for(int i=0;i<largo;i++){
		if(entrada[i]==' ' || entrada[i]=='\0'){
			return i;
		}
	}
	return -1;
}

/**
 * Función que devuelve un trozo de
 * un string
 * @param  entrada String de entrada
 * @param  inicio  Indice de inicio
 * @param  final   Indice de final
 * @param  largo   Entero, largo 
 *                 del string de entrada
 * @return         String
 */
char *subs(char entrada[],int inicio,int final,int largo){
	char *salida = (char*)malloc(sizeof(char)*(final-inicio));
	int j = 0;
	for(int i = 0;i<largo;i++){
		if(i>=inicio && i<final){
			salida[j]=entrada[i];
			j++;
			
		}

	}
	return salida;
}

/**
 * Funcion que lee el archivo de entrada
 * y devuelve un arreglo de caracteres
 * correspondientes a la maquina traga-
 * monedas
 * @param  nombreArchivo    String con el
 *                          nombre del 
 *                          archivo
 * @param  cantidadFilas    Puntero a Entero,
 *                          cantidad de filas
 * @param  cantidadColumnas Puntero a Entero,
 *                          cantidad de columnas
 * @return                  Arreglo de caracteres
 */
char *leerArchivo(char nombreArchivo[],int *cantidadFilas, int *cantidadColumnas){
  	char encabezado[]="00000000000000000000";
	FILE *punteroFile;

	if ((punteroFile = fopen(nombreArchivo,"r")) == NULL){
	   printf("Error! archivo no encontrado");

	   // Program exits if the file pointer returns NULL.
	   exit(1);
	}

	fgets(encabezado, 20, punteroFile );
	int indiceEspacio = encontrarEspacio(encabezado,20);
	if(indiceEspacio==-1){
		printf("Archivo invalido\n");
		exit(1);
	}
	char *filas = subs(encabezado,0,indiceEspacio,20);
	char *columnas = subs(encabezado,indiceEspacio,20,20);
	*cantidadFilas = atoi(filas);
	*cantidadColumnas = atoi(columnas);
	free(filas);
	free(columnas);

	char * salida = (char*)malloc(sizeof(char)*((*cantidadColumnas)*(*cantidadFilas)*2+(*cantidadColumnas)+1));
	char caracter;
	int j=0;
	while((caracter = fgetc(punteroFile)) != EOF){
		if(caracter!=' '){
			salida[j]=caracter;
			j++;
		}
	}
		
	fclose(punteroFile); 

	return salida;
}

/**
 * Función que lee el archivo secundario
 * y retorna un arreglo de Pares
 * @param  nombreArchivo  String con el
 *                        nombre del archivo
 * @param  cantidadLineas Puntero a Entero,
 *                        Cantidad de lineas
 * @param  tipoArchivo    Entero con el tipo de
 *                        archivo:
 *                        1: Bonus
 *                        2: Premios
 * @return                Arreglo de pares
 */	
par* leerArchivoSecundario(char nombreArchivo[],int*cantidadLineas,int tipoArchivo){
	FILE *punteroFile;

	if ((punteroFile = fopen(nombreArchivo,"r")) == NULL){
	   printf("Error! archivo bonus no encontrado");

	   // Program exits if the file pointer returns NULL.
	   exit(1);
	}
	char c;
	int maximoCaracteresLinea=0;
	int maximoCaracteresAux = 0;
	while ((c = fgetc(punteroFile))!=EOF){

		if(c=='\n'){
			
			*cantidadLineas=*cantidadLineas+1;
			if(maximoCaracteresAux>=maximoCaracteresLinea){
				maximoCaracteresLinea=maximoCaracteresAux;				
			}
			maximoCaracteresAux=0;
		}
		maximoCaracteresAux++;
	}
	*cantidadLineas=*cantidadLineas+1;
	maximoCaracteresLinea++;

	rewind(punteroFile);
	char ** salida = (char**)malloc(sizeof(char*)*(*cantidadLineas));
	for(int i=0;i<*cantidadLineas;i++){
		salida[i]=(char*)malloc(sizeof(char)*maximoCaracteresLinea);
		for(int j=0;j<maximoCaracteresLinea;j++){
			c = fgetc(punteroFile);
			if(c=='\n' || c==EOF){
				salida[i][j]='\0';
				j=maximoCaracteresLinea;
			}
			else{
				salida[i][j]=c;
			}
			
		}

	}
	fclose(punteroFile);
	par* listaSalida = (par*)malloc(sizeof(par)*(*cantidadLineas));
	
	for(int i=0;i<*cantidadLineas;i++){

		int nCaract1 = encontrarEspacio(salida[i],maximoCaracteresLinea);
		char* texto1 = subs(salida[i],0,nCaract1,maximoCaracteresLinea);
		texto1[nCaract1]='\0';
		char* texto2Aux = subs(salida[i],nCaract1+1,maximoCaracteresLinea,maximoCaracteresLinea);
		int nCaract2 = encontrarEspacio(texto2Aux,maximoCaracteresLinea);
		char* texto2 = subs(texto2Aux,0,nCaract2,maximoCaracteresLinea-(nCaract1+1));
		free(texto2Aux);
		texto2[nCaract2]='\0';
		if(tipoArchivo==1){
			listaSalida[i].texto=texto1;
			listaSalida[i].nCaract=nCaract1;
			listaSalida[i].numero=atoi(texto2);
		}
		else if(tipoArchivo==2){
			listaSalida[i].texto=texto2;
			listaSalida[i].nCaract=nCaract2;
			listaSalida[i].numero=atoi(texto1);

		}

	}
	free(salida);
	return listaSalida;
}


/**
 * Funcion que crea una columna a partir
 * @param  entrada          [description]
 * @param  cantidadColumnas [description]
 * @param  cantidadFilas    [description]
 * @param  comienzo         [description]
 * @return                  [description]
 */
char *crearColumna(char*entrada,int cantidadColumnas,int cantidadFilas,int comienzo){
	int largo = (cantidadColumnas)*(cantidadFilas)+(cantidadFilas);
	char*columna = (char*)malloc((cantidadFilas+1)*sizeof(char));
	int i = comienzo;
	int j = 0;
	int k = 0;
	while (i<largo)
	{

		columna[j]=entrada[i];
		i=i+cantidadColumnas+1;
		j++;
	}
	columna[j]='\0';


	
	return columna;
}


/**
 * Funcion Auxiliar que mueve el
 * rodillo un espacio
 * @param rodillo Arreglo de caracteres
 * @param largo   Largo del arreglo
 */
void moverRodilloAux(char*rodillo,int largo){
	char caracterAuxiliar=rodillo[largo-1];
	int k=0;
	for(int i=largo-1;i>0;i--){
		rodillo[i]=rodillo[i-1];
		k++;
	}
	rodillo[0]=caracterAuxiliar;
}

/**
 * Funcion que mueve el rodillo n veces
 * @param matriz         Matriz de caracteres
 * @param numeroRodillo  indice del rodillo
 * @param largoRodillo   largo del rodillo
 * @param desplazamiento Cantidad de veces 
 *                       que se desplaza
 */
void moverRodillo(char**matriz,int numeroRodillo,int largoRodillo,int desplazamiento){
	int veces = desplazamiento%largoRodillo;
	for(int i=desplazamiento;i>0;i--){
		moverRodilloAux(matriz[numeroRodillo],largoRodillo);
		
	}
}

/**
 * Funcion que genera el String de una fila
 * @param  matriz           Matriz de caracteres
 * @param  numeroFila       cantidad de filas
 * @param  cantidadColumnas cantidad de columnas
 * @return                  String
 */
char *generarStringFila(char**matriz,int numeroFila,int cantidadColumnas){
	char *salida=(char*)malloc(sizeof(char)*(cantidadColumnas+1));
	for(int i=0;i<cantidadColumnas;i++){
		salida[i]=matriz[i][numeroFila];
	}
	salida[cantidadColumnas]='\0';
	return salida;
}

/**
 * Funcion que comprueba que cada caracter de un string
 * sea igual al ingresado
 * @param  substring String
 * @param  caracter  Caracter a comparar
 * @param  largo     Largo de String
 * @return           1 si es verdadero, 0 si es falso
 */
int compararStringsConCaracter(char*substring,char caracter,int largo){
	for(int i=0;i<largo;i++){
		if(substring[i]!=caracter){
			return 0;
		}
	}
	return 1;
}

/**
 * Funcion que devuelve el puntaje obtenido
 * al buscar las combinaciones de forma 
 * horizontal
 * @param  stringFila String
 * @param  largoFila  Largo de String
 * @return            Puntaje correspondiente;
 */	
int puntajesCombinacion(char*stringFila,int largoFila){
	int puntaje = 0;
	int cantidadDeCombinaciones=(int)floor(largoFila/3);
	int *combinaciones=(int*)malloc(sizeof(int)*cantidadDeCombinaciones);
	int k = 0;
	for(int i=0;i<largoFila;i++){
		for(int j=largoFila-1;j>i+1;j--){
			if(compararStringsConCaracter(subs(stringFila,i,j+1,largoFila),stringFila[i],j-i+1)){
					combinaciones[k]=j-i+1;
					k++;
					i=j;
					j=largoFila-1;
				}

			}
	}

	for(int f=0;f<k;f++){
		if(combinaciones[f]>=3){
			puntaje = puntaje + 50*pow(combinaciones[f],1.5);
		}
		
	}
	free(combinaciones);
	return puntaje;

}

/**
 * Funcion que devuelve el puntaje total
 * obtenido de una matriz de caracteres
 * al revisar de forma horizontal
 * @param  matriz           Matriz de
 *                          caracteres
 * @param  cantidadColumnas Cantidad Columnas
 * @param  cantidadFilas    CantidadFilas
 * @return                  Puntaje final obtenido
 *                          dentro de una matriz 
 *                          de caracteres
 */
int buscarPuntaje(char**matriz,int cantidadColumnas,int cantidadFilas){
	int puntaje = 0,puntajeAux = 0;
	char*string;
	for(int i =0; i<cantidadFilas;i++){
		string=generarStringFila(matriz,i,cantidadColumnas);
		puntajeAux = puntajesCombinacion(string,cantidadColumnas);
		puntaje=puntaje+puntajeAux;
	}
	return puntaje;


}

/**
 * Funcion que imprime por pantalla la máquina
 * @param matriz           Matriz de caracteres
 * @param cantidadColumnas Cantidad de Columnas
 * @param cantidadFilas    Cantidad Filas
 */
void imprimirMaquina(char**matriz,int cantidadColumnas,int cantidadFilas){
	for(int j=0;j<cantidadFilas;j++){
		for(int i=0;i<cantidadColumnas;i++){
			printf("%c ",matriz[i][j]);
		}
		printf("\n");
	}
}

/**
 * Esta función devuelve una nueva matriz correspondiente a todas las
 * diagonales encontradas en la matriz de entrada de izquierda a derecha
 * y de arriba hacia abajo, NO DEVUELVE LAS DIAGONALES DE DERECHA A 
 * IZQUIERDA Y DE ARRIBA A ABAJO
 * @param  matriz           Matriz de caracteres
 * @param  cantidadColumnas Cantidad de columnas
 * @param  cantidadFilas    cantidad de Filas
 * @return                  [description]
 */
char ** devolverDiagonales(char**matriz,int cantidadColumnas,int cantidadFilas){
	char**salida=(char**)malloc(sizeof(char*)*(cantidadColumnas+cantidadFilas-1));
	int k=0;
	for(int i=cantidadColumnas-1;i>0;i--){
		int h=0;
		int j=0;
		salida[k]=(char*)malloc(sizeof(char)*(cantidadFilas+1));
		int f=i;
		while(cantidadColumnas>f){
			salida[k][h]=matriz[f][j];
			j++;
			f++;
			h++;
		}
		while(h<cantidadFilas){
			salida[k][h]=' ';
			h++;
		}
		salida[k][h]='\0';
		k++;
	}
	for(int i=0;i<cantidadFilas;i++){
		int j=0;
		salida[k]=(char*)malloc(sizeof(char)*(cantidadFilas+1));
		int h=0;
		int f=i;
		while(cantidadFilas>f){

			salida[k][h]=matriz[j][f];
			j++;
			f++;
			h++;
		}
		while(h<cantidadFilas){
			salida[k][h]=' ';
			h++;
		}
		salida[k][h]='\0';
		k++;
	
	}
	return salida;
}



/**
 * Esta función devuelve todos los puntajes de todas las
 * combinaciones posibles que se encuentran en las diagonales
 * de una matriz
 * 
 * @param  matrizDiagonales  Entero 
 * @param  largoLista       [description]
 * @param  largoStr         Largo 
 * @return                  [description]
 */
int puntajeDiagonales(char**matrizDiagonales,int largoLista,int largoStr){
	int puntaje = 0;
	for(int i = 0;i<largoLista;i++){
		puntaje = puntaje + puntajesCombinacion(matrizDiagonales[i],largoStr);
	}
	return puntaje;
}

/**
 * Funcion que imprime las veces que giró
 * el rodillo por ṕantalla
 * @param giros            Lista de numeros
 * @param cantidadColumnas Cantidad de rodillos/columnas
 */
void imprimirGiros(int*giros,int cantidadColumnas){
	for(int i=0;i<cantidadColumnas;i++){
			printf("El rodillo %d giró %d veces\n",i+1,giros[i]);		
	}
}

/**
 * Funcion que anula una matriz de
 * caracteres
 * @param matriz           Matriz de caracteres
 * @param cantidadColumnas Cantidad de rodillos/columnas
 */
void anularMatriz(char**matriz,int cantidadColumnas){
	for(int i=0;i<cantidadColumnas;i++){
		free(matriz[i]);
	}
	free(matriz);
}

/**
 * Funcion que anula una lista de pares
 * @param listaPar      Lista de pares
 * @param cantidadPares Cantidad de pares
 */		
void anularListaPares(par*listaPar,int cantidadPares){
	for(int i=0;i<cantidadPares;i++){
		free(listaPar[i].texto);
	}
	free(listaPar);
}

/**
 * Funcion que crea una matriz de caracteres
 * en base a un string
 * @param  entrada          String de entrada
 * @param  cantidadFilas    Cantidad de 
 *                          Filas
 * @param  cantidadColumnas Cantidad de
 *                          columnas
 * @return                 	Matriz de caractees
 */
char** crearMatriz(char*entrada,int cantidadFilas,int cantidadColumnas){
	char**matriz =(char**)malloc(sizeof(char*)*cantidadColumnas);
	for(int i=0;i<cantidadColumnas;i++){
		matriz[i]=crearColumna(entrada,cantidadColumnas,cantidadFilas,i);
	}
	return matriz;

}

/**
 * Funcion que desplaza las columnas/rodillos de una
 * matriz independientemente, devuelve un arreglo de
 * enteros.			
 * @param  matriz           Matriz de caracteres
 * @param  cantidadFilas    Cantidad de Filas
 * @param  cantidadColumnas Cantidad de Columnas
 * @return                  Arreglo de enteros
 */
int* desplazarRodillos(char**matriz,int cantidadFilas,int cantidadColumnas){
	int*giros =(int*)malloc(sizeof(int)*cantidadColumnas);
	for(int i=0;i<cantidadColumnas;i++){
	  	int desplazamientos = rand()%20;
	   	moverRodillo(matriz,i,cantidadFilas,desplazamientos);
	   	giros[i]=desplazamientos;
	 }
	 return giros;
}



/**
 * Devuelve la cantidad de dinero ganado por
 * los bonus encontrados en una matriz de 
 * caracteres
 * @param  matriz                   Matriz de caracteres
 * @param  cantidadFilas            Cantidad de Filas
 * @param  cantidadColumnas         Cantidad de Columnas
 * @param  listaBonus               Lista Par correspondiente
 *                                  a los bonus
 * @param  cantidadBonus            [description]
 * @param  cantidadBonusEncontrados Puntero a entero,
 *                                  veces que ha sido encontrado
 *                                  un bonus
 * @return                          Dinero obtenido
 */
int dineroBonus(char**matriz,int cantidadFilas,int cantidadColumnas,par*listaBonus,int cantidadBonus,int*cantidadBonusEncontrados){
	int l=0;
	int salida=0;
	for(int i=0;i<cantidadFilas;i++){
		char*stringFila=generarStringFila(matriz,i,cantidadColumnas);
		for(int j=0;j<cantidadBonus;j++){
			if(strstr(stringFila,listaBonus[j].texto) != NULL){
				salida = salida+listaBonus[j].numero;
				*cantidadBonusEncontrados=*cantidadBonusEncontrados+1;
			}
		}
		free(stringFila);
	}
	return salida;
}


// ALGORITMO QUICKSORT
// EXTRAIDO DE LA PAGINA
// https://www.e-urrea.com/noticias/2011/03/23/metodo-de-ordenacion-burbuja-y-quicksort-en-c/
// Y modificada para ordenar pares
int pivot(par *unarray, int izq, int der)
{
    int i;
    int pivote, valor_pivote;
    par aux;
    pivote = izq;
    valor_pivote = unarray[pivote].numero;
    for (i=izq+1; i<=der; i++){
        if (unarray[i].numero < valor_pivote){
                pivote++;
                aux=unarray[i];
                unarray[i]=unarray[pivote];
                unarray[pivote]=aux;

        }
    }
    aux=unarray[izq];
    unarray[izq]=unarray[pivote];
    unarray[pivote]=aux;
    return pivote;
}

void Quicksort(par *unarray, int izq, int der)
{
     int pivote;
     if(izq < der){
        pivote=pivot(unarray, izq, der);
        Quicksort(unarray, izq, pivote-1);
        Quicksort(unarray, pivote+1, der);
     }
}


/**
 * Funcion que devuelve el premio ganado
 * segun el puntaje obtenido
 * @param  puntaje         Entero
 * @param  listaPremios    Lista de Pares premios
 * @param  cantidadPremios Cantidad de Premios
 * @param  largoPremio     Puntero a entero, largo
 *                         del premio ganado
 * @return                 String
 */
char* obtenerPremio(int puntaje,par*listaPremios,int cantidadPremios,int* largoPremio){
	for(int i=0;i<cantidadPremios-1;i++){
		if(puntaje>=listaPremios[i].numero && puntaje<listaPremios[i+1].numero){
			*largoPremio=listaPremios[i].nCaract;
			return listaPremios[i].texto;
		}
	}
	if(puntaje>=listaPremios[cantidadPremios-1].numero){
		*largoPremio=listaPremios[cantidadPremios-1].nCaract;
		return listaPremios[cantidadPremios-1].texto;
	}
	*largoPremio=strlen("Nada");
	char*string="Nada";
	return string;
}


/**
 * Funcion que cuenta cuantos 
 * digitos tiene un entero
 * @param  entero Entero
 * @return        Entero
 */
int cantidadCaracteresEntero(int entero){
	int salida = 0;
	if(entero==0){
		return 1;
	}
	while(entero!=0){
		entero=entero/10;
		salida++;
	}
	return salida;
}


/**
 * Funcion que escribe el archivo de salida,
 * llamado resultados.out, con el puntaje obtenido,
 * el premio ganado, la cantidad de bonus encontrados
 * y el dinero por el bonus
 * @param puntajeObtenido          Entero
 * @param premio                   String
 * @param largoPremio              Largo del String
 * @param cantidadBonusEncontrados Entero
 * @param dineroPorBonus           Entero
 */
void guardarArchivoSalida(int puntajeObtenido,char*premio,int largoPremio,int cantidadBonusEncontrados,int dineroPorBonus){
	int largoPuntaje =cantidadCaracteresEntero(puntajeObtenido);
	int largoCantidadBonusEncontrados =  cantidadCaracteresEntero(cantidadBonusEncontrados);
	int largoDineroPorBonus = cantidadCaracteresEntero(dineroPorBonus);
	int largoTotalString = 67 + largoPuntaje+largoPremio+largoCantidadBonusEncontrados+largoDineroPorBonus+1;
	char*stringSalida =(char*)malloc(sizeof(char)*largoTotalString);
	sprintf(stringSalida,"Puntaje obtenido: %d\nPremio: %s\nBonus encontrados: %d\nDinero por Bonus: %d\n\0",puntajeObtenido,premio,cantidadBonusEncontrados,dineroPorBonus);
	printf("%s\n",stringSalida);

	FILE *punteroFile = fopen("resultados.out", "w");
	if (punteroFile == NULL)
	{
	    printf("Error opening file!\n");
	    exit(1);
	}
	fprintf(punteroFile, "%s",stringSalida);
	free(stringSalida);
	fclose(punteroFile);
}




void run(int semilla){
	//srand(time(NULL));
	srand(semilla);
	int cantidadColumnas = 0;
	int cantidadFilas = 0;
	int cantidadBonus = 0;
	int cantidadPremios = 0;
	int cantidadBonusEncontrados = 0;
	int largoPremio = 0;

	//ABRIENDO ARCHIVO  MAQUINA
	char *entrada = leerArchivo("maquina.in",&cantidadFilas,&cantidadColumnas);

	//ABRIENDO ARCHIVOS SECUNDARIOS
	par * listaBonus = leerArchivoSecundario("bonus.in",&cantidadBonus,1);
	par * listaPremios = leerArchivoSecundario("premios.in",&cantidadPremios,2);

	//ORDENANDO DE MENOR A MAYOR LA LISTA DE LOS PREMIOS
	Quicksort(listaPremios,0,cantidadPremios-1);

	//CREANDO MATRIZ
	char**matriz = crearMatriz(entrada,cantidadFilas,cantidadColumnas);

	//DESPLAZANDO RODILLOS
	int *giros = desplazarRodillos(matriz,cantidadFilas,cantidadColumnas);

	//CREANDO MATRIZ DE DIAGONALES
	char**matrizDiagonales=devolverDiagonales(matriz,cantidadColumnas,cantidadFilas);


	//MOSTRANDO MAQUINA Y GIROS
	printf("Columnas: %d - Filas: %d\n",cantidadColumnas,cantidadFilas);		  
	imprimirMaquina(matriz,cantidadColumnas,cantidadFilas);
	printf("\n");
	imprimirGiros(giros,cantidadColumnas);
	
	
	//BUSCANDO EL PUNTAJE
	int puntaje=buscarPuntaje(matriz,cantidadColumnas,cantidadFilas); + puntajeDiagonales(matrizDiagonales,(cantidadColumnas+cantidadFilas-1),cantidadFilas);

	//BUSCANDO DINERO DE BONUS
	int db = dineroBonus(matriz,cantidadFilas,cantidadColumnas,listaBonus,cantidadBonus,&cantidadBonusEncontrados) + dineroBonus(matrizDiagonales,cantidadFilas,(cantidadColumnas+cantidadFilas-1),listaBonus,cantidadBonus,&cantidadBonusEncontrados);


	//BUSCANDO EL PREMIO
	char*premio = obtenerPremio(puntaje,listaPremios,cantidadPremios,&largoPremio);

	printf("\n----RESULTADOS----\n");
	//GUARDANDO EL ARCHIVO
	guardarArchivoSalida(puntaje,premio,largoPremio,cantidadBonusEncontrados,db);

	//LIMPIANDO MEMORIA
	free(listaPremios);
	free(listaBonus);
	anularMatriz(matriz,cantidadColumnas);
	anularMatriz(matrizDiagonales,cantidadColumnas+cantidadFilas-1);
	anularListaPares(listaPremios,cantidadPremios);
	anularListaPares(listaBonus,cantidadBonus);
	free(giros);
	//free(premio);
	free(entrada);
	
}


int main( int argc, const char* argv[] )
{
	int semilla = 2018;
	run(semilla);
}

