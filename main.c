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

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////      ZONA DE IMPORTS         ////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h> // Posee varias funciones que son útiles para probar y mapear caracteres.

#define MAX_CLIENTES 10 //Numero maximo de clientes que se pueden almacenar
#define MAX_CUENTAS 20 //Numero maximo de cuentas que puede tener cada cliente
#define MAX_MOVIMIENTOS 50//Numero maximo de movimientos
#define CLIENTE_FILE "clientes.dat" //Constante para el nombre del archivo en el que se guardaran los clientes.
#define CUENTAS_FILE "cuentas.dat" //Constante para el nombre del archivo en el que se guardaran las cuentas.
#define MOVIMIENTOS_FILE "movimientos.dat"

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////      ZONA DE STRUCTS         ////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


/* Estructura de Datos del Cliente*/
typedef struct{
    int cuenta_cliente;
    int dni_cliente;
    int saldo;
}cuenta;


/* Estructura de Datos del Cuenta*/
typedef struct
{
    char nombre[20];
    char apellido[20];
    char sexo;
    int dni;
    char direccion[30];
    int telefono;
    char email[50];
}clienteInfo;

typedef struct
{
    int nro_cuenta;
    float monto;
    char tipo; //Puede ser E o D
}movimientoInfo;


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////      VARIABLES GLOBALES      ////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

//Variables globales para la solicitud de la fecha
static int dia, mes, anio;

//Variable estatica que almacena el numero de cuenta y asigna un valor inicial de 0000
static int numero_cuenta = 0001;

static int numero_clientes = 0;

static int numero_cuentas = 0;

static int numero_movimientos = 0;

clienteInfo clientes[MAX_CLIENTES];

cuenta cuentas[MAX_CUENTAS];

