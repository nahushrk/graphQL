//
//  graphLoader.h
//  graphQl
//
//  Created by Nahush Kulkarni on 4/15/15.
//  Copyright (c) 2015 Nahush Kulkarni. All rights reserved.
//

#include "globalDataStore.h"

#ifndef graphQl_graphLoader_h
#define graphQl_graphLoader_h

int nodeExists(node no)
{
    // cout<<node<<"\n";
    for(int i=0;i<graph.size();i++)
    {
        if(graph[i][0].value==no.value)
        {
            return i;
        }
    }
    return -1;
}

bool neighborExistsInGraph(int val, int nodeLoc)
{
	for(int i=0;i<graph[nodeLoc].size();i++)
	{
		if(graph[nodeLoc][i].value==val)
		{
			return true;
		}
	}
	return false;
}

node instantiateNodeFromString(string s)
{
//	cout<<s<<"\n";
	node n;
	n.free=true;
	int cloc= (int) s.find(',');
	if(cloc>0)	//is comma seperated, so is [value,label]
	{
		n.value=stoi(s.substr(0,cloc));
//		cout<<n.value<<"\n";
		n.label=s.substr(cloc+1,s.length()-1);
//		cout<<n.label<<"\n";
	}
	else
	{
		n.value=stoi(s);
		n.label=s;
	}
//	n.label=s;
	return n;
}

int loadGraphFromFile()	//line bust be tab seperated with each node either as an integer value or value<int>,label<string> cpmma seperated pair
{
    ifstream file(graph_file.c_str());
    string line="";
    while (getline(file, line))
    {
        if(line[0]=='#' || line=="")	//hash comments && empty lines are ignored
        {
            continue;
        }
        stringstream ss(line);
        string s="",t="";
        //get first node from pair
        getline(ss, s, '\t');
        getline(ss, t, '\t');
		
		node ns = instantiateNodeFromString(s);
//        ns.free=true;
//		if(s.find(',')>0)	//is comma seperated
//        ns.value=stoi(s);
//		ns.label=s;
		
		node nt = instantiateNodeFromString(t);
//        nt.free=true;
//        nt.value=stoi(t);
//		nt.label=t;
		
        int loc= nodeExists(ns);
        if(loc>=0)//node exists
        {
			if(!neighborExistsInGraph(nt.value, loc))	//prevent neighbor from added more than once
			{
				graph[loc].push_back(nt);
			}
            //            int tnode=nodeExists(stoi(t));
            //            if(tnode<0)
            //            {
            //                vector<int> tmp {stoi(t)};
            //                adjL->push_back(tmp);
            //            }
        }
        else // node does not exist
        {
            vector<node> tmp;
            tmp.push_back(ns);
            tmp.push_back(nt);
            //            int tnode=nodeExists(stoi(t));
            //            if(tnode<0)
            //            {
            //                vector<int> tmp {stoi(t)};
            //                adjL->push_back(tmp);
            //            }
            graph.push_back(tmp);
        }
        if(GRAPH_TYPE==1)
        {
            loc=nodeExists(nt);
            if(loc>=0)//node exists
            {
                graph[loc].push_back(ns);
            }
            else // node t does not exist
            {
                vector<node> tmp;
                tmp.push_back(nt);
                tmp.push_back(ns);
                graph.push_back(tmp);
            }
        }
    }
    
    return 1;
}

void printGraph()
{
    cout<<"printing graph\n";
    for(int i=0;i<graph.size();i++)
    {
        for(int j=0;j<graph[i].size();j++)
        {
            cout<<graph[i][j].value<<","<<graph[i][j].label<<"  ";
//			cout<<graph[i][j].value<<"\t";
        }
        cout<<"\n";
    }
}

int predicateExists(predicate no)
{
    // cout<<node<<"\n";
    for(int i=0;i<pattern.size();i++)
    {
        if(pattern[i][0].value==no.value)
        {
            return i;
        }
    }
    return -1;
}

predicate instantiatePredicateFromString(string s)
{
	predicate p;
	p.op=s.at(0);
	s=s.substr(1,s.length());
//	ps.value=stoi(s);
//	ps.label=s;
	int cloc= (int) s.find(',');
	if(cloc>0)	//is comma seperated, so is [value,label]
	{
		p.value=stoi(s.substr(0,cloc));
		//		cout<<n.value<<"\n";
		p.label=s.substr(cloc+1,s.length()-1);
		//		cout<<n.label<<"\n";
	}
	else
	{
		p.value=stoi(s);
		p.label=s;
	}
	return p;
}

