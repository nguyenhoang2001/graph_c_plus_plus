#include <iostream>
#include <queue>
#define UNVISITED 0
#define VISITED 1
#define DFS_MODE 1
#define BFS_MODE 0

using namespace std;

struct vertex
{
    int data;
    int mark;
    int color;
    vertex()
    {
        data = 0;
        mark = 0;
        color = -1;
    }
};

class Edge
{
private:
    /* data */
    int vert;
    int wt;

public:
    Edge()
    {
        this->vert = -1;
        this->wt = -1;
    }
    Edge(int v, int w)
    {
        this->vert = v;
        this->wt = w;
    }

    int vertice()
    {
        return this->vert;
    }

    int weight()
    {
        return this->wt;
    }
};

class Graph
{
private:
    int numvertex;
    int numEdge;
    int **matrix;
    vertex *vertices;

public:
    void Init(int numVert)
    {
        int i;
        this->numvertex = numVert;
        this->numEdge = 0;
        this->vertices = new vertex[numVert];
        for (i = 0; i < numVert; i++)
        {
            this->vertices[i].mark = UNVISITED;
        }
        this->matrix = new int *[numVert];
        for (i = 0; i < numVert; i++)
            matrix[i] = new int[numVert];
        for (i = 0; i < numVert; i++)
            for (int j = 0; j < numVert; j++)
                matrix[i][j] = 0;
    }

    Graph(int num)
    {
        Init(num);
    }

    ~Graph()
    {
        delete[] vertices;
        for (int i = 0; i < this->numvertex; i++)
            delete[] matrix[i];
        delete[] matrix;
    }

    int n()
    {
        return this->numvertex;
    }

    int e()
    {
        return this->numEdge;
    }

    int first(int v)
    {
        for (int i = 0; i < this->numvertex; i++)
        {
            if (matrix[v][i] != 0)
                return i;
        }
        return this->numvertex;
    }

    int next(int v, int w)
    {
        for (int i = w + 1; i < this->numvertex; i++)
            if (matrix[v][i] != 0)
                return i;
        return this->numvertex;
    }

    void setEdge(int v1, int v2, int w)
    {
        if (w <= 0)
        {
            cout << "error" << endl;
            return;
        }
        if (matrix[v1][v2] == 0)
            this->numEdge++;
        matrix[v1][v2] = w;
    }

    void delEdge(int v1, int v2)
    {
        if (matrix[v1][v2] != 0)
            this->numEdge--;
        matrix[v1][v2] = 0;
    }

    bool isEdge(int v1, int v2)
    {
        return matrix[v1][v2] != 0;
    }

    int weight(int v1, int v2)
    {
        return matrix[v1][v2];
    }

    int getMark(int v)
    {
        return vertices[v].mark;
    }

    void setMark(int v, int val)
    {
        vertices[v].mark = val;
    }

    void color_graph(int current)
    {
        int w;
        int color = 0;
        int arr_color[n()];
        int i = 0;
        for (w = first(current); w < n(); w = next(current, w))
        {
            if (vertices[w].color > -1)
            {
                arr_color[i++] = vertices[w].color;
            }
        }
        while (true)
        {
            bool found = true;
            for (int j = 0; j < i; j++)
            {
                if (color == arr_color[j])
                {
                    found = false;
                    break;
                }
            }
            if (found)
                break;
            else
                color += 1;
        }
        vertices[current].color = color;
    }

    void run_DFS_coloring_graph(int v)
    {
        color_graph(v);
        setMark(v, VISITED);
        for (int w = first(v); w < this->numvertex; w = next(v, w))
        {
            if (getMark(w) == UNVISITED)
            {
                run_DFS_coloring_graph(w);
            }
        }
    }

    void DFS(int v)
    {
        // Pre action
        cout << "Color of the vertex[ " << v << " ]: " << vertices[v].color << endl;
        setMark(v, VISITED);
        for (int w = first(v); w < this->numvertex; w = next(v, w))
        {
            if (getMark(w) == UNVISITED)
            {
                DFS(w);
            }
        }
    }

    void BFS(int start, queue<int> *q)
    {
        int v, w;
        q->push(start);
        setMark(start, VISITED);
        while (!(q->empty()))
        {
            v = q->front();
            q->pop();
            // Do the task
            cout << v << endl;
            for (w = first(v); w < n(); w = next(v, w))
            {
                if (getMark(w) == UNVISITED)
                {
                    setMark(w, VISITED);
                    q->push(w);
                }
            }
        }
    }

    void GraphTraverse(int i)
    {
        int v;
        for (v = 0; v < this->numvertex; v++)
            setMark(v, UNVISITED);
        for (v = 0; v < this->numvertex; v++)
        {
            if (i == 1)
            {
                if (getMark(v) == UNVISITED)
                    DFS(v);
            }
            else if (i == 2)
            {
                if (getMark(v) == UNVISITED)
                    run_DFS_coloring_graph(v);
            }
            else
            {
                if (getMark(v) == UNVISITED)
                {
                    queue<int> contain;
                    BFS(v, &contain);
                }
            }
        }
    }

    void copyMatrix(int **a)
    {
        for (int i = 0; i < this->numvertex; i++)
        {
            for (int j = 0; j < this->numvertex; j++)
            {
                matrix[i][j] = a[i][j];
            }
        }
    }

    void put_value_edge(int save_i, int save_j, int save_val_i, int save_val_j)
    {
        if (save_val_i == 1)
            setEdge(save_i, save_j, 1);
        if (save_val_j == 1)
            setEdge(save_j, save_i, 1);
    }

    void put_matrix_incidence(int a[][4], int size_i, int size_j)
    {
        int save_i, save_j, save_val_i, save_val_j;
        for (int j = 0; j < size_j; j++)
        {
            int count = 0;
            for (int i = 0; i < size_i; i++)
            {
                if (count == 0)
                {
                    if (a[i][j] == 1 || a[i][j] == -1)
                    {
                        save_i = i;
                        save_val_i = a[i][j];
                        count++;
                    }
                }
                else
                {
                    if (a[i][j] == 1 || a[i][j] == -1)
                    {
                        save_j = i;
                        save_val_j = a[i][j];
                        put_value_edge(save_i, save_j, save_val_i, save_val_j);
                        break;
                    }
                }
            }
        }
    }

    void printMatrix()
    {
        for (int i = 0; i < this->numvertex; i++)
        {
            for (int j = 0; j < this->numvertex; j++)
            {
                cout << this->matrix[i][j] << " ";
            }
            cout << endl;
        }
    }
};

int main()
{
    int size;
    cin >> size;
    Graph g(size);

    int **a = new int *[size];
    for (int i = 0; i < size; i++)
        a[i] = new int[size];

    int myarr[5][5] = {
        0, 0, 1, 0, 1,
        0, 0, 1, 0, 1,
        1, 1, 0, 1, 0,
        0, 0, 0, 1, 1,
        1, 1, 0, 1, 0};
    for (int i = 0; i < size; i++)
        for (int j = 0; j < size; j++)
            a[i][j] = myarr[i][j];
    g.copyMatrix(a);
    // g.GraphTraverse(2);
    g.GraphTraverse(1);
    //g.printMatrix();
}