
#include <iostream>
#include <map>
#include <fstream>
#include <string>

using namespace std;

#include <boost/lexical_cast.hpp>

using namespace boost;

class SingletonDatabase
{
    map<string, int> capitals;

    SingletonDatabase()
    {
        cout << "Initializing database\n";
        ifstream ifs("capitals.txt");

        string s, s2;

        while(getline(ifs, s))
        {
            getline(ifs, s2);

            int pop = lexical_cast<int>(s2);
            capitals[s] = pop;
        }
    }

public:
    SingletonDatabase(SingletonDatabase const& other) = delete;
    void operator=(SingletonDatabase const& other) = delete;

    static SingletonDatabase& get()
    {
        static SingletonDatabase db;
        return db;
    }

    int get_population(const string& name)
    {
        return capitals[name];
    }
};

int main()
{
    string city = "Tokyo";
    cout << city << " has population " << 
        SingletonDatabase::get().get_population("Tokyo") << '\n';
}