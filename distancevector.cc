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
    
    int src_node = l->GetSrc();
    int dest_node = l->GetDest();
    int new_latency = l->GetLatency();
    int age = routing_table.topo[src_node][dest_node].age;
    age++;
    routing_table.topo[src_node][dest_node].age = age;
    
    
    
    
    
    
    SendToNeighbors(new RoutingMessage());
}

void DistanceVector::ProcessIncomingRoutingMessage(RoutingMessage *m) {
    cerr << *this << " got a routing message: " << *m << " (ignored)" << endl;
    
    routing_table.topo[m->sendingNode] = m->vector;
    
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
        destination node.
        
        D(y) an estimate of the cost of the least-cost path from itself to node y
        
        Initialization
            for all destinaions y in N:
                D(destination) = c(src,destination)
            
        
    */
    
    
    return NULL;
}

Table* DistanceVector::GetRoutingTable() {
    
    Table *temp = new Table(routing_table);
    
    return temp;
}

ostream & DistanceVector::Print(ostream &os) const { 
    Node::Print(os);
    return os;
}
