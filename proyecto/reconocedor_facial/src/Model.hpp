/*
 * Model.h
 *
 *  Created on: May 19, 2012
 *      Author: apav-2-09
 */

#include <fstream>
#include <iostream>
#include <vector>
#include <imageplus/core.hpp>
#include <imageplus/core/multiarray.hpp>
#include "boost/filesystem.hpp"
#include "boost/filesystem/operations.hpp"
#include <Configuration.hpp>


using namespace std;
using namespace imageplus;
using namespace boost::filesystem;

#ifndef MODEL_H_
#define MODEL_H_

class Model {
public:
	// Constructor por defecto
	Model();

	// Constructor que nicializa las variables miembro _nombre e _id
	Model(const std::string& nombre, uint64 id);

	// Constructor que lee un modelo existente desde un fichero de disco
	Model(const std::string& path_name);

	// A�ade un vector de caracter�sticas al modelo (en el vector _data).
	void add(const MultiArray<float64, 1>& vec);

	// Guarda el modelo en un fichero dentro del directorio especificado
	void save(const std::string& path_name) const;

	// Devuelve el tama�o del vector (el n�mero de caras en el modelo)
	uint64 size() const;

	// Acceso al vector de caracter�sticas de una cara determinada
	const MultiArray<float64, 1>& operator[](uint64 num_vec) const;

	// M�todo que retorna el nombre de la persona
	std::string name() const;

	// M�todo que retorna el identificador num�rico
	uint64 id() const;



private:
	// Nombre de la persona
	std::string _nombre;

	// Identificador num�rico �nico asociado a la persona
	uint64 _id;

	// Vector de vectores de caracter�sticas
	// Un vector de caracter�sticas por cada imagen de la misma persona
	std::vector<MultiArray<float64, 1> > _data;
};


std::vector<Model> load_models (const std::string& directory_name);


#endif /* MODEL_H_ */
