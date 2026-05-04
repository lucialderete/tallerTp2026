/*
*    AUTHOR: Catedra de lenguajes de Taller 1 
*    DATE: 04/2025
*    LICENCE: Creative Commons 
*/

#include "funciones.h"


// DECLARE SUS FUNCIONES ACA
nodo *crearNodo(Producto p);
void InsertarNodo(nodo **Start, nodo *nuevoNodo );
void separarCategoria(nodo **listaHardware, nodo **listaSoftware,  Producto *arreglo, int cantidad);
void actualizarDisponibilidad(nodo *listaSoftware, nodo *listaHardware);
void eliminarProductos(nodo **listaSoftware, nodo **listaHardware);
void moverExcedentes(nodo **listaSoftware, nodo **listaExcedente);
void mostrarLista(nodo **lista);
void liberarLista(nodo **lista);

int main() 
{    
    int cantidad = 40;
    nodo *listaHardware = NULL;
    nodo *listaSoftware = NULL;
    nodo *listaExcedente = NULL;

    //arreglo 
    Producto * TodosLosProductos  = ProductoElectronicos();
    MostrarProductosDeArreglo(TodosLosProductos, 40, "Productos de Proveedor 1");
    //punto 1
    separarCategoria(&listaHardware, &listaSoftware, TodosLosProductos, cantidad);
    actualizarDisponibilidad(listaSoftware, listaHardware);
    eliminarProductos(&listaSoftware, &listaHardware);
    moverExcedentes(&listaSoftware, &listaExcedente);

   
   
    liberarLista(&listaExcedente);
    liberarLista(&listaSoftware);
    liberarLista(&listaHardware);
    free(TodosLosProductos);
    /*fin del programa*/
    printf("\nFin programa\n"); 
    return 0;
}

// IMPLEMENTE SUS FUNCIONES ACA
nodo *crearNodo(Producto p){
    nodo *nuevoNodo = (nodo *)malloc(sizeof(nodo));
    nuevoNodo -> Producto = p;
    nuevoNodo ->Siguiente= NULL;
    return nuevoNodo;
}

void InsertarNodo(nodo **Start, nodo *nuevoNodo ){
    nuevoNodo -> Siguiente = *Start;
    *Start = nuevoNodo; 
}

void separarCategoria(nodo **listaHardware, nodo **listaSoftware, Producto *arreglo, int cantidad){
    for(int i=0; i<cantidad; i++){
        nodo *nuevo = crearNodo(arreglo[i]);
        if(strcmp(arreglo[i].Categoria, "Software")==0){
            InsertarNodo(listaSoftware, nuevo);
        }else if(strcmp(arreglo[i].Categoria, "Hardware")==0){
            InsertarNodo(listaHardware, nuevo);
        }
    }
}

void actualizarDisponibilidad(nodo *listaSoftware, nodo *listaHardware){
    int continuar=1;
   
    while(continuar != 0){
        int idIngresado;
        int encontrado =0;
        printf("Ingrese el id del producto que desea actualizar la disponibilidad: ");
        scanf("%d", &idIngresado);

        nodo *aux = listaSoftware;
        while(aux != NULL){
            if(aux ->Producto.Id == idIngresado){
                aux -> Producto.Activo = 0;
                printf("estado del producto: %s desactivado\n", aux->Producto.Nombre);
                encontrado=1;
            }
            aux = aux->Siguiente;
        }
        aux = listaHardware;
        while(aux != NULL){
            if(aux -> Producto.Id == idIngresado){
                aux->Producto.Activo = 0;
                printf("estado del producto: %s desactivado\n", aux->Producto.Nombre);
                encontrado=1;
            }
            aux = aux->Siguiente;

        }
        if(encontrado == 0){
            printf("no se encontraron productos con ese id\n");
        }
        printf("desea cambiar la disponibilidad de otro producto?\n");
        printf("1: continuar || 0=terminar");
        scanf("%d", &continuar);
    }
}

void eliminarProductos(nodo **listaSoftware, nodo **listaHardware){
    
    nodo *aux =*listaSoftware;
    nodo *anterior = NULL;
    while(aux != NULL){
        if(aux -> Producto.Activo == 0){
            nodo *eliminar = aux;
            if(anterior == NULL){
                *listaSoftware = aux->Siguiente; //si era el primero de la lista mueve la cabecera
            }else{
                anterior -> Siguiente = aux -> Siguiente;
            }
            
            aux = aux -> Siguiente;//avanza al siguiente
            free(eliminar->Producto.Nombre);
            free(eliminar->Producto.Categoria);
            free(eliminar);
            
        }else{
            anterior = aux;
            aux = aux->Siguiente;
        }
    }
    aux = *listaHardware;
    anterior = NULL;
    while(aux != NULL){
        if(aux -> Producto.Activo == 0){
            nodo *eliminar = aux;
            if(anterior == NULL){
                *listaHardware = aux->Siguiente; //si era el primero de la lista mueve la cabecera
            }else{
                anterior -> Siguiente = aux -> Siguiente;
            }
            
            aux = aux -> Siguiente;//avanza al siguiente
            free(eliminar->Producto.Nombre);
            free(eliminar->Producto.Categoria);
            free(eliminar);
            
        }else{
            anterior = aux;
            aux = aux->Siguiente;
        }
    }

}

void moverExcedentes(nodo **listaSoftware, nodo **listaExcedente){
    printf("---verificar si hay excedentes---\n");
    int cantidadMax=50;
    int suma =0;
    nodo *aux = *listaSoftware;
    while(aux != NULL){
        suma += aux -> Producto.Stock;
        aux = aux->Siguiente;
    }
    printf("stock total software: %d\n", suma);
    //mientras la suma sea mayor a 50 y la lista no quede vacia
    while(suma > cantidadMax && *listaSoftware != NULL){
        nodo *actual = *listaSoftware;
        nodo *anterior = NULL;
        while(actual -> Siguiente != NULL){
            anterior = actual;
            actual = actual->Siguiente;
        }
        suma -= actual -> Producto.Stock;
        if(anterior == NULL){ //si el anterior es null solo queda 1 nodo en la lista
            *listaSoftware = NULL;
        }else{
            anterior -> Siguiente = NULL;
        }
        //mover el nodo
        InsertarNodo(listaExcedente, actual);
    }
}

void liberarLista(nodo **lista){
    nodo *aux = *lista;
    nodo *temp;
    while(aux != NULL){
        temp = aux -> Siguiente;
        free(aux -> Producto.Nombre);
        free(aux-> Producto.Categoria);
        free(aux);
        aux = temp;
    }
    *lista = NULL;
}