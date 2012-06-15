/*
 * Marc Pomar Torres y Laura Cotrina Barrios
 * */


#include <classifier.hpp>

uint64 clasificador_knn (const MultiArray<float64,1>& vec, const std::vector<Model>& modelos, uint64 k){

	//uint64 result;
	uint64 cares_max = 0;
	for (uint64 i = 0; i < modelos.size(); ++i){
		uint64 max = modelos[i].size();
		if( max > cares_max ) {
			cares_max = max;
		}
	}

	MultiArray<float64,2> distances(modelos.size(),cares_max);
	cout << "Distances array size -> [" << modelos.size() << "," << cares_max <<"]"<< endl;
	distances = std::numeric_limits<float64>::max();

	//Recorremos los modelos
	for (uint64 i = 0; i < modelos.size(); ++i){
		//Comprobamos todas las caras del modelo
		for (uint64 j=0; j < modelos[i].size(); ++j){
			distances[i][j] = euclidean_distance(vec, modelos[i][j]);
		}
	}

	vector<uint64> identificadores;

	for(uint64 i = 0; i < k; ++i){
		int64 *pos = new int64;
		float64 min;

		//Calculamos el minimo
		min = minval(distances,pos);

		//Calculamos el indice del mínimo
		int64 model, face, width, height;
		width = distances.dims()[0];
		height = distances.dims()[1];
		cout << "Matrix W:" << width << " H:" << height << endl;
		face = (*pos) / width;
		model = (*pos) - (face*width);
		cout << "Found min on -> " << *pos <<endl;
		cout << "Minimum index -> Model:" << model << " Face:" << face << endl;
		distances[model][face] = std::numeric_limits<float64>::max();
		identificadores.push_back(model);
	}

	//Votación
	vector<uint64> votes;
	for(uint64 i = 0; i < identificadores.size(); ++i){
	}

	return identificadores[0];
}

