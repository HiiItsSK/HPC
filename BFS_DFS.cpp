#include <iostream>
#include <vector>
#include <queue>
#include<stack>
#include <omp.h>
using namespace std;
class Graph {
private:
    int numVertices;
    vector<vector<int>> adjacencyList;
public:
    Graph(int numVertices){
        this->numVertices=numVertices;
        adjacencyList.resize(numVertices);
    }
    void addEdge(int start, int dest) {
        adjacencyList[start].push_back(dest);
        adjacencyList[start].push_back(start);
    }
    void BFS(int startVertex) {
        vector<bool> visited(numVertices, false);
        queue<int> q;
        visited[startVertex] = true;
        q.push(startVertex);

        while (!q.empty()) {
            int currentVertex = q.front();
            q.pop();
            cout << currentVertex << " ";

            #pragma omp parallel for
            for (int neighbor : adjacencyList[currentVertex]) {
                if (!visited[neighbor]) {
                    visited[neighbor] = true;
                    q.push(neighbor);
                }
            }
        }
    }

    void DFS(int startVertex) {
        vector<bool> visited(numVertices, false);
        stack<int> s;
        s.push(startVertex);

        while (!s.empty()) {
            int currentVertex = s.top();
            s.pop();

            if (!visited[currentVertex]) {
                visited[currentVertex] = true;
                cout << currentVertex << " ";

                #pragma omp parallel for
                for (int neighbor : adjacencyList[currentVertex]) {
                    s.push(neighbor);
                }
            }
        }
    }
};

int main() {
    int numVertices = 6;
    Graph graph(numVertices);

    // Add edges to the graph
    graph.addEdge(0, 1);
    graph.addEdge(0, 2);
    graph.addEdge(1, 3);
    graph.addEdge(2, 3);
    graph.addEdge(2, 4);
    graph.addEdge(3, 4);
    graph.addEdge(4, 5);

    cout << "BFS Traversal: ";
    graph.BFS(0);
    cout << endl;

    cout << "DFS Traversal: ";
    graph.DFS(0);
    cout << endl;

    return 0;
}
