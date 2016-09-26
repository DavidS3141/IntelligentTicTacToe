#ifndef EDGE_H
#define EDGE_H

class Node;

class Edge
{
public:
    Edge();
    Edge(int i);

    int id;

    Node* in;
    Node* out;
};

#endif // EDGE_H
