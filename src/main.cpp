//
// Created by waterbucket on 8/11/23.
//
#include "findPrimes/primesGen.h"
#include <string>
#include <vector>
#include <cmath>
#include <thread>
#include <filesystem>
#include <iostream>
#include <fstream>
#include <chrono>

inline bool isNumeric(const std::string &str) {
	for (char c: str) {
		if (!std::isdigit(c)) {
			return false;
		}
	}
	return true;
}

int main(int argc, char *argv[]) {
	if (argc != 5) {
		throw std::invalid_argument("Wrong argument number.");
	}
	if (!isNumeric(argv[1]) || !isNumeric(argv[2]) || !isNumeric(argv[3])) {
		throw std::invalid_argument("Invalid input.");
	}

	unsigned threads = std::stoi(argv[1]);
	int m = std::stoi(argv[2]);
	unsigned long long n = std::stoull(argv[3]);
	std::string file = argv[4];

	if (n <= 1) {
		throw std::invalid_argument("n must be greater than 1.");
	}

	if (threads == 1 && (m == 1 || m == 3)) {
		auto *results = new findPrimes::primesGen(n, m, file);
		auto start = std::chrono::steady_clock::now();
		results->run();
		auto end = std::chrono::steady_clock::now();
		long long duration = std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count();
		std::cout << "Time elapsed sieving: " << double(duration) / 1000000000 << " seconds." << std::endl;
		delete results;
		return 0;
	} else if (threads == 1 && (m == 0 || m == 2 || m == 4)) {
		auto *results = new findPrimes::primesGenVec(n, m, file);
		auto start = std::chrono::steady_clock::now();
		results->run();
		auto end = std::chrono::steady_clock::now();
		long long duration = std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count();
		std::cout << "Time elapsed sieving: " << double(duration) / 1000000000 << " seconds." << std::endl;
		auto startWrite = std::chrono::steady_clock::now();
		results->outputToFile();
		auto endWrite = std::chrono::steady_clock::now();
		long long durationWrite = std::chrono::duration_cast<std::chrono::nanoseconds>(endWrite - startWrite).count();
		std::cout << "Time elapsed writing to file: " << double(durationWrite) / 1000000000 << " seconds." << std::endl;
		delete results;
		std::cout << "Total time elapsed: " << (duration + durationWrite) / 1000000000 << " seconds." << std::endl;
		return 0;
	} else if (threads > 1 && (m == 1 || m == 3)) {
		auto startTotal = std::chrono::steady_clock::now();

		auto *sqrtN = new unsigned long long(sqrt(n));

		auto *preSieve = new findPrimes::primesGenVec(*sqrtN, m, file);

		auto startPreSieve = std::chrono::steady_clock::now();

		std::thread preSievingThread([preSieve]() { preSieve->run(); });

		unsigned long long perThread = (n - *sqrtN) / threads;
		auto vThread = new std::vector<std::thread>;
		std::vector<findPrimes::primesGenSeg *> results;

		if (preSievingThread.joinable()) {
			preSievingThread.join();
		}

		auto endPreSieve = std::chrono::steady_clock::now();
		long long durationPreSieve = std::chrono::duration_cast<std::chrono::nanoseconds>(
				endPreSieve - startPreSieve).count();
		std::cout << "Time elapsed pre-sieving: " << double(durationPreSieve) / 1000000000 << " seconds." << std::endl;

		auto *preSievedPrimes = new std::vector<unsigned long long>(*preSieve);
		delete preSieve;

		auto start = std::chrono::steady_clock::now();

		for (int i = 0; i < threads; ++i) {
			unsigned long long lL = *sqrtN + i * perThread + 1;
			unsigned long long uL = *sqrtN + (i + 1) * perThread;
			std::string fileName = ".temp+" + std::to_string(i) + "+" + file;

			if (i == threads - 1) {
				uL = n;
			}

			results.push_back(new findPrimes::primesGenSeg(lL, uL, *preSievedPrimes, m, fileName));

			std::thread thr([results, i]() {
				results[i]->run();
				delete results[i];
			});

			vThread->emplace_back(std::move(thr));
		}

		delete sqrtN;

		std::ofstream ofs(file);
		if (!ofs.is_open()) { throw std::runtime_error("Failed to open file."); }

		auto startWritePre = std::chrono::steady_clock::now();

		for (auto &v: *preSievedPrimes) {
			ofs << v << ' ';
		}

		auto endWritePre = std::chrono::steady_clock::now();
		long long durationWritePre = std::chrono::duration_cast<std::chrono::nanoseconds>(
				endWritePre - startWritePre).count();
		std::cout << "Time elapsed writing pre-sieved results to file: " << double(durationWritePre) / 1000000000
		          << " seconds." << std::endl;

		delete preSievedPrimes;

		auto end = std::chrono::steady_clock::now();
		long long duration = std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count();
		std::cout << "Time elapsed sieving: " << double(duration) / 1000000000 << " seconds." << std::endl;

		auto startCombine = std::chrono::steady_clock::now();

		for (int i = 0; i < threads; ++i) {
			(*vThread)[i].join();
			std::string fileName = ".temp+" + std::to_string(i) + "+" + file;
			std::ifstream ifs(fileName);
			unsigned long long temp;
			while (ifs >> temp) {
				ofs << temp << ' ';
			}
			std::filesystem::remove(fileName);
		}
		auto endCombine = std::chrono::steady_clock::now();
		long long durationCombine = std::chrono::duration_cast<std::chrono::nanoseconds>(
				endCombine - startCombine).count();
		std::cout << "Time elapsed combining results: " << double(durationCombine) / 1000000000 << " seconds."
		          << std::endl;
		auto endTotal = std::chrono::steady_clock::now();
		long long durationTotal = std::chrono::duration_cast<std::chrono::nanoseconds>(endTotal - startTotal).count();
		std::cout << "Total time elapsed: " << double(durationTotal) / 1000000000 << " seconds." << std::endl;
		ofs.close();
		return 0;
	} else if (threads > 1 && (m == 0 || m == 2 || m == 4)) {
		auto startTotal = std::chrono::steady_clock::now();

		unsigned long long sqrtN = sqrt(n);

		auto *preSieve = new findPrimes::primesGenVec(sqrtN, m, file);

		auto startPreSieve = std::chrono::steady_clock::now();

		std::thread preSievingThread([preSieve]() { preSieve->run(); });


		unsigned long long perThread = (n - sqrtN) / threads;
		std::vector<std::thread> vThread;
		std::vector<findPrimes::primesGenVecSeg *> results;

		if (preSievingThread.joinable()) {
			preSievingThread.join();
		}

		auto endPreSieve = std::chrono::steady_clock::now();
		long long durationPreSieve = std::chrono::duration_cast<std::chrono::nanoseconds>(
				endPreSieve - startPreSieve).count();
		std::cout << "Time elapsed pre-sieving: " << double(durationPreSieve) / 1000000000 << " seconds." << std::endl;

		std::vector<unsigned long long> preSievedPrimes = *preSieve;
		delete preSieve;

		auto start = std::chrono::steady_clock::now();

		for (int i = 0; i < threads; ++i) {
			unsigned long long lL = sqrtN + i * perThread + 1;
			unsigned long long uL = sqrtN + (i + 1) * perThread;
			std::string fileName = ".temp+" + std::to_string(i) + "+" + file;

			if (i == threads - 1) {
				uL = n;
			}

			results.push_back(new findPrimes::primesGenVecSeg(lL, uL, preSievedPrimes, m, fileName));

			std::thread thr([results, i]() { results[i]->run(); });

			vThread.emplace_back(std::move(thr));
		}

		std::ofstream ofs(file);

		if (!ofs.is_open()) { throw std::runtime_error("Failed to open file."); }

		auto startWritePre = std::chrono::steady_clock::now();

		for (auto &v: preSievedPrimes) {
			ofs << v << ' ';
		}

		auto endWritePre = std::chrono::steady_clock::now();
		long long durationWritePre = std::chrono::duration_cast<std::chrono::nanoseconds>(
				endWritePre - startWritePre).count();
		std::cout << "Time elapsed writing pre-sieved results to file: " << double(durationWritePre) / 1000000000
		          << " seconds." << std::endl;

		auto end = std::chrono::steady_clock::now();
		long long duration = std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count();
		std::cout << "Time elapsed sieving: " << double(duration) / 1000000000 << " seconds." << std::endl;

		auto startWrite = std::chrono::steady_clock::now();

		for (int i = 0; i < threads; ++i) {
			vThread[i].join();
			results[i]->output(ofs);
			delete results[i];
			std::filesystem::remove(".temp+" + std::to_string(i) + "+" + file);
		}

		auto endWrite = std::chrono::steady_clock::now();
		long long durationWrite = std::chrono::duration_cast<std::chrono::nanoseconds>(endWrite - startWrite).count();
		std::cout << "Time elapsed writing to file: " << double(durationWrite) / 1000000000 << " seconds." << std::endl;
		auto endTotal = std::chrono::steady_clock::now();
		long long durationTotal = std::chrono::duration_cast<std::chrono::nanoseconds>(endTotal - startTotal).count();
		std::cout << "Total time elapsed: " << double(durationTotal) / 1000000000 << " seconds." << std::endl;
		return 0;
	} else {
		throw std::invalid_argument("Invalid argument");
	}
}