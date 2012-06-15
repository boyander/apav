/*
 * DctCompensation.h
 *
 *  Created on: Jun 13, 2012
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


ImageRGB<uint8> compensateDCT(const ImageRGB<uint8>& imagen, uint8 discarded_coefs);
ImageGray<uint8> compensateDCT(const ImageGray<uint8>& imagen, uint8 discarded_coefs);
MultiArray<uint8,2> compensateDCT(const MultiArray<uint8,2>& imagen, uint8 discarded_coefs);
