// --------------------------------------------------------------
// Copyright (C)
// Universitat Politecnica de Catalunya (UPC) - Barcelona - Spain
// --------------------------------------------------------------
//!
//! \example tool_config_example.cpp
//!
//! This is an example of how to create a tool unsing the \ref ToolConfigMacros.
//!
//! The example is the source code of a dummy tool, and the output results
//! of running it with diferents options. 
//!
//! Here you can see only the source code of the tool example, to see the complete example with 
//! the output results of running this example, please see \ref ToolConfigMacros.
//!

//
// FIRST: Main Definitions
//
// - The NAME of your tool
//   - This is mandatory
//   - Asvoid the character '-', use always '_'
// - The GROUP where your tool belong
//   - This is optional
//   - Comment the second definition to not group your tool
//
#define IMAGEPLUS_TOOL_CONFIG_NAME  tool_config_example
#define IMAGEPLUS_TOOL_CONFIG_GROUP examples

//
// SECOND: Include tool_config.hpp header 
//
// Note that it is mandatory to FIRST define the name (and group)
// of your tool, and LATER on include this header.
//
#include <imageplus/toolbox/tool_config.hpp>
#include <imageplus/core.hpp>
#include <imageplus/io/readimage.hpp>
#include <imageplus/io/readsequence.hpp>
/*
 * Incluimos nuestras funciones
 */
#include <classifier.hpp>
#include <extract.hpp>
#include <auxiliary.hpp>

/*
 * Definen como se extraeran las caracteristicas de las imagenes para el modelo
 */
#define TAMANO_NORMALIZACION 40
#define CARACTERISTICAS_COEFS 60

/*
 * To found the main classes
 */
using namespace std;
using namespace imageplus;
using namespace imageplus::io;

//
//
// From now on you should use the IMAGEPLUS_TOOL_CONFIG_* macros
// for a better configuration.
//
// We have two parts:
//
// (1) Fill up the configuration and information of your tool:
//
// - Brief description of your tool
// - Detailed descritption of your tool
// - Parameters Configuration: 
//   - Declararion of all your parameters
//   - Default values for the parameters
//   - Configuration: 
//     - Select which paramteres are options, which flags and which arguments
//     - Description for all the parameters
//     - Optional abreviatures for options and flags 
// - Call the "read" functions for all the parameters (DO NOT FORGET THIS!)
//
// (2) The code of "main" function of your tool
//
// You should use the IMAGEPLUS_TOOL_CONFIG_* macros in the following 
// order to do all the previous tasks: 
//
IMAGEPLUS_TOOL_CONFIG_BRIEF()

"Here you should write a brief description ofyour tool...\n";

IMAGEPLUS_TOOL_CONFIG_DESCRIPTION()

"This is the detailed description of your tool.           \n" +
"What it does, how, why...                                \n" +
"                                                         \n"+
"You can add blank lines as the previous and the next one.\n" +
"                                                         \n"+
"\tAlso indented lines like this...                       \n" +
"                                                         \n"+
"This information will be shown in the help message.      \n";

IMAGEPLUS_TOOL_CONFIG_PARAMETERS()
std::string caras;
uint64 num_caras;
uint64 N;
std::string directorio;
uint64 k;
uint64 norm;
uint64 coef_dct;
uint64 iluminate_discard;
uint64 debug_mode;


IMAGEPLUS_TOOL_CONFIG_DEFAULT_VALUES()

//
// Here you should assign default values to your parameters
//
// Note that vectors can be initialized with some values.
//

caras = "/home/apav-2-09/PRACTICAS/otros/imatges_prova/p02/seq_%06d.png";
num_caras = 10;
N = 1;
directorio = "/home/apav-2-09/PRACTICAS/otros/modelos/discart_0";
k = 3;
norm = TAMANO_NORMALIZACION;
coef_dct = CARACTERISTICAS_COEFS;
iluminate_discard = 0;
debug_mode = 0;


IMAGEPLUS_TOOL_CONFIG_OPTIONS()

//
// Here you have to define your OPTIONS, with a description
//

