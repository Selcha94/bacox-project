
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

//Lista de pendientes
// 1)Dar de alta una cuenta
//  - Al dar de alta una cuenta, el cliente se tiene que guardar solamente si no existe en el archivo clientes.txt (OK)
//  - Ni bien se crea la cuenta, tiene que pedir un deposito mayor a cero (Falta)
//  - Aparte de guardar el cliente en clientes.txt, tambien hay que guardar la cuenta en cuentas.txt. Cada cuenta tendra:
//    - Numero (Lo calculamos al momento de crear la cuenta, por ejemplo tomamos el numero de la cuenta anterior + 1)
//    - Dni del titular
//    - Saldo
//  - Otra cosa que hay que guardar tambien es cada movimiento en un archivo movimientos.txt. Cada movimiento tendra:
//    - Numero de cuenta
//    - Monto
//    - Tipo de movimiento (E o D, dependiendo de si es extraccion o deposito)
// 2) Eliminar una cuenta
//  - Al eliminar una cuenta, hay que validar primero que su saldo sea cero. Caso contrario no dejar eliminarla (Falta)
//  - Al eliminar una cuenta, eliminar tambien al titular si es que no tiene ninguna otra cuenta aparte de la que se esta eliminando (Falta)
// 3) Listado de cuentas con saldo entre minimo y maximo
//  - Listar cuentas que tengan saldo entre un saldo minimo y maximo especificado por el usuario (Falta)
// 4) Realizar una extraccion
//  - Hacer una extraccion, validar que haya saldo suficiente primero (Falta)
// 5) Depositar dinero
//  - Depositar dinero en una cuenta
// 6) Generar un archivo de texto de movimientos para una fecha ingresada por el usuario
//  - Exportar en un archivo .txt todos los movimientos realizados en una cuenta para una determinada fecha que el usuario especifique por parametro (Falta)

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h> // Posee varias funciones que son útiles para probar y mapear caracteres.

#define MAX_CLIENTES 10 //Numero maximo de clientes que se pueden almacenar
#define CLIENTE_FILE "cliente.txt" //Constante para el nombre del archivo en el que se guardaran los clientes.

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////      VARIABLES GLOBALES      ////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

//Variables globales para la solicitud de la fecha
static int dia, mes, anio;
//Variable estatica que almacena el numero de cuenta y asigna un valor inicial de 0000
static int numero_cuenta = 0000;

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////      ZONA DE STRUCTS         ////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


/* Estructura de Datos del Cliente*/
typedef struct{
    int cuenta_cliente;
    int nro_cliente;
    float saldo;
}cuenta;


