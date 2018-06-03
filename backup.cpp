#include <iostream>
#include <fstream>
#include <vector>
#include <list>
#include <map>
#include <algorithm>
#include <climits>


#define MAX_SIZE 3
#define INF INT_MAX

class prepareGraph
{
public:
    prepareGraph()
    {
        randomizeGraph();
        initailizeMatrix();
        readData();
    }


    virtual int **getMatrix()
    {
        return matrix;
    }
protected:
    int** matrix = new int* [MAX_SIZE];

    void initailizeMatrix() const
    {
        for (int i = 0; i < MAX_SIZE; ++i)
            matrix[i] = new int[MAX_SIZE];
    }
    virtual void randomizeGraph()
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
    virtual void readData()
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
};


class Graph : public prepareGraph
{
public:
    Graph()
        :prepareGraph()
    {
        std::cout << "I did it!";
    }
private:



};

struct Element
{
    int poprzednik = -1;
    int sciezkaDojscia = INF;
    int wierzcholek;
};

class DijkstraAlgorithm
{
public:
    DijkstraAlgorithm(Graph& graph)
    {
        matrix = graph.getMatrix();
    }

    Element*  evaluate(int from, int destination)
    {
        initializeSingleSource(from);

        std::map<int, Element*> Q;
        for (int i=0; i<MAX_SIZE;++i)
        {
            Q[i] = &dojscia[i];
        }

        auto min = [](auto lArg, auto rArg)-> bool
        {
            return lArg.second->sciezkaDojscia < rArg.second->sciezkaDojscia;
        };

        while (!Q.empty())
        {
            auto lowest = std::min_element( std::begin(Q), std::end(Q), min);
            std::cout<<"Lowest in the map is: " <<lowest->first << " " <<lowest->second->sciezkaDojscia << std::endl;
            for (int i = 0; i < MAX_SIZE; ++i)
            {
                if (matrix[lowest->first][i] != INF)
                {
                    relax(lowest->first, i);
                }
            }
            Q.erase(lowest);
        }
        std::cout << "From the node: "<<from<<"to: "<< destination << " is : " << dojscia[destination].sciezkaDojscia << "\n";
    };

private:
    void initializeSingleSource(int source)
    {
        for (int i = 0;i < MAX_SIZE;++i)
        {
            dojscia[i].poprzednik = -1;
            dojscia[i].sciezkaDojscia = INF;
            dojscia[i].wierzcholek = i;
        }
        dojscia[source].poprzednik = -1;
        dojscia[source].sciezkaDojscia = 0;
    }

    void relax(int zrodlo, int destination)
    {
        if( dojscia[destination].sciezkaDojscia > dojscia[zrodlo].sciezkaDojscia + matrix[zrodlo][destination])
        {
            dojscia[destination].sciezkaDojscia = dojscia[zrodlo].sciezkaDojscia + matrix[zrodlo][destination];
            dojscia[destination].poprzednik = destination;
        }
    }


    Element dojscia[MAX_SIZE];
    int** matrix;
};

int main()
{
    srand( time( NULL ) );
    Graph graf;
    DijkstraAlgorithm example(graf);
    example.evaluate(0,2);
    return 0;
}
