/*
 * Configuration.cpp
 *
 *  Created on: Jun 13, 2012
 *      Author: apav-2-09
 */

#include "Configuration.hpp"

PersonalConfig::PersonalConfig() {
	//Setup default enviroment
	knn_K = 3;
	num_coefs_Extract = 60;
	discardedCoefsCompensation = 0;
	normalizationSize = 40;
}

void PersonalConfig::printConfiguration(){
	cout << "Running with following configuration:" << endl;
	cout << "\tNumber of extracted coefs: " << num_coefs_Extract << endl;
	cout << "\tDiscarded DCT coefs on comp: " << discardedCoefsCompensation << endl;
	cout << "\tNumber k on KNN: " << knn_K << endl;
	cout << "\tNormalization size in pixels: " << normalizationSize << endl;
}

 /* * * SETTERS * * */
void PersonalConfig::setKnn(const uint64 number){
	knn_K = number;
}

void PersonalConfig::setExtractionCoefs(const uint64 coefs){
	this->num_coefs_Extract = coefs;
}

void PersonalConfig::setDiscardedCompensationCoefs(const uint64 coefs){
	this->discardedCoefsCompensation = coefs;
}

void PersonalConfig::setNormalizationSize(const uint64 size){
	this->normalizationSize = size;
}

/* * * GETTERS * * */
uint64 PersonalConfig::getKnn(){
	return knn_K;
}

uint64 PersonalConfig::getExtractionCoefs(){
	return num_coefs_Extract;
}

uint64 PersonalConfig::getDiscardedCompensationCoefs(){
	return discardedCoefsCompensation;
}

uint64 PersonalConfig::getNormalizationSize(){
	return normalizationSize;
}
