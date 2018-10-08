//
//  main.cpp
//  investment
//
//  Created by Vanessa Lee on 2/7/18.
//  Copyright © 2018 Vanessa Lee. All rights reserved.
//

class Investment {
public:
    Investment(string n, int p);
    virtual ~Investment();
    virtual string description() const = 0;
    virtual bool fungible() const = 0;
    int purchasePrice() const;
    string name() const;
    
private:
    int m_price;
    string m_name;
};

Investment::Investment(string n, int p) {
    m_name = n;
    m_price = p;
}

Investment::~Investment() { }

int Investment::purchasePrice() const {
    return m_price;
}

string Investment::name() const {
    return m_name;
}

class Painting : public Investment {
public:
    Painting(string n, int p);
    virtual ~Painting();
    virtual string description() const;
    virtual bool fungible() const;
private:
};

Painting::Painting(string n, int p)
: Investment(n, p) { }

Painting::~Painting() {
    cout << "Destroying " << name() << ", a " << description() << endl;
}

string Painting::description() const {
    return "painting";
}

bool Painting::fungible() const {
    return false;
}

class Stock : public Investment {
public:
    Stock(string n, int p, string t);
    virtual ~Stock();
    virtual string description() const;
    virtual bool fungible() const;
private:
    string m_ticker;
};

Stock::Stock(string n, int p, string t)
: Investment(n, p) {
    m_ticker = t;
}

Stock::~Stock() {
    cout << "Destroying " << name() << ", a stock holding" << endl;
}

string Stock::description() const {
    return "stock trading";
}

bool Stock::fungible() const {
    return true;
}

class House : public Investment {
public:
    House(string n, int p);
    virtual ~House();
    virtual string description() const;
    virtual bool fungible() const;
private:
};

House::House(string n, int p)
: Investment(n, p) { }

House::~House() {
    cout << "Destroying the " << description() << " " << name() << endl;
}

string House::description() const {
    return "house";
}

bool House::fungible() const {
    return false;
}
