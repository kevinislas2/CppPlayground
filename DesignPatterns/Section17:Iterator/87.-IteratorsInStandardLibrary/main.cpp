
#include <string>
#include <vector>
#include <iostream>

using namespace std;

int main()
{
    vector<string> names {"john", "jane", "jill", "jack"};
    vector<string>::iterator it = names.begin();            //Exists as member function and as global [vector.begin(), begin(vector)]

    cout << "first name is " << *it << '\n';

    ++it;

    it->append(string(" goodall"));

    cout << "second name is " << *it << '\n';

    while(++it != names.end()) {
        cout << "another name: " << *it << '\n';
    }

    // Some containers may be accessed in reverse order
    for(auto ri = names.rbegin(); ri != names.rend(); ++ri){         // advancemment, we dont need to use -- (this would actually take us back)
        cout << *ri;

        if(ri+1 != names.rend()) {
            cout << ", "; 
        }
    }
    cout << '\n';

    //Constant iterators
    vector<string>::const_reverse_iterator jack = crbegin(names);
    // *jack += string("reacher"); // It wont allow us to modify the element

    //Range based for loop
    for (auto& name : names)        //Uses begin() and end() : name is automatically *it and it is increased on each step
    //for (auto&& name : names)     //On some structures we might want to ensure that we use the rvalue reference ()
    {
        cout << "name = " << name << '\n';
    }
}