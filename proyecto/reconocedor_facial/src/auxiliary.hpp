/*
 * auxiliary.cpp
 *
 *  Created on: Jun 13, 2012
 *      Author: apav-2-09
 */

#include <imageplus/core.hpp>

/*
 * Incluimos nuestras funciones creadas en las prácticas
 */
#include <classifier.hpp>
#include <extract.hpp>
#include <DctCompensation.hpp>
#include <Model.hpp>

using namespace std;
using namespace imageplus;

MultiArray<float64,1> prepareImage(ImageRGB<uint8>& imagen,PersonalConfig& config);
MultiArray<float64,1> prepareImage(ImageGray<uint8>& imagen,PersonalConfig& config);
int64 resolveImage(const MultiArray<float64,1>& descriptor, vector<Model>& modelos, PersonalConfig& config);
