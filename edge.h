#ifndef EDGE_H
#define EDGE_H

#include "node.h"

class Edge
{
public:
    Edge();

    Node* in;
    Node* out;
};

#endif // EDGE_H
