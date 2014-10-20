/**
 *
 * Pure c++ implementation
 *
 */

#include <iostream>
#include <cstring>
#include <cmath>
#include <future>

namespace hash_pure_cpp{

	typedef long long Int64;
	typedef unsigned long long ull;

#define LETTERS_TO_FILL 9

	Int64 TARGET_HASH = 910897038977002;
	char* letters = "acdegilmnoprstuw";


	struct NineLeters{

		NineLeters(){ data[LETTERS_TO_FILL] = '\0'; }

		/** get iteration variable and fill internal char array with the data */
		void deconstruct(unsigned long long iter_i){
			const unsigned int len = LETTERS_TO_FILL;
			for (unsigned int i = 0; i < len; i++){
				auto tmp = (iter_i >> (i * 4)) & 15;
				data[i] = letters[tmp];
			}
		}

		char data[LETTERS_TO_FILL + 1];
	};

	int lookup[26] = { 0, 0, 1, 2, 3, 0, 4, 0, 5, 0, 0, 6, 7, 8, 9, 10, 0, 11, 12, 13, 14, 0, 15, 0, 0, 0 };

	Int64 hash(const char* c){
		Int64 h = 7;
		for (unsigned int i = 0; i < 7; i++) {
			h = (h * 37 + lookup[c[i] - 'a']);
		}
		return h;
	}

	/* executed by each thread */
	std::string calc(int id, ull start, ull end){
		std::cout << "[" << id << "] " << start << " : " << end << '\n';

		std::string res = "_";
		auto diff = end - start;
		diff /= 100;
		int per = 0; // progress
		
		NineLeters nl;

		for (auto i = start; i < end; i++) {
			// report progres
			if ((i % diff) == 0){
				std::cout << "[" << id << "] " << per << '\n';
				++per;
			}
			
			// get letters combination for iteration
			nl.deconstruct(i);
			
			// get hash
			Int64 hash_ = hash(nl.data);

			// check match
			if (hash_ == TARGET_HASH){
				std::cout << "FIN found'" << nl.data << "'" << '\n';
				res = nl.data;
				break;
			}
		}
		std::cout << "--- [" << id << "] Fin---" << '\n';
		return res;
	}

	// start 13:50:4
	// end 14:49:12
	// 14:40:2 main.cpp : 68[W] FIN found'asparagus'
	// 14:40:2 main.cpp : 72[I] -- - [4] Fin-- -
	int main(int argc, char** argv) {
		ull ITER_COUNT = pow(16, LETTERS_TO_FILL);

		// MULTITHREAD
		const int THREAD_CNT = 6;
		auto nn = ITER_COUNT / THREAD_CNT;

		// spawn threads
		std::future<std::string> fs[THREAD_CNT];
		for (int i = 0; i < THREAD_CNT; i++){
			// range for task to calculate over
			auto st = nn*i;
			auto end = (i == THREAD_CNT - 1) ? ITER_COUNT : nn*(i + 1);

			// create task & start the thread
			std::packaged_task<std::string(int, ull, ull)> task(calc);
			fs[i] = task.get_future();
			std::thread(std::move(task), i, st, end).detach();
		}

		// join threads
		for (int i = 0; i < THREAD_CNT; i++){
			fs[i].wait();
			auto res = fs[i].get();
			std::cout << "[" << i << "] '" << res.c_str() << "'" << '\n';
		}

		system("pause");
		std::cout << "---Fin---" << '\n';
		return 0;
	}
}