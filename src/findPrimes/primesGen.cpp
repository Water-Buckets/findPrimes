//
// Created by waterbucket on 8/13/23.
//

#include "primesGen.h"

namespace findPrimes {

	inline namespace v1 {
		primesGen::primesGen(const unsigned long long int &u, const unsigned int &i, const std::string &s) : ofs(
				std::ofstream(s)), pMethods{nullptr, &primesGen::eratosthenesSieve, nullptr, &primesGen::sundaramSieve,
		                                    nullptr} {
			fileName = s;
			uL = u;
			method = i;
			pCustomMethods = nullptr;
		}

		primesGen::primesGen(const unsigned long long int &u,
		                     bool (*pM)(const unsigned long long int &, std::ofstream &),
		                     const std::string &s) : ofs(std::ofstream(s)),
		                                             pMethods{nullptr, nullptr, nullptr, nullptr, nullptr} {
			fileName = s;
			uL = u;
			method = 0;
			pCustomMethods = pM;
		}

		bool primesGen::eratosthenesSieve() {
			if (!ofs.is_open()) {
				return false;
			} else {
				if (uL >= 2) ofs << 2 << ' ';
				unsigned long long k = uL + 1;
				std::vector<bool> isPrime(k, true);
				for (unsigned long long i = 3; i <= uL; i += 2) {
					if (isPrime[i]) {
						ofs << i << ' ';
						for (unsigned long long j = i * i; j <= k; j += 2 * i) {
							isPrime[j] = false;
						}
					}
				}
				return true;
			}
		}

		bool primesGen::sundaramSieve() {
			if (!ofs.is_open()) {
				return false;
			} else {
				unsigned long long k = (uL - 1) / 2;
				std::vector<bool> isPrime(k + 1, true);
				unsigned long long h = (unsigned long long) ((sqrt(1 + 2 * k) - 1) / 2) + 1;
				for (unsigned long long i = 1; i <= h; ++i) {
					unsigned long long p = 2 * i + 1;
					for (unsigned long long j = 2 * i + 2 * i * i; j <= k; j += p) {
						isPrime[j] = false;
					}
				}
				if (uL >= 2) ofs << 2 << ' ';
				for (unsigned long long i = 1; i < k + 1; ++i) {
					if (isPrime[i])
						ofs << (2 * i + 1) << ' ';
				}
				return true;
			}
		}

		bool primesGen::run() {
			if (pCustomMethods == nullptr) {
				if (method == 0 || method == 2 || method == 4) {
					throw std::invalid_argument("Unsupported method.");
				} else {
					return (this->*pMethods[method])();
				}
			} else {
				return (*pCustomMethods)(uL, ofs);
			}
		}

		primesGenVec::primesGenVec(const unsigned long long int &u, const unsigned int &i, const std::string &s)
				: primesGen(u, i, s),
				  pMethods{&primesGenVec::trialDivision, &primesGenVec::eratosthenesSieve, &primesGenVec::eulerSieve,
				           &primesGenVec::sundaramSieve, &primesGenVec::incrementalSieve} {
			pCustomMethods = nullptr;
		}

		primesGenVec::primesGenVec(const unsigned long long int &u,
		                           bool (*pM)(const unsigned long long int &, std::vector<unsigned long long int> &),
		                           const std::string &s) : primesGen(u, nullptr, s),
		                                                   pMethods{nullptr, nullptr, nullptr, nullptr, nullptr} {
			pCustomMethods = pM;
		}

		bool primesGenVec::trialDivision() {
			if (uL >= 2) primes.push_back(2);
			for (unsigned long long i = 3; i <= uL; i += 2) {
				bool isPrime = false;
				for (unsigned long long p: primes) {
					if (p * p > i) break;
					if (i % p == 0) {
						isPrime = true;
						break;
					}
				}
				if (!isPrime) primes.push_back(i);
			}
			return true;
		}

		bool primesGenVec::eratosthenesSieve() {
			if (uL >= 2) primes.push_back(2);
			unsigned long long k = uL + 1;
			std::vector<bool> isPrime(k, true);
			for (unsigned long long i = 3; i <= uL; i += 2) {
				if (isPrime[i]) {
					primes.push_back(i);
					for (unsigned long long j = i * i; j <= k; j += 2 * i) {
						isPrime[j] = false;
					}
				}
			}
			return true;
		}

		bool primesGenVec::eulerSieve() {
			std::vector<bool> isPrime(uL + 1, true);
			for (unsigned long long i = 2; i <= uL; ++i) {
				if (isPrime[i]) {
					primes.push_back(i);
				}
				for (unsigned long long j = 0; j < primes.size() && i * primes[j] <= uL; ++j) {
					isPrime[i * primes[j]] = false;
					if (i % primes[j] == 0) {
						break;
					}
				}
			}
			return true;
		}

		bool primesGenVec::sundaramSieve() {
			unsigned long long k = (uL - 1) / 2;
			std::vector<bool> isPrime(k + 1, true);
			unsigned long long h = (unsigned long long) ((sqrt(1 + 2 * k) - 1) / 2) + 1;
			for (unsigned long long i = 1; i <= h; ++i) {
				unsigned long long p = 2 * i + 1;
				for (unsigned long long j = 2 * i + 2 * i * i; j <= k; j += p) {
					isPrime[j] = false;
				}
			}
			if (uL >= 2) primes.push_back(2);
			for (unsigned long long i = 1; i < k + 1; ++i) {
				if (isPrime[i])
					primes.push_back(2 * i + 1);
			}
			return true;
		}

		bool primesGenVec::incrementalSieve() {
			std::vector<unsigned long long> mp;
			for (unsigned long long i = 2; i < uL + 1; ++i) {
				bool flag = true;
				unsigned long long limit = sqrt(i);
				for (unsigned long long k = 0; k < primes.size(); ++k) {
					if (primes[k] > limit) break;
					while (mp[k] < i) {
						mp[k] += primes[k];
					}
					if (mp[k] == i) {
						flag = false;
						break;
					}
				}
				if (flag) {
					primes.push_back(i);
					mp.push_back(i * i);
				}
			}
			return true;
		}

		bool primesGenVec::run() {
			if (pCustomMethods == nullptr) {
				return (this->*pMethods[method])();
			} else {
				return (*pCustomMethods)(uL, primes);
			}
		}


		primesGenSeg::primesGenSeg(const unsigned long long int &l, const unsigned long long int &u,
		                           const std::vector<unsigned long long> &pSP, const unsigned int &i,
		                           const std::string &s) : primesGen(
				u, i, s), pMethods{nullptr, &primesGenSeg::eratosthenesSieve, nullptr, &primesGenSeg::sundaramSieve,
		                           nullptr} {
			lL = l;
			preSievedPrimes = pSP;
			pCustomMethods = nullptr;

		}

		primesGenSeg::primesGenSeg(const unsigned long long int &l, const unsigned long long int &u,
		                           const std::vector<unsigned long long> &pSP,
		                           bool (*pM)(const unsigned long long &l, const unsigned long long &u,
		                                      const std::vector<unsigned long long> &pSP,
		                                      std::ofstream &ofs),
		                           const std::string &s) : primesGen(u, nullptr, s),
		                                                   pMethods{nullptr, nullptr, nullptr, nullptr, nullptr} {
			lL = l;
			preSievedPrimes = pSP;
			pCustomMethods = pM;
		}

		bool primesGenSeg::eratosthenesSieve() {
			if (!ofs.is_open()) {
				return false;
			} else {
				std::vector<bool> isPrime(uL - lL + 1, true);
				for (auto prime: preSievedPrimes) {
					unsigned long long firstMultiple = std::max(prime * prime, (lL + prime - 1) / prime * prime);
					for (unsigned long long j = firstMultiple; j <= uL; j += prime) {
						isPrime[j - lL] = false;
					}
				}
				for (unsigned long long i = (lL % 2 != 0 ? lL : lL + 1); i <= uL; i += 2) {
					if (isPrime[i - lL]) {
						ofs << i << ' ';
					}
				}
				return true;
			}
		}

		bool primesGenSeg::sundaramSieve() {
			if (!ofs.is_open()) {
				return false;
			} else {
				unsigned long long newLL = (lL + 1) / 2;
				unsigned long long newUL = (uL - 1) / 2;

				std::vector<bool> isPrime(newUL - newLL + 1, true);

				unsigned long long h = (unsigned long long) ((sqrt(1 + 2 * newUL) - 1) / 2) + 1;

				for (unsigned long long i = 1; i <= h; ++i) {
					for (unsigned long long j = i; j <= 2 * (newUL - i) / (2 * i + 1); ++j) {
						unsigned long long index = i + j + 2 * i * j;
						if (index >= newLL && index <= newUL) {
							isPrime[index - newLL] = false;
						}
					}
				}

				if (2 >= lL && 2 <= uL) ofs << 2 << ' ';

				for (unsigned long long i = 0; i <= newUL - newLL; ++i) {
					if (isPrime[i]) {
						ofs << (2 * (i + newLL) + 1) << ' ';
					}
				}
				return true;
			}
		}

		bool primesGenSeg::run() {
			if (pCustomMethods == nullptr) {
				if (method == 0 || method == 2 || method == 4) {
					throw std::invalid_argument("Unsupported method.");
				} else {
					return (this->*pMethods[method])();
				}
			} else {
				return (*pCustomMethods)(lL, uL, preSievedPrimes, ofs);
			}
		}


		primesGenVecSeg::primesGenVecSeg(const unsigned long long int &l, const unsigned long long int &u,
		                                 const std::vector<unsigned long long int> &pSP, const unsigned int &i,
		                                 const std::string &s) : primesGenVec(u, i, s),
		                                                         pMethods{&primesGenVecSeg::trialDivision,
		                                                                  &primesGenVecSeg::eratosthenesSieve,
		                                                                  &primesGenVecSeg::eulerSieve,
		                                                                  &primesGenVecSeg::sundaramSieve,
		                                                                  &primesGenVecSeg::incrementalSieve} {
			lL = l;
			preSievedPrimes = pSP;
			pCustomMethods = nullptr;
		}

		primesGenVecSeg::primesGenVecSeg(const unsigned long long int &l, const unsigned long long int &u,
		                                 const std::vector<unsigned long long int> &pSP,
		                                 bool (*pM)(const unsigned long long int &, const unsigned long long int &,
		                                            const std::vector<unsigned long long int> &,
		                                            std::vector<unsigned long long> &pVec),
		                                 const std::string &s) : primesGenVec(u, nullptr, s),
		                                                         pMethods{nullptr, nullptr, nullptr, nullptr, nullptr} {
			lL = l;
			preSievedPrimes = pSP;
			pCustomMethods = pM;
		}

		bool primesGenVecSeg::trialDivision() {
			if (lL <= 2 && uL >= 2) primes.push_back(2);
			if (lL % 2 == 0) ++lL;
			for (unsigned long long i = lL; i <= uL; i += 2) {
				bool isPrime = true;
				for (unsigned long long p: preSievedPrimes) {
					if (p * p > i) break;
					if (i % p == 0) {
						isPrime = false;
						break;
					}
				}
				if (isPrime) primes.push_back(i);
			}
			return true;
		}

		bool primesGenVecSeg::eratosthenesSieve() {
			std::vector<bool> isPrime(uL - lL + 1, true);
			for (auto prime: preSievedPrimes) {
				unsigned long long firstMultiple = std::max(prime * prime, (lL + prime - 1) / prime * prime);
				for (unsigned long long j = firstMultiple; j <= uL; j += prime) {
					isPrime[j - lL] = false;
				}
			}
			for (unsigned long long i = (lL % 2 != 0 ? lL : lL + 1); i <= uL; i += 2) {
				if (isPrime[i - lL]) {
					primes.push_back(i);
				}
			}
			return true;
		}

		bool primesGenVecSeg::eulerSieve() {
			std::vector<bool> isPrime(uL - lL + 1, true);

			for (unsigned long long p: preSievedPrimes) {
				for (unsigned long long i = std::max(p * p, (lL + p - 1) / p * p); i <= uL; i += p) {
					isPrime[i - lL] = false;
				}
			}

			if (lL == 1) isPrime[0] = false;
			if (lL <= 2 && uL >= 2) primes.push_back(2);

			for (unsigned long long i = lL % 2 == 0 ? lL + 1 : lL; i <= uL; i += 2) {
				if (isPrime[i - lL]) {
					primes.push_back(i);
				}
			}
			return true;
		}

		bool primesGenVecSeg::sundaramSieve() {
			unsigned long long newLL = (lL + 1) / 2;
			unsigned long long newUL = (uL - 1) / 2;

			std::vector<bool> isPrime(newUL - newLL + 1, true);

			unsigned long long h = (unsigned long long) ((sqrt(1 + 2 * newUL) - 1) / 2) + 1;

			for (unsigned long long i = 1; i <= h; ++i) {
				for (unsigned long long j = i; j <= 2 * (newUL - i) / (2 * i + 1); ++j) {
					unsigned long long index = i + j + 2 * i * j;
					if (index >= newLL && index <= newUL) {
						isPrime[index - newLL] = false;
					}
				}
			}

			if (2 >= lL && 2 <= uL) primes.push_back(2);

			for (unsigned long long i = 0; i <= newUL - newLL; ++i) {
				if (isPrime[i]) {
					primes.push_back(2 * (i + newLL) + 1);
				}
			}
			return true;
		}

		bool primesGenVecSeg::incrementalSieve() {
			primes = preSievedPrimes;
			std::vector<unsigned long long> mp(primes.size());
			std::vector<unsigned long long> results;

			// Initialize the multiples of pre-sieved primes
			for (unsigned long long k = 0; k < primes.size(); ++k) {
				mp[k] = ((lL + primes[k] - 1) / primes[k]) * primes[k];
			}

			for (unsigned long long i = lL; i <= uL; ++i) {
				bool isPrime = true;
				unsigned long long limit = sqrt(i);
				for (unsigned long long k = 0; k < primes.size(); ++k) {
					if (primes[k] > limit) break;
					while (mp[k] < i) {
						mp[k] += primes[k];
					}
					if (mp[k] == i) {
						isPrime = false;
						break;
					}
				}
				if (isPrime) {
					primes.push_back(i);
					results.push_back(i);
					mp.push_back(i * i);
				}
			}
			primes = results;
			return true;
		}

		bool primesGenVecSeg::run() {
			if (pCustomMethods == nullptr) {
				return (this->*pMethods[method])();
			} else {
				return (*pCustomMethods)(lL, uL, preSievedPrimes, primes);
			}
		}
	}

