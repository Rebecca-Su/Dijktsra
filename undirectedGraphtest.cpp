#include <iostream>
#include "undirectedGraph.h"

int main();

int main()
{
	UndirectedGraph g;
	string thisLine;
	string command;
	string param;
	size_t pos;
	string in_attr;
	vector<string> info;
	int index1;
	int index2;

	while(!cin.eof())
	{
		getline(cin, thisLine);
		pos = thisLine.find(" ");

		if(pos == string::npos)
			command = thisLine;
		else
		{
			command = thisLine.substr(0, pos);
			param = thisLine.substr(pos + 1, thisLine.size());

			stringstream ss(param);

			while(ss.good())
			{
				getline(ss, in_attr, ';');
				info.push_back(in_attr);
			}
		}

		if(command == "setd" ||
		   command == "degree" ||
		   command == "d" ||
		   command == "shortest_d" ||
		   command == "print_path")
		{
			index1 = g.search(info[0]);
			if(index1 == -1)
			{
				cout << "failure" << endl;
				info.clear();
				continue;
			}
			else if(command == "setd"||
					command == "d" ||
					command == "shortest_d" ||
					command == "print_path")
			{
				index2 = g.search(info[1]);
				
				if(index2 == -1 || index2 == index1)
				{
					cout << "failure" << endl;
					info.clear();
					continue;
				}
			}
		}

		if(command == "i")
		{
			index1 = g.search(info[0]);
			if(index1 != -1)
				cout << "failure" << endl;
			else
				cout << g.insert(info[0]) << endl;
		}
		else if(command == "setd")
		{
			if(stod(info[2]) <= 0)
				cout << "failure" << endl;
			else
				cout << g.setD(index1, index2, info[0], info[1], stod(info[2])) << endl;
		}
		else if(command == "s")
		{
			int result = g.search(info[0]);
			
			if(result == -1)
					cout << "not found" << endl;
			else
				cout << "found " << info[0] << endl;
		}
		else if(command == "degree")
		{
			cout << "degree of " << info[0] << " " << g.getDegree(index1) << endl;
		}
		else if(command == "graph_nodes")
		{
			cout << "number of nodes " << g.getNumNodes() << endl;
		}
		else if(command == "graph_edges")
		{
			cout << "number of edges " << g.getNumEdges() << endl;
		}
		else if(command == "d")
		{
			double result = g.getD(index1, index2);
			
			if(result == -1)
				cout << "failure" << endl;
			else
				cout << "direct distance " << info[0] << " to " << info[1] << " " << result << endl;
		}
		else if(command == "shortest_d")
		{
			double result = g.shortestD(index1, index2);
	
			if(result == 0)
				cout << "failure" << endl;
			else
				cout << "shortest distance " << info[0] << " to " << info[1] << " " << result << endl; 
		}
		else if(command == "print_path")
		{
			g.printPath(index1, index2);
			cout << endl;
		}
		else if(command == "clear")
		{
			cout << g.clear() << endl;
		}
		
		info.clear();
	}
	return 0;
}
