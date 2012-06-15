/*
 * extract.hpp
 *
 *  Created on: May 10, 2012
 *      Author: apav-2-09
 */
#include <imageplus/core.hpp>
#include <imageplus/core/multiarray.hpp>
#include <imageplus/math/statistics/multiarray_statistics.hpp>
#include <imageplus/math/numeric/interpolation.hpp>
#include <imageplus/math/numeric/distances.hpp>

#include <imageplus/math/transforms/fourier.hpp>
#include <imageplus/math/transforms/zigzag.hpp>


using namespace std;
using namespace imageplus;
using namespace imageplus::math::statistics;
using namespace imageplus::math::transforms;
using namespace imageplus::math::numeric;


MultiArray<float64,1> extraer_caracteristicas_dct(const ImageGray<uint8>& ima, uint64 ancho, uint64 num_coef);
float64 calc_similarity(const MultiArray<float64,1> &cIm1,MultiArray<float64,1> &cIm2, std::string type);