	namespace v2 {

		primesGen::primesGen(const unsigned long long int &u, const unsigned int &m, const std::string &f)
				: pMethods{nullptr, &primesGen::eratosthenesSieve, nullptr, &primesGen::sundaramSieve, nullptr} {
			uL = u;
			method = m;
			pCustomMethods = nullptr;
			file = f;
		}

		primesGen::primesGen(const unsigned long long int &u,
		                     void (*pM)(const unsigned long long int &, const std::string &), const std::string &f)
				: pMethods{nullptr} {
			uL = u;
			pCustomMethods = pM;
			method = 0;
			file = f;
		}

		void primesGen::run() {
			if (pCustomMethods == nullptr) {
				if (method == 1 || method == 3) {
					(this->*pMethods[method])();
				} else {
					throw std::invalid_argument("Invalid method.");
				}
			} else {
				(*pCustomMethods)(uL, file);
			}
		}

		void primesGen::eratosthenesSieve() {
			std::ofstream ofs(file);
			if (!ofs.is_open()) {
				throw std::runtime_error("Failed to open file.");
			} else {
				if (uL >= 2) ofs << 2 << ' ';
				unsigned long long k = uL + 1;
				std::vector<bool> isPrime(k, true);
				for (unsigned long long i = 3; i <= uL; i += 2) {
					if (isPrime[i]) {
						ofs << i << ' ';
						for (unsigned long long j = i * i; j <= k; j += 2 * i) {
							isPrime[j] = false;
						}
					}
				}
				ofs.close();
			}
		}

