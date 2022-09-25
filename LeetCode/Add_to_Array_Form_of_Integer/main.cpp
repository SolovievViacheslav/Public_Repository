#include <iostream>
#include <bits/stdc++.h>

using namespace std;

class Solution {
public:
    vector<int> num2vec(int num)
    {
        vector<int> res;
        int m=0,r=num,n=num;
        while(n)
        {
            r=n%10;
            n=n/10;
            res.push_back(r);
        }
        vector<int> res2;
        res2.resize(res.size());
        int j=res2.size()-1;
        for(int i=0;i<res2.size();i++,j--)
        {
            res2[j]=res[i];
        }
        res=res2;
        //res.pop_back();
        return res;
    }
    vector<int> addToArrayForm(vector<int>& num, int k) {
        vector<int> res;
        vector<int> vk=num2vec(k);
        while(vk.size()<num.size())
            vk.insert(vk.begin(),0);
        while(num.size()<vk.size())
            num.insert(num.begin(),0);

        res.resize(max(num.size()+1,vk.size()+1));

        int last_indx=num.size()-1;
        int j=vk.size()-1;
        int m=0;
        int i=0;
        int v=0;

        last_indx=res.size()-1-1;

        for(i=last_indx;i>=0;i--,j--)
        {
            int t=((num[i]+vk[j])+m)%10;
            m=(num[i]+vk[j]+m)/10;
            res[res.size()-1-v]=t;
            v++;
        }

        if(m){
            res[res.size()-1-v]=m;
            v++;
            j--;
        }

        if(res[0]==0)res.erase(res.begin());
        return res;
    }
};
int main()
{
    Solution s;

    vector<vector<int>> vok;
    vector<int> k;
    vector <vector<int>> v={{1,2,0,0},//34 //{1,2,3,4}
                            {2,7,4},
                            {2,1,5},
                            {0},
                            {1},
                            {0},
                            {6},
                            {7}//993
                           };

    k.push_back(34);vok.push_back({1,2,3,4});
    k.push_back(181);vok.push_back({4,5,5});
    k.push_back(806);vok.push_back({1,0,2,1});
    k.push_back(23);vok.push_back({2,3});
    k.push_back(33);vok.push_back({3,4});
    k.push_back(10000);vok.push_back({1,0,0,0,0});
    k.push_back(809);vok.push_back({8,1,5});
    k.push_back(993);vok.push_back({1,0,0,0});

    int passed=0;
    for(int i=0;i<v.size();i++)
    {
        vector<int>vt=v[i];
        vector<int>vokt=vok[i];
        int kt=k[i];

        vector<int>y=s.addToArrayForm(vt,kt);

        if(y!=vokt)
        {
            int t;
            t=9;
        }
        else
        {
            int t;
            t=9;
            passed++;
        }
    }

    int tests=k.size();
    if(tests!=passed)
    {
        cout<<"NOT Passed "<<tests-passed;
    }
    /*for(int i=0;i<y.size();i++)
        cout<<y[i]<<"\n";*/
    s.num2vec(123);
    cout << "Hello World!" << endl;
    return 0;
}
