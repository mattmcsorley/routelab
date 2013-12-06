#include "distancevector.h"

DistanceVector::DistanceVector(unsigned n, SimulationContext* c, double b, double l) :
    Node(n, c, b, l)
{}

DistanceVector::DistanceVector(const DistanceVector & rhs) :
    Node(rhs)
{
    *this = rhs;
}

DistanceVector & DistanceVector::operator=(const DistanceVector & rhs) {
    Node::operator=(rhs);
    return *this;
}

DistanceVector::~DistanceVector() {}


/** Write the following functions.  They currently have dummy implementations **/
void DistanceVector::LinkHasBeenUpdated(Link* l) {
    cerr << *this << ": Link Update: " << *l << endl;
    SendToNeighbors(new RoutingMessage());
}

void DistanceVector::ProcessIncomingRoutingMessage(RoutingMessage *m) {
    cerr << *this << " got a routing message: " << *m << " (ignored)" << endl;
}

void DistanceVector::TimeOut() {
    cerr << *this << " got a timeout: (ignored)" << endl;
}

Node* DistanceVector::GetNextHop(Node *destination) { 
    
    /*  
        Here we need to find out what the next hop will be based on the table
        Shortest distance to destination and continue to pass destination to that node  
        
        deque<this> *this::GetNeighbors();
        
        We are given the table within this node.  That means we will have to check
        against the table and see the distance from the current node to the requested
        destination node. If that distance is 
        
    */
    return NULL;
}

Table* DistanceVector::GetRoutingTable() {
    /*
        So every node has its own table with distances to neighbors
        and estimates to all other nodes.
        
        check if its table already exits
    */
    
    return NULL;
}

ostream & DistanceVector::Print(ostream &os) const { 
    Node::Print(os);
    return os;
}
