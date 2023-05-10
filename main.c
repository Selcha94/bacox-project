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
}clienteInfo;

/* Estructura de Datos del Cuenta*/

typedef struct{
    int numero_cuenta;
    float saldo;
}cuenta;


/*Funcion principal Main*/

int main()
{
    clienteInfo clientes[MAX_CLIENTES]; //Array para almacenar las cuentas de los clientes
    int num_clientes = 0; //numero actual de clientes

    while 1{
        menu();

        // Leer la opcion seleccionada por el usuario Menu
        int opcion;
        printf("\nIngrese una opcion: ");
        scanf("%i",&opcion);

        switch(opcion)
    {
        case 1:
            registrarCliente();
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
            return 0;
        default:
            printf("\n");
            printf("\t\t\tVuelva a intentarlo e ingrese una opcion correcta.");
        }
    }
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

void registrarCliente(clienteInfo clientes[], int *num_clientes ){
    //Verificamos si se ha alcanzado el numero maximo de clientes
    if (*num_clientes == MAX_CLIENTES){
        printf("No se pueden agregar mas clientes\n");
        return;
    }

    //Registrar un nuevo cliente
    clienteInfo nuevo_cliente;
    printf("\nIngrese el Nombre del cliente:");
    scanf("%s",nuevo_cliente.nombre);
    printf("\nIngrese el Apellido del cliente:");
    scanf("%s",nuevo_cliente.apellido);
    printf("\nIngrese el sexo (M o F):");
    scanf("%c",&nuevo_cliente.sexo);
    printf("\nIngrese el DNI del cliente (sin puntos):");
    scanf("%d",&nuevo_cliente.dni);
    printf("\nIngrese la direccion del cliente:");
    scanf("%s",nuevo_cliente.direccion);
    printf("\nIngrese telefono del cliente:");
    scanf("%s",nuevo_cliente.telefono);
    printf("\nIngrese el Email del cliente:");
    scanf("%s",nuevo_cliente.email);

    //Verificamos si el cliente ya existe
    int posicion = buscarCliente(clientes, *num_clientes, nuevo_cliente);
    if (posicion != -1){
        printf("El cliente ya esta registrado\n");
        return;
    }

    //Agregar el nuevo cliente a la lista
    clientes[*num_clientes] = nuevo_cliente;
    (*num_clientes++);

    printf("\n");
    printf("\t\t\t\tEl cliente ha sido registrado con exito!!!\n");

}

//Funcion para buscar clientes en el arreglo de clientes
int buscarCliente(clienteInfo clientes[],int num_clientes, clienteInfo cliente_buscado){

    int i;
    for (i=0; i < num_clientes;i++){
        if(strcmp(clientes[i].nombre, cliente_buscado.nombre)== 0 && strcmp(clientes[i].apellido, cliente_buscado.apellido) == 0 && clientes[i].sexo == cliente_buscado.sexo &&
           clientes[i].dni == cliente_buscado.dni &&
           strcmp(clientes[i].direccion, cliente_buscado.direccion) == 0 &&
           strcmp(clientes[i].telefono, cliente_buscado.telefono) == 0 &&
           strcmp(clientes[i].email, cliente_buscado.email) == 0
           )
            return i;
    }
    return -1;
}
