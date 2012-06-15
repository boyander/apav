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
#include <imageplus/io/writeimage.hpp>

#include <DctCompensation.hpp>


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
std::string input;
std::string output;
uint64 iluminate_discard;



IMAGEPLUS_TOOL_CONFIG_DEFAULT_VALUES()

//
// Here you should assign default values to your parameters
//
// Note that vectors can be initialized with some values.
//

input = "/home/apav-2-09/PRACTICAS/otros/test.jpg";
output = "/home/apav-2-09/PRACTICAS/otros/testDCTCompensated.jpg";
iluminate_discard = 3;


IMAGEPLUS_TOOL_CONFIG_OPTIONS()

//
// Here you have to define your OPTIONS, with a description
//

IMAGEPLUS_TOOL_CONFIG_OPTION ( input, "Imagen de entrada");
IMAGEPLUS_TOOL_CONFIG_OPTION ( output, "Imagen de salida");
IMAGEPLUS_TOOL_CONFIG_OPTION ( iluminate_discard, "Número de coeficientes descartados al realizar la compensación de iluminación");

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

IMAGEPLUS_TOOL_CONFIG_READ( input );
IMAGEPLUS_TOOL_CONFIG_READ( output );
IMAGEPLUS_TOOL_CONFIG_READ( iluminate_discard );


IMAGEPLUS_TOOL_CONFIG_MAIN()
{
	// Creamos una instancia para leer imagenes
	ReadImage reader;

	ImageGray<uint8> gry;

	//Leemos la imagen de entrada
	reader.open(cfg.input);
	reader >> gry;

	//Creamos una instancia para escribir imagenes a disco
	WriteImage writer;

	//Compensamos la imagen
	cout << "Ilumination compensation, discarding " << cfg.iluminate_discard << " coeficients" << endl;
	gry = compensateDCT(gry, cfg.iluminate_discard);

	//Guardamos la imagen compensada
	writer.open(cfg.output);
	writer << gry;

}

//
// This last line is mandatory!
//
IMAGEPLUS_TOOL_CONFIG_END()
