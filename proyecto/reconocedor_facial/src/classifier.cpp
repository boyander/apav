/*
 * Marc Pomar Torres y Laura Cotrina Barrios
 * */


#include <classifier.hpp>

int64 clasificador_knn (const MultiArray<float64,1>& vec, const std::vector<Model>& modelos, PersonalConfig& c){
	uint64 k = c.getKnn();

	uint64 cares_max = 0;
	for (uint64 i = 0; i < modelos.size(); ++i){
		uint64 max = modelos[i].size();
		if( max > cares_max ) {
			cares_max = max;
		}
	}

	MultiArray<float64,2> distances(modelos.size(),cares_max);
	if(c.getDebug()){
		cout << "Distances array size -> [" << modelos.size() << "," << cares_max <<"]"<< endl;
	}
	distances = std::numeric_limits<float64>::max();

	//Test image vector size
	uint64 vSize = vec.size();

	//Recorremos los modelos
	for (uint64 i = 0; i < modelos.size(); ++i){
		//Comprobamos todas las caras del modelo
		for (uint64 j=0; j < modelos[i].size(); ++j){
			uint64 modelVectorSize = modelos[i][j].size();
			if(vSize != modelVectorSize){
				//Error, insuficcient coefs at model
				if(c.getDebug()){
					cout << "Classify Error, sizes missmatch on DCT Coefs: Test image ->"
						<< vSize << "\t Model-> " << modelos[i].name() << endl;
				}
				return 0;
			}
			/*if(c.getDebug()){
				cout << "Reference: " << vSize << "\t Matrix: " << modelos[i][j].size() << endl;
			}*/
			distances[i][j] = euclidean_distance(vec, modelos[i][j]);
		}
	}

	vector<uint64> identificadores;

	for(uint64 i = 0; i < k; ++i){
		float64 min = std::numeric_limits<float64>::max();
		uint64 posX = 0, posY = 0;
		for(uint64 xx = 0; xx < distances.size(); ++xx){
			for(uint64 yy = 0; yy < distances[xx].size(); ++yy){
				if( distances[xx][yy] < min ){
					min = distances[xx][yy];
					posX = xx;
					posY = yy;
				}
			}
		}
		distances[posX][posY] = std::numeric_limits<float64>::max();
		if(c.getDebug()){
			cout << "Found min on -> " << posX <<endl;
		}
		identificadores.push_back(posX);
	}

	/*	int64 *pos = new int64;
		float64 min;

		//Calculamos el minimo
		min = minval(distances,pos);

		//Calculamos el indice del mínimo
		int64 model, face, width, height;
		width = distances.dims()[0];
		height = distances.dims()[1];
		if(c.getDebug()){
			cout << "Matrix W:" << width << " H:" << height << endl;
		}
		face = (*pos) / width;
		model = (*pos) - (face*width);
		if(c.getDebug()){
			cout << "Found min on -> " << *pos <<endl;
			cout << "Minimum index -> Model:" << model << " Face:" << face << endl;
		}
		distances[model][face] = std::numeric_limits<float64>::max();
		identificadores.push_back(model);*/


	//Votación
	uint64 max = 0;
	int64 mostVoted = -1;
	std::map<uint64, uint64> m;
	vector<uint64>::iterator vi;
	for (vi = identificadores.begin(); vi != identificadores.end(); vi++) {
		m[*vi]++;
		if (m[*vi] >= max) {
			max = m[*vi];
			mostVoted = *vi;
		}
	}

	if(c.getDebug()){
		for(uint64 i = 0; i < identificadores.size(); ++i){
			cout << "\tID Resultado " << i << ": " << modelos[identificadores[i]].id() << endl;
		}
	}

	return mostVoted;
}

