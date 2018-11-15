#include "pch.h"
#include "life.h"

LifeGenerator::LifeGenerator(int N)
{
	this->N =( N + 2 ); // +2 dodaje wartoœæ dla krawedzi omijajac problemy ifowe pozniej
	initializeMatrixes();
}

LifeGenerator::~LifeGenerator()
{
	for (int i = 0; i < N; ++i)
	{
		delete[] oldMatrix[i];
	}
	for (int i = 0; i < N; ++i)
	{
		delete[] newMatrix[i];
	}


	delete[] oldMatrix;
	delete[] newMatrix;

}

void LifeGenerator::zeroMatrix(int** matrix, int N)
{
	for (int i = 0; i < N; ++i)
	{
		for (int j = 0; j < N; ++j)
		{
			matrix[i][j] = 0;
		}
	}
}

int** LifeGenerator::createMatrix(int N)
{
	int** matrix = new int*[N];
	for (int i = 0; i < N; ++i)
	{
		matrix[i] = new int[N];
	}
	return matrix;
}

void LifeGenerator::initializeMatrixes()
{
	oldMatrix = createMatrix(N);
	newMatrix = createMatrix(N);

	zeroMatrix(oldMatrix, N);
	zeroMatrix(newMatrix, N);


	show();

	randomiseMatrixValues(oldMatrix, N);
	//randomiseMatrixValues(newMatrix, N);


}

void LifeGenerator::randomiseMatrixValues(int** matrix, int N)
{
	for (int i = 1; i < N-1; ++i)
	{
		for (int j = 1; j < N-1; ++j)
		{
			matrix[i][j] =  rand() % 2 ;
			//matrix[i][j] = 1;
			if (i == 0 || j == 0 || i == N || j == N )
			{
				matrix[i][j] = 0;
			}
		}
	}
}

void LifeGenerator::wskaznikZycia(int** newMatrix, int** oldMatrix, int row, int N) // ustalanie ktora komorka umiera / zyje / bedzie zyc
{

	std::vector<int> wskaznikZycia;
	int wsk;
	//std::lock_guard<std::mutex> block_threads_until_finish_this_job(barrier);
	for (int i = 1; i < N-1; i++) //petla glowna liczy dla ktorej komorki wskaznik
	{
		wsk = 0;
		 //prawa strona
		if (oldMatrix[row][i + 1] == 1)
		{
			wsk++;
		}

		if (oldMatrix[(int)row + 1][i + 1] == 1)
		{
			wsk++;
		}

		if (oldMatrix[(int)row - 1][i + 1] == 1)
		{
			wsk++;
		}

		// lewa strona 

		if (oldMatrix[row][i - 1] == 1)
		{
			wsk++;
		}

		if (oldMatrix[(int)row + 1][i - 1] == 1)
		{
			wsk++;
		}

		if (oldMatrix[(int)row - 1][i - 1] == 1)
		{
			wsk++;
		}

		// gora

		if (oldMatrix[(int)row + 1][i] == 1)
		{
			wsk++;
		}

		// dol
		
		if (oldMatrix[(int)row - 1][i] == 1)
		{
			wsk++;
		}
		wskaznikZycia.push_back(wsk);
	}




	for (int  i = 1; i < N - 2; i++)
	{

		if (wskaznikZycia[i]== 3 || wskaznikZycia[i] == 2)
		{
			newMatrix[row][i] = 1;
		}
		else
		{
			newMatrix[row][i] = 0;
		}
		//std::cout << wskaznikZycia[i] << " ";
		
	}
	wskaznikZycia.clear();
	//std::lock_guard<std::mutex> block_threads_until_finish_this_job(barrier);

}

void LifeGenerator::multiplyMatrixes()
{
	int** tmp;
	
	while (true)
	{
		for (int i = 1; i < N - 1; ++i)
		{
			g_num_mutex.lock();
			threads.push_back(std::thread(wskaznikZycia, newMatrix, oldMatrix, i, N));
			g_num_mutex.unlock();
		}

		for (auto thread = threads.begin(); thread != threads.end(); ++thread)
		{
			thread->join();
		}
		show();
		tmp = newMatrix;
		newMatrix = oldMatrix;
		oldMatrix = tmp;
		threads.clear();
		
	}




}

void LifeGenerator::show()
{
	//std::cout << "Old Matrix " << std::endl;
	//displayMatrix(oldMatrix, N);

	std::cout << "New Matrix " << std::endl;
	displayMatrix(newMatrix, N);
	Sleep(1000);
	system("CLS");
}

void  LifeGenerator::displayMatrix(int** matrix, int N)
{
	for (int i = 0; i < N; ++i)
	{
		for (int j = 0; j < N; ++j)
		{
			if ( i == 0 || j == 0 || i == N-1 || j == N-1)
			{
				std::cout << "*" << ' ';
			}
			else
			{
				std::cout << matrix[i][j] << ' ';
			}
		}
		std::cout << std::endl;
	}
}
