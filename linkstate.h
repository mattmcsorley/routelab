#ifndef _linkstate
#define _linkstate

#include "node.h"

#define INT_MAX 21474783

class LinkState: public Node {
    private:
        // Anything you need in addition to Node members

    public:
        
        LinkState(unsigned, SimulationContext* , double, double);
        LinkState(const LinkState &);
        LinkState & operator=(const LinkState &);
        ~LinkState();

        // Inherited from Node
        void LinkHasBeenUpdated(Link *l);
        void ProcessIncomingRoutingMessage(RoutingMessage *m);
        void TimeOut();
        Node* GetNextHop(Node* destination);
        Table* GetRoutingTable();
       
        
        ostream & Print(ostream & os) const;

        // Anything else
        Node* GetMatchingNode(unsigned n); 
};

inline ostream & operator<<(ostream & os, const LinkState & n) {
    return n.Print(os);
}

#endif
