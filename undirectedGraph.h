#include <iostream>
#include <vector>
#include <sstream>

using std::string;
using std::cin;
using std::cout;
using std::stod;
using std::endl;
using std::vector;
using std::stringstream;

class Node
{
public:
    Node(string in_name, int in_key);
private:
    string name;
    int key;
    int degree;
    friend class UndirectedGraph;
};

class Edge
{
public:
    Edge(Node * in_src, Node * in_dest, double in_d);
private:
	Node * src;
    Node * dest;
    double d;
    friend class UndirectedGraph;
};

class UndirectedGraph
{
public:
    UndirectedGraph();
    ~UndirectedGraph();
    string insert(string in_name);
    string setD(int in_index1, int in_index2, string in_name1, string in_name2, double in_d);
    bool insertEdge(string in_name, int in_key1, int in_key2, double in_d);
    int search(string in_name);
    int getDegree(int in_index);
    int getNumNodes();
    int getNumEdges();
    double getD(int in_index1, int in_index2);
    double shortestD(int in_index1, int in_index2);
    Node * getPath(int in_index, vector<string> &in_p);
    string printPath(int in_index1, int in_index2);
    string clear();
private:
    vector<vector<Edge>> adj;
    vector<Node> nodes;
    int num_nodes;
    int num_edges;
    vector<Node *> path;
};

class PQNode
{
public:
    PQNode();
    PQNode(int in_index);
    int getIndex();
    double getDistance();
private:
    int index;
    double distance;
    friend class PriorityQueue;
};

class PriorityQueue
{
public:
    PriorityQueue(int in_size);
    ~PriorityQueue();
    PQNode extractMin();
    bool decreaseKey(int in_index, double in_value);
    bool isEmpty();
private:
    vector<PQNode> pq;
    void heapify(int in_index);
    int parent(int in_index);
    int left(int in_index);
    int right(int in_index);
};
