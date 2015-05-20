//
//  globalDataStore.h
//  graphQl
//
//  Created by Nahush Kulkarni on 4/15/15.
//  Copyright (c) 2015 Nahush Kulkarni. All rights reserved.
//

#ifndef graphQl_globalDataStore_h
#define graphQl_globalDataStore_h

#include <string>

using namespace std;

string graph_file = "test_db.txt";
string pattern_file = "pattern.txt";

#define GRAPH_TYPE 1 //mode-2:directed, 1:undirected

struct node
{
    int value;
    bool free;
	string label;
};

struct predicate
{
    int value;
    char op;	//operator
	string label;
};


vector<vector<node> > graph;
vector<vector<predicate> > pattern;

//feasible mates
vector<vector<node> > feasibleMates;

//feasible mappings
vector<node> feasibleMappings;

/* --  setters and getters  --  */

void initializeFeasibleMappings()
{
	if(feasibleMappings.size()>0)
	{
		feasibleMappings.clear();
	}
	node n {-1,true};
	for(int i=0;i<pattern.size();i++)
	{
		feasibleMappings.push_back(n);
	}
}



#endif
