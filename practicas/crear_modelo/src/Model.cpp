/*
 * Model.cpp
 *
 *  Created on: May 19, 2012
 *      Author: apav-2-09
 */

#include "Model.hpp"

// Constructor por defecto
Model::Model() {

}

// Constructor que nicializa las variables miembro _nombre e _id
Model::Model(const std::string& nombre, uint64 id) {
	_nombre = nombre;
	_id = id;
}

// Constructor que lee un modelo existente desde un fichero de disco
Model::Model(const std::string& path_name) {

	//Stream de entrada de fichero
	ifstream file;
	//Abrimos el fichero en modo binario
	file.open(path_name.c_str(),std::ios::in | std::ios::binary );

	if(!file.is_open()){
		cout << "No such file \"" << path_name << "\""<< endl;
		return;
	}

	//Leemos la cabecera

	//Id del modelo
	file.read((char*)&_id,sizeof(_id));
	cout << "ID -> " << _id << endl;

	//Longitud del nombre
	size_t longitud = 0;
	file.read((char*)&longitud,sizeof(longitud));
	//cout << "LNombre -> " << longitud << endl;

	//Nombre
	char* nombre = new char[longitud+1];
	file.read(nombre,longitud);
	nombre[longitud] = char(0);
	_nombre = std::string(nombre, longitud);
	cout << "Nombre -> " << _nombre << endl;

	//Elementos del modelo
	size_t mod_elems;
	file.read((char*)&mod_elems,sizeof(mod_elems));

	cout << "Faces on model -> " << mod_elems << endl;
	for (size_t i = 0; i < mod_elems; ++i) {

		//Numero de coeficients
		size_t num_coefs = 0;
		file.read((char*)&num_coefs,sizeof(num_coefs));
		MultiArray<float64,1> coeficients((uint64)num_coefs);

		//Llegim els coeficients
		for (size_t j = 0; j < num_coefs; ++j) {
			float64 r_coef;
			file.read((char*)&r_coef,sizeof(float64));
			coeficients[j] = r_coef;
		}

		//Guardem al vector els elements
		_data.push_back(coeficients);
	}
	//Cerramos el fichero
	file.close();
	cout << "Readed model!" << endl;

}

// Añade un vector de características al modelo (en el vector _data).
void Model::add(const MultiArray<float64, 1>& vec) {
	_data.push_back(vec);
}

// Guarda el modelo en un fichero dentro del directorio especificado
void Model::save(const std::string& path_name) const {

	//Stream de salida a fichero
	ofstream file;
	//Abrimos el fichero
	file.open(path_name.c_str(),std::ios::out | std::ios::binary );

	//Ecribimos la cabecera

	std::cout << "path_name = |" << path_name << "|" << std::endl;

	//Id del modelo
	file.write((char*)&_id,sizeof(uint64));

	std::cout << "ID = " << _id << std::endl;

	//Longitud del nombre
	size_t lon_nombre = _nombre.length();
	file.write((char*)&lon_nombre,sizeof(size_t));

	//Nombre
	file.write((char*)_nombre.c_str(),_nombre.length());

	//Elementos del modelo
	size_t num_elems = _data.size();
	file.write((char*) &num_elems,sizeof(size_t));

	//Guardamos el vector de caracteristicas del modelo
	for (size_t i = 0; i < _data.size(); ++i) {
		size_t num_coefs = _data[i].size();
		file.write((char*)&num_coefs,sizeof(_data[i].size()));
		for (size_t j = 0; j < _data[i].size(); ++j){
			file.write((char*)&_data[i][j],sizeof(_data[i][j]));
		}
	}

	//Cerramos el fichero
	file.close();

}

// Devuelve el tamaño del vector (el número de caras en el modelo)
uint64 Model::size() const {
	return _data.size();
}

// Acceso al vector de características de una cara determinada
const MultiArray<float64, 1>& Model::operator[](uint64 num_vec) const {
	return _data[num_vec];
}

// Método que retorna el nombre de la persona
std::string Model::name() const {
	return _nombre;
}
// Método que retorna el identificador numérico
uint64 Model::id() const {
	return _id;
}

std::vector<Model> load_models(const std::string& directory_name)
{
	vector<Model> modelos;

	directory_iterator end_itr; // default construction yields past-the-end

	for (directory_iterator itr(directory_name); itr != end_itr; ++itr) {
		if ( !is_directory( *itr ) ){
			string filename = itr->leaf();
			cout << "Model Found -> " << filename << std::endl;
			Model modelo (directory_name + "/" + filename);
			modelos.push_back(modelo);
		}
	}
	return modelos;
}

