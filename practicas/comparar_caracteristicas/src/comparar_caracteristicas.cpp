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

#define DEBUG false

//
// SECOND: Include tool_config.hpp header 
//
// Note that it is mandatory to FIRST define the name (and group)
// of your tool, and LATER on include this header.
//
#include <imageplus/toolbox/tool_config.hpp>
#include <imageplus/core.hpp>
#include <imageplus/io/readimage.hpp>
#include <imageplus/io/writeimage.hpp>

/*
 * Incluimos nuestras funciones
 */
#include <extract.hpp>


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
    std::string     imagen_1;
    std::string     imagen_2;
    uint64     		distancia;
    uint64    		num_coef;

    
IMAGEPLUS_TOOL_CONFIG_DEFAULT_VALUES()

    //
    // Here you should assign default values to your parameters
    //
    // Note that vectors can be initialized with some values.
    //

    imagen_1 = "imgRef.bmp";
    imagen_2 = "imgComp.bmp";
    distancia = 0;
    num_coef = 10;
        
        
IMAGEPLUS_TOOL_CONFIG_OPTIONS()

    //
    // Here you have to define your OPTIONS, with a description 
    //

    IMAGEPLUS_TOOL_CONFIG_OPTION ( imagen_1, "Nombre del fichero con la imagen de la primera cara a comparar");
	IMAGEPLUS_TOOL_CONFIG_OPTION ( imagen_2, "Nombre del fichero con la imagen de la segunda cara a comparar");
	IMAGEPLUS_TOOL_CONFIG_OPTION ( distancia, "Valor entero que indica qué distancia utilizar. Usaremos el valor 0 para indicar la distancia euclídea y 1 para la distancia de Manhattan");
	IMAGEPLUS_TOOL_CONFIG_OPTION ( num_coef, "Valor entero que indica el número de coeficientes a utilizar en la extracción de características");

    
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
        
    IMAGEPLUS_TOOL_CONFIG_READ( imagen_1 );
	IMAGEPLUS_TOOL_CONFIG_READ( imagen_2 );
	IMAGEPLUS_TOOL_CONFIG_READ( distancia );
	IMAGEPLUS_TOOL_CONFIG_READ( num_coef );


    
//
// This is the "main" function of your tool.
//
// You can access to all your parameters (options, flags, and arguments)
// with the "cfg" object (see the code.)
//
// Run the exemple with "--help" to see your configuration.
//
IMAGEPLUS_TOOL_CONFIG_MAIN()
{   
	//Variables para las imagenes de entrada
    ImageRGB <uint8> img1,img2;

    // Creamos una instancia para leer imagenes
    ReadImage reader;

    //Leemos las imagenes de entrada
    reader.open(cfg.imagen_1); reader >> img1;
    reader.open(cfg.imagen_2); reader >> img2;

    //Config data
    uint64 ancho = 40;
    uint64 nCoef = (uint64) cfg.num_coef;

    //Caracteristicas de las imagenes
    MultiArray<float64,1> descriptor_Im1,descriptor_Im2;

    //Convertimos las imagenes en color a RGB
    ImageGray<uint8> gry1 = to_gray(img1);
    ImageGray<uint8> gry2 = to_gray(img2);

    //Extraemos caracteristicas
    descriptor_Im1 = extraer_caracteristicas_dct(gry1, ancho, nCoef);
    descriptor_Im2 = extraer_caracteristicas_dct(gry2, ancho, nCoef);

    //Para comparar internamente las distancias
    if(DEBUG){
		//Calculamos las distancias
		std::cout << "Distancias entre las 2 imagenes" << std::endl;
		std::cout << "-----------------" << std::endl;
		std::cout << "Euclidean\t" << calc_similarity(descriptor_Im1,descriptor_Im2,"euclidean") << std::endl;
		std::cout << "Manhattan\t" << calc_similarity(descriptor_Im1,descriptor_Im2,"manhattan") << std::endl;
		std::cout << "Infinity Norm\t" << calc_similarity(descriptor_Im1,descriptor_Im2,"infinity_norm") << std::endl;
    }

    //Imprimimos la distancia
    if(cfg.distancia == 0){
    	std::cout << calc_similarity(descriptor_Im1,descriptor_Im2,"euclidean") << std::endl;
    }else if (cfg.distancia == 1){
    	std::cout << calc_similarity(descriptor_Im1,descriptor_Im2,"manhattan") << std::endl;
    }else{
    	std::cout << "No Existen mas metodos implementados!" << std::endl;
    }
}

//
// This last line is mandatory!
//
IMAGEPLUS_TOOL_CONFIG_END()
