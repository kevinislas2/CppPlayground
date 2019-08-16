#include <string>
#include <vector>
#include <ostream>
#include <utility>
#include <iostream>

using namespace std;

class CodeBuilder
{
    string class_name;
    vector<pair<string, string>> fields;
    size_t indent = 2;
public:

  CodeBuilder(const string& class_name)
    : class_name{class_name}
  {
  }

  CodeBuilder& add_field(const string& name, const string& type)
  {
    fields.emplace_back(make_pair(name, type));
    return *this;
  }

  friend ostream& operator<<(ostream& os, const CodeBuilder& obj)
  {
    os << "class " << obj.class_name << "\n{\n";
    for (auto field : obj.fields) {
        os << string(obj.indent, ' ') << field.second << ' ' << field.first << ";\n";
    }
    os << "};\n";
    return os;
  }
};

int main() {
    auto cb = CodeBuilder{"Person"}.add_field("name", "string").add_field("age", "int");

    cout << cb;
}