#include <iostream>
#include <list>
#include <queue>
#include <stack>
#include <fstream>
#include "WordLadder.h"

using namespace std;

WordLadder::WordLadder(const string &filename)
{
    string oneline;
    ifstream myfile;
    myfile.open(filename);
    while(getline(myfile, oneline))
    {
        if(oneline.size()!=5) 
        {
            cout<<"word in dictionary does not have 5 characters"<<endl;
            return;
        }

        dict.push_back(oneline);
    }
}


void WordLadder::outputLadder(const string &start, const string &end, const string &outputFile)
{
    bool findstart=false, findend=false;
    ofstream output;
    output.open(outputFile);

    for(list<string>::iterator iter=dict.begin(); iter!=dict.end(); iter++) 
    {
        if(*iter==start) findstart=true;
        if(*iter==end) findend=true;
    }

    if(!(findstart && findend))  
    {
        cout<<"start or end word not found"<<endl;
        return;
    }

    stack<string> stk;
    stk.push(start);

    queue<stack<string>> que;
    que.push(stk);

    while(!que.empty())
    {
        stack<string> front=que.front();
        string topword=front.top();
        for(list<string>::iterator iter=dict.begin(); iter!=dict.end(); iter++)
        {
            if(off_by_one(topword, *iter)) 
            {
                stack<string> newstack=front;
                newstack.push(*iter);
                if(*iter==end) 
                {
                    output_ladder_to_file(newstack, output);
                    return;
                }
                else
                {
                    que.push(newstack);
                    iter = dict.erase(iter);
                }
        
            }

        }
        
        que.pop();
    }

    output<<"No Word Ladder Found"<<endl;
    return;

}

bool WordLadder::off_by_one(string &word1, string& word2) const
{
    int off_num=0;
    for(unsigned i=0; i<word1.size(); i++)
    {
        if(word1[i]!=word2[i]) off_num+=1; 
    }

    if(off_num==1) return true;
    else return false;

}

void WordLadder::output_ladder_to_file(stack<string> &stk, ofstream &output)
{
    stack<string> stk_rev;
    while(!stk.empty())
    {
        stk_rev.push(stk.top());
        stk.pop();
        
    }

    while(!stk_rev.empty())
    {
        output<<stk_rev.top()<<endl;
        stk_rev.pop();
        
    }

}
















