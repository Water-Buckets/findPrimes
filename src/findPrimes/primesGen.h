//
// Created by waterbucket on 8/13/23.
//

#ifndef FINDPRIMES_PRIMESGEN_H
#define FINDPRIMES_PRIMESGEN_H

#include "fstream"
#include "string"
#include "vector"

namespace findPrimes {

	class primesGen {
	protected:

		unsigned long long uL;
		std::ofstream ofs;
		unsigned method;
		std::string fileName;

	private:
		bool (findPrimes::primesGen::*pMethods[5])();

		virtual bool eratosthenesSieve();

		virtual bool sundaramSieve();

		bool (*pCustomMethods)(const unsigned long long &n, std::ofstream &ofs);

	public:

		explicit primesGen(const unsigned long long &u, const unsigned &i = 0, const std::string &s = "primes.txt");

		primesGen(const unsigned long long &u, bool (*pM)(const unsigned long long &n, std::ofstream &ofs),
		          const std::string &s = "primes.txt");

		virtual std::string getFileName() { return fileName; };

		virtual primesGen &operator=(const unsigned long long &i) {
			uL = i;
			return *this;
		}

		virtual bool run();

		virtual ~primesGen() = default;

	};

	class primesGenVec : public primesGen {
	protected:

	private:

		bool (findPrimes::primesGenVec::*pMethods[5])();

		virtual bool trialDivision();

		bool eratosthenesSieve() override;

		virtual bool eulerSieve();

		bool sundaramSieve() override;

		virtual bool incrementalSieve();

		std::vector<unsigned long long> primes;

		bool (*pCustomMethods)(const unsigned long long &n, std::vector<unsigned long long> &pVec);

	public:
		explicit primesGenVec(const unsigned long long &u, const unsigned &i = 0, const std::string &s = "primes.txt");

		primesGenVec(const unsigned long long &u,
		             bool (*pM)(const unsigned long long &n, std::vector<unsigned long long> &pVec),
		             const std::string &s = "primes.txt");

		bool run() override;

#pragma clang diagnostic push
#pragma ide diagnostic ignored "google-explicit-constructor"

		virtual operator std::vector<unsigned long long>() const {
			return this->primes;
		}

#pragma clang diagnostic pop

		virtual bool outputToFile() {
			if (!ofs.is_open()) {
				return false;
			} else {
				for (auto &v: primes) {
					ofs << v << ' ';
				}
				return true;
			}
		}

		~primesGenVec() override = default;
	};

	class primesGenMT : public primesGen {

	protected:
		unsigned long long lL;
		std::vector<unsigned long long> preSievedPrimes;
	private:
		bool (findPrimes::primesGenMT::*pMethods[5])();

		bool (*pCustomMethods)(const unsigned long long &l, const unsigned long long &u,
		                       const std::vector<unsigned long long> &pSP,
		                       std::ofstream &ofs);

		bool eratosthenesSieve() override;

		bool sundaramSieve() override;

		primesGenMT &operator=(const unsigned long long &i) override {
			uL = i;
			return *this;
		};

	public:
		primesGenMT(const unsigned long long int &l, const unsigned long long int &u,
		            const std::vector<unsigned long long> &pSP, const unsigned int &i = 0,
		            const std::string &s = "primes.txt");

		primesGenMT(const unsigned long long int &l, const unsigned long long int &u,
		            const std::vector<unsigned long long> &pSP,
		            bool (*pM)(const unsigned long long &l, const unsigned long long &u,
		                       const std::vector<unsigned long long> &pSP,
		                       std::ofstream &ofs),
		            const std::string &s);

		bool run() override;

		~primesGenMT() override = default;
	};

	class primesGenVecMT : public primesGenVec {
	protected:
		unsigned long long lL;
		std::vector<unsigned long long> preSievedPrimes;
	private:
		bool (findPrimes::primesGenVecMT::*pMethods[5])();

		bool (*pCustomMethods)(const unsigned long long &l, const unsigned long long &u,
		                       const std::vector<unsigned long long> &pSP,
		                       std::vector<unsigned long long> &pVec);

		bool trialDivision() override;

		bool eratosthenesSieve() override;

		bool eulerSieve() override;

		bool sundaramSieve() override;

		bool incrementalSieve() override;

		std::vector<unsigned long long> primes;

		primesGenVecMT &operator=(const unsigned long long &i) override {
			uL = i;
			return *this;
		};

	public:
		primesGenVecMT(const unsigned long long int &l, const unsigned long long int &u,
		               const std::vector<unsigned long long> &pSP, const unsigned int &i = 0,
		               const std::string &s = "primes.txt");

		primesGenVecMT(const unsigned long long int &l, const unsigned long long int &u,
		               const std::vector<unsigned long long> &pSP,
		               bool (*pM)(const unsigned long long &l, const unsigned long long &u,
		                          const std::vector<unsigned long long> &pSP,
		                          std::vector<unsigned long long> &pVec),
		               const std::string &s);

		bool run() override;

#pragma clang diagnostic push
#pragma ide diagnostic ignored "google-explicit-constructor"

		operator std::vector<unsigned long long>() const override {
			return this->primes;
		}

#pragma clang diagnostic pop

		bool outputToFile() override {
			if (!ofs.is_open()) {
				return false;
			} else {
				for (auto &v: primes) {
					ofs << v << ' ';
				}
				return true;
			}
		}

		~primesGenVecMT() override = default;
	};
} // findPrimes

#endif //FINDPRIMES_PRIMESGEN_H
