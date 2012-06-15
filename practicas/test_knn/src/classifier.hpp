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

#include <Model.hpp>


using namespace std;
using namespace imageplus;
using namespace imageplus::math::statistics;
using namespace imageplus::math::transforms;
using namespace imageplus::math::numeric;

uint64 clasificador_knn (const MultiArray<float64,1>& vec, const std::vector<Model>& modelos, uint64 k);
