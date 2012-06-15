/*
 * Marc Pomar Torres y Laura Cotrina Barrios
 * */

#include <mean_var.hpp>

MultiArray<uint8,2> compensa_media_varianza (const MultiArray<uint8,2>& ima1, const MultiArray<uint8,2>&
ima2){

	//Bari means Variance :-)
	float64 meanIm1 = 1,meanIm2 = 1;
	float64 bariIm1 = 1,bariIm2 = 1;
	meanIm1 = mean(ima1);
	meanIm2 = mean(ima2);
	bariIm1 = sqrt(variance(ima1));
	bariIm2 = sqrt(variance(ima2));

	imageplus::uint64 x=0,y=0;

	//Tamaño del MultiArray
	x = ima1.dims(0);
	y = ima2.dims(1);
	
	MultiArray<uint8,2> compensated(x,y);

	cout << "Media Img1 ->" << meanIm1 << "  Variancia ->" << bariIm1<< endl;
	cout << "Media Img2 ->" << meanIm2 << "  Variancia ->" << bariIm2<< endl;

	for (uint64 j=0; j < x; ++j)
	for (uint64 i=0; i < y; ++i)
	{
		float64 f = ((((float64 )ima2[i][j] - meanIm2) / bariIm2) * bariIm1) + meanIm1;
		 if(f > 255.0){
			 f = 255.0;
		 } else if(f < 0.0){
			 f = 0.0;
		 }
		 compensated[i][j] = (uint8) f;
	}
	
	return compensated;
}


ImageGray<uint8> compensa_media_varianza (const ImageGray<uint8>& ima1, const ImageGray<uint8>& ima2){	
	MultiArray<uint8,2> r;
	r = compensa_media_varianza(ima1(0),ima2(0));
	imageplus::uint64 x=r.dims(0),y=r.dims(1);
	ImageGray<uint8> s(x,y);
	s(0) = r;
	return s;
}
