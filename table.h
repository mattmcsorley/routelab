#ifndef _table
#define _table

#include <iostream>
#include <map>

using namespace std;

struct TopoLink {

    TopoLink(): cost(-1), age(0), visited(false) {}


    TopoLink(const TopoLink & rhs) {
        *this = rhs;
    }

    TopoLink & operator=(const TopoLink & rhs) {
        this->cost = rhs.cost;
        this->age = rhs.age;

        return *this;
    }

    int cost;
    int age;

    bool visited;
};

// Students should write this class
class Table {
    private:
        
        
    public:
        Table();
        Table(const Table &);
        Table & operator=(const Table &);
        
        map < int, map < int, TopoLink > > topo; //aka costMap



        ostream & Print(ostream &os) const;

        // Anything else you need
        
        #if defined(LINKSTATE)
            // Hop map
            map <int, int> hopMap;
            /*
            Boolean that keeps track of whether a link has been updated in the 
            topology that has not been incorporated into this node's hopMap
            */
            
            bool hopMapNeedsChanging;

        #endif

        #if defined(DISTANCEVECTOR)
            // Int to int map that has shortest path to all other nodes (distance vector)
            // Like: 1, 5
            //       2, 3
            // meaning from this node, it costs 5 to get to node 1, 3 to get to node 2
            
            map <int, TopoLink> distanceVector;
            
            
            // Int to int map that is the cost of the direct link to the node's neighbors
            
            map <int, TopoLink> neighborLinks;
            
            // Topo (up above) is used to keep track of other nodes' distance vectors
            
            map <int, int> hopMap;
        #endif
};

inline ostream & operator<<(ostream &os, const Table & t) { return t.Print(os);}


#endif
