#include <iostream>
#include <vector>

using namespace std;

vector<vector<int>> all_sub_sets;

void gen_sub_set(vector<int> &sub_set, int i ,vector<int> &vec)
{
    if(i==0)
    {
    }
    if(i==vec.size())
    {
        all_sub_sets.push_back(sub_set);
        return ;
    }
    cout<<vec[i];
    gen_sub_set(sub_set, i+1 , vec);
    sub_set.push_back(vec[i]);
    gen_sub_set(sub_set , i+1 , vec);
    sub_set.pop_back();

}

int main()
{
    int n ;
    cin >> n ;
    vector<int> vec(n) ;

    for(int i=0 ; i<n ; ++i)
    {
        cin>> vec[i] ;
    }

    vector<int> empty_vec ;
    gen_sub_set(empty_vec , 0 , vec) ;
    for(auto sub_set: all_sub_sets)
    {
        for(auto i : sub_set)
        {
            cout<< i <<" ";
        }
        cout<<endl ;
    }

    return 0;
}
