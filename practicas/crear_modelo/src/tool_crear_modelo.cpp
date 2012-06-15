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
//   - Avoid the character '-', use always '_' 
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
#include <imageplus/io/readsequence.hpp>
/*
 * Incluimos nuestras funciones
 */
#include <Model.hpp>
#include <extract.hpp>
#include <Configuration.hpp>
#include <DctCompensation.hpp>

/*
 * Definen como se extraeran las caracteristicas de las imagenes para el modelo
 */
#define CARACTERISTICAS_SIZE 40
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
std::string nombre;
uint64 id;
std::string directorio;
std::string caras;
uint64 num_caras;
uint64 coef_dct;
uint64 norm;
uint64 discarded;

IMAGEPLUS_TOOL_CONFIG_DEFAULT_VALUES()

//
// Here you should assign default values to your parameters
//
// Note that vectors can be initialized with some values.
//

nombre = "Laura Marc";
id = 0;
directorio = "/home/apav-2-09/PRACTICAS/otros/modelos/";
caras = "/home/apav-2-09/PRACTICAS/P9/caras/modelo001/seq_%06d.png";
num_caras = 10;
coef_dct = CARACTERISTICAS_COEFS;
norm = CARACTERISTICAS_SIZE;
discarded = 0;

IMAGEPLUS_TOOL_CONFIG_OPTIONS()

//
// Here you have to define your OPTIONS, with a description
//

IMAGEPLUS_TOOL_CONFIG_OPTION ( nombre, "Nombre de la persona asociada al modelo");
IMAGEPLUS_TOOL_CONFIG_OPTION ( id, "Identificador numérico asociado a la persona");
IMAGEPLUS_TOOL_CONFIG_OPTION ( directorio, "Directorio donde se guardan los modelos");
IMAGEPLUS_TOOL_CONFIG_OPTION ( caras, "El nombre de las imágenes de entrada, en formato printf");
IMAGEPLUS_TOOL_CONFIG_OPTION ( num_caras, "El número de imágenes a leer");
IMAGEPLUS_TOOL_CONFIG_OPTION ( coef_dct, "El número de coeficientes en cada imagen del modelo");
IMAGEPLUS_TOOL_CONFIG_OPTION ( norm, "Tamaño en que se normaliza la imagen");
IMAGEPLUS_TOOL_CONFIG_OPTION ( discarded, "Parametro de compensacion de iluminacion");



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

IMAGEPLUS_TOOL_CONFIG_READ( nombre );
IMAGEPLUS_TOOL_CONFIG_READ( id );
IMAGEPLUS_TOOL_CONFIG_READ( directorio );
IMAGEPLUS_TOOL_CONFIG_READ( caras );
IMAGEPLUS_TOOL_CONFIG_READ( num_caras );
IMAGEPLUS_TOOL_CONFIG_READ( coef_dct );
IMAGEPLUS_TOOL_CONFIG_READ( norm );
IMAGEPLUS_TOOL_CONFIG_READ( discarded );


IMAGEPLUS_TOOL_CONFIG_MAIN()
	{

		//Modelo en el cual guardaremos los datos
		Model modelo = Model(cfg.nombre, cfg.id);

		// Configuration Setup
		PersonalConfig *c = new PersonalConfig();
		c->setExtractionCoefs(cfg.coef_dct);
		c->setNormalizationSize(cfg.norm);
		c->setDiscardedCompensationCoefs(cfg.discarded);
		c->printConfiguration();

		//Lector de imagenes en un path
		cout << "Leyendo Secuencia para el modelo \"" << cfg.nombre << "\" desde: " << cfg.caras << std::endl;
		ReadSequence rseq(cfg.caras, 1, cfg.num_caras);

		//Leemos tantas imagenes como nos haya sido indicado
		for (uint64 i = 0; i < cfg.num_caras; i++) {
			cout << "Leyendo imagen " << i << std::endl;

			//Leemos la imagen de la secuencia
			ImageGray<uint8> imgGray;
			rseq >> imgGray;

			//Compensamos la iluminacion
			imgGray = compensateDCT(imgGray, c->getDiscardedCompensationCoefs());

			// Normalizamos el tamaño de la imagen
			imgGray = normalizarImagen(imgGray,c->getNormalizationSize());

			//Extraemos las caracteristicas de la imagen
			MultiArray<float64,1> crt;
			crt = extraer_caracteristicas_dct(imgGray,c->getExtractionCoefs());

			//Añadimos el vector de caracteristicas extraido al modelo actual
			modelo.add(crt);
		}


		stringstream name;
		//name << cfg.directorio << "model" << setw(3) << setfill('0') << cfg.id << ".bin";
		name << cfg.directorio;
		//Guardamos el modelo en disco
		cout << "Guardando el modelo en -> " << name.str() << std::endl;

		modelo.save(name.str());

	}

	//
	// This last line is mandatory!
	//
	IMAGEPLUS_TOOL_CONFIG_END()
