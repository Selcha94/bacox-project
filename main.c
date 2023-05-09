#include <stdio.h>
#include <stdlib.h>

#define MAX_CLIENTES 10 //Numero maximo de clientes que se pueden almacenar

/*Prototipo de las Funciones*/

void menu();

/* Estructura de Datos del Cliente*/

typedef struct
{
    char nombre[20];
    char apellido[20];
    char sexo;
    double dni;
    char direccion[50];
    char telefono[15];
    char email[30];
}cliente;

/* Estructura de Datos del Cuenta*/

typedef struct{
    int numero_cuenta;
    float saldo;
}cuenta;


/*Funcion principal Main*/

int main()
{
    struct cliente clientes[MAX_CLIENTES]; //Array para almacenar las cuentas de los clientes
    int num_clientes = 0;


    menu();
    // Leer la opcion seleccionada por el usuario Menu
    int opcion;
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
    //Mostrar Menu de opciones
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

    //Registrar un nuevo cliente
    struct cliente nuevo_cliente;
    printf("\nIngrese el Nombre del cliente:\t");
    scanf("%s",nuevo_cliente.nombre);
    printf("\nIngrese el Apellido del cliente:\t");
    scanf("%s",nuevo_cliente.apellido);
    printf("\nIngrese el sexo (M o F):\t");
    scanf("%c",&nuevo_cliente.sexo);
    printf("\nIngrese el DNI del cliente:\t");
    scanf("%d",&nuevo_cliente.dni);
    printf("\nIngrese la direccion del cliente:\t");
    scanf("%s",nuevo_cliente.direccion);
    printf("\nIngrese el telefono del cliente:\t");
    scanf("%s",nuevo_cliente.telefono);
    printf("\nIngrese el Email del cliente:\t");
    scanf("%s",nuevo_cliente.email);

    //Agregar el nuevo cliente a la lista
    clientes[num_clientes] = nuevo_cliente;
    num_clientes++;

    printf("El cliente ha sido registrado con exito\n");


}
