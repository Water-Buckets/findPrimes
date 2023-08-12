//
// Created by waterbucket on 8/13/23.
//

#include "primesGen.h"

namespace findPrimes {
	primesGen::primesGen(const unsigned long long int &u, const unsigned int &i, const std::string &s) : ofs(
			std::ofstream(s)), pMethods{nullptr, &primesGen::eratosthenesSieve, nullptr, &primesGen::sundaramSieve,
	                                    nullptr} {
		fileName = s;
		uL = u;
		method = i;
		pCustomMethods = nullptr;
	}

	primesGen::primesGen(const unsigned long long int &u, bool (*pM)(const unsigned long long int &, std::ofstream &),
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


	primesGenMT::primesGenMT(const unsigned long long int &l, const unsigned long long int &u,
	                         const std::vector<unsigned long long> &pSP, const unsigned int &i,
	                         const std::string &s) : primesGen(
			u, i, s), pMethods{nullptr, &primesGenMT::eratosthenesSieve, nullptr, &primesGenMT::sundaramSieve,
	                           nullptr} {
		lL = l;
		preSievedPrimes = pSP;
		pCustomMethods = nullptr;

	}

	primesGenMT::primesGenMT(const unsigned long long int &l, const unsigned long long int &u,
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

	bool primesGenMT::eratosthenesSieve() {
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

	bool primesGenMT::sundaramSieve() {
		if (!ofs.is_open()) {
			return false;
		} else {
			unsigned long long newLL = (lL + 1) / 2;
			unsigned long long newUL = (uL - 1) / 2;

			std::vector<bool> isPrime(newUL + 1, true);

			unsigned long long h = (unsigned long long) ((sqrt(1 + 2 * newUL) - 1) / 2) + 1;

			for (unsigned long long i = 1; i <= h; ++i) {
				unsigned long long p = 2 * i + 1;
				unsigned long long start = std::max(2 * i + 2 * i * i, (newLL + i - 1) / i * i);
				for (unsigned long long j = start; j <= newUL; j += p) {
					isPrime[j] = false;
				}
			}

			if (2 >= 2 * newLL + 1 && 2 <= 2 * newUL + 1) ofs << 2 << ' ';

			for (unsigned long long i = newLL; i <= newUL; ++i) {
				if (isPrime[i])
					ofs << (2 * i + 1) << ' ';
			}
			return true;
		}
	}

	bool primesGenMT::run() {
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


	primesGenVecMT::primesGenVecMT(const unsigned long long int &l, const unsigned long long int &u,
	                               const std::vector<unsigned long long int> &pSP, const unsigned int &i,
	                               const std::string &s) : primesGenVec(u, i, s),
	                                                       pMethods{&primesGenVecMT::trialDivision,
	                                                                &primesGenVecMT::eratosthenesSieve,
	                                                                &primesGenVecMT::eulerSieve,
	                                                                &primesGenVecMT::sundaramSieve,
	                                                                &primesGenVecMT::incrementalSieve} {
		lL = l;
		preSievedPrimes = pSP;
		pCustomMethods = nullptr;
	}

	primesGenVecMT::primesGenVecMT(const unsigned long long int &l, const unsigned long long int &u,
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

	bool primesGenVecMT::trialDivision() {
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

	bool primesGenVecMT::eratosthenesSieve() {
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

	bool primesGenVecMT::eulerSieve() {
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

	bool primesGenVecMT::sundaramSieve() {
		unsigned long long newLL = (lL + 1) / 2;
		unsigned long long newUL = (uL - 1) / 2;

		std::vector<bool> isPrime(newUL + 1, true);

		unsigned long long h = (unsigned long long) ((sqrt(1 + 2 * newUL) - 1) / 2) + 1;

		for (unsigned long long i = 1; i <= h; ++i) {
			unsigned long long p = 2 * i + 1;
			unsigned long long start = std::max(2 * i + 2 * i * i, (newLL + i - 1) / i * i);
			for (unsigned long long j = start; j <= newUL; j += p) {
				isPrime[j] = false;
			}
		}

		if (2 >= 2 * newLL + 1 && 2 <= 2 * newUL + 1) primes.push_back(2);

		for (unsigned long long i = newLL; i <= newUL; ++i) {
			if (isPrime[i])
				primes.push_back(2 * i + 1);
		}
		return true;
	}

	bool primesGenVecMT::incrementalSieve() {
		primes = preSievedPrimes;
		std::vector<unsigned long long> mp(primes.size());

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
				mp.push_back(i * i);
			}
		}
		return true;
	}

	bool primesGenVecMT::run() {
		if (pCustomMethods == nullptr) {
			return (this->*pMethods[method])();
		} else {
			return (*pCustomMethods)(lL, uL, preSievedPrimes, primes);
		}
	}


} // findPrimes