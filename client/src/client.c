#include "client.h"
#include <readline/readline.h>

int main(void)
{
	/*---------------------------------------------------PARTE 2-------------------------------------------------------------*/

	int conexion;
	char* ip;
	char* puerto;
	char* valor;

	t_log* logger;
	t_config* config;

	/* ---------------- LOGGING ---------------- */

	/*logger = iniciar_logger();
	log_info(logger,"Soy un Log");
	terminar_programa(conexion, logger, config);*/
	// Usando el logger creado previamente
	// Escribi: "Hola! Soy un log"


	/* ---------------- ARCHIVOS DE CONFIGURACION ---------------- */

	logger = iniciar_logger();
	config = iniciar_config();
	/*if(config == NULL){
	log_info(logger,"No se encontro el archivo de config\n");
	terminar_programa(conexion,logger, config);
	}else{*/
	// Usando el config creado previamente, leemos los valores del config y los 
	// dejamos en las variables 'ip', 'puerto' y 'valor'
	ip = config_get_string_value(config,"IP");
	puerto = config_get_string_value(config,"PUERTO");
	valor = config_get_string_value(config,"CLAVE");

	// Loggeamos el valor de config
	//log_info(logger,valor);
	//log_info(logger,ip);
	//log_info(logger,puerto);
	
	/*}*/
	


	/* ---------------- LEER DE CONSOLA ---------------- */
	
	//logger = iniciar_logger();
	//leer_consola(logger);
	//terminar_programa(conexion, logger, config);
	/*---------------------------------------------------PARTE 3-------------------------------------------------------------*/

	// ADVERTENCIA: Antes de continuar, tenemos que asegurarnos que el servidor esté corriendo para poder conectarnos a él

	// Creamos una conexión hacia el servidor
	conexion = crear_conexion(ip, puerto);
	
	// Enviamos al servidor el valor de CLAVE como mensaje
	enviar_mensaje(valor,conexion);
	// Armamos y enviamos el paquete
	paquete(conexion);

	//terminar_programa(conexion,logger,config);

	printf("\nCliente cerrado\n");

	/*---------------------------------------------------PARTE 5-------------------------------------------------------------*/
	// Proximamente
}

t_log* iniciar_logger(void)
{
	t_log* nuevo_logger;

	if((nuevo_logger = log_create("tp0.log","LOG",true,LOG_LEVEL_INFO)) == NULL){
		printf("No se puede crear el logger\n");
		exit(1);
	}

	return nuevo_logger;
}

t_config* iniciar_config(void)
{
	t_config* nuevo_config;

	if((nuevo_config = config_create("cliente.config")) == NULL){
		printf("No se pudo encontrar la config\n");
		exit(2);
	}

	return nuevo_config;
}

void leer_consola(t_log* logger)
{
	char* leido;

	// La primera te la dejo de yapa
	//leido = readline("> ");
	while (strcmp(leido,"") != 0) {
		free(leido);
        leido = readline(">");
        log_info(logger, leido);
    }
	// El resto, las vamos leyendo y logueando hasta recibir un string vacío


	// ¡No te olvides de liberar las lineas antes de regresar!
	free(leido);
}

void paquete(int conexion)
{
	// Ahora toca lo divertido!
	char* leido = NULL;
	t_paquete* paquete = crear_paquete();

	// Leemos y esta vez agregamos las lineas al paquete
	leido = readline("> ");
	while(strcmp(leido, "") != 0){
		agregar_a_paquete(paquete,leido,strlen(leido) + 1);
		free(leido);
		leido = readline("> ");
	}

	// ¡No te olvides de liberar las líneas y el paquete antes de regresar!
	free(leido);

	enviar_paquete(paquete,conexion);

	eliminar_paquete(paquete);
}

void terminar_programa(int conexion, t_log* logger, t_config* config)
{
	/* Y por ultimo, hay que liberar lo que utilizamos (conexion, log y config) 
	  con las funciones de las commons y del TP mencionadas en el enunciado */
		if(logger != NULL){
		log_destroy(logger);
	  }
		if(config != NULL){
		config_destroy(config);
	  }
	  liberar_conexion(conexion);
}
