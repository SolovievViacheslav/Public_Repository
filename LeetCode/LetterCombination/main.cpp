#include <iostream>
#include <bits/stdc++.h>

using namespace std;



vector<string> func(string digits)
{
    map<string,vector<string> > sym;
    vector<string> rv;

    sym["2"]={"a","b","c"};
    sym["3"]={"d","e","f"};
    sym["4"]={"g","h","i"};
    sym["5"]={"j","k","l"};
    sym["6"]={"m","n","o"};
    sym["7"]={"p","q","r","s"};
    sym["8"]={"t","u","v"};
    sym["9"]={"w","x","y","z"};

    //f="a"+"b";
    if(digits.length()==1)
    {
        char ch=digits[0];
        string d1(1,ch);

        if(sym.find(d1)!=sym.end())
        {
            for(int i=0;i<sym[d1].size();i++)
            {
                rv.push_back(sym[d1][i]);
            }
        }

    }else if(digits.length()==2)
    {
        char ch=digits[0];
        string d1(1,ch);
        ch=digits[1];
        string d2(1,ch);

        for(int i=0;i<sym[d1].size();i++)
        {
            for(int j=0;j<sym[d2].size();j++)
             rv.push_back(sym[d1][i]+sym[d2][j]);
        }
    }
    else if(digits.length()==3)
    {
        char ch;
        ch=digits[0]; string d1(1,ch);
        ch=digits[1]; string d2(1,ch);
        ch=digits[2]; string d3(1,ch);
        for(int i=0;i<sym[d1].size();i++)
            for(int j=0;j<sym[d2].size();j++)
                for(int k=0;k<sym[d3].size();k++)
                    rv.push_back(sym[d1][i]+sym[d2][j]+sym[d3][k]);

    }else if(digits.length()==4)
    {
        char ch;
        ch=digits[0]; string d1(1,ch);
        ch=digits[1]; string d2(1,ch);
        ch=digits[2]; string d3(1,ch);
        ch=digits[3]; string d4(1,ch);
        for(int i=0;i<sym[d1].size();i++)
            for(int j=0;j<sym[d2].size();j++)
                for(int k=0;k<sym[d3].size();k++)
                    for(int m=0;m<sym[d4].size();m++)
                        rv.push_back(sym[d1][i]+sym[d2][j]+sym[d3][k]+sym[d4][m]);


    }else if(digits.length()==5)
    {
        char ch;
        ch=digits[0]; string d1(1,ch);
        ch=digits[1]; string d2(1,ch);
        ch=digits[2]; string d3(1,ch);
        ch=digits[3]; string d4(1,ch);
        ch=digits[4]; string d5(1,ch);
        for(int i=0;i<sym[d1].size();i++)
            for(int j=0;j<sym[d2].size();j++)
                for(int k=0;k<sym[d3].size();k++)
                    for(int m=0;m<sym[d4].size();m++)
                        for(int n=0;n<sym[d5].size();n++)
                            rv.push_back(sym[d1][i]+
                                         sym[d2][j]+
                                         sym[d3][k]+
                                         sym[d4][m]+
                                         sym[d5][n]);



    }



    return rv;
}

int main()
{
    string s_in="23456";
    func(s_in);

    return 0;
}
