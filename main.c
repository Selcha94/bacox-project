#include <stdio.h>
#include <stdlib.h>

/* Estructura de Datos del Cliente*/
typedef struct
{
    char apellidoYNombre[30];
    char sexo[2];
    int dni[8];
    int telefono[15];
    char email[30];
} infoCliente;


int main(int argc, char *argv[])
{
    int i;
    infoCliente CLI[10];
    for (i=0;i<10,i++){
        printf("Ingrese su apellido y nombre:");
        fgets(CLI[i].apellidoYNombre,30,stdin);
        printf("Ingrese su sexo(F/M):");
        fgets(CLI[i].sexo,1,stdin);
        printf("Ingrese su DNI(sin puntos):");
        scanf("%i",&CLI[i].dni);
        printf("Ingrese su Telefono:");
        scanf("%i",&CLI[i].telefono);
        printf("Ingrese su email:");
        fgets(CLI[i].email,30,stdin);
        fflush(stdin);//Limpia la pantalla con los datos ingresados para que en el nuevo ciclo for no sea visible
    }

    return 0;
}
