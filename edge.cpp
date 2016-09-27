#include "edge.h"
#include "node.h"

int Edge::counter = 0;

Edge::Edge(Node *in_, Node *out_) {
	in = in_;
	out = out_;
	in->childs.push_back(this);
	out->parents.push_back(this);
    id = counter;
    counter++;
}
