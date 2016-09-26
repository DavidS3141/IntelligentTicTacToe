#include "edge.h"

int Edge::counter = 0;

Edge::Edge(Node *in_, Node *out_) {
	in = in_;
	out = out_;
    id = counter;
    counter++;
}
