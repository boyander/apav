/*
 * auxiliary.cpp
 *
 *  Created on: Jun 13, 2012
 *      Author: apav-2-09
 */

#include <auxiliary.hpp>

/* Wrapper para el proceso de una ImageRGB */
MultiArray<float64,1> prepareImage(ImageRGB<uint8>& imagen,PersonalConfig& config){
	// Convertimos la imagen a ImageGray
	ImageGray<uint8> gry;
	gry = to_gray(imagen);

	// Procesamos la imagen
	return prepareImage(gry,config);
}

/*uint8 norm_size, uint8 discarded_coefs, uint8 coef_dct*/

/* Procesa la imagen y devuelve el descriptor DCT */
MultiArray<float64,1> prepareImage(ImageGray<uint8>& imagen,PersonalConfig& config){

	// Compensamos la iluminacion
	imagen =  compensateDCT(imagen,config.getDiscardedCompensationCoefs());

	// Normalizamos el tamaño
	imagen = normalizarImagen(imagen, config.getNormalizationSize());

	//Extraemos las caracteristicas de la imagen
	MultiArray<float64,1> crt;
	crt = extraer_caracteristicas_dct(imagen,config.getExtractionCoefs());

	return crt;
}

/* Con el descriptor DCT identifica la imagen en los modelos */
int64 resolveImage(const MultiArray<float64,1>& descriptor, vector<Model>& modelos, PersonalConfig& config){
	int64 solved_id;
	uint64 k = config.getKnn();
	if(config.getDebug()){
		cout << "Analysing picture, knn(k)=" << k << endl;
	}
	//Comparamos con los modelos
	solved_id = clasificador_knn(descriptor,modelos,config);

	return solved_id;
}
