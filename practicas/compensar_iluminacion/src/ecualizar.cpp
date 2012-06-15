
#include <ecualizar.hpp>


MultiArray<uint64,1> calcula_histograma(MultiArray<uint8,2>& in){
	//Histograma
	MultiArray<uint64,1> r(256);

	//Inicializamos todos los valores a cero
	r = 0;

	//Tamaño del MultiArray
	imageplus::uint64 x=0,y=0;
	x = in.dims(0);
	y = in.dims(1);

	for (uint64 j=0; j < x; ++j)
	for (uint64 i=0; i < y; ++i)
	{
		 r[in[j][i]] += 1;
	}
	return r;
}

MultiArray<uint8,2> ecualiza_histograma (const MultiArray<float64,2>& in){
	//Tamaño del MultiArray
	uint64 x=0,y=0;
	x = in.dims(0);
	y = in.dims(1);

	//Calculamos el histograma y lo normalizamos
	MultiArray<uint64,1> histogram;
	MultiArray<uint8,2> in_conv = convert<uint8>(in);
	histogram = calcula_histograma(in_conv);

	//std::cout << histogram << std::endl;

	//Calculamos la acumulada
	MultiArray<int64,1> prob(256);
	prob[0] = histogram[0];
	for(int64 i=1; i<256; i++){
		prob[i] = histogram[i] + prob[i-1];
	}

	//Imagen resultante
	MultiArray<uint8,2> result(x,y);
	int64 min = minval(prob);
	//std::cout << "Max " << maxval(in) << " Max converted " << int64(maxval(in_conv)) << " Min converted " << int64(minval(in_conv)) << std::endl;
	for (uint64 j=0; j < x; ++j)
	for (uint64 i=0; i < y; ++i)
	{
		 float64 num = (float64)(prob[in_conv[j][i]] - min);
		 float64 den = 1 - min;
		 float64 a = (num/den) * 255.0;

		 if( a > 255.0 ){
			 a = 255.0;
		 }else if( a < 0.0 ){
			 a = 0.0;
		 }

		 result[j][i] = mnint<uint8>(a);
	}
	return result;
}
