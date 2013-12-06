#ifndef _table
#define _table

#include <iostream>
#include <map>

using namespace std;

struct TopoLink {
    TopoLink(): cost(-1), age(0), distance(-1), visited(false) {}

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
    int distance;
    bool visited;
};

// Students should write this class
class Table {
    private:
        
        
    public:
        Table();
        Table(const Table &);
        Table & operator=(const Table &);


        ostream & Print(ostream &os) const;

        // Anything else you need
        // So here is the map we are going to use.
        map < int, map < int, TopoLink > > topo; //aka costMap
        
        // Hop map
        map <int, int> hopMap;
        /*
        Boolean that keeps track of whether a link has been updated in the 
        topology that has not been incorporated into this node's hopMap
        */
        
        bool hopMapNeedsChanging;
        
        #if defined(LINKSTATE)
        void find(int *src,int *dest);
        #endif

        #if defined(DISTANCEVECTOR)
        #endif
};

inline ostream & operator<<(ostream &os, const Table & t) { return t.Print(os);}


#endif