		void primesGen::sundaramSieve() {
			std::ofstream ofs(file);
			if (!ofs.is_open()) {
				throw std::runtime_error("Failed to open file.");
			} else {
				unsigned long long k = (uL - 1) / 2;
				std::vector<bool> isPrime(k + 1, true);
				unsigned long long h = (unsigned long long) ((sqrt(1 + 2 * k) - 1) / 2) + 1;
				for (unsigned long long i = 1; i <= h; ++i) {
					unsigned long long p = 2 * i + 1;
					for (unsigned long long j = 2 * i + 2 * i * i; j <= k; j += p) {
						isPrime[j] = false;
					}
				}
				if (uL >= 2) ofs << 2 << ' ';
				for (unsigned long long i = 1; i < k + 1; ++i) {
					if (isPrime[i])
						ofs << (2 * i + 1) << ' ';
				}
			}
		}

		primesGenVec::primesGenVec(const unsigned long long &u, const unsigned int &m, const std::string &f)
				: primesGen(u, m, f),
				  pMethods{&primesGenVec::trialDivision, &primesGenVec::eratosthenesSieve, &primesGenVec::eulerSieve,
				           &primesGenVec::sundaramSieve, &primesGenVec::incrementalSieve} {
			pCustomMethods = nullptr;
		}

