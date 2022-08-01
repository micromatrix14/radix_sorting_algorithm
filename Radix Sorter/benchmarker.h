#ifndef PERFOMANCE_MONITOR
#define PERFOMANCE_MONITOR

#include <iostream>
#include <chrono>

class benchmarker {
public:
	benchmarker() {
		first = std::chrono::high_resolution_clock::now();
	}
	virtual ~benchmarker() {
		auto second = std::chrono::high_resolution_clock::now();
		auto elapsed = second - first;
		auto diff = std::chrono::duration_cast<std::chrono::microseconds>(elapsed).count();
		std::cout << "\ntime elapsed = " << diff << "us = " << diff / 1000.0 << "ms\n";
	}
private:
	std::chrono::time_point<std::chrono::high_resolution_clock> first;
};

#endif