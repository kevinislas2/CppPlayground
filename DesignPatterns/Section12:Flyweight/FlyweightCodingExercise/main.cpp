/*
Flyweight Coding Exercise

You are given a class called Sentence, which takes a string such as "hello world".
You need to provide an interface such that the indexer
operator [] returns a WordToken that can be used to capitalize a particula word in the sentence

Typical use would be something like:

Sentence sentence("Hello World");
sentence[i].capitalize = true;
cout << sentence.str(); // prints "hello WORLD"
*/

#include <string>
#include <map>
#include <sstream>
#include <iostream>
#include <vector>

using namespace std;

struct Sentence
{
  struct WordToken
  {
    bool capitalize = false;
  };

  Sentence(const string& text)
    {
        string word;
        istringstream ss{text};
        while(ss >> word) {
            words.push_back(word);
        }
    }

  WordToken& operator[](size_t index)
  {
    
    if(index >= words.size()) {
        throw out_of_range("Index exceeded the number of words");
    }

    if(wordTokens.find(index) != wordTokens.end()) {
        wordTokens[index] = WordToken{};
    }
    return wordTokens[index];
  }

  string str() const
  {

    stringstream ss{};

    for(size_t i = 0; i < words.size(); ++i) {

        if(wordTokens.find(i) != wordTokens.end()
            && wordTokens.at(i).capitalize) {

            for(const char& c : words[i]) {
                // Given that c is a const reference wee need to copy it to a separate char before appending to ss
                char b = toupper(c);
                ss << b;
            }
        } else {
            ss << words[i];
        }

        // Add a space to every word except the last one
        if(i != words.size() - 1) {
            ss << ' ';
        }
    }

    return ss.str();
  }

private:
    map<size_t, WordToken> wordTokens{};
    vector<string> words;
};

int main() {

    Sentence sentence("Hello World");
    sentence[1].capitalize = true;
    cout << sentence.str() << '\n'; // prints "hello WORLD"

    //sentence[2].capitalize = true; // Throws bad range exception
    return 0;
}