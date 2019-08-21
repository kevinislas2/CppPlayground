/*
make
./runTests
*/

#include <iostream>
#include <map>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

#include <boost/lexical_cast.hpp>
#include <gtest/gtest.h>
#include <gmock/gmock.h>

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

struct SingletonRecordFinder
{
    int total_population(vector<string> names) {
        int result{0};
        for (auto& name : names)
        {
            result += SingletonDatabase::get().get_population(name);
        }
        return result;
    }
};

TEST(RecordFinderTests, SingletonTotalPopulationTest)
{
    SingletonRecordFinder rf;
    vector<string> names{"Seoul", "Mexico City"};
    int tp = rf.total_population(names);
    EXPECT_EQ(17500000+17400000, tp);           // Strongly typed to the production db
    // Not unit test but rather integration test
}

int main(int ac, char* av[])
{
    testing::InitGoogleTest(&ac, av);
    return RUN_ALL_TESTS();
}