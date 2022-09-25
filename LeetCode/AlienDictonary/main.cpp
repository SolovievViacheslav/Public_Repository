#include <iostream>
#include <bits/stdc++.h>

using namespace std;

int cmp(char ch1,char ch2, string order)
{
    int rv;
    map<char,int> mp;
    for(int i=0;i<order.length();i++)
        mp[order[i]]=i;
    return rv;
}

bool func(vector <string>& words, string order)
{
    bool rv=true;
    map<char,int> mp;
    for(int i=0;i<order.length();i++)
        mp[order[i]]=i;

    for(int i=0;i<words.size()-1;i++)
    {
        int min_len;
        min_len=words[i].length()<words[i+1].length()?words[i].length():
                                                      words[i+1].length();

        bool cheqv=true;
        int j=0;
        for(j=0;j<min_len;j++)
        {
            char ch1=words[i][j];
            char ch2=words[i+1][j];
            if(ch1!=ch2)cheqv=false;
            if(mp[ch1]<mp[ch2])break;
            if(mp[ch1]==mp[ch2])continue;
            if(mp[ch1]>mp[ch2])
                    return false;

        }

        if((j==min_len)&&cheqv)
            if(words[i].length()>words[i+1].length())return false;

    }

    return rv;
}

int main()
{
    //vector <string> words={"hello","leetcode"};
    //string order="hlabcdefgijkmnopqrstuvwxyz";
    string order="abcdefghijklmnopqrstuvwxyz";
    vector <string> words={"apple","app"};
    bool j= func(words,order);
    cout << "Hello World!" << endl;
    return 0;
}
