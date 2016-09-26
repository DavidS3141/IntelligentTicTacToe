#include "graph.h"
#include "node.h"
#include "edge.h"

Graph::Graph()
{

}

Graph::Graph(int n, vector<pair<int, int> > edgesVec){
    //init edges and nodes
    for (int i=0; i<n; i++){
        nodes.push_back(new Node(i));
    }
    for (int i=0; i<edgesVec.size(); i++){
        edges.push_back(new Edge(i));
    }

    //fill in information
    for (int i=0; i<edgesVec.size(); i++){
        edges[i]->in = nodes[edgesVec[i].first];
        edges[i]->out = nodes[edgesVec[i].second];
        nodes[edgesVec[i].first]->childs.push_back(edges[i]);
        nodes[edgesVec[i].second]->parents.push_back(edges[i]);
    }
}
