/*
 * DctCompensation.cpp
 *
 *  Created on: Jun 13, 2012
 *      Author: apav-2-09
 */

#include "DctCompensation.hpp"

ImageRGB<uint8> compensateDCT(const ImageRGB<uint8>& imagen, uint8 discarded_coefs){
	ImageRGB<uint8> img;
	img(RED_CHANNEL) = compensateDCT(imagen(RED_CHANNEL),discarded_coefs);
	img(BLUE_CHANNEL) = compensateDCT(imagen(BLUE_CHANNEL),discarded_coefs);
	img(GREEN_CHANNEL) = compensateDCT(imagen(GREEN_CHANNEL),discarded_coefs);
	return img;
}

ImageGray<uint8> compensateDCT(const ImageGray<uint8>& imagen, uint8 discarded_coefs){
	ImageGray<uint8> img;
	img(0) = compensateDCT(imagen(0),discarded_coefs);
	return img;
}

MultiArray<uint8,2> compensateDCT(const MultiArray<uint8,2>& imagen, uint8 discarded_coefs){
	// Transformada DCT de la imatge
	MultiArray<float64,2> dctTransform = dct2d(convert<float64>(imagen));

	// Zigzag scan mode
	ZigZagScan zz(imagen.dims(0));
	MultiArray<float64,1> zzcoefs = zz.coefs(dctTransform);  // Get image coeeficients ordered in zigzag orders

	// Discard selected DCT coefs
	for (uint64 i = 0; i < discarded_coefs; i++){
		zzcoefs[i] = 0.0;
    }

	// Return zigzagged coefs to normal state
	MultiArray<float64,2> rec_ma;
	rec_ma = zz.dezigzag(zzcoefs); // Undo zigzag and restore image

	// Inverse DCT Transform
	MultiArray<float64,2> r;
	r = idct2d(rec_ma);

	return convert<uint8>(r);
}
