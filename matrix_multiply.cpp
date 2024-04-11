#include <iostream>
#include <pthread.h>
#include <vector>

using namespace std;

struct ThreadData
{
  int startRow;
  int endRow;
  int matrixSize;
  vector<vector<int>> *A;
  vector<vector<int>> *B;
  vector<vector<int>> *C;
};

void *multiplyRange(void *arg)
{
  ThreadData *data = (ThreadData *)arg;

  for (int i = data->startRow; i < data->endRow; ++i)
  {
    for (int j = 0; j < data->matrixSize; ++j)
    {
      (*data->C)[i][j] = 0;
      for (int k = 0; k < data->matrixSize; ++k)
      {
        (*data->C)[i][j] += (*data->A)[i][k] * (*data->B)[k][j];
      }
    }
  }

  pthread_exit(NULL);
}

int main()
{
  int n = 4;                                   // Размер матрицы
  int numThreads = 2;                          // Количество потоков
  vector<vector<int>> A(n, vector<int>(n, 1)); // Инициализация матрицы A
  vector<vector<int>> B(n, vector<int>(n, 2)); // Инициализация матрицы B
  vector<vector<int>> C(n, vector<int>(n, 0)); // Матрица для результата

  vector<ThreadData> threadData(numThreads);
  vector<pthread_t> threads(numThreads);
  int rowsPerThread = n / numThreads;

  for (int i = 0; i < numThreads; ++i)
  {
    threadData[i].startRow = i * rowsPerThread;
    threadData[i].endRow = (i == numThreads - 1) ? n : (i + 1) * rowsPerThread;
    threadData[i].matrixSize = n;
    threadData[i].A = &A;
    threadData[i].B = &B;
    threadData[i].C = &C;

    pthread_create(&threads[i], NULL, multiplyRange, (void *)&threadData[i]);
  }

  for (int i = 0; i < numThreads; ++i)
  {
    pthread_join(threads[i], NULL);
  }

  // Вывод результата
  for (int i = 0; i < n; ++i)
  {
    for (int j = 0; j < n; ++j)
    {
      cout << C[i][j] << " ";
    }
    cout << endl;
  }

  return 0;
}
