#ifndef NODE_H
#define NODE_H

#include <Vector>
using namespace std;

class Node
{
public:
    Node();

    Vector childs;
    Vector parents;
};

#endif // NODE_H
