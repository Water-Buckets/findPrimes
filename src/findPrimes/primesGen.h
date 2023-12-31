//
// Created by waterbucket on 8/13/23.
//

#ifndef FINDPRIMES_PRIMESGEN_H
#define FINDPRIMES_PRIMESGEN_H

#include <fstream>
#include <string>
#include <vector>
#include <cmath>
#include <iostream>

namespace findPrimes {

	/*inline*/ namespace v1 {

		class primesGen {
		protected:

			unsigned long long uL;
			std::ofstream ofs;
			unsigned method;
			std::string fileName;

		private:
			bool (findPrimes::v1::primesGen::*pMethods[5])();

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

			virtual ~primesGen() {
				ofs.close();
			};

		};

		class primesGenVec : public primesGen {
		protected:
			std::vector<unsigned long long> primes;
		private:

			bool (findPrimes::v1::primesGenVec::*pMethods[5])();

			virtual bool trialDivision();

			bool eratosthenesSieve() override;

			virtual bool eulerSieve();

			bool sundaramSieve() override;

			virtual bool incrementalSieve();

			bool (*pCustomMethods)(const unsigned long long &n, std::vector<unsigned long long> &pVec);

		public:
			explicit primesGenVec(const unsigned long long &u, const unsigned &i = 0,
			                      const std::string &s = "primes.txt");

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

			~primesGenVec() override {
				ofs.close();
			};
		};

		class primesGenSeg : public primesGen {

		protected:
			unsigned long long lL;
			std::vector<unsigned long long> preSievedPrimes;
		private:
			bool (findPrimes::v1::primesGenSeg::*pMethods[5])();

			bool (*pCustomMethods)(const unsigned long long &l, const unsigned long long &u,
			                       const std::vector<unsigned long long> &pSP, std::ofstream &ofs);

			bool eratosthenesSieve() override;

			bool sundaramSieve() override;

			primesGenSeg &operator=(const unsigned long long &i) override {
				uL = i;
				return *this;
			};

		public:
			primesGenSeg(const unsigned long long int &l, const unsigned long long int &u,
			             const std::vector<unsigned long long> &pSP, const unsigned int &i = 0,
			             const std::string &s = "primes.txt");

			primesGenSeg(const unsigned long long int &l, const unsigned long long int &u,
			             const std::vector<unsigned long long> &pSP,
			             bool (*pM)(const unsigned long long &l, const unsigned long long &u,
			                        const std::vector<unsigned long long> &pSP, std::ofstream &ofs),
			             const std::string &s);

			bool run() override;

			~primesGenSeg() override {
				ofs.close();
			};
		};

		class primesGenVecSeg : public primesGenVec {
		protected:
			unsigned long long lL;
			std::vector<unsigned long long> preSievedPrimes;
		private:
			bool (findPrimes::v1::primesGenVecSeg::*pMethods[5])();

			bool (*pCustomMethods)(const unsigned long long &l, const unsigned long long &u,
			                       const std::vector<unsigned long long> &pSP, std::vector<unsigned long long> &pVec);

			bool trialDivision() override;

			bool eratosthenesSieve() override;

			bool eulerSieve() override;

			bool sundaramSieve() override;

			bool incrementalSieve() override;


			primesGenVecSeg &operator=(const unsigned long long &i) override {
				uL = i;
				return *this;
			};

		public:
			primesGenVecSeg(const unsigned long long int &l, const unsigned long long int &u,
			                const std::vector<unsigned long long> &pSP, const unsigned int &i = 0,
			                const std::string &s = "primes.txt");

			primesGenVecSeg(const unsigned long long int &l, const unsigned long long int &u,
			                const std::vector<unsigned long long> &pSP,
			                bool (*pM)(const unsigned long long &l, const unsigned long long &u,
			                           const std::vector<unsigned long long> &pSP,
			                           std::vector<unsigned long long> &pVec), const std::string &s);

			bool run() override;

			~primesGenVecSeg() override {
				ofs.close();
			};
		};

	}

