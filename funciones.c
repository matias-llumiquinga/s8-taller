#include <stdio.h>
#include <string.h>
#include <math.h>
#include "funciones.h"

void imprimirInstruccionesAvisos(int i, int opcInstrucciones)
{
    switch (opcInstrucciones)
    {
    case 0:
        printf("Ingrese la cantidad de productos a registrar (Entero: 1-5):\t");
        break;
    case 1:
        printf("Ingrese el nombre del producto %d:\t", i + 1);
        break;
    case 2:
        printf("Ingrese el tiempo en horas para fabricar una unidad del producto %d (0<tiempo<=50):\t", i + 1);
        break;
    case 3:
        printf("Ingrese la cantidad de dinero para fabricar una unidad del producto %d (0<dinero<=50):\t", i + 1);
        break;
    case 4:
        printf("Ingrese la cantidad TOTAL de dinero que dispone la fabrica (0<dinero<=1500):\t");
        break;
    case 5:
        printf("Ingrese el tiempo TOTAL en horas que dispone la fabrica (0<tiempo<=1500):\t");
        break;
    case 6:
        printf("Ingrese la cantidad demandada del producto %d (Entero: 0<demanda<=30):\t\t\t", i + 1);
        break;
    case 11:
        printf("Ingrese:\n1.Modificar Tiempo/Recursos Disponibles\n2.Ingresar Nuevo Producto\n3.Modificar la demanda\n4.Modificar Producto(s)\n5.Eliminar Producto(s)\n6.Mostrar Registro y Resultados\n7.Finalizar\n>>\t");
        break;
    case 12:
        printf("Ingrese el nombre del producto a editar:\t");
        break;
    case 13:
        printf("Ingrese el nuevo nombre del producto %d:\t\t", i + 1);
        break;
    case 14:
        printf("Ingrese el nombre del producto a eliminar:\t");
        break;
    case 15:
        printf("Ingrese el nombre del producto a modificar su demanda:\t");
        break;
    case 31:
        printf("-HA EXCEDIDO EL MAXIMO DE %d CARACTERES-\n", NUM_CARACTERES_NOMBRES);
        break;
    case 32:
        printf("-PRODUCTO NO REGISTRADO-\n");
        break;
    case 33:
        printf("-OPCION INVALIDA-\n");
        break;
    case 34:
        printf("-NUMERO INVALIDO-\n");
        break;
    case 35:
        printf("-YA EXISTEN 5 PRODUCTOS REGISTRADOS-\n");
        break;
    case 36:
        if (i == 1)
        {
            printf("-SE HA ELIMINADO %d ELEMENTO-\n", i);
        }
        else
        {
            printf("-SE HAN ELIMINADO %d ELEMENTOS-\n", i);
        }
        break;
    case 37:
        if (i == 0)
        {
            printf("-(%d) ELEMENTOS REGISTRADOS-\n\n", i);
        }
        else
        {
            printf("-(%d/5) ELEMENTO REGISTRADOS-\n\n", i);
        }
        break;
    case 38:
        printf("-DATOS DE FABRICACION POR UNIDAD-\n");
        break;
    default:
        break;
    }
}

void validarNumCaracteres(char texto[NUM_CARACTERES_NOMBRES], int i, int opcInstrucciones)
{
    int longitudCadena = 0;
    do
    {
        imprimirInstruccionesAvisos(i, opcInstrucciones);

        strcpy(texto, "");
        while (texto[0] == '\0' || texto[0] == '\n')
        {
            fgets(texto, NUM_CARACTERES_NOMBRES, stdin);
        }
        longitudCadena = strlen(texto);

        if (texto[longitudCadena - 1] != '\n')
        {
            imprimirInstruccionesAvisos(0, 31);
            while (getchar() != '\n')
                ;
        }
    } while (texto[longitudCadena - 1] != '\n');
    texto[longitudCadena - 1] = '\0';
}

