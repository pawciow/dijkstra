#include "prepareGraph.h"
prepareGraph::prepareGraph()
{
     randomizeGraph();
     initailizeMatrix();
     readData();
}
int** prepareGraph::getMatrix()
  {
     return matrix;
  }
void prepareGraph::initailizeMatrix() const
  {
     for (int i = 0; i < MAX_SIZE; ++i)
        matrix[i] = new int[MAX_SIZE];
  }
void prepareGraph::randomizeGraph()
  {
        // Wygenerowanie losowego pliku txt z tablica sasiedztwa
        int tmpMatrix[MAX_SIZE][MAX_SIZE];
        // int** tmpMatrix = new int*[100];
        for (int i = 0; i < MAX_SIZE; ++i)
        {
            // tmpMatrix[i] = new int[MAX_SIZE];
            std::generate_n(tmpMatrix[i], MAX_SIZE,
                []() { return rand() % 5 + 1;} );
        }

        // Wypełnienie większości pól nieskończonością, żeby wszystko nie było ze wszystkim bezpośrednio połączone
        for(int i = 0; i < MAX_SIZE/2; ++i)
        {
            int k = (rand() % MAX_SIZE + 1);
            int j = (rand() % MAX_SIZE + 1);
            tmpMatrix[k][j] = INF;
        }

        for(int i = 0; i < MAX_SIZE; ++i)
        {
            tmpMatrix[i][i] = 0;
        }// bo droga do tego samego grafu to 0}

        std::fstream plik;
        plik.open("/home/pawciow/CLionProjects/Graf/test.txt", std::ios::out | std::ios::trunc);
        if (!plik.is_open())
        {
            std::cout << "Can't get into the file" << std::endl;
            return;
        }
        std::cout << "I'm in" << std::endl;

        // Zapis do pliku
        for (int i = 0; i < MAX_SIZE; ++i)
        {
            for (int j = 0; j < MAX_SIZE; ++j)
                plik << tmpMatrix[i][j] << " ";
            plik << std::endl;
        }
        // free(tmpMatrix);
    }
void prepareGraph::readData()
    {
        std::fstream plik;
        plik.open("/home/pawciow/CLionProjects/Graf/test.txt", std::ios::in);
        if (!plik.is_open())
        {
            std::cout << "Can't get into the file" << std::endl;
            return;
        }
        std::cout << "I'm in" << std::endl;

        for (int i = 0; i < MAX_SIZE; ++i)
        {
            for (int j = 0; j < MAX_SIZE; ++j)
                plik >> matrix[i][j];
        }
    }