		primesGenVec::primesGenVec(const unsigned long long int &u,
		                           void (*pM)(const unsigned long long int &, std::vector<unsigned long long int> &),
		                           const std::string &f) : primesGen(u, nullptr, f), pMethods{nullptr} {
			pCustomMethods = pM;
		}

		void primesGenVec::trialDivision() {
			if (uL >= 2) primes.push_back(2);
			for (unsigned long long i = 3; i <= uL; i += 2) {
				bool isPrime = false;
				for (unsigned long long p: primes) {
					if (p * p > i) break;
					if (i % p == 0) {
						isPrime = true;
						break;
					}
				}
				if (!isPrime) primes.push_back(i);
			}
		}

		void primesGenVec::eratosthenesSieve() {
			if (uL >= 2) primes.push_back(2);
			unsigned long long k = uL + 1;
			std::vector<bool> isPrime(k, true);
			for (unsigned long long i = 3; i <= uL; i += 2) {
				if (isPrime[i]) {
					primes.push_back(i);
					for (unsigned long long j = i * i; j <= k; j += 2 * i) {
						isPrime[j] = false;
					}
				}
			}
		}

		void primesGenVec::eulerSieve() {
			std::vector<bool> isPrime(uL + 1, true);
			if (uL >= 2) primes.push_back(2);
			for (unsigned long long i = 3; i <= uL; i += 2) {
				if (isPrime[i]) {
					primes.push_back(i);
				}
				for (unsigned long long j = 0; j < primes.size() && i * primes[j] * 2 <= uL; ++j) {
					isPrime[i * primes[j] * 2] = false;
					if (i % (primes[j] * 2) == 0) {
						break;
					}
				}
			}
		}

