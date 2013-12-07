#ifndef _messages
#define _messages

#include <iostream>
#include "node.h"
#include "link.h"

struct RoutingMessage {
    RoutingMessage();
    RoutingMessage(const RoutingMessage &rhs);
    RoutingMessage &operator=(const RoutingMessage &rhs);

    ostream & Print(ostream &os) const;

    

    #if defined(LINKSTATE)
        RoutingMessage(int a, int src, int dest, int lat);
        
        int link_age;
        int src_node;
        int dest_node;
        int new_latency;
    #endif
    #if defined(DISTANCEVECTOR)

        RoutingMessage(int s, map <int, TopoLink> v);
        
        int sendingNode;
        map <int, TopoLink> vector;

    #endif
};

inline ostream & operator<<(ostream &os, const RoutingMessage & m) { return m.Print(os);}

#endif
