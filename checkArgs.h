#ifndef _CHECKARGS_H_
#define _CHECKARGS_H_

extern char *optarg;
extern int optind, opterr, optopt;

class checkArgs {
private:
	// 1) Modificar esta sección
	const std::string optString = "s:p:d:h";
	
	const std::string opciones = "-s www_server -p puerto_tcp -o archivo [-h]";

	const std::string descripcion  = "Descripción:\n"
		                             "\t-s  IP o nombre del servidor web\n"
									 "\t-p  Puerto TCP de conexión del servidor\n"
									 "\t-o  Archivo de salida\n"
									 
	
	typedef struct args_t{
		std::string SERVER;
		uint16_t    PORT;
		std::string ARCHIVO;
	} args_t;
	
	// 2) Modificar constructor
	// 3) Modificar ciclo "getopt" en método checkArgs::getArgs()
	// 4) Recuerde que para compilar nuevamente, y por tratarse
	//    de un archivo header, debe hacer primero un make clean
	
	args_t  parametros;
	
	int argc;
	char **argv;

	
public:
	checkArgs(int _argc , char **_argv);
	~checkArgs();
	args_t getArgs();;
	
private:
	void printUsage();
	
	
};

checkArgs::checkArgs(int _argc , char **_argv){
	parametros.SERVER = "";
	parametros.PORT   = 0;
	parametros.ARCHIVO   = "";
	
	argc = _argc;
	argv = _argv;
	
}

checkArgs::~checkArgs(){
	
}

checkArgs::args_t checkArgs::getArgs(){
	int opcion;
	
	while ((opcion = getopt (argc, argv, optString.c_str())) != -1){
		switch (opcion) {
			case 's':
					parametros.SERVER = optarg;
					break;
			case 'p':
					parametros.PORT = atoi(optarg);
					break;
			case 'd':
					parametros.ARCHIVO = optarg;
					break;
			case 'h':
			default:
					printUsage();
					exit(EXIT_FAILURE);
		}
	}

	if ( parametros.SERVER == "" ||
		 parametros.PORT <= 0 ||
		 parametros.ARCHIVO == "" ){
		printUsage();
		exit(EXIT_FAILURE);
	}
	
	return(parametros);
}

void checkArgs::printUsage(){
	printf("Uso: %s %s\n%s\n", argv[0], opciones.c_str(), descripcion.c_str());
}



#endif
