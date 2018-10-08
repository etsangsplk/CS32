#include "provided.h"
#include <string>
#include <map>
#include <vector>
#include <functional>
#include <iostream>
#include <fstream>

using namespace std;

class WordListImpl
{
public:
    WordListImpl();
    bool loadWordList(string filename);
    bool contains(string word) const;
    vector<string> findCandidates(string cipherWord, string currTranslation) const;
private:
    //    map<string, string> m_listOfWords;
    //    map<char, char> m_alphabet;
    vector<string> m_listOfWords;
};

WordListImpl::WordListImpl()
{
    //    for(char letter = 'A'; letter != '['; letter++)
    //    {
    //        char num = '1';
    //        m_alphabet[letter] = num;
    //        num++;
    //    }
}

bool WordListImpl::loadWordList(string filename)
{
    ifstream infile(filename);
    if(!infile)
        return false;
    
    string word = "";
    while(getline(infile, word))
    {
        string alphaNum = "";
        if(isalpha(word[0]) || word[0] == '\'')
        {
            //            for(int i = 0; i < word.size(); i++)
            //            {
            //                if(word[i] == '\'')
            //                    alphaNum += "'";
            //                else
            //                {
            //                    map<char, char>::const_iterator it = m_alphabet.find(word[i]);
            //                    alphaNum += it->second;
            //                }
            //            }
            //            m_listOfWords[word] = alphaNum;
            m_listOfWords.push_back(word);
        }
    }
//    for(int i = 0; i < m_listOfWords.size(); i++)
//        cout << m_listOfWords[i] << endl;
    return true;
}

bool WordListImpl::contains(string word) const
{
    // O(1)
//    map<string, string>::const_iterator it = m_listOfWords.find(word);
//    if(it->first == word)
//        return true;
    for(int i = 0; i < m_listOfWords.size(); i++)
    {
        if(m_listOfWords[i] == word)
            return true;
    }
    return false; // This compiles, but may not be correct
}

vector<string> WordListImpl::findCandidates(string cipherWord, string currTranslation) const
{
    // O(Q), Q = words that match pattern, not N words
    vector<string> candidates;
    if(cipherWord.size() != currTranslation.size())
        return candidates;
    //    for(int i = 0; cipherWord.size(); i++)
    //    {
    //
    //    }
    
    return candidates;  // This compiles, but may not be correct
}

//***** hash functions for string, int, and char *****

unsigned int hash(const std::string& s)
{
    return std::hash<std::string>()(s);
}

unsigned int hash(const int& i)
{
    return std::hash<int>()(i);
}

unsigned int hash(const char& c)
{
    return std::hash<char>()(c);
}

//******************** WordList functions ************************************

// These functions simply delegate to WordListImpl's functions.
// You probably don't want to change any of this code.

WordList::WordList()
{
    m_impl = new WordListImpl;
}

WordList::~WordList()
{
    delete m_impl;
}

bool WordList::loadWordList(string filename)
{
    return m_impl->loadWordList(filename);
}

bool WordList::contains(string word) const
{
    return m_impl->contains(word);
}

vector<string> WordList::findCandidates(string cipherWord, string currTranslation) const
{
    return m_impl->findCandidates(cipherWord, currTranslation);
}

