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

/*Llamada a funciones*/

void menu();

/*Funcion principal Main*/

int main(int argc, char *argv[])
{
    int opcion;
    float saldo;
    menu();
    printf("\nIngrese una opcion: ");
    scanf("%i",&opcion);

    switch(opcion)
    {
    case 1:
        cliente();
        break;
    case 2:
        break;
    case 3:
        break;
    case 4:
        break;
    case 5:
        break;
    case 6:
        break;
    case 7:
        break;
    default:
        printf("Vuelva a intentarlo e ingrese una opcion correcta.");

    }
    return 0;
}

/*Funciones*/

/*Funcion Menu*/

void menu(){
    printf("========================================================================================\n");
    printf("\t\t                       Bienvenido a Bacox!\n");
    printf("========================================================================================\n");
    printf("Seleccione una de las siguientes opciones disponibles:\n");
    printf("\t1. Dar de Alta una cuenta.\n");
    printf("\t2. Eliminar una cuenta.\n");
    printf("\t3. Listado de cuentas con saldo entre minimo y maximo\n");
    printf("\t4. Realizar una extraccion.\n");
    printf("\t5. Depositar Dinero.\n");
    printf("\t6. Movimientos.\n");
    printf("\t7. Salir\n");

}

/*Funcion Cliente con informacion del Cliente*/

void cliente(){
    int i;
    infoCliente CLI[10];
    for (i=0;i<10;i++){
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
    system("pause");
    system("cls");
    for (i=0;i<10;i++){
        printf("El titular, %s, de la cuenta nro. %i posee un saldo dispobible de : %f", CLI[i].apellidoYNombre);
    }
    system("pause");
}
