#include "node.h"

int Node::counter = 0;

Node::Node(){
    id = counter;
    counter++;
}