void buscarReemplazarEliminar(char nombresProductos[NUM_PRODUCTOS][NUM_CARACTERES_NOMBRES], int cantidadProductos,
                              int reemplazarEliminar, int *eliminados,
                              float tiempoUnidad[NUM_PRODUCTOS], float recursosUnidad[NUM_PRODUCTOS],
                              int cantDemandada[NUM_PRODUCTOS])
{
    int encontrado = 0, paraEliminar = 0;
    char nombreProductoBuscado[NUM_CARACTERES_NOMBRES];
    if (reemplazarEliminar == 0)
    {
        validarNumCaracteres(nombreProductoBuscado, 0, 12);
    }
    else if (reemplazarEliminar == 1)
    {
        validarNumCaracteres(nombreProductoBuscado, 0, 14);
    }
    else if (reemplazarEliminar == 2)
    {
        validarNumCaracteres(nombreProductoBuscado, 0, 15);
    }

    *eliminados = 0;

    for (int i = 0; i < cantidadProductos; i++)
    {
        if (strcmp(nombreProductoBuscado, nombresProductos[i]) == 0)
        {
            encontrado = 1;
            paraEliminar++;
        }
    }
    if (encontrado == 1 && reemplazarEliminar == 0)
    {
        for (int i = 0; i < cantidadProductos; i++)
        {
            if (strcmp(nombreProductoBuscado, nombresProductos[i]) == 0)
            {
                validarNumCaracteres(nombresProductos[i], i, 13);
                tiempoRecursos(&tiempoUnidad[i], &recursosUnidad[i], nombresProductos[i], i);
            }
        }
    }
    if (encontrado == 1 && reemplazarEliminar == 1)
    {
        do
        {
            for (int i = 0; i < cantidadProductos; i++)
            {
                if (strcmp(nombreProductoBuscado, nombresProductos[i]) == 0)
                {
                    for (int j = 0; j < NUM_PRODUCTOS - 1; j++)
                    {
                        if (j >= i)
                        {
                            strcpy(nombresProductos[j], nombresProductos[j + 1]);
                            tiempoUnidad[j] = tiempoUnidad[j + 1];
                            recursosUnidad[j] = recursosUnidad[j + 1];
                            cantDemandada[j] = cantDemandada[j + 1];
                        }
                    }
                }
            }
            *eliminados = *eliminados + 1;
        } while (*eliminados != paraEliminar);
        imprimirInstruccionesAvisos(*eliminados, 36);
    }
    if (encontrado == 1 && reemplazarEliminar == 2)
    {
        for (int i = 0; i < cantidadProductos; i++)
        {
            if (strcmp(nombreProductoBuscado, nombresProductos[i]) == 0)
            {
                cantDemandada[i] = validarEntero(0, i, 5, 6);
            }
        }
    }
    

    if (encontrado == 0)
    {
        imprimirInstruccionesAvisos(0, 32);
    }
}

int validarEntero(int cantidadOpcs, int i, int opcEntero, int opcInstrucciones)
{
    int numE, continuar;
    float numF;

    do
    {
        numE = 0;
        numF = 0;
        continuar = 1;

        imprimirInstruccionesAvisos(i, opcInstrucciones);
        scanf("%f", &numF);
        numE = (int)numF;

        if (numE != numF)
        {
            continuar = 0;
        }
        else
        {
            switch (opcEntero)
            {
            case 1:
            {
                int opcs[cantidadOpcs];
                for (int i = 0; i < cantidadOpcs; i++)
                {
                    opcs[i] = i + 1;

                    if (numF == opcs[i])
                    {
                        continuar = 1;
                        break;
                    }
                    else
                    {
                        continuar = 0;
                    }
                }
                break;
            }
            case 2:
                if (numE <= 0 || numE > 5)
                {
                    continuar = 0;
                }
                break;
            case 5:
                if (numE <= 0 || numE > 30)
                {
                    continuar = 0;
                }
                break;

            default:
                break;
            }
        }

        if (continuar == 0 && opcEntero == 1)
        {
            imprimirLineas();
            imprimirInstruccionesAvisos(0, 33);
            imprimirLineas();
        }
        else if (continuar == 0 && opcEntero > 1)
        {
            imprimirInstruccionesAvisos(0, 34);
        }
    } while (continuar == 0);
    return numE;
}

