#include "undirectedGraph.h"
//all inputs are checked in undirectedGraphtest.cpp 

PQNode::PQNode()
{
    index = -1 ;
    distance = 0;
}

PQNode::PQNode(int in_index)
{
    index = in_index;
    distance = 0;
}

int PQNode::getIndex()
{
    return index;
}

double PQNode::getDistance()
{
    return distance;
}

PriorityQueue::PriorityQueue(int in_size)
{
    size_t size = in_size;
    pq.resize(size);

    for(size_t i = 0; i < size; i++)
	{
		PQNode * pqnode = new PQNode(i); 
        pq[i] = *pqnode;
		
		delete pqnode;
		pqnode = nullptr;
	}
}

PriorityQueue::~PriorityQueue()
{
	pq.clear();
}

int PriorityQueue::parent(int in_index)
{
    return (in_index - 1)/2;
}

int PriorityQueue::left(int in_index)
{
    return 2 * in_index + 1;
}

int PriorityQueue::right(int in_index)
{
    return 2 * in_index + 2;
}

PQNode PriorityQueue::extractMin()
{
    PQNode min = pq[0];
	pq.erase(pq.begin());
	
	//heapify after removing the minimum
    heapify(0);

    return min;
}

bool PriorityQueue::decreaseKey(int in_index, double in_value)
{
    int curr_pos = 0;

	//Searches linearly in priority queue for the location of in_index
    for(size_t i = 0; i < pq.size(); i++)
    {
        if(pq[i].index == in_index)
            curr_pos = i;
    }

	//skips over if old distance is less than input distance 
	if(pq[curr_pos].distance == 0 || (pq[curr_pos].distance > in_value))
    {
        pq[curr_pos].distance = in_value;
 
		//process similar to heapify
		while(curr_pos != 0 && (pq[parent(curr_pos)].distance == 0 || pq[parent(curr_pos)].distance > pq[curr_pos].distance))
        {
            int parent_pq_pos = parent(curr_pos);

			PQNode temp = pq[curr_pos];
            pq[curr_pos] = pq[parent_pq_pos];
            pq[parent_pq_pos] = temp;

            curr_pos = parent_pq_pos;
		}
    	return true;
	}
    return false;
}

bool PriorityQueue::isEmpty()
{
    if(pq.size() == 0)
        return true;
    else
        return false;
}

//recursive implementation of heapify
void PriorityQueue::heapify(int in_index)
{
    int l = left(in_index);
    int r = right(in_index);
    int min = in_index;
    int size = pq.size();

    if(l < size && pq[l].distance != 0 && (pq[in_index].distance == 0 || pq[l].distance < pq[in_index].distance))
        min = l;

    if(r < size && pq[r].distance != 0 && (pq[in_index].distance == 0 || pq[r].distance < pq[min].distance))
        min = r;

    if(min != in_index)
    {
        PQNode temp = pq[in_index];
        pq[in_index] = pq[min];
        pq[min] = temp;

        heapify(min);
    }
}

Node::Node(string in_name, int in_key)
{
    name = in_name;
    key = in_key;
    degree = 0;
}

Edge::Edge(Node * in_src, Node * in_dest, double in_d)
{
	src = in_src;
    dest = in_dest;
    d = in_d;
}

UndirectedGraph::UndirectedGraph()
{
    num_nodes = 0;
    num_edges = 0;
}

UndirectedGraph::~UndirectedGraph()
{
    nodes.clear();
    adj.clear();
    path.clear();
}

string UndirectedGraph::insert(string in_name)
{
    int index = num_nodes;

    Node * node = new Node(in_name, index);
    Edge * edge = new Edge(node, node, 0);

	//resizes modes and adjacency list when a new node is inserted
    nodes.push_back(*node);
    adj.resize(index + 1);
    adj[index].push_back(*edge);

    num_nodes++;
    
	delete node;
	delete edge;
	node = nullptr;
	edge = nullptr;

	return "success";
}
//helper function to setD
bool UndirectedGraph::insertEdge(string in_name, int in_key1, int in_key2, double in_d)
{
    bool is_inserted = false;
    
	for(size_t i = 0; i < adj[in_key1].size(); i++)
    {
		//replaces value if distance already exists
        if(adj[in_key1][i].dest->name == in_name)
        {
            adj[in_key1][i].d = in_d;
            is_inserted = true;
            break;
        }
    }

    if(!is_inserted)
    {
		//new edge added 
        Edge * edge = new Edge(&nodes[in_key1], &nodes[in_key2], in_d);
        adj[in_key1].push_back(*edge);
    	delete edge;
    	edge = nullptr;
	}

	return is_inserted;
}