/* Estructura de Datos del Cuenta*/
typedef struct
{
    char nombre[20];
    char apellido[20];
    char sexo;
    double dni;
    char direccion[30];
    char telefono[15];
    char email[50];
    cuenta cuenta_cliente; // Agregar el miembro cuenta_cliente de tipo cuenta
}clienteInfo;


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////      ZONA DE PROTOTIPOS      ////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/*Prototipo de las Funciones*/
void menu();
void solicitarDeposito(clienteInfo *cliente);
void registrarCliente(clienteInfo clientes[], int *num_clientes);
int buscarCliente(clienteInfo clientes[],int num_clientes, clienteInfo cliente_buscado);
void convertirMayusculaMinuscula(char* cadena);
void convertirEmailMinuscula(char *cadena);
void solicitudFecha( int *dia, int *mes, int *anio);
void guardarClientesEnArchivo(clienteInfo cliente);
void mostrarCliente();

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////      ZONA DE MAIN            ////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/*Funcion principal Main*/
int main()
{
    clienteInfo clientes[MAX_CLIENTES]; //Array para almacenar las cuentas de los clientes
    int num_clientes = 0; //Contador de numero actual de clientes

    // Solicitud de ingreso de fecha
    solicitudFecha( &dia, &mes, &anio);

    while(1){

        menu();

        // Leer la opcion seleccionada por el usuario Menu
        int opcion;
        printf("\nIngrese una opcion: ");
        scanf("%i",&opcion);
        getchar(); //Esto te "absrobe" el enter con el que ingresaste el numero de opcion en la linea de arriba

        switch(opcion)
    {
        case 1:
            registrarCliente(clientes, &num_clientes);
            break;
        case 2:
            break;
        case 3:
            mostrarCliente();
            break;
        case 4:
            break;
        case 5:
            break;
        case 6:
            break;
        case 7:
            printf("\nSaliendo del programa...\n");
            return 0;
        default:
            printf("\n");
            printf("\t\t\tVuelva a intentarlo e ingrese una opcion correcta.\n");
            break;
        }
    }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////    FUNCIONES AUXILIARES    //////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

//Mostrar Menu de opciones
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

// Funcion para solicitar fecha
void solicitudFecha( int *dia, int *mes, int *anio){

    printf("\n Ingrese la fecha correspondiente (en formato dd/mm/aaaa): ");
    scanf("%d/%d/%d", dia, mes, anio);
    printf("========================================================================================\n");
    printf("\n");
    printf("\t\t\t\t La fecha ingresada es: %02d/%02d/%d \n\n ", *dia, *mes, *anio);

}
// Recibe un string y un largo maximo
// Devuelve 1 si el largo del string es menor o igual al maximo
// Devuelve 0 en otro caso
int validar_largo(char* cadena, int largo_maximo){

    printf("%i",strlen(cadena));
    printf("%i",largo_maximo);
    return strlen(cadena) <= largo_maximo;
}

void limpiar_buffer(){
    char buffer_char = getchar();
    while(buffer_char != '\n'){
        buffer_char = getchar();
    }
}

/*Funcion que recibe como parametro una cadena de caracteres
y convierte la primera letra en mayuscula y el resto en minuscula, pero verifica primero si se cumple si la
primera letra esta en mayuscula y si lo que le sigue esta en minuscula*/
void convertirMayusculaMinuscula(char* cadena){
    int i = 0;
    if(cadena[i]>='a' && cadena[i]<='z'){
        cadena[i] -='a' - 'A'; //convierte la primera letra en mayuscula
    }

    i++;

    while(cadena[i] != '\0'){
        if(cadena[i] >= 'A' && cadena [i] <= 'Z'){
            cadena[i] += 'a' - 'A'; //convierte la letra a minuscula
        }
        i++;
    }
}

//Convertir email a minuscula
void convertirEmailMinuscula(char *cadena){
    int i;
    for (i=0; cadena[i]; i++){
        cadena[i] = tolower(cadena[i]);
    }
}

//Funcion para buscar clientes en el arreglo de clientes
int buscarCliente(clienteInfo clientes[], int num_clientes, clienteInfo cliente_buscado){

    int i;
    for (i=0; i < num_clientes;i++){
        if (strcmp(clientes[i].nombre, cliente_buscado.nombre) == 0 &&
        strcmp(clientes[i].apellido, cliente_buscado.apellido) == 0 &&
        clientes[i].sexo == cliente_buscado.sexo && clientes[i].dni == cliente_buscado.dni &&
        strcmp(clientes[i].direccion, cliente_buscado.direccion) == 0 &&
        strcmp(clientes[i].telefono, cliente_buscado.telefono) == 0 &&
        strcmp(clientes[i].email, cliente_buscado.email) == 0){
            return i;
        }
    }
    return -1;
}

/*Funcion para realizar Depositos de dinero.*/
//En esta funcion, se pasa un puntero al cliente para poder modificar directamente la cuenta del cliente
void solicitarDeposito(clienteInfo *cliente){
    cliente->cuenta_cliente.cuenta_cliente = numero_cuenta;
    numero_cuenta++; //Incrementa el numero de cuenta para el siguiente cliente
    printf("\n Ingrese el monto del deposito realizado por el cliente: \t");
    scanf("%f", &cliente->cuenta_cliente.saldo);

    guardarClientesEnArchivo(*cliente);

}

/*Funcion Cliente con informacion del Cliente*/
void registrarCliente(clienteInfo clientes[], int *num_clientes){
    //Verificamos si se ha alcanzado el numero maximo de clientes

    if (*num_clientes == MAX_CLIENTES){
        printf("No se pueden agregar mas clientes\n");
        return;
    }

    //Registrar un nuevo cliente

    clienteInfo nuevo_cliente;

    printf("\nIngrese el Nombre del cliente (%i caracteres maximo):", sizeof(nuevo_cliente.nombre));
    fgets(nuevo_cliente.nombre, sizeof(nuevo_cliente.nombre),stdin);
    nuevo_cliente.nombre[strcspn(nuevo_cliente.nombre, "\n")] = '\0';//Elimina el caracter del '\n' despues de leerlo
    convertirMayusculaMinuscula(nuevo_cliente.nombre); //Verifica si la primera letra esta en mayuscula y sino lo esta la convertieen mayuscula


    printf("\nIngrese el Apellido del cliente (%i caracteres apellido):", sizeof(nuevo_cliente.apellido));
    fgets(nuevo_cliente.apellido, sizeof(nuevo_cliente.apellido),stdin);
    nuevo_cliente.apellido[strcspn(nuevo_cliente.apellido, "\n")] = '\0';
    convertirMayusculaMinuscula(nuevo_cliente.apellido);

    int sexo_valido = 0;
    while (! sexo_valido){
        printf("\nIngrese el sexo (M o F):");
        scanf(" %c",&nuevo_cliente.sexo);;
        if (nuevo_cliente.sexo != 'M' && nuevo_cliente.sexo != 'F'){
            printf("Sexo invalido, debe ser M o F");
        }
        else{
            sexo_valido = 1;
        }
    }

    printf("\nIngrese el DNI del cliente (sin puntos):");
    scanf(" %d",&nuevo_cliente.dni);

    printf("\nIngrese la direccion del cliente:");
    fgets(nuevo_cliente.direccion, sizeof(nuevo_cliente.direccion),stdin);
    getchar(); //De nuevo, "absorbo" el enter del input anterior
    nuevo_cliente.direccion[strcspn(nuevo_cliente.apellido,"\n")]='\0';
    convertirMayusculaMinuscula(nuevo_cliente.direccion);

    printf("\nIngrese telefono del cliente:");
    scanf("%s",nuevo_cliente.telefono);

    printf("\nIngrese el Email del cliente:");
    scanf("%s",nuevo_cliente.email);
    convertirEmailMinuscula(nuevo_cliente.email); //Verifica si el correo esta escrito en minuscula o mayuscula y hace la conversion a minuscula si esta en mayuscula

    // Llamada a la funcion para asignar un numero de cliente
    solicitarDeposito(&nuevo_cliente);

    //Verificamos si el cliente ya existe

    int posicion = buscarCliente(clientes, *num_clientes, nuevo_cliente);
    if (posicion != -1){
        printf("\n\t\t\t\tEl cliente ya esta registrado\n\n");
        return;
    }
    //Agregar el nuevo cliente a la lista
    clientes[*num_clientes] = nuevo_cliente;
    (*num_clientes)++;

    guardarClientesEnArchivo(nuevo_cliente);// Llama a la función para guardar el cliente en el archivo
    printf("\n\t\t\t\tEl cliente ha sido registrado con exito!!!\n\n");


}

//Funcion para guardar clientes dentro un archivo, esta funcion recibira como parametros al cliente  a guardar y el nombre del archivo.
void guardarClientesEnArchivo(clienteInfo cliente){

    FILE *archivo = fopen(CLIENTE_FILE,"a"); //Con "a" abre y crea un nuevo fichero
    if (archivo == NULL){
        printf("Ha ocurrido un error al intentar abrir el archivo.\n");
        return;
    }
    fprintf(
            archivo,
            "%s;%s;%c;%lf;%s;%s;%s;%d;%.2f\n",
            cliente.nombre,
            cliente.apellido,
            cliente.sexo,
            cliente.dni,
            cliente.direccion,
            cliente.telefono,
            cliente.email,
            cliente.cuenta_cliente.cuenta_cliente,
            cliente.cuenta_cliente.saldo
    );

    fclose(archivo);
}

//Funcion para leer y mostrar los clientes almacenados en el archivo.
void mostrarCliente() {
    FILE *archivo = fopen(CLIENTE_FILE,"r");
    if (archivo == NULL) {
        printf("Ha ocurrido un error al intentar abrir el archivo.\n");
        return;
    }

    clienteInfo cliente;
     while (fscanf(archivo, "%s;%s;%c;%lf;%s;%[^;];%[^;];%d;%lf\n", cliente.nombre, cliente.apellido, &cliente.sexo, &cliente.dni, cliente.direccion, cliente.telefono, cliente.email,&cliente.cuenta_cliente.cuenta_cliente, &cliente.cuenta_cliente.saldo) != EOF) {
        printf("Nombre: %s\n", cliente.nombre);
        printf("Apellido: %s\n", cliente.apellido);
        printf("Sexo: %c\n", cliente.sexo);
        printf("DNI: %.0lf\n", cliente.dni);
        printf("Dirección: %s\n", cliente.direccion);
        printf("Telefono: %s\n", cliente.telefono);
        printf("Email: %s\n", cliente.email);
        printf("Numero de cuenta: %d\n", cliente.cuenta_cliente.cuenta_cliente);
        printf("Saldo: %.2f\n", cliente.cuenta_cliente.saldo);
        printf("----------------------------\n");
    }
    fclose(archivo);
}



