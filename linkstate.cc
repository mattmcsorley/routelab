#include "linkstate.h"
#include "context.h"
#include <set>


LinkState::LinkState(unsigned n, SimulationContext* c, double b, double l) :
    Node(n, c, b, l)
{}

LinkState::LinkState(const LinkState & rhs) :
    Node(rhs)
{
    *this = rhs;
}

LinkState & LinkState::operator=(const LinkState & rhs) {
    Node::operator=(rhs);
    return *this;
}

LinkState::~LinkState() {}


/** Write the following functions.  They currently have dummy implementations **/
void LinkState::LinkHasBeenUpdated(Link* l) {
    //cerr << *this << ": Link Update: " << *l << endl;
    
    // You use your knowledge of the nodes to get the age because each node has the topo table
    
    // Get new latency from updated link and update the link in this node's cost table
    int src_node = l->GetSrc();
    int dest_node = l->GetDest();
    int new_latency = l->GetLatency();
    routing_table.topo[src_node][dest_node].cost = new_latency;
    
    // Update the age of the updated link (done like this for readability purposes)
    int age = routing_table.topo[src_node][dest_node].age;
    routing_table.topo[src_node][dest_node].age = ++age;
    
    // Send the message
    SendToNeighbors(new RoutingMessage(age, src_node, dest_node, new_latency));
}

void LinkState::ProcessIncomingRoutingMessage(RoutingMessage *m) {
    
    //cerr << *this << " got a routing message: " << *m << endl;
    
    // This message contains the src_node, dest_node, and age
    
    int age = m->link_age;
    int src = m->src_node;
    int dest = m->dest_node;
    int lat = m->new_latency;
    
    /*
        We need to update this nodes table with the new information
        Check to see if our map as this src/dest already
                if not seen add them to the table
                else then update age
    */
    
    if(routing_table.topo[src][dest].cost == -1)
    {
        //We have not see this combination before update the table
        routing_table.topo[src][dest].age = age;
        routing_table.topo[src][dest].cost = lat;
        routing_table.hopMapNeedsChanging = true; // a change has been made in the hop map
        //cerr << "link change made hopMapNeedsChanging set to : true :"<< endl;
        SendToNeighbors(m);
    }
    else if(routing_table.topo[src][dest].age < age)
    {
        // We have seen this combination before we now just update the age
        routing_table.topo[src][dest].age = age;
        routing_table.topo[src][dest].cost = lat;
        routing_table.hopMapNeedsChanging = true; //a change has been made in the hop map
       // cerr << "link change made hopMapNeedsChanging set to : true :"<< endl;
        SendToNeighbors(m);
    }
    else
    {
        //No changes were made
        //cerr << "No change to hopMapNeedsChanging made its diaper is clean bitches"<< endl;
        
    }
    
   // cerr << "message processed successfully"<< endl;
    
}

void LinkState::TimeOut() {
    //cerr << *this << " got a timeout: (ignored)" << endl;
}

Node* LinkState::GetNextHop(Node *destination) {
    
    /*
        We need to figure out if this node as been updated to
        determine if we need to run dijkstra's again.
        
        If the hopMap hasn't been updated, routing_table.hopMapNeedsChanging
        will be true. This means dijkstra's must be run again and hopMap will be updated.
        hopMopNeedsChanging will then be set to false
        
        If routing_table.hopMopNeedsChanging is false, the hopMap is already up to date
        and we just need to return a copy of the next node in this path's journey.
    */
    
    /*
        Djikstra Algorithm on the topo table to update the hopTable
    */
    
    if (routing_table.hopMapNeedsChanging) {
        
        map<int, int> dist;
        set<int> visited;
        
        map<int, map<int, TopoLink> > topo = routing_table.topo;
        int size = topo.size();
        set<int> queue;

        map<int, TopoLink>::const_iterator itr;
        map<int, TopoLink> neighbors;

        map<int, int>::const_iterator prev_itr;
        map<int, int> previous;

        for(int i =0 ; i < size ; i++) 
        {
            dist[i] = INT_MAX;
            previous[i] = -1;
        }
        
        dist[number] = 0;
        queue.insert(number); //Inserts itself into the queue
       
        
        while ( !queue.empty() ) 
        {
            int min = INT_MAX;
            int smallest = -1; //this is the smallest node number 
            for(int i = 0; i < size; i++)
            {
                
                if(queue.count(i) > 0){
                  
                    if(visited.count(i) < 1)
                    {
                        //If it is not visited we need to find the distance
                        if(dist[i] < min)
                        {
                            min = dist[i];
                            smallest = i;
                        }
                    }

                }
            }
            
            //Remove smallest from the queue
            queue.erase(smallest);
            visited.insert(smallest);

            //Find the neighbors for the node previously inserted
            neighbors = topo[smallest];
            for(itr = neighbors.begin() ; itr != neighbors.end() ; itr++)
            {
               
                if( visited.count(itr->first) < 1 ) 
                {
                    int v = itr->first;
                    
                    //queue.insert(v);
                    int currentDist;
                    int altDist;

                    currentDist = dist[v];
                    altDist = dist[smallest] + topo[smallest][v].cost;
                    

                    if(altDist < currentDist)
                    {
                        dist[v] = altDist;
                        previous[v] = smallest;
                        //routing_table.hopMap[]
                        if( visited.count(v) < 1)
                        {
                            queue.insert(v);
                        }
                    }
                }
            }
        }

        map<int, int> hopMapTemp;
        for(prev_itr = previous.begin(); prev_itr != previous.end(); prev_itr++) {
        unsigned int before = prev_itr->second;
            int current = prev_itr->first;
            int current2 = prev_itr->first;
            while(before != number) {
                current = before;
                before = previous[before];
            }
            hopMapTemp[current2] = current;
        }

       
        Node *a = new Node(hopMapTemp[destination->number], NULL, 0, 0);
        
        Node * realNode = context->FindMatchingNode(const_cast<Node *>(a));
        //free(a);
        routing_table.hopMap = hopMapTemp;
        routing_table.hopMapNeedsChanging = false;
        return realNode;

    }  
    else{
        
        Node *a = new Node(routing_table.hopMap[destination->number], NULL, 0, 0);
        //cout << "MAKEING NEW NODE" << endl;
        Node * realNode = context->FindMatchingNode(const_cast<Node *>(a));
        //free(a);
        return realNode;
        
    } 
    return NULL;
}



Table* LinkState::GetRoutingTable() {
    
    /*
        This method will return a copy of routing_table
    */
    
    Table *temp = new Table(routing_table);
    
    return temp;
}


Node * LinkState::GetMatchingNode(unsigned n) {
    return context->FindMatchingNode(new Node(n, NULL, 0,0));
    //return NULL;
}




ostream & LinkState::Print(ostream &os) const { 
    Node::Print(os);
    return os;
}