string UndirectedGraph::setD(int in_index1, int in_index2, string in_name1, string in_name2, double in_d)
{
	//inserts edges on both sides because it is undirected graph
    bool is_inserted = insertEdge(in_name2, in_index1, in_index2, in_d);
    insertEdge(in_name1, in_index2, in_index1, in_d);

    if(!is_inserted)
    {
        nodes[in_index1].degree ++;
        nodes[in_index2].degree ++;
    	num_edges ++;
	}
    return "success";
}

int UndirectedGraph::search(string in_name)
{
    for(int i = 0; i < num_nodes; i++)
    {
        if(nodes[i].name == in_name)
            return i;
	}
    return -1;
}

int UndirectedGraph::getDegree(int in_index)
{
    return nodes[in_index].degree;
}

int UndirectedGraph::getNumNodes()
{
    return num_nodes;
}

int UndirectedGraph::getNumEdges()
{
    return num_edges;
}

double UndirectedGraph::getD(int in_index1, int in_index2)
{
    for(size_t i = 0; i < adj[in_index1].size(); i++)
    {
        if(adj[in_index1][i].dest->name == nodes[in_index2].name)
            return adj[in_index1][i].d;
    }

    return -1;
}

string UndirectedGraph::clear()
{
    adj.clear();
    nodes.clear();
    path.clear();
    num_nodes = 0;
    num_edges = 0;

    return "success";
}

double UndirectedGraph::shortestD(int in_index1, int in_index2)
{
    PriorityQueue pq(nodes.size());
    vector<int> included(num_nodes, 0);
    vector<double> distance(0);
    path.resize(num_nodes);
    distance.resize(num_nodes);
    PQNode min;
	bool is_changed(false);

    //add first city to path
	path[in_index1] = &nodes[in_index1];

    while(!pq.isEmpty())
    {
		//extract min
        min = pq.extractMin();
		int min_index = min.getIndex();
        distance[min_index] = min.getDistance();
		
		//if the min is the destination city, the distance it holds is already the minimum
        if(min_index == in_index2)
            return distance[min_index];

		//checks for all nearby cities to the minimum city
        for(size_t i = 1; i < adj[min_index].size(); i++)
        {
			//relaxes and modifies priority queue
            included[min_index] = 2;
            int dest_index = adj[min_index][i].dest->key;

			//only relax if dest city isn't already included
            if(included[dest_index] != 2)
            {
				//dest city is visited, not included
                included[dest_index] = 1;
                double curr_d = getD(min_index, dest_index);
 
 				is_changed = pq.decreaseKey(dest_index, distance[min_index] + curr_d);
  
				//the prev city of dest city is min if successfully relaxes
				if(is_changed)
					path[dest_index] = &nodes[min_index];
			}
        }
    }

	//if distance = 0, cities are not conncected
    return distance[in_index2];
}

//recursive helper function for getting path order
Node * UndirectedGraph::getPath(int in_index, vector<string> &in_p)
{
    in_p.push_back(nodes[in_index].name);

    if(path[in_index]->key == in_index)
        return path[in_index];

    getPath(path[in_index]->key, in_p);

    return nullptr;
}

string UndirectedGraph::printPath(int in_index1, int in_index2)
{
    double exist = shortestD(in_index1, in_index2);
    vector<string> p;

	//cities are not connected
    if(exist == 0)
        return "failure";
    
	getPath(in_index2, p);

	//prints path
    for(int i = p.size() - 1; i > 0; i--)
        cout << p[i] << " ";

    cout << p[0];

    return "";
}


