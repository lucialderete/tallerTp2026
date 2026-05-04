/*
*    AUTHOR: Catedra de lenguajes de Taller 1 
*    DATE: 04/2025
*    LICENCE: Creative Commons 
*/

#include "funciones.h"
// DESARROLLE SU PARCIAL AQUÍ Y NO MODIFIQUE NADA EN EL ARCHIVO FUNCIONES.H
// DECLARE SUS FUNCIONES ACÁ
NodoPaciente * crearListaVacia();
NodoPaciente * crearNodo(Paciente* pacientes, int *id, int i);
void insertarNodo(NodoPaciente ** start, NodoPaciente * nodo);
void cargarPacientes(NodoPaciente ** start, Paciente * pacientes, int *id);
void mostrarListaDePacientes(NodoPaciente *start, char titulo[]);
void PosibleAlta(NodoPaciente * start, char departamentoOrigen[], int edadUmbral);
void eliminarPorDepartamento(NodoPaciente ** start, char * DepartamentoOrigen);
NodoPaciente * quitarNodo(NodoPaciente ** start);
void moverSegunDiagnostico(NodoPaciente ** start, NodoPaciente ** startCronico);
void liberarmemoria(NodoPaciente ** start);

int main() 
{    
    int id = 2201;
    int * idPaciente = &id;
    Paciente * fichasCardio  = PacientesCardio();
    Paciente * fichasTraumato  = PacientesTraumato();
    Paciente * fichasPediatria  = PacientesPediatria();

    MostrarPacientesDeArreglo(fichasCardio,30,"Pacientes de Cardiologia");  
    MostrarPacientesDeArreglo(fichasTraumato, 30, "Pacientes de Traumatologia");
    MostrarPacientesDeArreglo(fichasPediatria, 30, "Pacientes de Pediatria");

    /*Inicio de programa*/
    NodoPaciente * ArchivoCentral = crearListaVacia();
    NodoPaciente * PacientesSeguimientoCronico = crearListaVacia();
    cargarPacientes(&ArchivoCentral, fichasCardio, idPaciente);
    cargarPacientes(&ArchivoCentral, fichasTraumato, idPaciente);
    cargarPacientes(&ArchivoCentral, fichasPediatria, idPaciente);
    PosibleAlta(ArchivoCentral, "Pediatria", 3);
    eliminarPorDepartamento(&ArchivoCentral, "Traumatologia");
    moverSegunDiagnostico(&ArchivoCentral, &PacientesSeguimientoCronico);
    mostrarListaDePacientes(ArchivoCentral, "Archivo Central");
    mostrarListaDePacientes(PacientesSeguimientoCronico, "Pacientes de Seguimiento Cronico");
    liberarmemoria(&ArchivoCentral);
    liberarmemoria(&PacientesSeguimientoCronico);


    /*fin del programa*/
    printf("\nFin programa\n"); 
    return 0;
}

// IMPLEMENTE SUS FUNCIONES ACA
NodoPaciente * crearListaVacia(){
    return NULL;
}

NodoPaciente * crearNodo(Paciente* pacientes, int * id, int i){
    NodoPaciente * paciente = (NodoPaciente *) malloc(sizeof(NodoPaciente));
    paciente->datos.IDPaciente = *id;
    paciente->datos.DepartamentoOrigen = (char *) malloc(strlen(pacientes[i].DepartamentoOrigen)+1);
    strcpy(paciente->datos.DepartamentoOrigen, pacientes[i].DepartamentoOrigen);
    paciente->datos.NombreCompleto = (char *) malloc(strlen(pacientes[i].NombreCompleto)+1);
    strcpy(paciente->datos.NombreCompleto, pacientes[i].NombreCompleto);
    paciente->datos.Edad = pacientes[i].Edad;
    paciente->datos.DiagnosticoPrincipal = (char *) malloc(strlen(pacientes[i].DiagnosticoPrincipal)+1);
    strcpy(paciente->datos.DiagnosticoPrincipal, pacientes[i].DiagnosticoPrincipal);
    paciente->datos.EstadoAlta = pacientes[i].EstadoAlta;

    return paciente;
}

