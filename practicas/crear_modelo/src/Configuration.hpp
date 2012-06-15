/*
 * Configuration.h
 *
 *  Created on: Jun 13, 2012
 *      Author: apav-2-09
 */

#include <imageplus/core.hpp>

using namespace std;
using namespace imageplus;

class PersonalConfig {
	private:
		uint64 knn_K;
		uint64 num_coefs_Extract;
		uint64 discardedCoefsCompensation;
		uint64 normalizationSize;
	public:
		PersonalConfig();

		void printConfiguration();

		/* * * SETTERS * * */
		void setKnn(const uint64 number);
		void setExtractionCoefs(const uint64 coefs);
		void setDiscardedCompensationCoefs(const uint64 coefs);
		void setNormalizationSize(const uint64 size);

		/* * * GETTERS * * */
		uint64 getKnn();
		uint64 getExtractionCoefs();
		uint64 getDiscardedCompensationCoefs();
		uint64 getNormalizationSize();
	};

