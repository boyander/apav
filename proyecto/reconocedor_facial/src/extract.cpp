/*
 * Marc Pomar Torres y Laura Cotrina Barrios
 * */


#include <extract.hpp>

MultiArray<float64,1> extraer_caracteristicas_dct(const ImageGray<uint8>& ima, uint64 num_coef){

	//Transformada DCT de la imatge
	MultiArray<float64,2> dctTransform = dct2d(convert<float64>(ima(0)));

	//Vector de salida con el tamaño de num_coef
	MultiArray<float64,1> output(num_coef);

	//ZigZag Scan
	ZigZagScan zz(ima.size_x());

	//Cogemos solo los coeficientes necesarios
	MultiArray<float64,1> zzcoefs = zz.coefs(dctTransform);  // Get image coeeficients ordered in zigzag orders
	for(uint64 i=0; i < num_coef; i++)
		output[i] = zzcoefs[i];

	//std::cout << output << std::endl;

	return output;
}

ImageGray<uint8> normalizarImagen(const ImageGray<uint8>& ima, uint64 ancho){
	//Normalizamos el tamaño de la imagen
	boost::array<std::size_t,2> dims;
	dims[0] = ancho;
	dims[1] = ancho;
	return imageplus::math::numeric::resize(ima,dims);
}

float64 calc_similarity(const MultiArray<float64,1> &cIm1,MultiArray<float64,1> &cIm2, std::string type){
	float64 r;
	if( type == "manhattan" ){
		r = manhattan_distance(cIm1,cIm2);
	} else if ( type == "euclidean" ) {
		r = euclidean_distance(cIm1,cIm2);
	} else if ( type == "infinity_norm" ) {
		r = infinity_norm_distance(cIm1,cIm2);
	} else {
		throw "Sin implementar!";
	}
	return r;
}