float validarFlotante(int i, int opcFlotante, int opcInstrucciones)
{

    float numF;
    int continuar;
    do
    {
        numF = 0;
        continuar = 1;
        imprimirInstruccionesAvisos(i, opcInstrucciones);
        scanf("%f", &numF);

        switch (opcFlotante)
        {
        case 1:
            if (numF <= 0 || numF > 50)
            {
                continuar = 0;
            }
            break;
        case 2:
            if (numF <= 0 || numF > 1500)
            {
                continuar = 0;
            }
            break;
        default:
            break;
        }
        if (continuar == 0)
        {
            imprimirInstruccionesAvisos(0, 34);
        }
    } while (continuar == 0);
    return numF;
}

void tiempoRecursos(float *tiempoUnidad, float *recursosUnidad, char nombresProductos[NUM_CARACTERES_NOMBRES], int i)
{
    float time;
    int resources;

    *tiempoUnidad = validarFlotante(i, 1, 2);
    *recursosUnidad = validarFlotante(i, 1, 3);
}

void menu(char nombresProductos[NUM_PRODUCTOS][NUM_CARACTERES_NOMBRES], int cantOpcsMenu,
          int *cantProductos, int *continuar,
          float tiempoUnidad[NUM_PRODUCTOS], float recursosUnidad[NUM_PRODUCTOS],
          float *tiempoDisponible, float *recursosDisponibles,
          int cantDemandada[NUM_PRODUCTOS])
{
    int eliminados;
    imprimirLineas();
    *continuar = validarEntero(cantOpcsMenu, 0, 1, 11);
    switch (*continuar)
    {
    case 1:
        imprimirLineas();
        *tiempoDisponible = validarFlotante(0, 2, 5);
        *recursosDisponibles = validarFlotante(0, 2, 4);
        break;
    case 2:
        imprimirLineas();
        if (*cantProductos >= 5)
        {
            imprimirInstruccionesAvisos(0, 35);
            *cantProductos = 5;
            break;
        }
        else
        {
            validarNumCaracteres(nombresProductos[*cantProductos], *cantProductos, 1);
            tiempoRecursos(&tiempoUnidad[*cantProductos], &recursosUnidad[*cantProductos], nombresProductos[*cantProductos], *cantProductos);
            *cantProductos = *cantProductos + 1;
        }
        break;
    case 3:
        imprimirLineas();
        buscarReemplazarEliminar(nombresProductos, *cantProductos, 2, &eliminados, tiempoUnidad, recursosUnidad, cantDemandada);
        break;
    case 4:
        imprimirLineas();
        buscarReemplazarEliminar(nombresProductos, *cantProductos, 0, &eliminados, tiempoUnidad, recursosUnidad, cantDemandada);
        break;
    case 5:
        imprimirLineas();
        buscarReemplazarEliminar(nombresProductos, *cantProductos, 1, &eliminados, tiempoUnidad, recursosUnidad, cantDemandada);
        *cantProductos = *cantProductos - eliminados;
        break;
    case 6:

        imprimirLineas();

        printf("-TIEMPO DISPONIBLE DE LA EMPRESA:\t%.2fH\n", *tiempoDisponible);
        printf("-RECURSOS DISPONIBLES DE LA EMPRESA:\t$%.2f\n\n", *recursosDisponibles);
        imprimirInstruccionesAvisos(0, 38);
        imprimirInstruccionesAvisos(*cantProductos, 37);

        printf("%4s%-22s%-22s%-22s%-22s\n", "", "NOMBRE PRODUCTOS", "TIEMPO FABRICACION(H)", "DINERO FABRICACION($)", "CANT. DEMANDADA");
        for (int i = 0; i < *cantProductos; i++)
        {
            printf("%-1d%-3s%-22s%-22.2f%-22.2f%-22d\n", i + 1, ".", nombresProductos[i], tiempoUnidad[i], recursosUnidad[i], cantDemandada[i]);
        }

        tiempoRecursosRequeridos(tiempoUnidad, recursosUnidad, cantDemandada, *cantProductos, *tiempoDisponible, *recursosDisponibles);
        break;

    default:
        break;
    }
}

