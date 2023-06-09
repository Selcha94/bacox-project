//Lista de pendientes
// permitir modificar el importe o finalizar la operación en EXTRACCION
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
    int monto;
    char tipo; //Puede ser E o D
    int dia;
    int mes;
    int anio;
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
void registrarMovimiento(int nro_cuenta, int monto, char tipo_movimiento);
int buscarCliente(clienteInfo cliente_buscado);
void convertirMayusculaMinuscula(char* cadena);
void convertirEmailMinuscula(char *cadena);
void solicitudFecha( int *dia, int *mes, int *anio);
int verificarFecha(char *char_dia, char *char_mes, char *char_anio, int *int_dia, int *int_mes, int *int_anio);
void guardarClientesEnArchivo(clienteInfo cliente);
void guardarCuentasEnArchivo(cuenta cuentaCliente);
void guardarMovimientosEnArchivo(movimientoInfo movimiento);
void mostrarCliente();
void realizarExtraccion();
void realizarDeposito();
void eliminarCuenta();
void listaClientes();
void listadoMovimientos();

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
        char input[1];//Vairable para almacenar el input del usuario
        printf("\nIngrese una opcion: ");
        scanf("%s",input);

        //Valida que la opcion ingresada sea un numero
        int es_numero = 1;
        for(int i=0; input[i] !='\0';i++){
            if(!isdigit(input[i])){
                es_numero = 0;
                break;
            }
        }
        if(es_numero){
            opcion = atoi(input); //convierte el input en entero
            getchar(); //absorbe el salto de linea
            switch(opcion) {
        case 1:
            registrarCliente();
            break;
        case 2:
            eliminarCuenta();
            break;
        case 3:
            mostrarCliente();
            break;
        case 4:
            realizarExtraccion();
            break;
        case 5:
            realizarDeposito();
            break;
        case 6:
            listadoMovimientos();
            break;
        case 7:
            listaClientes();
            break;
        case 8:
            printf("\nSaliendo del programa...\n");
            return 0;
        default:
            printf("\n");
            printf("\t\t\tVuelva a intentarlo e ingrese una opcion valida.\n");
            break;
        }
    }else{
        printf("\n");
        printf("\nLa opcion ingresada es incorrecta, recuerde ingresar un numero dentro de las opcion especificadas.\n");
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

        numero_cuenta++;
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
    printf("\t7. Listado de clientes.\n");
    printf("\t8. Salir\n");

}

