#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <memory>

using namespace std;

enum class OutputFormat
{
    markdown,
    html
};

/*

Markdown lists:
* elem1
* elem2

Html lists:

<ul>
  <li>elem1</li>
  <li>elem2</li>
</ul>


*/

struct ListStrategy
{   
    virtual ~ListStrategy() = default;
    // Not pure virtual so Markdown doesnt have to empty implement
    virtual void start(ostringstream& oss) = 0;
    virtual void end(ostringstream& oss) = 0;

    virtual void add_list_item(ostringstream& oss, const string& item) = 0;
};

struct MarkdownListStrategy : ListStrategy {

    void start(ostringstream& oss) override {}
    void end(ostringstream& oss) override {}
    void add_list_item(ostringstream& oss, const string& item) override
    {
        oss << "* " << item << '\n';
    }
};

struct HtmlListStrategy : ListStrategy {
    void start(ostringstream& oss) override {
        oss << "<ul>\n";
    }

    void end(ostringstream& oss) override {
        oss << "</ul>\n";
    }

    void add_list_item(ostringstream& oss, const string& item) override {
        oss << "  <li>" << item << "</li>\n";
    }
};

template <typename LS>
struct TextProcessor
{
    void clear() 
    {
        oss.str("");
        oss.clear();
    }
    void append_list(const vector<string>& items)
    {
        list_strategy.start(oss);
        for (auto& item : items) {
            list_strategy.add_list_item(oss, item);
        }
        list_strategy.end(oss);
    }

    string str() const { return oss.str();}
private:
    ostringstream oss;
    LS list_strategy;
};

int main(int argc, char* argv[])
{
    // markdown
    TextProcessor<MarkdownListStrategy> markdownProcessor;
    markdownProcessor.append_list({"foo", "bar", "baz"});
    cout << markdownProcessor.str() << '\n';

    //html
    TextProcessor<HtmlListStrategy> htmlProcessor;
    htmlProcessor.append_list({"foo", "bar", "baz"});
    cout << htmlProcessor.str() << '\n';

    return 0;
}