IMAGEPLUS_TOOL_CONFIG_OPTION ( caras, "Nombre de las imágenes faciales que se van a reconocer (formato printf)");
IMAGEPLUS_TOOL_CONFIG_OPTION ( N, "Número de modelos a leer");
IMAGEPLUS_TOOL_CONFIG_OPTION ( num_caras, "Número de imagenes faciales a leer");
IMAGEPLUS_TOOL_CONFIG_OPTION ( directorio, "Directorio donde se guardan los modelos");
IMAGEPLUS_TOOL_CONFIG_OPTION ( k, "El parámetro k de kNN");
IMAGEPLUS_TOOL_CONFIG_OPTION ( norm, "Tamaño para la normalización (en píxels)");
IMAGEPLUS_TOOL_CONFIG_OPTION ( coef_dct, "Número de coeficientes a preservar de la DCT");
IMAGEPLUS_TOOL_CONFIG_OPTION ( iluminate_discard, "Número de coeficientes descartados al realizar la compensación de iluminación");
IMAGEPLUS_TOOL_CONFIG_OPTION ( debug_mode, "Habilita el modo debug, para comprobar los resultados de clasificación");

IMAGEPLUS_TOOL_CONFIG_FLAGS()

//
// Here you have to define your FLAGS, with a description
// and an optional abreviature
//

IMAGEPLUS_TOOL_CONFIG_ARGUMENTS()

IMAGEPLUS_TOOL_CONFIG_READ_PARAMETERS()

//
// Here you have to read all your parameters
//
// DO NOT FORGET THIS STEP!!
//

IMAGEPLUS_TOOL_CONFIG_READ( caras );
IMAGEPLUS_TOOL_CONFIG_READ( num_caras );
IMAGEPLUS_TOOL_CONFIG_READ( N );
IMAGEPLUS_TOOL_CONFIG_READ( directorio );
IMAGEPLUS_TOOL_CONFIG_READ( k );
IMAGEPLUS_TOOL_CONFIG_READ( norm );
IMAGEPLUS_TOOL_CONFIG_READ( coef_dct );
IMAGEPLUS_TOOL_CONFIG_READ( iluminate_discard );
IMAGEPLUS_TOOL_CONFIG_READ( debug_mode );


IMAGEPLUS_TOOL_CONFIG_MAIN()
{
	// Configuration Setup
	PersonalConfig *c = new PersonalConfig();
	c->setDiscardedCompensationCoefs(cfg.iluminate_discard);
	c->setExtractionCoefs(cfg.coef_dct);
	c->setKnn(cfg.k);
	c->setNormalizationSize(cfg.norm);
	c->setDebug(cfg.debug_mode);

	//Show configuration
	c->printConfiguration();

	// Cargamos los modelos del disco
	vector<Model> modelos;
	modelos = load_models(cfg.directorio);

	// Comprobamos que se hayan cargado los modelos
	if(modelos.size() > 0){
		std::cout << "Loaded " << modelos.size() << " models!" << std::endl;
	}else{
		std::cout << "No models found on dir, exiting!" << std::endl;
		return 1;
	}


	//Lector de imagenes en un path
	cout << "Identifying sequence images on path: \"" << cfg.caras <<"\"" << std::endl;
	ReadSequence rseq(cfg.caras, 1, cfg.num_caras);

	//Leemos tantas imagenes de test como nos haya sido indicado
	for (uint64 i = 0; i < cfg.num_caras; i++) {

		if(c->getDebug()){
			cout << "Leyendo imagen " << i << endl;
		}

		//Leemos la imagen de la secuencia
		ImageGray<uint8> imgGray;
		rseq >> imgGray;

		//Procesamos la imagen y extraemos el descriptor
		MultiArray<float64,1> descriptor;
		descriptor = prepareImage(imgGray,(*c));

		//Resolvemos la imagen con los modelos
		int64 solved_id;
		solved_id = resolveImage(descriptor,modelos,(*c));

		if(solved_id != -1){
			//Imprimimos el nombre de la solucion usando el identificador
			cout << "\tImage \"" << setw(6) << setfill('0') << i+1
				 << "\" corresponds to: \"" << modelos[solved_id].name() << "\""
				 << "\twith ID: " << modelos[solved_id].id() << endl;
		}else{
			cout << "Classification Error!" << endl;
			return -1;
		}
	}
}

//
// This last line is mandatory!
//
IMAGEPLUS_TOOL_CONFIG_END()
