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
std::string cara;
uint64 N;
std::string directorio;
uint64 k;

IMAGEPLUS_TOOL_CONFIG_DEFAULT_VALUES()

//
// Here you should assign default values to your parameters
//
// Note that vectors can be initialized with some values.
//

cara = "/home/apav-2-09/PRACTICAS/otros/identificar/sample.png";
N = 1;
directorio = "/home/apav-2-09/PRACTICAS/otros/modelos";
k = 3;


IMAGEPLUS_TOOL_CONFIG_OPTIONS()

//
// Here you have to define your OPTIONS, with a description
//

IMAGEPLUS_TOOL_CONFIG_OPTION ( cara, "Nombre de la imagen facial que se va a reconocer");
IMAGEPLUS_TOOL_CONFIG_OPTION ( N, "Número de modelos a leer");
IMAGEPLUS_TOOL_CONFIG_OPTION ( directorio, "Directorio donde se guardan los modelos");
IMAGEPLUS_TOOL_CONFIG_OPTION ( k, "El parámetro k de kNN");

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

IMAGEPLUS_TOOL_CONFIG_READ( cara );
IMAGEPLUS_TOOL_CONFIG_READ( N );
IMAGEPLUS_TOOL_CONFIG_READ( directorio );
IMAGEPLUS_TOOL_CONFIG_READ( k );


IMAGEPLUS_TOOL_CONFIG_MAIN()
{

	//Cargamos los modelos del disco
	vector<Model> modelos;
	modelos = load_models(cfg.directorio);
	std::cout << "All models loaded" << std::endl;

	cout << "Identifying image at ->\"" << cfg.cara << "\"" <<endl;
	ReadImage rima;
	try{
		rima.open(cfg.cara);
	}catch (ImagePlusFileNotFound e){
	    cout << "File for face image not found!" << endl;
	    return 0;
	}


	ImageGray<uint8> gry;
	ImageRGB<uint8>  rgb;

	rima >> rgb;
	gry = to_gray( rgb );

	//Extraemos las caracteristicas de la imagen
	MultiArray<float64,1> crt;
	crt = extraer_caracteristicas_dct(gry,CARACTERISTICAS_SIZE,CARACTERISTICAS_COEFS);

	//Comparamos con los modelos
	uint64  solved_id = clasificador_knn (crt, modelos, cfg.k);

	//Imprimimos el nombre de la solucion
	cout << "Inserted image corresponds to -> \"" << modelos[solved_id].name() <<"\""<< endl;

}

//
// This last line is mandatory!
//
IMAGEPLUS_TOOL_CONFIG_END()
