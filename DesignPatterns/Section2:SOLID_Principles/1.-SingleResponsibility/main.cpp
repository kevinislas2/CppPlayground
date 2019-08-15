#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>

using namespace std;
 
/*
Single responsibility principle states that a class or function should only be concerned about
its functionality over the system. This functionality should be encapsulated.

"A class should have only one reason to change" - Robert C. Martin
*/

struct Journal
{
    string title;
    vector<string> entries;
    Journal(const string& title) : title(title) {}

    void add_entry(const string& entry)
    {   
        static int count = 1;
        entries.push_back(std::to_string(count++) + ": " + entry);
    }

    /*
    Journal should not be concerned with saving, this function should be separated from Journal
    This would mean that journal would also have to deal with loading, etc...
    If we have various classes, each would be implementing its own save/load functions,
    that would imply that a change in save/load requirements would imply a change in every class
    that uses save/load

    **Separation of concerns**

    void save(const string& filename)
    {
        ofstream ofs(filename);
        for (auto& e : entries) {
            ofs << e << '\n';
        }
    }
     */

};

/*
    Implementing save functionality in a separate struct facilitates refactoring
 */
struct PersistenceManager
{
    static void save(const Journal& j, const string& filename)
    {
        ofstream ofs(filename);
        for (auto& e : j.entries) {
            ofs << e << '\n';
        }
    }
};

int main() {

    Journal journal{"Dear Diary"};
    journal.add_entry("I ate a bug");
    journal.add_entry("I cried today");
    
    PersistenceManager::save(journal, "myJournal.txt");
    
    return 0;
}
