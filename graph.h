#ifndef GRAPH_H
#define GRAPH_H

#include <vector>
class Node;
class Edge;

using namespace std;

class Graph
{
public:
    Graph();
    Graph(int n, vector<pair<int, int> > edgesVec);

    vector<Node*> nodes;
    vector<Edge*> edges;
};

#endif // GRAPH_H
