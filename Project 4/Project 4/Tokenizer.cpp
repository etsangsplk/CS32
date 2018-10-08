#include "provided.h"
#include <string>
#include <vector>
#include <sstream>
using namespace std;

class TokenizerImpl
{
public:
    TokenizerImpl(string separators);
    vector<string> tokenize(const std::string& s) const;
private:
    vector<char> m_separators;
    
};

TokenizerImpl::TokenizerImpl(string separators)
{
    for(int i = 0; i < separators.size(); i++)
        m_separators[i] = separators[i];
}

vector<string> TokenizerImpl::tokenize(const std::string& s) const
{
    // O(SP)
    vector<string> tokens;
    
    string temp = "";
    for(int i = 0; i < s.size(); i++)
    {
        for(int j = 0; j < m_separators.size(); j++)
        {
            if(isalpha(s[i]))
            {
                temp += s[i];
                break;
            }
            else if(s[i] == m_separators[j])
            {
                if(temp != "")
                    tokens.push_back(temp);
                temp = "";
                break;
            }
        }
    }
    return tokens;  // This compiles, but may not be correct
}

//******************** Tokenizer functions ************************************

// These functions simply delegate to TokenizerImpl's functions.
// You probably don't want to change any of this code.

Tokenizer::Tokenizer(string separators)
{
    m_impl = new TokenizerImpl(separators);
}

Tokenizer::~Tokenizer()
{
    delete m_impl;
}

vector<string> Tokenizer::tokenize(const std::string& s) const
{
    return m_impl->tokenize(s);
}
