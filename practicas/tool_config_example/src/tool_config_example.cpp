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

    //
    // Here you have to declare all your configuration parameters:
    // options, flags and arguments.

    // Your Options:
    int64           value;
    std::string     input_file;
    std::string     output_file;


    
IMAGEPLUS_TOOL_CONFIG_DEFAULT_VALUES()

    //
    // Here you should assign default values to your parameters
    //
    // Note that vectors can be initialized with some values.
    //

    value  = 126;
    input_file  = "image.bmp";
    output_file  = "imageOut.bmp";
        
        
IMAGEPLUS_TOOL_CONFIG_OPTIONS()

    //
    // Here you have to define your OPTIONS, with a description 
    //

    IMAGEPLUS_TOOL_CONFIG_OPTION ( value,      "NxN size of output image.");
    IMAGEPLUS_TOOL_CONFIG_OPTION ( input_file, "Input image file.");
    IMAGEPLUS_TOOL_CONFIG_OPTION ( output_file, "Output image file.");
    
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
        
    IMAGEPLUS_TOOL_CONFIG_READ( value   );
    IMAGEPLUS_TOOL_CONFIG_READ( input_file     );
    IMAGEPLUS_TOOL_CONFIG_READ( output_file     );


    
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
    std::cout << "Value:    " << cfg.value    << std::endl;
    std::cout << "Input  file:   " << cfg.input_file      << std::endl;
    std::cout << "Output file:   " << cfg.output_file    << std::endl;
    
    ImageRGB <uint8> rgb;


    imageplus::uint64 x=0,y=0;

    //Create an image reader intance
    ReadImage rima(cfg.input_file);
    //create a image writer example
    WriteImage wima(cfg.output_file);

    rima >> rgb;
    x = rgb.size_x();
    y = rgb.size_y();
    ImageRGB <uint8> inv_rgb(x,y);

    //Invert image loop
    for (uint64 jj=0; jj < y; ++jj)
    for (uint64 ii=0; ii < x; ++ii)
    {
        inv_rgb(RED_CHANNEL)[ii][jj] = rgb(RED_CHANNEL)[x-ii-1][jj];
        inv_rgb(GREEN_CHANNEL)[ii][jj] = rgb(GREEN_CHANNEL)[x-ii-1][jj];
        inv_rgb(BLUE_CHANNEL)[ii][jj] = rgb(BLUE_CHANNEL)[x-ii-1][jj];

    }

    BBox2D bb(Coord2D<>(x-cfg.value-1,y-cfg.value-1), cfg.value,cfg.value);
    //BBox2D bb(Coord2D<>(5,5), 10,10);
    // Get subimage
    ImageRGB<uint8> rect = copy_view(inv_rgb, bb);
    wima << rect;


}

//
// This last line is mandatory!
//
IMAGEPLUS_TOOL_CONFIG_END()
