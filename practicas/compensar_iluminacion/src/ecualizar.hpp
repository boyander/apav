/*
 * ecualizar.hpp
 *
 *  Created on: May 3, 2012
 *      Author: apav-2-09
 */

#include <imageplus/core.hpp>
#include <imageplus/core/multiarray.hpp>
#include <imageplus/math/statistics/multiarray_statistics.hpp>
#include <imageplus/math/numeric/numeric_util.hpp>

using namespace std;
using namespace imageplus;
using namespace imageplus::math::statistics;
using namespace imageplus::math::numeric;

#ifndef ECUALIZAR_HPP_
#define ECUALIZAR_HPP
MultiArray<uint64,1> calcula_histograma (const MultiArray<uint8,2>& in);
MultiArray<uint8,2> ecualiza_histograma (const MultiArray<float64,2>& in);

#endif /* ECUALIZAR_HPP_ */


