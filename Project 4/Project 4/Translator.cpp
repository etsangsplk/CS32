#include "provided.h"
#include <string>
#include <vector>
#include <map>
using namespace std;

class TranslatorImpl
{
public:
    TranslatorImpl();
    bool pushMapping(string ciphertext, string plaintext);
    bool popMapping();
    string getTranslation(const string& ciphertext) const;
private:
    map<char, char> m_table;
    vector<map<char, char>> m_oldMaps;
    int m_pushMapCall;
    int m_popMapCall;
};

TranslatorImpl::TranslatorImpl()
: m_pushMapCall(0), m_popMapCall(0)
{
    // no big-O requirements
    for(char letter = 'A'; letter != '['; letter++)
        m_table[letter] = '?';
}

bool TranslatorImpl::pushMapping(string ciphertext, string plaintext)
{
    // O(N+L) or O(1)
    if(ciphertext.size() != plaintext.size())
        return false;
    
    m_oldMaps.push_back(m_table);
    
    transform(ciphertext.begin(), ciphertext.end(), ciphertext.begin(), toupper);
    transform(plaintext.begin(), plaintext.end(), plaintext.begin(), toupper);
    
    for(int i = 0; i < ciphertext.size(); i++)
    {
        if(!isalpha(ciphertext[i]) || !isalpha(plaintext[i]))
            return false;
        map<char, char>::iterator it = m_table.find(ciphertext[i]);
        it->second = plaintext[i];
    }
    
    m_pushMapCall++;
    return true;
}

bool TranslatorImpl::popMapping()
{
    // O(1)
    if(m_popMapCall == m_pushMapCall)
        return false;
    
    vector<map<char, char>>::iterator it;
    it = m_oldMaps.end();
    it--;
    m_table = (*it);
    
    it = m_oldMaps.erase(it);
    
    m_popMapCall++;
    return true;
}

string TranslatorImpl::getTranslation(const string& ciphertext) const
{
    // no big-O requirements
    string result = "";
    string temp = ciphertext;
    transform(temp.begin(), temp.end(), temp.begin(), toupper);
    
    for(int i = 0; i < temp.size(); i++)
    {
        map<char, char>::const_iterator it = m_table.find(temp[i]);
        if(!isupper(ciphertext[i]))
        {
            char temp = it->second;
            temp = tolower(temp);
            result += temp;
        }
        else if(!isalpha(temp[i]))
            result += temp[i];
        else
            result += it->second;
    }
    return result;
}

//******************** Translator functions ************************************

// These functions simply delegate to TranslatorImpl's functions.
// You probably don't want to change any of this code.

Translator::Translator()
{
    m_impl = new TranslatorImpl;
}

Translator::~Translator()
{
    delete m_impl;
}

bool Translator::pushMapping(string ciphertext, string plaintext)
{
    return m_impl->pushMapping(ciphertext, plaintext);
}

bool Translator::popMapping()
{
    return m_impl->popMapping();
}

string Translator::getTranslation(const string& ciphertext) const
{
    return m_impl->getTranslation(ciphertext);
}
