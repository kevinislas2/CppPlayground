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
    // Not pure virtual so Markdown doesnt have to empty implement
    virtual void start(ostringstream& oss) {}
    virtual void end(ostringstream& oss) {}

    virtual void add_list_item(ostringstream& oss, const string& item) = 0;
};

struct MarkdownListStrategy : ListStrategy {
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

struct TextProcessor
{
    void clear() 
    {
        oss.str("");
        oss.clear();
    }
    void append_list(const vector<string>& items)
    {
        list_strategy->start(oss);
        for (auto& item : items) {
            list_strategy->add_list_item(oss, item);
        }
        list_strategy->end(oss);
    }

    void set_output_format(const OutputFormat& format)
    {
        switch(format)
        {
            case OutputFormat::markdown:
                list_strategy = make_unique<MarkdownListStrategy>();
                break;
            case OutputFormat::html:
                list_strategy = make_unique<HtmlListStrategy>();
                break;
        }
    }

    string str() const { return oss.str();}
private:
    ostringstream oss;
    unique_ptr<ListStrategy> list_strategy;
};

int main(int argc, char* argv[])
{

    vector<string> items{"foo", "bar", "baz"};

    TextProcessor tp;
    tp.set_output_format(OutputFormat::markdown);
    tp.append_list(items);
    cout << tp.str() << '\n';

    tp.clear();
    tp.set_output_format(OutputFormat::html);
    tp.append_list(items);
    cout << tp.str() << '\n';

    return 0;
}