// Funcion para solicitar fecha
void solicitudFecha( int *diaSolicitud, int *mesSolicitud, int *anioSolicitud){

    // dia_ingresado, mes_ingresado, anio_ingresado;
    int fecha_valida = 0;

    char char_dia[3];
    char char_mes[3];
    char char_anio[5];

    while (!fecha_valida){

        printf("\nIngrese el dia de la fecha correspondiente:");
        fgets(char_dia, sizeof(char_dia),stdin);
        getchar();

        printf("\nIngrese el mes de la fecha correspondiente:");
        fgets(char_mes, sizeof(char_mes),stdin);
        getchar();

        printf("\nIngrese el anio de la fecha correspondiente:");
        fgets(char_anio, sizeof(char_anio),stdin);
        getchar();

        fecha_valida = verificarFecha(char_dia,char_mes,char_anio,diaSolicitud, mesSolicitud, anioSolicitud);
        if(!fecha_valida){
            printf("\nLa fecha ingresada es invalida. Intentelo nuevamente.\n");
        }
    }

    *diaSolicitud = atoi(char_dia);
    *mesSolicitud = atoi(char_mes);
    *anioSolicitud = atoi(char_anio);

    printf("========================================================================================\n");
    printf("\n");
    printf("\t\t\t\t La fecha ingresada es: %02d/%02d/%d \n\n ", *diaSolicitud, *mesSolicitud, *anioSolicitud);

}
int verificarFecha(char *char_dia, char *char_mes, char *char_anio, int *int_dia, int *int_mes, int *int_anio){

    //Verificar si el año es valido
    if(!validarNumeros(char_anio)){
        printf("\nAnio invalido.Recuerde ingresar solo numeros.\n");

    }
    else{
        *int_anio = atoi(char_anio);
    }

    if(*int_anio < 1900 || *int_anio > 2100){
        printf("\nEl anio ingresado es invalido\n");
        return 0;
    }

    //Verificar si el mes es valido
    if(!validarNumeros(char_mes)){
        printf("\nMes invalido. Recuerde ingresar solo numeros.\n");
        return 0;
    }
    else{
        *int_mes = atoi(char_mes);
    }

    if(*int_mes < 1 || *int_mes > 12){
        printf("\nEl mes ingresado es invalido, recuerde ingresar un mes del 1 al 12\n");
        return 0; //mes invalido
    }
    //Valida si el dia es valido
    if(!validarNumeros(char_dia)){
        printf("\nDia invalido. Recuerde ingresar solo numeros.\n");
        return 0;
    }
    else{
        *int_dia = atoi(char_dia);
    }

    int dias;

    switch(*int_mes){
        case 2: //febrero
        //Verifica si es un año bisiesto
        if((*int_anio % 4 == 0 && *int_anio % 100 != 0) || *int_anio % 400 == 0 ){
            dias = 29;
        }else{
            dias = 28;
        }
        break;

        case 4://abril
        case 6://Junio
        case 9://Septiembre
        case 11:// Noviembre
            dias = 30;
            break;
        default: //Meses con 31 dias
            dias = 31;
        break;
    }
    if (*int_dia < 1 || *int_dia > dias){
        printf("\nEl dia ingresado esta por fuera del rango permitido del mes.\n");
        return 0; //Dia invalido
    }
    return 1; //Fecha valida
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

int validarEmail(char *cadena){
    int i;

    for (i=0; cadena[i]; i++){
        if (cadena[i] == '@')   {
            return 1;
        }
    }

    printf("\nRecuerde ingresar el @ dentro del campo del email.\n");
    return 0;

}

//Funcion que verifica que haya un arroba dentro del campo de email y despues hace la conversion a minuscula
void convertirEmailMinuscula(char *cadena){
    for (int i=0; cadena[i]; i++)   {
        cadena[i] =tolower(cadena[i]); //tolower funcion dentro de la libreria ctype.h para convertir en minuscula la cadena
    }
}

//Funcion para  validar los campos de nombre,apellido y direccion para que solo se ingresen letras
//Recibe una cadena de caracteres y verifica si todos los caracteres son letras o espacios con la funcion isalpha()
int validarLetra(const char *cadena){
    int i;
    for(i=0; cadena[i] != '\0'; i++){
        if(!isalpha(cadena[i]) && cadena[i] !=' '){ //isalpha funcion de la biblioteca ctype.h
            return 0; //Si se encuentra algun caracter no valido, retorna falso
            }
    }
    return 1; //Si los caracteres ingresados son un espacio o letras, retorna verdadero
}

//Funcion para validar los campos para que solo se ingresen numeros
//Toma una cadena como argumento y verifica que todos los caracteres ingresados sean numeros con la funcion isdigit
int validarNumeros(const char *cadena) {
    int i;
    for(i=0;cadena[i] != '\0';i++){
        if (!isdigit(cadena[i])){ //isdigit es una funcion de la biblioteca ctype.h
            return 0; //La cadena contiene otros caracteres que no son numeros
        }
    }
    return 1; //La cadena contiene numeros
}


//Funcion para buscar clientes en el arreglo de clientes
int buscarCliente(clienteInfo cliente_buscado){

    int i;
    for (i=0; i < numero_clientes;i++){
        if (
            strcmp(clientes[i].nombre, cliente_buscado.nombre) == 0 &&
            strcmp(clientes[i].apellido, cliente_buscado.apellido) == 0 &&
            clientes[i].sexo == cliente_buscado.sexo &&
            clientes[i].dni == cliente_buscado.dni &&
            strcmp(clientes[i].direccion, cliente_buscado.direccion) == 0 &&
            clientes[i].telefono == cliente_buscado.telefono &&
            strcmp(clientes[i].email, cliente_buscado.email) == 0
        ){
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

    fwrite(&movimiento , sizeof(movimientoInfo), 1, archivo);

    fclose(archivo);
}

void registrarMovimiento(int nro_cuenta, int monto, char tipo_movimiento){
    movimientoInfo nuevo_movimiento;

    nuevo_movimiento.nro_cuenta = nro_cuenta;
    nuevo_movimiento.monto = monto;
    nuevo_movimiento.tipo = tipo_movimiento;
    nuevo_movimiento.dia = dia;
    nuevo_movimiento.mes = mes;
    nuevo_movimiento.anio = anio;

    movimientos[numero_movimientos] = nuevo_movimiento;
    numero_movimientos++;

    guardarMovimientosEnArchivo(nuevo_movimiento);

}

/*Funcion para realizar Depositos de dinero.*/
//En esta funcion, se pasa un puntero al cliente para poder modificar directamente la cuenta del cliente
void solicitarDeposito(cuenta *cuenta){

    int monto = 0;
    int monto_valido = 0;

    while (!monto_valido){
        printf("\nIngrese el monto del deposito realizado por el cliente:");
        scanf("%i", &monto);
        if (monto > 0){
            monto_valido = 1;
            cuenta->saldo += monto;
        }
        else{
            printf("\nMonto del deposito debe ser mayor a cero\n");
        }
    }

    registrarMovimiento(cuenta->cuenta_cliente, monto, 'D');

}

/*Funcion para realizar Extracciones de dinero.*/
//En esta funcion, se pasa un puntero al cliente para poder modificar directamente la cuenta del cliente
void solicitarExtraccion(cuenta *cuenta){

    printf("\nIngrese el monto a extraer de la cuenta:");
    int monto = 0;
    scanf("%i", &monto);

    if (cuenta->saldo < monto){
        printf("\nSaldo Insuficiente\n");
        return;
    }
    cuenta->saldo -= monto;

    registrarMovimiento(cuenta->cuenta_cliente, monto, 'E');
    return;
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

    int nombre_valido = 0;
    while(!nombre_valido){
        printf("\nIngrese el Nombre del cliente (%i caracteres maximo):", sizeof(nuevo_cliente.nombre));
        fgets(nuevo_cliente.nombre, sizeof(nuevo_cliente.nombre),stdin);
        nuevo_cliente.nombre[strcspn(nuevo_cliente.nombre, "\n")] = '\0';//Elimina el caracter del '\n' despues de leerlo
        if (!validarLetra(nuevo_cliente.nombre)){
            printf("\nNombre invalido.Recuerde ingresar solo letras y espacios.\n");
        }else{
            nombre_valido = 1;
        }
    }
    convertirMayusculaMinuscula(nuevo_cliente.nombre); //Verifica si la primera letra esta en mayuscula y sino lo esta la convertieen mayuscula

    int apellido_valido = 0;
    while(!apellido_valido){
        printf("\nIngrese el Apellido del cliente (%i caracteres apellido):", sizeof(nuevo_cliente.apellido));
        fgets(nuevo_cliente.apellido, sizeof(nuevo_cliente.apellido),stdin);
        nuevo_cliente.apellido[strcspn(nuevo_cliente.apellido, "\n")] = '\0';
        if (!validarLetra(nuevo_cliente.apellido)){
            printf("\nApellido invalido.Recuerde ingresar solo letras y espacios.\n");
        }else{
            apellido_valido = 1;
        }
    }
    convertirMayusculaMinuscula(nuevo_cliente.apellido);

    int sexo_valido = 0;
    while (! sexo_valido){
        printf("\nIngrese el sexo (M o F):");
        scanf("%c",&nuevo_cliente.sexo);
        if (nuevo_cliente.sexo != 'M' && nuevo_cliente.sexo != 'F'){
            printf("\n\tSexo invalido, debe ser M o F\n");
        }
        else{
            sexo_valido = 1;
        }
    }
    getchar(); //De nuevo, "absorbo" el enter del input anterior

    int dni_valido = 0;
    while(!dni_valido){
        char dni_char[9]; //Ponemos 9 en vez de 8 para contemplar el \n
        printf("\nIngrese el DNI del cliente (ocho numeros sin puntos):");
        fgets(dni_char, sizeof(dni_char),stdin);
        if(!validarNumeros(dni_char)){
            printf("\nDNI invalido. Recuerde ingresar solo numeros, sin puntos.\n");
        }else{
            dni_valido = 1;
            dni_char[strcspn(dni_char, "\n")] = '\0';
            nuevo_cliente.dni = atoi(dni_char);
            getchar();
        }
    }
    getchar();

    printf("\nIngrese la direccion del cliente (%i caracteres maximo):", sizeof(nuevo_cliente.direccion));
    fgets(nuevo_cliente.direccion, sizeof(nuevo_cliente.direccion),stdin);
    nuevo_cliente.direccion[strcspn(nuevo_cliente.direccion,"\n")]='\0';
    convertirMayusculaMinuscula(nuevo_cliente.direccion);

    int telefono_valido = 0;
    while(!telefono_valido){
        char telefono_char[9]; //Ponemos 9 en vez de 8 para contemplar el \n
        printf("\nIngrese telefono del cliente (8 digitos, sin 0 ni 15):");
        fgets(telefono_char, sizeof(telefono_char), stdin);
        if(!validarNumeros(telefono_char)){
            printf("\nTelefono invalido. Recuerde ingresar solo numeros, sin 0 ni 15.\n");
        }else{
            telefono_valido = 1;
            telefono_char[strcspn(telefono_char, "\n")] = '\0';
            nuevo_cliente.telefono = atoi(telefono_char);
            getchar();
        }
    }
    getchar();

    int emailValido = 0;
    while (!emailValido){
        printf("\nIngrese el Email del cliente:");
        fgets(nuevo_cliente.email, sizeof(nuevo_cliente.email),stdin);
        nuevo_cliente.email[strcspn(nuevo_cliente.email,"\n")]='\0';
        emailValido = validarEmail(nuevo_cliente.email);
    }
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

    fwrite(&cuenta_cliente, sizeof(cuenta), 1, archivo);

    fclose(archivo);
}

//Funcion para guardar clientes dentro un archivo, esta funcion recibira como parametros al cliente  a guardar y el nombre del archivo.
void guardarClientesEnArchivo(clienteInfo cliente){

    FILE *archivo = fopen(CLIENTE_FILE,"ab"); //Con "a" abre y crea un nuevo fichero
    if (archivo == NULL){
        printf("Ha ocurrido un error al intentar abrir el archivo.\n");
        return;
    }

    fwrite(&cliente , sizeof(clienteInfo), 1, archivo);

    fclose(archivo);
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////        FUNCIONES DE ELIMINAR CUENTA    ///////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void eliminarCuenta(){

    printf("\nIngrese el numero de la cuenta:");
    int nro_cuenta_a_eliminar = 0;
    scanf("%i", &nro_cuenta_a_eliminar);

    //Esta variable me va a servir para saber si la cuenta que elimino es la unica que el cliente tenia
    int dni_cliente_cuenta = 0;

    for (int i=0; i < numero_cuentas; i++){

        if (cuentas[i].cuenta_cliente == nro_cuenta_a_eliminar ){

            if (cuentas[i].saldo > 0){
                printf("\nLa cuenta tiene saldo mayor a cero, no se puede eliminar.\n");
                return;
            }

            dni_cliente_cuenta = cuentas[i].dni_cliente;

            //La posicion en donde esta la cuenta a eliminar la piso con la ultima cuenta
            cuentas[i] = cuentas[numero_cuentas - 1];

            //Y la posicion de la ultima cuenta la piso con una cuenta vacia
            cuenta cuenta_vacia;
            cuentas[numero_cuentas - 1] = cuenta_vacia;

            //Actualizo en el archivo las dos cuentas modificadas
            actualizarArchivoCuentas(i, cuentas[i]);
            actualizarArchivoCuentas(numero_cuentas - 1, cuenta_vacia);

            //Bajo en uno el numero de cuentas
            numero_cuentas--;
            printf("\nCuenta eliminada con exito\n");

            //Vuelvo a recorrer una vez mas el listado de cuentas para saber si al cliente le queda otra cuenta
            for (int i=0; i < numero_cuentas; i++){

                if (cuentas[i].dni_cliente == dni_cliente_cuenta ){
                    //Al cliente le queda otra cuenta, no lo elimino
                    return;
                }

            }

            //Si llego aca es porque al cliente no le quedan mas cuentas, lo elimino.
            for (int i=0; i < numero_clientes; i++){

                if(clientes[i].dni == dni_cliente_cuenta){

                    //Misma logica que hice arriba para eliminar cuenta
                    clientes[i] = clientes[numero_clientes - 1];
                    clienteInfo clienteVacio;
                    clientes[numero_clientes - 1] = clienteVacio;

                    //Actualizo en el archivo las dos cuentas modificadas
                    actualizarArchivoClientes(i, clientes[i]);
                    actualizarArchivoClientes(numero_clientes - 1, clienteVacio);

                    //Bajo en uno el numero de clientes
                    numero_clientes--;
                    printf("\nCliente eliminado con exito\n");
                    break;
                }

            }

            return;

        }
    }

    printf("\nNo existe ninguna cuenta para el numero ingresado\n");
    return;

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
///////////////////////////////////        FUNCIONES DE REALIZAR EXTRACCION    ///////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void realizarExtraccion(){

    printf("\nIngrese el numero de la cuenta:");
    int nro_cuenta_extraccion = 0;
    scanf("%i", &nro_cuenta_extraccion);

    for (int i=0; i < numero_cuentas; i++){
        if (cuentas[i].cuenta_cliente == nro_cuenta_extraccion ){
            cuentas[i];

            solicitarExtraccion(&cuentas[i]);
            actualizarArchivoCuentas(i, cuentas[i]); //Le paso linea del archivo a actualizar y los datos actualizados de cuenta
            return;
        }
    }
    printf("\nNo existe ninguna cuenta para el numero ingresado\n");
    return;

}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////        FUNCIONES DE REALIZAR DEPOSITO      ///////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void realizarDeposito(){

    printf("\nIngrese el numero de la cuenta:");
    int nro_cuenta_deposito = 0;
    scanf("%i", &nro_cuenta_deposito);

    for (int i=0; i < numero_cuentas; i++){
        if (cuentas[i].cuenta_cliente == nro_cuenta_deposito ){
            cuentas[i];

            solicitarDeposito(&cuentas[i]);
            actualizarArchivoCuentas(i, cuentas[i]); //Le paso linea del archivo a actualizar y los datos actualizados de cuenta
            return;
        }
    }
    printf("\nNo existe ninguna cuenta para el numero ingresado");
    return;

}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////        FUNCIONES DE LISTA MOVIMIENTOS    ////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void listadoMovimientos(){

    FILE *archivo;
    archivo = fopen("movimientosListado.txt","a");

    if (archivo == NULL) {
        printf("No se pudo crear el archivo.\n");
        return 1;
    }

    int dia_movimiento;
    int mes_movimiento;
    int anio_movimiento;
    int contador_deposito = 0;
    int contador_extraccion = 0;

    int hay_resultados = 0;

    // Solicitud de ingreso de fecha
    solicitudFecha(&dia_movimiento,&mes_movimiento,&anio_movimiento);
    for(int i=0;i < numero_movimientos;i++){

        if(movimientos[i].dia == dia_movimiento && movimientos[i].mes == mes_movimiento && movimientos[i].anio == anio_movimiento){

            hay_resultados = 1;

            fprintf(archivo,"Tipo: %c\n", movimientos[i].tipo);
            fprintf(archivo,"Cuenta: %i\n", movimientos[i].nro_cuenta);
            fprintf(archivo,"Monto: %d\n", movimientos[i].monto);
            fprintf(archivo,"Dia: %i\n",movimientos[i].dia);
            fprintf(archivo,"Mes: %i\n",movimientos[i].mes);
            fprintf(archivo,"Anio: %i\n",movimientos[i].anio);
            fprintf(archivo,"----------------------------\n");

            if(movimientos[i].tipo == 'D'){
                contador_deposito += movimientos[i].monto;
            }else{
                contador_extraccion += movimientos[i].monto;
            }
        }
    }

    if (!hay_resultados){
        fprintf(archivo,"\nNo se encontraron resultados\n");
    }else{
        fprintf(archivo,"\nTotal deposito: %i\n",contador_deposito);
        fprintf(archivo,"\nTotal extraccion: %i\n", contador_extraccion);
        fprintf(archivo,"\nLa diferencia es: %i\n", contador_deposito-contador_extraccion);

    }
    fclose(archivo);

}


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////        FUNCIONES DE LISTA CLIENTES      ////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

//Esta funcion devuelve la lista de datos de cada cliente, sin ningun filtro
void listaClientes(){

    if (numero_clientes == 0){
        printf("\nNo hay clientes que mostrar\n");
        return;
    }

    for (int x=0; x < numero_clientes; x++){

        printf("\nNombre: %s\n",clientes[x].nombre);
        printf("Apellido: %s\n",clientes[x].apellido);
        printf("SEXO: %c\n",clientes[x].sexo);
        printf("DNI: %i\n",clientes[x].dni);
        printf("Direccion: %s\n",clientes[x].direccion);
        printf("Telefono: %i\n",clientes[x].telefono);
        printf("Email: %s\n",clientes[x].email);
        printf("----------------------------\n");
    }

}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////    FUNCIONES PARA ACTUALIZAR ARCHIVOS    ////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void actualizarArchivoClientes(int linea_a_actualizar, clienteInfo cliente_actualizado){
    FILE *archivo = fopen(CLIENTE_FILE,"rb+");
    if (archivo == NULL) {
        printf("No se encontro el archivo de clientes a actualizar\n");
        return;
    }

    //Me desplazo en el archivo hasta el cliente que tengo que actualizar
    int bytes_desplazamiento = linea_a_actualizar * sizeof(cliente_actualizado);
    fseek(archivo, (float)bytes_desplazamiento, SEEK_SET);

    //Piso el cliente viejo con el nuevo
    fwrite(&cliente_actualizado , sizeof(clienteInfo), 1, archivo);

    //No se si hace falta, pero por las dudas vuelvo a poner el cursor al final del archivo
    bytes_desplazamiento = numero_clientes * sizeof(clienteInfo);
    fseek(archivo, (float)bytes_desplazamiento, SEEK_SET);
    fclose(archivo);

}

void actualizarArchivoCuentas(int linea_a_actualizar, cuenta cuenta_actualizada){
    FILE *archivo = fopen(CUENTAS_FILE,"rb+");
    if (archivo == NULL) {
        printf("No se encontro el archivo de cuentas a actualizar\n");
        return;
    }

    //Me desplazo en el archivo hasta la cuenta que tengo que actualizar
    int bytes_desplazamiento = linea_a_actualizar * sizeof(cuenta);
    fseek(archivo, (float)bytes_desplazamiento, SEEK_SET);

    //Piso la cuenta vieja con la nueva
    fwrite(&cuenta_actualizada , sizeof(cuenta), 1, archivo);

    //No se si hace falta, pero por las dudas vuelvo a poner el cursor al final del archivo
    bytes_desplazamiento = numero_cuentas * sizeof(cuenta);
    fseek(archivo, (float)bytes_desplazamiento, SEEK_SET);
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
