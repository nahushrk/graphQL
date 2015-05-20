//
//  edgeMatching.h
//  graphQl
//
//  Created by Nahush Kulkarni on 4/17/15.
//  Copyright (c) 2015 Nahush Kulkarni. All rights reserved.
//

#include "graphLoader.h"

#ifndef graphQl_edgeMatching_h
#define graphQl_edgeMatching_h

bool areNeighbors_Pattern(int u, int v)
{
    for(int i=0;i<pattern[u].size();i++)
    {
		if(v<pattern.size())	//for validation
		if(pattern[u][i].value==pattern[v][0].value)
		{
			return true;
		}
    }
    return false;
}

bool areNeighbors_Graph(int nval1, int nval2)
{
	for(int i=0;i<graph.size();i++)
	{
		if(graph[i][0].value==nval1)
		{
			if(graph[i].size()>1)
			for(int j=1;j<graph[i].size();j++)
			{
				if(graph[i][j].value==nval2)
				{
					return true;
				}
			}
		}
	}
	return false;
}

bool checkFunction(int indexOf_ui, int v)	//v is actual value of Ø(ui)
{
    for(int indexOf_uj=0;indexOf_uj<indexOf_ui;indexOf_uj++)	//for each u before ui in feasibleMate
    {
        if(areNeighbors_Pattern(indexOf_ui,indexOf_uj))	//e(ui,uj) belongs to E(P)
		{
			
			 for(int k=0;k<feasibleMappings.size();k++)	//for each feasibleMapping of uj
			{
				if(feasibleMappings[k].value>0)		//check only occupied feasible mapped nodes
				if(areNeighbors_Graph(v, feasibleMappings[indexOf_uj].value)==false)	// e'(v,ø(uj)) does not belong in E(G)
				{
					return false;
				}
			}
			
		}
	}
    return true;
}

void printFeasibleMapping()
{
	cout<<"printing feasible mapping\n";
	for(int i=0;i<feasibleMappings.size();i++)
	{
		cout<<feasibleMappings[i].value<<","<<feasibleMappings[i].label<<"\t";
	}
	cout<<"\n";
}

bool allFeasibleMappingDone()
{
	for(int i =0;i<feasibleMappings.size();i++)
	{
		if(feasibleMappings[i].value==-1)
		{
			return false;
		}
	}
	return true;
}

bool markNode(int v)
{
	for(int i=0;i<feasibleMates.size();i++)
	{
		for(int j=0;j<feasibleMates[i].size();j++)
		{
			if(feasibleMates[i][j].value==v)
			{
				feasibleMates[i][j].free=false;
			}
			else
			{
				feasibleMates[i][j].free=true;
			}
		}
	}
	return true;
}

bool markNodesOnwards(int loc)
{
	for(int i=0;i<feasibleMates.size();i++)
	{
		for(int j=0;j<feasibleMates[i].size();j++)
		{
			feasibleMates[i][j].free=true;
		}
	}
	for(int i=0;i<feasibleMappings.size();i++)
	{
		if(feasibleMappings[i].value>0)		//select one feasibleMapping
		{
			for(int j=loc;j<feasibleMates.size();j++)
			{
				for(int k=0;k<feasibleMates[j].size();k++)
				{
					if(feasibleMates[j][k].value==feasibleMappings[i].value)
					{
						feasibleMates[j][k].free=false;
					}
				}
			}
		}
	}
	return true;
}

bool searchFunction(int indexOf_ui=0)
{
    for(int indexOf_v=0;indexOf_v<feasibleMates[indexOf_ui].size();indexOf_v++)	//iterate over all ø(ui)
    {
		markNodesOnwards(indexOf_ui);
        if(feasibleMates[indexOf_ui][indexOf_v].free==true)
        {
			int v=feasibleMates[indexOf_ui][indexOf_v].value;
			string l=feasibleMates[indexOf_ui][indexOf_v].label;
            if(!(checkFunction(indexOf_ui,v)))
                continue;
            else
            {
				feasibleMappings[indexOf_ui].value=v;
				feasibleMappings[indexOf_ui].label=l;
				
				
				if(indexOf_ui<(pattern.size()-1))
				{
					searchFunction(indexOf_ui+1);
				}
				else if (allFeasibleMappingDone())
				{
					printFeasibleMapping();
					feasibleMappings[indexOf_ui].value=-1;
					feasibleMappings[indexOf_ui].label="";
					if(indexOf_v==(feasibleMates[indexOf_ui].size()-1))
					{
						feasibleMappings[indexOf_ui].value=-1;
						feasibleMappings[indexOf_ui].label="";
						return true;
					}
				}
				else if(indexOf_v==(feasibleMates[indexOf_ui].size()-1))
				{
					printFeasibleMapping();
					feasibleMappings[indexOf_ui].value=-1;
					feasibleMappings[indexOf_ui].label="";
					return true;
				}
            }
        }
    }
    return false;
}

#endif