void tiempoRecursosRequeridos(float tiempoUnidad[NUM_PRODUCTOS], float recursosUnidad[NUM_PRODUCTOS], int cantDemandada[NUM_PRODUCTOS],
                              int cantProductos,
                              float tiempoDisponible, float recursosDisponibles)
{
    float tiempoRequerido = 0;
    float recursosRequeridos = 0;

    for (int i = 0; i < cantProductos; i++)
    {
        tiempoRequerido = tiempoRequerido + (tiempoUnidad[i] * cantDemandada[i]);
        recursosRequeridos = recursosRequeridos + (recursosUnidad[i] * cantDemandada[i]);
    }
    printf("\n-SE REQUIERE DE %.2fH PARA CUMPLIR CON LA DEMANDA\n", tiempoRequerido);
    printf("-SE REQUIERE DE $%.2f PARA CUMPLIR CON LA DEMANDA\n\n", recursosRequeridos);
    if (tiempoRequerido <= tiempoDisponible && recursosRequeridos <= recursosDisponibles)
    {
        printf("-LA EMPRESA SI CUMPLIRA CON LA DEMANDA\n", recursosRequeridos);
    }
    else
    {
        printf("-LA EMPRESA NO CUMPLIRA CON LA DEMANDA\n", recursosRequeridos);
        printf("-SE RECOMIENDA FABRICAR:\n");
        recomendarProduccion(tiempoUnidad, recursosUnidad, cantDemandada, cantProductos, tiempoDisponible, recursosDisponibles);
    }
}

void imprimirLineas()
{
    for (int i = 0; i < NUM_CARACTERES_NOMBRES * 6; i++)
    {
        printf("-");
    }
    printf("\n");
}

