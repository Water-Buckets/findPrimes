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
		results->run();
		delete results;
		return 0;
	} else if (threads == 1 && (m == 0 || m == 2 || m == 4)) {
		auto *results = new findPrimes::primesGenVec(n, m, file);
		results->run();
		results->outputToFile();
		delete results;
		return 0;
	} else if (threads > 1 && (m == 1 || m == 3)) {
		auto *sqrtN = new unsigned long long(sqrt(n));

		auto *preSieve = new findPrimes::primesGenVec(*sqrtN, m, file);

		std::thread preSievingThread([preSieve]() { preSieve->run(); });

		unsigned long long perThread = (n - *sqrtN) / threads;
		auto vThread = new std::vector<std::thread>;
		std::vector<findPrimes::primesGenSeg *> results;

		if (preSievingThread.joinable()) {
			preSievingThread.join();
		}

		auto *preSievedPrimes = new std::vector<unsigned long long>(*preSieve);
		delete preSieve;

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

		for (auto &v: *preSievedPrimes) {
			ofs << v << ' ';
		}

		delete preSievedPrimes;

		for (auto &thr: *vThread) {
			if (thr.joinable()) {
				thr.join();
			}
		}

		delete vThread;

		for (int i = 0; i < threads; ++i) {
			std::string fileName = ".temp+" + std::to_string(i) + "+" + file;
			std::ifstream ifs(fileName);
			unsigned long long temp;
			while (ifs >> temp) {
				ofs << temp << ' ';
			}
			std::filesystem::remove(fileName);
		}
		ofs.close();
		return 0;
	} else if (threads > 1 && (m == 0 || m == 2 || m == 4)) {
		unsigned long long sqrtN = sqrt(n);

		auto *preSieve = new findPrimes::primesGenVec(sqrtN, m, file);

		std::thread preSievingThread([preSieve]() { preSieve->run(); });


		unsigned long long perThread = (n - sqrtN) / threads;
		std::vector<std::thread> vThread;
		std::vector<findPrimes::primesGenVecSeg *> results;

		if (preSievingThread.joinable()) {
			preSievingThread.join();
		}

		std::vector<unsigned long long> preSievedPrimes = *preSieve;
		delete preSieve;

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

		for (auto &v: preSievedPrimes) {
			ofs << v << ' ';
		}


		for (auto &thr: vThread) {
			if (thr.joinable()) {
				thr.join();
			}
		}

		for (int i = 0; i < threads; ++i) {
			std::vector<unsigned long long> temp = *results[i];
			for (auto &v: temp) {
				ofs << v << ' ';
			}
			delete results[i];
			std::filesystem::remove(".temp+" + std::to_string(i) + "+" + file);
		}
	} else {
		throw std::invalid_argument("Invalid argument");
	}
}