void insertarNodo(NodoPaciente ** start, NodoPaciente * nodo){
    nodo->siguiente = *start;
    *start = nodo;
}

void cargarPacientes(NodoPaciente ** start, Paciente * pacientes, int *id){
    for (int i = 0; i < 30; i++)
    {
        NodoPaciente * fichaPersonal = crearNodo(pacientes, id, i);
        insertarNodo(start, fichaPersonal);
        (*id)++;
    }
}

void mostrarListaDePacientes(NodoPaciente *start, char titulo[]){
    NodoPaciente * aux = start;
    printf("%s \n", titulo);
    while (aux)
    {
        printf("ID: %d \n", aux->datos.IDPaciente);
        printf("Nombre Completo: %s \n", aux->datos.NombreCompleto);
        printf("Departamento de origen: %s \n", aux->datos.DepartamentoOrigen);
        printf("Edad: %d \n", aux->datos.Edad);
        printf("Diagnostico principal: %s \n", aux->datos.DiagnosticoPrincipal);
        printf("Estado alta: %d \n", aux->datos.EstadoAlta);
        printf("\n");

        aux = aux->siguiente;
    }  
    return;
}

void PosibleAlta(NodoPaciente * start, char departamentoOrigen[], int edadUmbral){
    NodoPaciente * aux = start;
    while (aux)
    {
        if (!strcmp(aux->datos.DepartamentoOrigen, departamentoOrigen))
        {
            if (aux->datos.Edad < edadUmbral)
            {
                aux->datos.EstadoAlta = 1;
            }
        }
        
        aux = aux->siguiente;
    }
    return;
}


void eliminarPorDepartamento(NodoPaciente ** start, char * DepartamentoOrigen){
    NodoPaciente ** aux = start;
    while (*aux)
    {
        if (!strcmp((*aux)->datos.DepartamentoOrigen, DepartamentoOrigen))
        {
            NodoPaciente * temp = *aux;
            *aux = (*aux)->siguiente;
            temp->siguiente = NULL;
            free(temp->datos.DepartamentoOrigen);
            free(temp->datos.NombreCompleto);
            free(temp->datos.DiagnosticoPrincipal);
            free(temp);
        } else {
            aux = &(*aux)->siguiente;
        }
    }    
}


NodoPaciente * quitarNodo(NodoPaciente ** start){
    NodoPaciente ** aux = start;
    if (*aux)
    {
        NodoPaciente * temp = *aux;
        *aux = (*aux)->siguiente;
        temp->siguiente = NULL;
        return temp;
    } 
    return NULL;
}


void moverSegunDiagnostico(NodoPaciente ** start, NodoPaciente ** startCronico){
    NodoPaciente ** auxRecorre = start;
    while (*auxRecorre)
    {
        NodoPaciente ** aux = auxRecorre;
        if (strstr((*auxRecorre)->datos.DiagnosticoPrincipal, "Cronico"))
        {
            NodoPaciente * temp = quitarNodo(auxRecorre);
            if (temp == NULL)
            {
                printf("Error moviendo los pacientes.\n");
            } else {
                if (*startCronico == NULL)
                {
                    *startCronico = temp;
                    (*startCronico)->siguiente = NULL;
                } else {
                    NodoPaciente * auxCronico = *startCronico;
                    while (auxCronico->siguiente != NULL)
                    {
                        auxCronico = auxCronico->siguiente;
                    }
                    auxCronico->siguiente = temp;
                    temp->siguiente = NULL;                    
                }
            }
           
        } else {
            (*auxRecorre) = (*auxRecorre)->siguiente;
        }
    }
}

void liberarmemoria(NodoPaciente ** start){
    NodoPaciente * aux = *start;
    NodoPaciente * temp;
    while (aux)
    {
        temp = aux->siguiente;
        free(aux->datos.DepartamentoOrigen);
        free(aux->datos.DiagnosticoPrincipal);
        free(aux->datos.NombreCompleto);
        free(aux);
        aux = temp;
    }
    *start = NULL;
}