		void primesGenVec::sundaramSieve() {
			unsigned long long k = (uL - 1) / 2;
			std::vector<bool> isPrime(k + 1, true);
			unsigned long long h = (unsigned long long) ((sqrt(1 + 2 * k) - 1) / 2) + 1;
			for (unsigned long long i = 1; i <= h; ++i) {
				unsigned long long p = 2 * i + 1;
				for (unsigned long long j = 2 * i + 2 * i * i; j <= k; j += p) {
					isPrime[j] = false;
				}
			}
			if (uL >= 2) primes.push_back(2);
			for (unsigned long long i = 1; i < k + 1; ++i) {
				if (isPrime[i])
					primes.push_back(2 * i + 1);
			}
		}

		void primesGenVec::incrementalSieve() {
			std::vector<unsigned long long> mp;
			for (unsigned long long i = 2; i < uL + 1; ++i) {
				bool flag = true;
				unsigned long long limit = sqrt(i);
				for (unsigned long long k = 0; k < primes.size(); ++k) {
					if (primes[k] > limit) break;
					while (mp[k] < i) {
						mp[k] += primes[k];
					}
					if (mp[k] == i) {
						flag = false;
						break;
					}
				}
				if (flag) {
					primes.push_back(i);
					mp.push_back(i * i);
				}
			}
		}

		void primesGenVec::run() {
			if (pCustomMethods == nullptr) {
				if (method == 1 || method == 3) {
					(this->*pMethods[method])();
				} else {
					throw std::invalid_argument("Invalid method.");
				}
			} else {
				(*pCustomMethods)(uL, primes);
			}
			primes.shrink_to_fit();
		}
	}
} // findPrimes