int loadPatternFromFile()
{
    ifstream file(pattern_file.c_str());
    string line="";
    while (getline(file, line))
    {
        if(line[0]=='#' || line=="")
        {
            continue;
        }
        stringstream ss(line);
        string s="",t="";
        //get first node from pair
        getline(ss, s, '\t');
        getline(ss, t, '\t');
		predicate ps = instantiatePredicateFromString(s);
//        ps.op=s.at(0);
//        s=s.substr(1,s.length());
//        ps.value=stoi(s);
//		ps.label=s;
		predicate pt = instantiatePredicateFromString(t);
//        pt.op=t.at(0);
//        t=t.substr(1,t.length());
//        pt.value=stoi(t);
//		pt.label=t;
        int loc= predicateExists(ps);
        if(loc>=0)//node exists
        {
            pattern[loc].push_back(pt);
            //            int tnode=nodeExists(stoi(t));
            //            if(tnode<0)
            //            {
            //                vector<int> tmp {stoi(t)};
            //                adjL->push_back(tmp);
            //            }
        }
        else // node does not exist
        {
            vector<predicate> tmp;
            tmp.push_back(ps);
            tmp.push_back(pt);
            //            int tnode=nodeExists(stoi(t));
            //            if(tnode<0)
            //            {
            //                vector<int> tmp {stoi(t)};
            //                adjL->push_back(tmp);
            //            }
            pattern.push_back(tmp);
        }
        if(GRAPH_TYPE==1)
        {
            loc=predicateExists(pt);
            if(loc>=0)//node exists
            {
                pattern[loc].push_back(ps);
            }
            else // node t does not exist
            {
                vector<predicate> tmp;
                tmp.push_back(pt);
                tmp.push_back(ps);
                pattern.push_back(tmp);
            }
        }
    }
    
    return 1;
}

void printPattern()
{
    cout<<"printing pattern\n";
    for(int i=0;i<pattern.size();i++)
    {
        for(int j=0;j<pattern[i].size();j++)
        {
            cout<<pattern[i][j].op<<pattern[i][j].value<<","<<pattern[i][j].label<<"  ";
        }
        cout<<"\n";
    }
}


/*
int nodeExists(int node, vector<vector<int> > *adjL)
{
    // cout<<node<<"\n";
    for(int i=0;i<adjL->size();i++)
    {
        if((*adjL)[i][0]==node)
        {
            return i;
        }
    }
    return -1;
}

int loadDataFromFile(string filename, vector<vector<int> > *adjL)
{
    ifstream file(filename.c_str());
    string line="";
    while (getline(file, line))
    {
        if(line[0]=='#' || line=="")
        {
            continue;
        }
        stringstream ss(line);
        string s="",t="";
        //get first node from pair
        getline(ss, s, '\t');
        getline(ss, t, '\t');
        int loc= nodeExists(stoi(s), adjL);
        if(loc>=0)//node exists
        {
            (*adjL)[loc].push_back(stoi(t));
            //            int tnode=nodeExists(stoi(t));
            //            if(tnode<0)
            //            {
            //                vector<int> tmp {stoi(t)};
            //                adjL->push_back(tmp);
            //            }
        }
        else // node does not exist
        {
            vector<int> tmp;
            tmp.push_back(stoi(s));
            tmp.push_back(stoi(t));
            //            int tnode=nodeExists(stoi(t));
            //            if(tnode<0)
            //            {
            //                vector<int> tmp {stoi(t)};
            //                adjL->push_back(tmp);
            //            }
            adjL->push_back(tmp);
        }
        if(GRAPH_TYPE==1)
        {
            loc=nodeExists(stoi(t), adjL);
            if(loc>=0)//node exists
            {
                (*adjL)[loc].push_back(stoi(s));
            }
            else // node t does not exist
            {
                vector<int> tmp;
                tmp.push_back(stoi(t));
                tmp.push_back(stoi(s));
                adjL->push_back(tmp);
            }
        }
    }
    
    return 1;
}

void printGraph(vector<vector<int> > *adjL)
{
    cout<<"printing graph\n";
    for(int i=0;i<adjL->size();i++)
    {
        for(int j=0;j<(*adjL)[i].size();j++)
        {
            cout<<(*adjL)[i][j]<<"\t";
        }
        cout<<"\n";
    }
}
*/
#endif
