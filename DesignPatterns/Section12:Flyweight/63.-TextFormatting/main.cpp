
#include <iostream>
#include <string>
#include <cstring>
#include <vector>

using namespace std;

class FormattedText
{
    string plain_text;

    //bad bool formatting
    bool *caps;
public:
    FormattedText(const string& plain_text)
        : plain_text(plain_text)
        {
            caps = new bool[plain_text.length()];
            memset(caps, 0, plain_text.length());       //Ensure that array is set to 0;
        }

    ~FormattedText()
    {
        delete[] caps;
    }

    void capitalize(int start, int end)
    {
        for (int i=start; i <= end; i++) {
            caps[i] = true;
        }
    }

    friend ostream &operator<<(ostream& os, const FormattedText &obj) {
        string s;
        for (int i = 0; i < obj.plain_text.length(); ++i) {
            char c = obj.plain_text[i];

            s += (obj.caps[i] ? toupper(c) : c);
        }

        return os << s;
    }
};

class BetterFormattedText
{
public:
    struct TextRange
    {
        int start, end;
        bool capitalize;  // bold, italic, etc.

        bool covers(int position) const
        {
            return position >= start && position <= end;
        }
    };
    TextRange& get_range(int start, int end)
    {
        formatting.emplace_back(TextRange{start, end});
        
        return *formatting.rbegin();    //Returns iterator to rightmost part of vector
    }

    BetterFormattedText(const string& plain_text)
        : plain_text{plain_text}
        {}

    friend ostream& operator<<(ostream& os, const BetterFormattedText &obj) {

        string s;
        for(int i = 0; i < obj.plain_text.length(); ++i) {
            auto c = obj.plain_text[i];

            // This could probably be optimized by storing ranges in a different ds
            for (const auto& rng : obj.formatting) {
                if(rng.covers(i) && rng.capitalize) {
                    c = toupper(c);
                }
            }

            s += c;
        }

        return os << s;
    }

private:
    string plain_text;
    vector<TextRange> formatting;
};

int main(int argc, char* argv[])
{
    FormattedText ft{"This is a brave new world"};
    ft.capitalize(10, 15);

    cout << ft << '\n';

    BetterFormattedText bft{"This is a brave new world"};
    bft.get_range(10, 20).capitalize = true;
    cout << bft << '\n';
}