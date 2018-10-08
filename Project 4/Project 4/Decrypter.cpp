#include "provided.h"
#include <string>
#include <vector>
using namespace std;

class DecrypterImpl
{
public:
    DecrypterImpl();
    bool load(string filename);
    vector<string> crack(const string& ciphertext);
private:
};

DecrypterImpl::DecrypterImpl()
{
    // no big-O requirement
}

bool DecrypterImpl::load(string filename)
{
    WordList w;
    if(w.loadWordList(filename))
        return true;
    return false;  // This compiles, but may not be correct
}

vector<string> DecrypterImpl::crack(const string& ciphertext)
{
    
    return vector<string>();  // This compiles, but may not be correct
}

//******************** Decrypter functions ************************************

// These functions simply delegate to DecrypterImpl's functions.
// You probably don't want to change any of this code.

Decrypter::Decrypter()
{
    m_impl = new DecrypterImpl;
}

Decrypter::~Decrypter()
{
    delete m_impl;
}

bool Decrypter::load(string filename)
{
    return m_impl->load(filename);
}

vector<string> Decrypter::crack(const string& ciphertext)
{
   return m_impl->crack(ciphertext);
}
