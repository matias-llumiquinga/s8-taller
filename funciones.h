# define NUM_CARACTERES_NOMBRES 22
# define NUM_CARACTERES_INST 200
# define NUM_PRODUCTOS 5


void imprimirInstruccionesAvisos(int i, int opcInstrucciones);


void validarNumCaracteres(char texto[NUM_CARACTERES_NOMBRES], int i, int opcInstrucciones);


int validarEntero(int cantidadOpcs, int i, int opcEntero, int opcInstrucciones);
float validarFlotante(int i, int opcFlotante, int opcInstrucciones);




void buscarReemplazarEliminar(char nombresProductos[NUM_PRODUCTOS][NUM_CARACTERES_NOMBRES], int cantidadProductos,
                              int reemplazarEliminar, int *eliminados,
                              float tiempoUnidad[NUM_PRODUCTOS], float recursosUnidad[NUM_PRODUCTOS],
                              int cantDemandada[NUM_PRODUCTOS]);

void tiempoRecursos(float *tiempoUnidad, float *recursosUnidad, char nombresProductos[NUM_CARACTERES_NOMBRES], int i);



void menu(char nombresProductos[NUM_PRODUCTOS][NUM_CARACTERES_NOMBRES], int cantOpcsMenu,
          int *cantProductos, int *continuar,
          float tiempoUnidad[NUM_PRODUCTOS], float recursosUnidad[NUM_PRODUCTOS],
          float *tiempoDisponible, float *recursosDisponibles,
          int cantDemandada[NUM_PRODUCTOS]);

void tiempoRecursosRequeridos(float tiempoUnidad[NUM_PRODUCTOS], float recursosUnidad[NUM_PRODUCTOS], int cantDemandada[NUM_PRODUCTOS],
                              int cantProductos,
                              float tiempoDisponible, float recursosDisponibles);

void imprimirLineas();



void recomendarProduccion(float tiempoUnidad[NUM_PRODUCTOS], float recursosUnidad[NUM_PRODUCTOS], int cantDemandada[NUM_PRODUCTOS],
                          int cantProductos,
                          float tiempoDisponible, float recursosDisponibles);