void recomendarProduccion(float tiempoUnidad[NUM_PRODUCTOS], float recursosUnidad[NUM_PRODUCTOS], int cantDemandada[NUM_PRODUCTOS],
                          int cantProductos,
                          float tiempoDisponible, float recursosDisponibles)
{
    float valoresAcumTiempo[NUM_PRODUCTOS];
    int valoresAcumRecursos[NUM_PRODUCTOS], acumUnidadesTiempo[NUM_PRODUCTOS], acumUnidadesRecursos[NUM_PRODUCTOS], unidadesCumplidas[NUM_PRODUCTOS];
    float inicialTiempoDisponible = tiempoDisponible, tiempoProceso = tiempoDisponible;
    float inicialRecursosDisponibles = recursosDisponibles, recursosProceso = recursosDisponibles;

    for (int i = 0; i < NUM_PRODUCTOS; i++)
    {
        valoresAcumTiempo[i] = 0;
        valoresAcumRecursos[i] = 0;
        acumUnidadesTiempo[i] = 0;
        acumUnidadesRecursos[i] = 0;
        unidadesCumplidas[i] = 0;
    }

    for (int i = 0; i < cantProductos; i++)
    {
        acumUnidadesTiempo[i] = 0;
        while (acumUnidadesTiempo[i] < cantDemandada[i] && valoresAcumTiempo[i] <= tiempoDisponible)
        {
            valoresAcumTiempo[i] = valoresAcumTiempo[i] + tiempoUnidad[i];
            acumUnidadesTiempo[i] = acumUnidadesTiempo[i] + 1;
        }
        if (valoresAcumTiempo[i] > tiempoDisponible)
        {
            valoresAcumTiempo[i] = valoresAcumTiempo[i] - tiempoUnidad[i];
            tiempoDisponible = tiempoDisponible - valoresAcumTiempo[i];
            acumUnidadesTiempo[i] = acumUnidadesTiempo[i] - 1;
        }
        else
        {
            tiempoDisponible = tiempoDisponible - valoresAcumTiempo[i];
        }

        acumUnidadesRecursos[i] = 0;
        while (acumUnidadesRecursos[i] < cantDemandada[i] && valoresAcumRecursos[i] <= recursosDisponibles)
        {
            valoresAcumRecursos[i] = valoresAcumRecursos[i] + recursosUnidad[i];
            acumUnidadesRecursos[i] = acumUnidadesRecursos[i] + 1;
        }
        if (valoresAcumRecursos[i] > recursosDisponibles)
        {
            valoresAcumRecursos[i] = valoresAcumRecursos[i] - recursosUnidad[i];
            recursosDisponibles = recursosDisponibles - valoresAcumRecursos[i];
            acumUnidadesRecursos[i] = acumUnidadesRecursos[i] - 1;
        }
        else
        {
            recursosDisponibles = recursosDisponibles - valoresAcumRecursos[i];
        }

        if (acumUnidadesRecursos[i] < acumUnidadesTiempo[i])
        {
            valoresAcumTiempo[i] = valoresAcumTiempo[i] - (tiempoUnidad[i] * (acumUnidadesTiempo[i] - acumUnidadesRecursos[i]));
            unidadesCumplidas[i] = acumUnidadesRecursos[i];
            acumUnidadesTiempo[i] = unidadesCumplidas[i];
            tiempoDisponible = tiempoProceso - valoresAcumTiempo[i];
            tiempoProceso = tiempoDisponible;
            recursosProceso = recursosDisponibles;
        }
        else if (acumUnidadesRecursos[i] > acumUnidadesTiempo[i])
        {
            valoresAcumRecursos[i] = valoresAcumRecursos[i] - (recursosUnidad[i] * (acumUnidadesRecursos[i] - acumUnidadesTiempo[i]));
            unidadesCumplidas[i] = acumUnidadesTiempo[i];
            acumUnidadesRecursos[i] = unidadesCumplidas[i];
            recursosDisponibles = recursosProceso - valoresAcumRecursos[i];
            recursosProceso = recursosDisponibles;
            tiempoProceso = tiempoDisponible;
        }
        else
        {
            unidadesCumplidas[i] = acumUnidadesRecursos[i];
            tiempoProceso = tiempoDisponible;
            recursosProceso = recursosDisponibles;
        }
    }

    /*for (int i = 0; i < cantProductos; i++)
    {
        if (acumUnidadesRecursos[i] <= acumUnidadesTiempo[i])
        {
            unidadesCumplidas[i] = acumUnidadesRecursos[i];
        }
        else
        {
            unidadesCumplidas[i] = acumUnidadesTiempo[i];
        }
    }*/

    for (int i = 0; i < cantProductos; i++)
    {
        printf("--%2d ELEMENTO(S) DEL PRODUCTO %d\n", unidadesCumplidas[i], i + 1);
    }
    printf("---TIEMPO INVERTIDO:\t%.2fH/%.2fH\n---TIEMPO SOBRANTE:\t%.2fH\n", inicialTiempoDisponible - tiempoDisponible, inicialTiempoDisponible, tiempoDisponible);
    printf("---RECURSOS INVERTIDOS:\t$%.2f/$%.2f\n---RECURSOS SOBRANTES:\t$%.2f\n", inicialRecursosDisponibles - recursosDisponibles, inicialRecursosDisponibles, recursosDisponibles);
}
