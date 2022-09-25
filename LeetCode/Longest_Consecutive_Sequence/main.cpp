#include <iostream>
#include <bits/stdc++.h>

using namespace std;
int func (vector<int> nums)
{
    int max_n=0;
    int n=1;
    if(nums.size())
    {
        sort(nums.begin(),nums.end());
        for(int i=0;i<nums.size()-1;i++)
        {
            if(nums[i+1]==nums[i])continue;
            int d=nums[i+1]-nums[i];
            if(d==1)
                n++;
            else
            {
                max_n=n>max_n?n:max_n;
                n=1;
            }
        }
        max_n=n>max_n?n:max_n;
    }
    return max_n;
}
int main()
{
    //vector<int>v={100,4,200,1,3,2};
    //vector<int>v={0,3,7,2,5,8,4,6,0,1};//9
    vector<int>v={1,2,0,1};
    func(v);
    cout << "Hello World!" << endl;
    return 0;
}
