int encontrarEspacio(char entrada[],int largo);
char *subs(char entrada[],int inicio,int final,int largo);
char *leerArchivo(char nombreArchivo[],int *cantidadFilas, int *cantidadColumnas);
par* leerArchivoSecundario(char nombreArchivo[],int*cantidadLineas,int tipoArchivo);
char *crearColumna(char*entrada,int cantidadColumnas,int cantidadFilas,int comienzo);//
void moverRodilloAux(char*rodillo,int largo);//
void moverRodillo(char**matriz,int numeroRodillo,int largoRodillo,int desplazamiento);
char *generarStringFila(char**matriz,int numeroFila,int cantidadColumnas);//
int compararStringsConCaracter(char*substring,char caracter,int largo);
int puntajesCombinacion(char*stringFila,int largoFila);
int buscarPuntaje(char**matriz,int cantidadColumnas,int cantidadFilas);
void imprimirMaquina(char**matriz,int cantidadColumnas,int cantidadFilas);
char ** devolverDiagonales(char**matriz,int cantidadColumnas,int cantidadFilas);
int puntajeDiagonales(char**matrizDiagonales,int largoLista,int largoStr);
void imprimirGiros(int*giros,int cantidadColumnas);
void anularMatriz(char**matriz,int cantidadColumnas);
void anularListaPares(par*listaPar,int cantidadPares);
char **crearMatriz(char*entrada,int cantidadFilas,int cantidadColumnas);//
int* desplazarRodillos(char**matriz,int cantidadFilas,int cantidadColumnas);
int dineroBonus(char**matriz,int cantidadFilas,int cantidadColumnas,par*listaBonus,int cantidadBonus,int*cantidadBonusEncontrados);
int pivot(par *unarray, int izq, int der);
void Quicksort(par *unarray, int izq, int der);
char* obtenerPremio(int puntaje,par*listaPremios,int cantidadPremios,int* largoPremio);
int cantidadCaracteresEntero(int entero);
void guardarArchivoSalida(int puntajeObtenido,char*premio,int largoPremio,int cantidadBonusEncontrados,int dineroPorBonus);
void run(int semilla);



