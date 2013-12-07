#include "distancevector.h"
#include "context.h"

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
    
    
    // Update neighbor link
    routing_table.neighborLinks[dest_node].cost = new_latency;
    routing_table.distanceVector[dest_node].cost = -1;
    routing_table.topo[dest_node][dest_node].cost = 0;
    
    // Check if I need to update my own distance vector. If I make a change, send the new distance vector out. If no change was made, send no message
    if (updateDistanceVector()) {
        cout << "Sending to neighbors inside LinkHasBeenUpdated" << endl;
        SendToNeighbors(new RoutingMessage(number, routing_table.distanceVector));
    }
}

void DistanceVector::ProcessIncomingRoutingMessage(RoutingMessage *m) {
    cerr << *this << " got a routing message: " << *m << " (ignored)" << endl;
    
    // Update topo
    routing_table.topo[m->sendingNode] = m->vector;
    
    map<int, TopoLink>::const_iterator messageDV_itr;
    
    for (messageDV_itr = m->vector.begin(); messageDV_itr != m->vector.end(); messageDV_itr++) {
        if (routing_table.distanceVector[messageDV_itr->first].cost == -1) {
            // Initialize any connections that haven't been seen yet
        }
    }
    
    // Check if I need to update my own distance vector. If I make a change, send the new distance vector out. If no change was made, send no message
    if (updateDistanceVector()) {
        SendToNeighbors(new RoutingMessage(number, routing_table.distanceVector));
    }
    
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
        
    */
    
    cout << "I am: "<< number << endl;
    cout << "Destination: "<< destination->number << endl;
    cout << "Sending next hop: "<< routing_table.hopMap[destination->number] << endl;
    
    map<int, int>::const_iterator hop_itr;
    
    hop_itr = routing_table.hopMap.begin();
    while (hop_itr != routing_table.hopMap.end()) {
        cout << "To get to " << hop_itr->first << ": " << hop_itr->second << endl;
        hop_itr++;
    }
    
    Node *a = new Node(routing_table.hopMap[destination->number], NULL, 0, 0);
    Node * realNode = context->FindMatchingNode(const_cast<Node *>(a));
    
    return realNode;
    
}

Table* DistanceVector::GetRoutingTable() {
    Table *temp = new Table(routing_table);
    return temp;

}

bool DistanceVector::updateDistanceVector() {
    bool updated = false;
    
    map<int, TopoLink>::const_iterator dv_itr;
    map<int, TopoLink>::const_iterator neighbor_itr;
    
    
    for (dv_itr = routing_table.distanceVector.begin(); dv_itr != routing_table.distanceVector.end(); dv_itr++) {
        int currentNode = dv_itr->first;
        cout << "Current node: " << currentNode << endl;
        if (currentNode == number)
        {
            routing_table.distanceVector[currentNode].cost = 0;
            continue;
        }
        
        
        int currMin = 100000000;
        int altPath = 0;
        int nextHop = -1;
        
        for (neighbor_itr = routing_table.neighborLinks.begin(); neighbor_itr != routing_table.neighborLinks.end(); neighbor_itr++) {
           int currentNeighbor = neighbor_itr->first;
           cout << "Current neighbor: " << currentNeighbor << endl;
           
           if (routing_table.neighborLinks[currentNeighbor].cost != -1 && routing_table.topo[currentNeighbor][currentNode].cost != -1) {
               altPath = routing_table.neighborLinks[currentNeighbor].cost + routing_table.topo[currentNeighbor][currentNode].cost;
           
               if (altPath < currMin) {
                   currMin = altPath;
                   nextHop = currentNeighbor;
               }
           }
       }
       
       if (currMin != 100000000 && currMin != routing_table.distanceVector[currentNode].cost) {
           routing_table.distanceVector[currentNode].cost = currMin;
           routing_table.hopMap[currentNode] = nextHop;
           updated = true;
       }
    }
    
    
    return updated;
    
    
    
}

ostream & DistanceVector::Print(ostream &os) const { 
    Node::Print(os);
    return os;
}
