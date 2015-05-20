//
//  feasibleMates.h
//  graphQl
//
//  Created by Nahush Kulkarni on 4/16/15.
//  Copyright (c) 2015 Nahush Kulkarni. All rights reserved.
//

#include "globalDataStore.h"

#ifndef graphQl_feasibleMates_h
#define graphQl_feasibleMates_h

int findFeasibleMates()
{
    for(int u=0;u<pattern.size();u++)   //select ui
    {
        vector<node> tmp;
        feasibleMates.push_back(tmp);
        switch (pattern[u][0].op)
        {
            case '=':
            {
                for(int v=0;v<graph.size();v++) //select vi
                {
                    if(pattern[u][0].value==graph[v][0].value)
                    {
                        feasibleMates[u].push_back(graph[v][0]);
                    }
                }
            }
                break;
                
            case '>':
            {
                for(int v=0;v<graph.size();v++) //select vi
                {
                    if(pattern[u][0].value<graph[v][0].value)
                    {
                        feasibleMates[u].push_back(graph[v][0]);
                    }
                }
            }
                break;
                
            case '<':
            {
                for(int v=0;v<graph.size();v++) //select vi
                {
                    if(pattern[u][0].value>graph[v][0].value)
                    {
                        feasibleMates[u].push_back(graph[v][0]);
                    }
                }
            }
                break;
                
            case '!':
            {
                for(int v=0;v<graph.size();v++) //select vi
                {
                    if(pattern[u][0].value!=graph[v][0].value)
                    {
                        feasibleMates[u].push_back(graph[v][0]);
                    }
                }
            }
                break;
                
            default:
                break;
        }

    }
    return 0;
}

bool findFeasibleMatesUsingLabel()	//select feasible mates by comparing labels instaed of values
{
	for(int u=0;u<pattern.size();u++)   //select ui
	{
		vector<node> tmp;
		feasibleMates.push_back(tmp);
		for(int v=0;v<graph.size();v++) //select vi
		{
			if(pattern[u][0].label==graph[v][0].label)
			{
				feasibleMates[u].push_back(graph[v][0]);
			}
		}
	}

	return true;
}

void printFeasibleMates()
{
    cout<<"printing feasible mates\n";
    for(int i=0;i<feasibleMates.size();i++)
    {
        for(int j=0;j<feasibleMates[i].size();j++)
        {
            cout<<feasibleMates[i][j].value<<","<<feasibleMates[i][j].label<<"\t";
        }
        cout<<"\n";
    }
}

#endif