	inline namespace v2 {
		//improvements of v1, including DMA related features, optimised functions and algorithms, reduce memory usage.
		//yet to be done.

		class primesGen {
		protected:
			unsigned long long uL;
			std::string file;
			unsigned method;
		private:
			void (findPrimes::v2::primesGen::*pMethods[5])();

			virtual void eratosthenesSieve();

			virtual void sundaramSieve();

			void (*pCustomMethods)(const unsigned long long &n, const std::string &s);

		public:
			primesGen(const unsigned long long &u, const unsigned &m, const std::string &f = "primes.txt");

			primesGen(const unsigned long long &u, void (*pM)(const unsigned long long &n, const std::string &s),
			          const std::string &f = "primes.txt");

			std::string getFileName() { return file; };

			virtual void run();
		};

		class primesGenVec : virtual public primesGen {
		protected:
			std::vector<unsigned long long> primes;

		private:
			void (findPrimes::v2::primesGenVec::*pMethods[5])();

			virtual void trialDivision();

			void eratosthenesSieve() override;

			virtual void eulerSieve();

			void sundaramSieve() override;

			virtual void incrementalSieve();

			void (*pCustomMethods)(const unsigned long long &n, std::vector<unsigned long long> &pVec);

		public:

			primesGenVec(const unsigned long long &u, const unsigned &m, const std::string &f = "primes.txt");


			primesGenVec(const unsigned long long &u,
			             void (*pM)(const unsigned long long &n, std::vector<unsigned long long> &pVec),
			             const std::string &f = "primes.txt");

			void run() override;

#pragma clang diagnostic push
#pragma ide diagnostic ignored "google-explicit-constructor"

			virtual operator std::vector<unsigned long long>() const {
				return this->primes;
			}

#pragma clang diagnostic pop

			void output(std::ostream &o) const {
				for (auto &i: primes) {
					o << i << ' ';
				}
			}

			virtual void outputToFile() {
				std::ofstream ofs(file);
				if (!ofs.is_open()) {
					throw std::runtime_error("Failed to open file.");
				} else {
					output(ofs);
					ofs.close();
				}
			}
		};

		class primesGenSeg : virtual public primesGen {
		protected:
			unsigned long long lL;
			std::vector<unsigned long long> preSievedPrimes;
		private:
			void (findPrimes::v2::primesGenSeg::*pMethods[5])();

			void (*pCustomMethods)(const unsigned long long &l, const unsigned long long &u,
			                       const std::vector<unsigned long long> &pSP, const std::string &s);

			void eratosthenesSieve() override;

			void sundaramSieve() override;

		public:
			primesGenSeg(const unsigned long long &l, const unsigned long long &u,
			             const std::vector<unsigned long long> &pSP, const unsigned &m, const std::string &f);

			primesGenSeg(const unsigned long long &l, const unsigned long long &u,
			             const std::vector<unsigned long long> &pSP,
			             void (*pM)(const unsigned long long &l, const unsigned long long &u,
			                        const std::vector<unsigned long long> &pSP, const std::string &s),
			             const std::string &f);

			void run() override;
		};

		class primesGenVecSeg : public primesGenVec {
		protected:
			unsigned long long lL;
			std::vector<unsigned long long> preSievedPrimes;
		private:
			void (findPrimes::v2::primesGenVecSeg::*pMethods[5])();

			void (*pCustomMethods)(const unsigned long long &l, const unsigned long long &u,
			                       const std::vector<unsigned long long> &pSP, std::vector<unsigned long long> &pVec);

			void trialDivision() override;

			void eratosthenesSieve() override;

			void eulerSieve() override;

			void sundaramSieve() override;

			void incrementalSieve() override;

		public:
			primesGenVecSeg(const unsigned long long &l, const unsigned long long &u,
			                const std::vector<unsigned long long> &pSP, const unsigned &m, const std::string &f);

			primesGenVecSeg(const unsigned long long &l, const unsigned long long &u,
			                const std::vector<unsigned long long> &pSP,
			                void (*pM)(const unsigned long long &l, const unsigned long long &u,
			                           const std::vector<unsigned long long> &pSP,
			                           std::vector<unsigned long long> &pVecs), const std::string &f);

			void run() override;

		};
	}
} // findPrimes

#endif //FINDPRIMES_PRIMESGEN_H
