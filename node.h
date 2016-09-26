#ifndef NODE_H
#define NODE_H

using namespace std;

#include <vector>

class Node
{
public:
    Node();

    vector<Edge*> childs;
    vector<Edge*> parents;
};

#endif // NODE_H
