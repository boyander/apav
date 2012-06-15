/*
 * mean_var.hpp
 * Marc Pomar Torres i Laura Cotrina Barrios
 *
 */
#include <imageplus/core.hpp>
#include <imageplus/core/multiarray.hpp>
#include <imageplus/math/statistics/multiarray_statistics.hpp>

using namespace std;
using namespace imageplus;
using namespace imageplus::math::statistics;

MultiArray<uint8,2> compensa_media_varianza (const MultiArray<uint8,2> &ima1, const MultiArray<uint8,2> &ima2);
ImageGray<uint8> compensa_media_varianza (const ImageGray<uint8> &ima1, const ImageGray<uint8> &ima2);
