#ifndef EDGE_H
#define EDGE_H

class Node;

class Edge
{
public:
    Edge(Node* in_, Node* out_);

    static int counter; //writes id

    int id;
    Node* in;
    Node* out;
};

#endif // EDGE_H
