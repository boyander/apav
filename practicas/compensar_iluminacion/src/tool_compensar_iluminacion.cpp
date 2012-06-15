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
#include <imageplus/io/readimage.hpp>
#include <imageplus/io/writeimage.hpp>

/*
 * Incluimos nuestras funciones
 */
#include <ecualizar.hpp>
#include <mean_var.hpp>


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
    std::string     imagen_referencia;
    std::string     imagen_a_compensar;
    std::string     imagen_salida_mv;
    std::string     imagen_salida_ecu;

    
IMAGEPLUS_TOOL_CONFIG_DEFAULT_VALUES()

    //
    // Here you should assign default values to your parameters
    //
    // Note that vectors can be initialized with some values.
    //

    imagen_referencia = "imgRef.bmp";
    imagen_a_compensar = "imgComp.bmp";
    imagen_salida_mv = "imgOut.bmp";
    imagen_salida_ecu = "imgEqOut.bmp";
        
        
IMAGEPLUS_TOOL_CONFIG_OPTIONS()

    //
    // Here you have to define your OPTIONS, with a description 
    //

    IMAGEPLUS_TOOL_CONFIG_OPTION ( imagen_referencia, "Nombre del fichero con la imagen de referencia.");
	IMAGEPLUS_TOOL_CONFIG_OPTION ( imagen_a_compensar, "Nombre del fichero con la imagen a compensar.");
	IMAGEPLUS_TOOL_CONFIG_OPTION ( imagen_salida_mv, "Nombre del fichero a escribir la imagen compensada en media y varianza.");
	IMAGEPLUS_TOOL_CONFIG_OPTION ( imagen_salida_ecu, "Nombre del fichero a escribir la imagen ecualizada.");

    
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
        
    IMAGEPLUS_TOOL_CONFIG_READ( imagen_referencia );
	IMAGEPLUS_TOOL_CONFIG_READ( imagen_a_compensar );
	IMAGEPLUS_TOOL_CONFIG_READ( imagen_salida_mv );
	IMAGEPLUS_TOOL_CONFIG_READ( imagen_salida_ecu );


    
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
    ImageRGB <uint8> imgRef,imgToComp;

    //Variables para las imagenes de salida
    ImageRGB <uint8> imgComp,imgEc;

    // Creamos una instancia para leer imagenes
    ReadImage reader;

    //Leemos las imagenes de entrada
    reader.open(cfg.imagen_referencia); reader >> imgRef;
    reader.open(cfg.imagen_a_compensar); reader >> imgToComp;

    /*
     * Imagen compensada con la media
     *
     * */

    //Compensamos los 3 canales de la imagen de a compensar
    imgComp(RED_CHANNEL) = compensa_media_varianza(imgRef(RED_CHANNEL),imgToComp(RED_CHANNEL));
    imgComp(BLUE_CHANNEL) = compensa_media_varianza(imgRef(BLUE_CHANNEL),imgToComp(BLUE_CHANNEL));
    imgComp(GREEN_CHANNEL) = compensa_media_varianza(imgRef(GREEN_CHANNEL),imgToComp(GREEN_CHANNEL));

    //Creamos una instancia para escribir imagenes a disco
    WriteImage writer;

    //Guardamos la imagen compensada en media y varianza en disco
    writer.open(cfg.imagen_salida_mv); writer << imgComp;

    /*
     * Imagen compensada con ecualizacion de histograma
     *
     * */

    //Convertimos la imagen a float64
    ImageRGB <float64> imgRef_f = convert<float64>(imgToComp);

    //Ecualizamos la imagen
    imgEc(RED_CHANNEL) = ecualiza_histograma (imgRef_f(RED_CHANNEL));
    imgEc(BLUE_CHANNEL) = ecualiza_histograma (imgRef_f(BLUE_CHANNEL));
    imgEc(GREEN_CHANNEL) = ecualiza_histograma (imgRef_f(GREEN_CHANNEL));

    //Escribimos la imagen en el disco
    writer.open(cfg.imagen_salida_ecu); writer << imgEc;
}

//
// This last line is mandatory!
//
IMAGEPLUS_TOOL_CONFIG_END()
