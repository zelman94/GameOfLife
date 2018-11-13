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

	randomiseMatrixValues(oldMatrix, N);
	randomiseMatrixValues(newMatrix, N);


}

void LifeGenerator::randomiseMatrixValues(int** matrix, int N)
{
	for (int i = 1; i < N-1; ++i)
	{
		for (int j = 1; j < N-1; ++j)
		{
			matrix[i][j] =  rand() % 2 ;
		}
	}
}

void LifeGenerator::wskaznikZycia(int** newMatrix, int** oldMatrix, int row, int N) // ustalanie ktora komorka umiera / zyje / bedzie zyc
{

	std::vector<int> wskaznikZycia;
	int wsk;

	for (int i = 1; i < N-1; i++) //petla glowna liczy dla ktorej komorki wskaznik
	{
		wsk = 0;
		// prawa strona
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





	for (int  i = 1; i < N - 1; i++)
	{

		if (wskaznikZycia[i]==3 || newMatrix[row][i] == 2)
		{
			newMatrix[row][i] = 1;
		}
		else
		{
			newMatrix[row][i] = 0;
		}

		
	}
	wskaznikZycia.clear();

}

void LifeGenerator::multiplyMatrixes()
{
	
	
	for (int i = 1; i < N-1; ++i)
	{
		threads.push_back(std::thread(wskaznikZycia, newMatrix, oldMatrix, i, N));
	}

	for (auto thread = threads.begin(); thread != threads.end(); ++thread)
	{
		thread->join();
	}



}

void LifeGenerator::show()
{
	std::cout << "Matrix A" << std::endl;
	displayMatrix(newMatrix, N);

}

void  LifeGenerator::displayMatrix(int** matrix, int N)
{
	for (int i = 0; i < N; ++i)
	{
		for (int j = 0; j < N; ++j)
		{
			if ( i == 0 || j == 0 || i == N-1 || j == N-1)
			{
				std::cout << "*" << '\t';
			}
			else
			{
				std::cout << matrix[i][j] << '\t';
			}
		}
		std::cout << std::endl;
	}
}
