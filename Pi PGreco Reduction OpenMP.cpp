#include <iostream>
#include <omp.h>
#include <cmath>
#include <stdio.h>
#include <time.h>
#include <cstdlib>

using namespace std;

const int NUM_THREADS = 2;

int main() {
	double num_steps = 10000000.0;
	double step = 1.0 / (double)num_steps;
	long double pGreco = 0;
	double startTime = omp_get_wtime(), stopTime;
	omp_set_num_threads(NUM_THREADS);
	#pragma omp parallel reduction (+:pGreco)
	{
		int id, nthreads;
		double x, somma = 0.0;
		id = omp_get_thread_num();
		nthreads = omp_get_num_threads();
			for (int i = id; i < num_steps; i += nthreads) {
				x = (i + 0.5) * step;
				somma += 4.0 / (1.0 + x * x);
			}
		pGreco += somma * step;
	}
	stopTime = omp_get_wtime();
	cout << "Tempo impiegato : " << (stopTime - startTime) * 1000 << " millisecondi." << endl;

}
