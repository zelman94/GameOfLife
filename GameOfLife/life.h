#ifndef _MATRIXCALCULATOR_H
#define _MATRIXCALCULATOR_H

#include <iostream>
#include <thread>
#include <vector>
#include <random>
#include <cstring>
#include <mutex>
#include <stdio.h> 
#include <windows.h> 

static std::mutex barrier;
static std::mutex g_num_mutex;
class LifeGenerator
{
public:
	LifeGenerator(const int N = 4);
	~LifeGenerator();
	void show();
	void multiplyMatrixes();
private:
	int** oldMatrix;
	int** newMatrix;


	int N;


	std::vector<std::thread> threads;

	int** createMatrix(int N);
	void initializeMatrixes();
	void randomiseMatrixValues(int** matrix, int N);
	static void wskaznikZycia(int** newMatrix, int** oldMatrix, int row, int N);
	void displayMatrix(int** matrix, int N);
	void zeroMatrix(int** matrix, int N);
};


#endif