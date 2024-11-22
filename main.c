#include <stdio.h>
#include <string.h>
#include <math.h>
#include "funciones.h"

int main(int argc, char *argv[])
{
    char nombresProductos[NUM_PRODUCTOS][NUM_CARACTERES_NOMBRES];
    int cantProductos = 0, continuar = 0, eliminados = 0, recursosDisponibles = 0;
    float tiempoPUnidad[NUM_PRODUCTOS];
    int recursosPUnidad[NUM_PRODUCTOS], cantPDemandada[NUM_PRODUCTOS];
    float tiempoDisponible = 0;

    for (int i = 0; i < NUM_PRODUCTOS; i++)
    {
        tiempoPUnidad[i] = 0;
        recursosPUnidad[i] = 0;
        strcpy(nombresProductos[i], "");
    }

    imprimirLineas();
    tiempoDisponible = validarFlotante(0, 2, 5);
    imprimirLineas();
    recursosDisponibles = validarEntero(0, 0, 4, 4);
    imprimirLineas();
    cantProductos = validarEntero(0, 0, 2, 0);

    for (int i = 0; i < cantProductos; i++)
    {
        imprimirLineas();
        validarNumCaracteres(nombresProductos[i], i, 1);
        tiempoRecursos(&tiempoPUnidad[i], &recursosPUnidad[i], nombresProductos[i], i);
        cantPDemandada[i]=validarEntero(0, i, 5, 6);
    }

    do
    {
        menu(nombresProductos, 6, &cantProductos, &continuar, tiempoPUnidad, recursosPUnidad, &tiempoDisponible, &recursosDisponibles, cantPDemandada);
    } while (continuar != 6);

    return 0;
}