movimientoInfo movimientos[MAX_MOVIMIENTOS];

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////      ZONA DE PROTOTIPOS      ////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/*Prototipo de las Funciones*/
void cargarDatos(); //Funcion inicial que busca cuentas, clientes y movimientos en disco y los carga en memoria
void menu();
void solicitarDeposito(cuenta *cuenta);
void registrarCliente();
void registrarMovimiento(int nro_cuenta, float monto, char tipo_movimiento);
int buscarCliente(clienteInfo cliente_buscado);
void convertirMayusculaMinuscula(char* cadena);
void convertirEmailMinuscula(char *cadena);
void solicitudFecha( int *dia, int *mes, int *anio);
void guardarClientesEnArchivo(clienteInfo cliente);
void guardarCuentasEnArchivo(cuenta cuentaCliente);
void guardarMovimientosEnArchivo(movimientoInfo movimiento);
void mostrarCliente();

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////      ZONA DE MAIN            ////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/*Funcion principal Main*/
int main()
{
    //Cargo en memoria los datos que tenga guardados en disco
    cargarDatos();

    // Solicitud de ingreso de fecha
    solicitudFecha( &dia, &mes, &anio);

    while(1){

        menu();

        // Leer la opcion seleccionada por el usuario Menu
        int opcion;
        printf("\nIngrese una opcion: ");
        scanf("%i",&opcion);
        getchar(); //Esto te "absorbe" el enter con el que ingresaste el numero de opcion en la linea de arriba

        switch(opcion)
    {
        case 1:
            registrarCliente();
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
////////////////////////////////////////    FUNCIONES INICIALES     //////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

//Funcion que carga datos de disco a memoria
void cargarDatos(){

    FILE *archivo_clientes = fopen(CLIENTE_FILE,"rb");
    if (archivo_clientes == NULL) {
        //Si no encuentro el archivo, no pasa nada. Podria ser por ejemplo la primera vez que abre el banco.
        printf("No se encontro el archivo de clientes\n");
    }

    for ( int i = 0; i < MAX_CLIENTES; i++){
        if (fread(&clientes[i], sizeof(clienteInfo),1,archivo_clientes)!=1)
            break;

        numero_clientes++;

    }
    if (numero_clientes > 0){
        printf("Cargado el archivo de clientes\n");
    }
    fclose(archivo_clientes);

    FILE *archivo_cuentas = fopen(CUENTAS_FILE,"rb");
    if (archivo_cuentas == NULL) {
        //Si no encuentro el archivo, no pasa nada. Podria ser por ejemplo la primera vez que abre el banco.
        printf("No se encontro el archivo de cuentas\n");
    }

    for ( int i = 0; i < MAX_CUENTAS; i++){
        if (fread(&cuentas[i], sizeof(cuenta),1,archivo_cuentas)!=1)
            break;

        numero_cuentas++;
    }
    if (numero_cuentas > 0){
        printf("Cargado el archivo de cuentas\n");
    }
    fclose(archivo_cuentas);

    FILE *archivo_movimientos = fopen(MOVIMIENTOS_FILE,"rb");
    if (archivo_movimientos == NULL) {
        //Si no encuentro el archivo, no pasa nada. Podria ser por ejemplo la primera vez que abre el banco.
        printf("No se encontro el archivo de movimientos\n");
    }

    for ( int i = 0; i < MAX_MOVIMIENTOS; i++){
        if (fread(&movimientos[i], sizeof(movimientoInfo),1,archivo_movimientos)!=1)
            break;

        numero_movimientos++;
    }
    if (numero_movimientos > 0){
        printf("Cargado el archivo de movimientos\n");
    }
    fclose(archivo_movimientos);

    return;
}

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

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////        FUNCIONES DE CREACION DE CLIENTES Y CUENTAS    //////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

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
int buscarCliente(clienteInfo cliente_buscado){

    int i;
    for (i=0; i < numero_clientes;i++){
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

void guardarMovimientosEnArchivo(movimientoInfo movimiento){
    FILE *archivo = fopen(MOVIMIENTOS_FILE,"ab"); //Con "a" abre y crea un nuevo fichero
    if (archivo == NULL){
        printf("Ha ocurrido un error al intentar abrir el archivo.\n");
        return;
    }
    fwrite(&movimiento.nro_cuenta , sizeof(&movimiento.nro_cuenta), 1, archivo);
    fwrite(&movimiento.monto, sizeof(&movimiento.monto), 1, archivo);
    fwrite(&movimiento.tipo, sizeof(&movimiento.tipo), 1, archivo);

    fclose(archivo);
}

void registrarMovimiento(int nro_cuenta, float monto, char tipo_movimiento){
    movimientoInfo nuevo_movimiento;

    nuevo_movimiento.nro_cuenta = nro_cuenta;
    nuevo_movimiento.monto = monto;
    nuevo_movimiento.tipo = tipo_movimiento;

    movimientos[numero_movimientos] = nuevo_movimiento;
    numero_movimientos++;

    guardarMovimientosEnArchivo(nuevo_movimiento);

}

/*Funcion para realizar Depositos de dinero.*/
//En esta funcion, se pasa un puntero al cliente para poder modificar directamente la cuenta del cliente
void solicitarDeposito(cuenta *cuenta){

    printf("\nIngrese el monto del deposito realizado por el cliente:");
    int monto = 0;
    scanf("%i", &monto);
    cuenta->saldo += monto;

    registrarMovimiento(cuenta->cuenta_cliente, monto, "D");

}

/*Funcion Cliente con informacion del Cliente*/
void registrarCliente(){
    //Verificamos si se ha alcanzado el numero maximo de clientes

    if (numero_clientes == MAX_CLIENTES){
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
        scanf("%c",&nuevo_cliente.sexo);
        if (nuevo_cliente.sexo != 'M' && nuevo_cliente.sexo != 'F'){
            printf("Sexo invalido, debe ser M o F");
        }
        else{
            sexo_valido = 1;
        }
    }
    getchar(); //De nuevo, "absorbo" el enter del input anterior

    printf("\nIngrese el DNI del cliente (sin puntos):");
    scanf("%i",&nuevo_cliente.dni);
    getchar(); //De nuevo, "absorbo" el enter del input anterior

    printf("\nIngrese la direccion del cliente (%i caracteres maximo):", sizeof(nuevo_cliente.direccion));
    fgets(nuevo_cliente.direccion, sizeof(nuevo_cliente.direccion),stdin);
    nuevo_cliente.direccion[strcspn(nuevo_cliente.direccion,"\n")]='\0';
    convertirMayusculaMinuscula(nuevo_cliente.direccion);

    printf("\nIngrese telefono del cliente:");
    scanf("%i",&nuevo_cliente.telefono);
    getchar(); //De nuevo, "absorbo" el enter del input anterior

    printf("\nIngrese el Email del cliente:");
    fgets(nuevo_cliente.email, sizeof(nuevo_cliente.email),stdin);
    nuevo_cliente.email[strcspn(nuevo_cliente.email,"\n")]='\0';
    convertirEmailMinuscula(nuevo_cliente.email); //Verifica si el correo esta escrito en minuscula o mayuscula y hace la conversion a minuscula si esta en mayuscula

    //Verificamos si el cliente ya existe
    int posicion = buscarCliente(nuevo_cliente);
    if (posicion == -1){
        //Agregar el nuevo cliente a la lista
        clientes[numero_clientes] = nuevo_cliente;
        numero_clientes++;

        guardarClientesEnArchivo(nuevo_cliente);// Llama a la función para guardar el cliente en el archivo
        printf("\n\t\t\t\tEl cliente ha sido registrado con exito!!!\n\n");
    }
    else {
        printf("\n\t\t\t\tEl cliente ya esta registrado\n\n");
    }

    //Ahora seguimos con la cuenta
    cuenta nueva_cuenta;
    nueva_cuenta.cuenta_cliente = numero_cuenta;
    nueva_cuenta.dni_cliente = nuevo_cliente.dni;
    nueva_cuenta.saldo = 0;

    //Aumento el nro de cuenta
    numero_cuenta++; //Incrementa el numero de cuenta para el siguiente cliente

    //Pido al cliente hacer un deposito
    solicitarDeposito(&nueva_cuenta);

    //Me guardo la cuenta en la lista de cuentas
    cuentas[numero_cuentas] = nueva_cuenta;
    numero_cuentas++;

    //Guardo la cuenta en disco
    guardarCuentasEnArchivo(nueva_cuenta);




}

//Funcion para guardar cuentas dentro un archivo, esta funcion recibira como parametros a la cuenta  a guardar y el nombre del archivo.
void guardarCuentasEnArchivo(cuenta cuenta_cliente){
    FILE *archivo = fopen(CUENTAS_FILE,"ab"); //Con "a" abre y crea un nuevo fichero
    if (archivo == NULL){
        printf("Ha ocurrido un error al intentar abrir el archivo.\n");
        return;
    }
    fwrite(&cuenta_cliente.cuenta_cliente, sizeof(&cuenta_cliente.cuenta_cliente), 1, archivo);
    fwrite(&cuenta_cliente.dni_cliente, sizeof(&cuenta_cliente.dni_cliente), 1, archivo);
    fwrite(&cuenta_cliente.saldo, sizeof(&cuenta_cliente.saldo), 1, archivo);

    fclose(archivo);
}

//Funcion para guardar clientes dentro un archivo, esta funcion recibira como parametros al cliente  a guardar y el nombre del archivo.
void guardarClientesEnArchivo(clienteInfo cliente){

    FILE *archivo = fopen(CLIENTE_FILE,"ab"); //Con "a" abre y crea un nuevo fichero
    if (archivo == NULL){
        printf("Ha ocurrido un error al intentar abrir el archivo.\n");
        return;
    }
    fwrite(&cliente.nombre , sizeof(&cliente.nombre), 1, archivo);
    fwrite(&cliente.apellido, sizeof(&cliente.apellido), 1, archivo);
    fwrite(&cliente.sexo, sizeof(&cliente.sexo), 1, archivo);
    fwrite(&cliente.dni , sizeof(&cliente.dni), 1, archivo);
    fwrite(&cliente.direccion, sizeof(&cliente.direccion), 1, archivo);
    fwrite(&cliente.telefono, sizeof(&cliente.telefono), 1, archivo);
    fwrite(&cliente.email, sizeof(&cliente.email), 1, archivo);

    fclose(archivo);
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////        FUNCIONES DE MOSTRAR CLIENTES    //////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

//Funcion para leer y mostrar los clientes almacenados en el archivo.
void mostrarCliente() {

    int minimo;
    int maximo;

    printf("\nIngrese el saldo minimo de la cuenta a buscar:");
    scanf("%i",&minimo);
    getchar();

    printf("\nIngrese el saldo maximo de la cuenta a buscar:");
    scanf("%i",&maximo);
    getchar();

    int hay_resultados = 0;

    for (int x=0; x < numero_clientes; x++){
        for (int y=0; y < numero_cuentas; y++){
            if (cuentas[y].dni_cliente == clientes[x].dni){
                if(cuentas[y].saldo >= minimo && cuentas[y].saldo <= maximo){
                    hay_resultados = 1;
                    printf("\nNombre: %s\n",clientes[x].nombre);
                    printf("Apellido: %s\n",clientes[x].apellido);
                    printf("DNI: %i\n",clientes[x].dni);
                    printf("Numero de cuenta: %i\n",cuentas[y].cuenta_cliente);
                    printf("Saldo: %i\n",cuentas[y].saldo);
                    printf("----------------------------\n");
                }
            }
        }
    }

    if (! hay_resultados){
        printf("\nNo se encontraron resultados para los parametros especificados\n");
    }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////    FUNCIONES PARA ACTUALIZAR ARCHIVOS    ////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void actualizarArchivoClientes(int linea_a_actualizar, clienteInfo cliente_actualizado){
    FILE *archivo = fopen(CLIENTE_FILE,"rb");
    if (archivo == NULL) {
        printf("No se encontro el archivo de clientes a actualizar\n");
        return;
    }

    //Me desplazo en el archivo hasta el cliente que tengo que actualizar
    int bytes_desplazamiento = linea_a_actualizar * sizeof(cliente_actualizado);
    fseek(archivo, (float)bytes_desplazamiento, SEEK_SET);

    //Piso el cliente viejo con el nuevo
    fwrite(&cliente_actualizado.nombre , sizeof(&cliente_actualizado.nombre), 1, archivo);
    fwrite(&cliente_actualizado.apellido, sizeof(&cliente_actualizado.apellido), 1, archivo);
    fwrite(&cliente_actualizado.sexo, sizeof(&cliente_actualizado.sexo), 1, archivo);
    fwrite(&cliente_actualizado.dni , sizeof(&cliente_actualizado.dni), 1, archivo);
    fwrite(&cliente_actualizado.direccion, sizeof(&cliente_actualizado.direccion), 1, archivo);
    fwrite(&cliente_actualizado.telefono, sizeof(&cliente_actualizado.telefono), 1, archivo);
    fwrite(&cliente_actualizado.email, sizeof(&cliente_actualizado.email), 1, archivo);

    fclose(archivo);

}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////    FUNCIONES DEPRECADAS    //////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

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
