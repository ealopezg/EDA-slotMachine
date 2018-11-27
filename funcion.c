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
	//printf("TOTAL LINEAS: %d\n",*cantidadLineas);
	rewind(punteroFile);
	char ** salida = (char**)malloc(sizeof(char*)*(*cantidadLineas));
	//printf("HOLAAAAAA\n");
	for(int i=0;i<*cantidadLineas;i++){
		salida[i]=(char*)malloc(sizeof(char)*maximoCaracteresLinea);
		for(int j=0;j<maximoCaracteresLinea;j++){
			c = fgetc(punteroFile);
			//printf("%d\n",c);

			if(c=='\n' || c==EOF){
				salida[i][j]='\0';
				j=maximoCaracteresLinea;
			}
			else{
				salida[i][j]=c;
			}
			
		}

	}
	printf("HOLA\n");
	if (fclose(punteroFile)) { printf("error closing file."); exit(-1); }
	
	printf("HOLA\n");
	par* listaSalida = 	(par*)malloc(sizeof(par)*(*cantidadLineas));
	
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