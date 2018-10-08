// ======================================= Investment
class Investment
{
  public:
    Investment(string nm, int pp);
    string name() const;
    int purchasePrice() const;
    virtual string description() const = 0;
    virtual bool fungible() const;
    virtual ~Investment() {}
  private:
    string m_name;
    int m_purchasePrice;
};

Investment::Investment(string nm, int pp)
 : m_name(nm), m_purchasePrice(pp)
{}

string Investment::name() const
{
  return m_name;
}

int Investment::purchasePrice() const
{
  return m_purchasePrice;
}

bool Investment::fungible() const
{
  return false;
}

// ======================================= Painting
class Painting : public Investment
{
  public:
    Painting(string nm, int pp);
    virtual string description() const;
    virtual ~Painting();
};

Painting::Painting(string nm, int pp)
 : Investment(nm, pp)
{}

string Painting::description() const
{
  return "painting";
}

Painting::~Painting()
{
  cout << "Destroying " << name() << ", a painting" << endl;
}

// ======================================= Stock
class Stock : public Investment
{
  public:
    Stock(string nm, int pp, string ticker);
    virtual string description() const;
    virtual bool fungible() const;
    virtual ~Stock();
  private:
    string m_tickerSymbol;
};

Stock::Stock(string nm, int pp, string ticker)
 : Investment(nm, pp), m_tickerSymbol(ticker)
{}

string Stock::description() const
{
  return "stock trading as " + m_tickerSymbol;
}

bool Stock::fungible() const
{
  return true;
}

Stock::~Stock()
{
  cout << "Destroying " << name() << ", a stock holding" << endl;
}

// ======================================= House
class House : public Investment
{
  public:
    House(string nm, int pp);
    virtual string description() const;
    virtual ~House();
};

House::House(string nm, int pp)
 : Investment(nm, pp)
{}

string House::description() const
{
  return "house";
}

House::~House()
{
  cout << "Destroying the house " + name() << endl;
}
Problem 2:
  // Return false if the somePredicate function returns false for at
  // least one of the array elements; return true otherwise.
bool allTrue(const double a[], int n)
{
    if (n <= 0)
        return true;
    if ( ! somePredicate(a[0]))
        return false;
    return allTrue(a+1, n-1);
}

  // Return the number of elements in the array for which the
  // somePredicate function returns false.
int countFalse(const double a[], int n)
{
    if (n <= 0)
        return 0;
    int t = ! somePredicate(a[0]);  // 1 if false, 0 if true
    return t + countFalse(a+1, n-1);
}

  // Return the subscript of the first element in the array for which
  // the somePredicate function returns false.  If there is no such
  // element, return -1.
int firstFalse(const double a[], int n)
{
    if (n <= 0)
        return -1;
    if ( ! somePredicate(a[0]))
        return 0;
    int k = firstFalse(a+1, n-1);
    if (k == -1)
        return -1;
    return 1 + k;  // element k of "the rest of a" is element 1+k of a
}

  // Return the subscript of the smallest double in the array (i.e.,
  // the one whose value is <= the value of all elements).  If more
  // than one element has the same smallest value, return the smallest
  // subscript of such an element.  If the array has no elements to
  // examine, return -1.
int indexOfMin(const double a[], int n)
{
    if (n <= 0)
        return -1;
    if (n == 1)
        return 0;
    int k = 1 + indexOfMin(a+1, n-1);  // indexOfMin can't return -1 here
    return a[0] <= a[k] ? 0 : k;

    // Here's an alternative for the last two lines above:
    // int k = indexOfMin(a, n-1);  // indexOfMin can't return -1 here
    // return a[k] <= a[n-1] ? k : n-1;
}

  // If all n2 elements of a2 appear in the n1 element array a1, in
  // the same order (though not necessarily consecutively), then
  // return true; otherwise (i.e., if the array a1 does not include
  // a2 as a not-necessarily-contiguous subsequence), return false.
  // (Of course, if a2 is empty (i.e., n2 is 0), return true.)
  // For example, if a1 is the 7 element array
  //    10 50 40 20 50 40 30
  // then the function should return true if a2 is
  //    50 20 30
  // or
  //    50 40 40
  // and it should return false if a2 is
  //    50 30 20
  // or
  //    10 20 20
bool includes(const double a1[], int n1, const double a2[], int n2)
{
    if (n2 <= 0)
        return true;
    if (n1 < n2)
        return false;

      // If we get here, a1 and a2 are nonempty
    if (a1[0] == a2[0])
        return includes(a1+1, n1-1, a2+1, n2-1);  // rest of a1, rest of a2
    else
        return includes(a1+1, n1-1, a2, n2);  // rest of a1, all of a2
}
Problem 3:
bool pathExists(string maze[], int nRows, int nCols, int sr, int sc, int er, int ec)
{
    if (sr == er  &&  sc == ec)
        return true;

    maze[sr][sc] = '@';  // anything non-'.' will do

    if (maze[sr-1][sc] == '.'  &&  pathExists(maze, nRows, nCols, sr-1, sc, er, ec))
        return true;
    if (maze[sr+1][sc] == '.'  &&  pathExists(maze, nRows, nCols, sr+1, sc, er, ec))
        return true;
    if (maze[sr][sc-1] == '.'  &&  pathExists(maze, nRows, nCols, sr, sc-1, er, ec))
        return true;
    if (maze[sr][sc+1] == '.'  &&  pathExists(maze, nRows, nCols, sr, sc+1, er, ec))
        return true;

    return false;
}
or

bool pathExists(string maze[], int nRows, int nCols, int sr, int sc, int er, int ec)
{
    if (maze[sr][sc] != '.')
        return false;

    if (sr == er  &&  sc == ec)
        return true;

    maze[sr][sc] = '@';  // anything non-'.' will do

    if (pathExists(maze, nRows, nCols, sr-1, sc, er, ec))
        return true;
    if (pathExists(maze, nRows, nCols, sr+1, sc, er, ec))
        return true;
    if (pathExists(maze, nRows, nCols, sr, sc-1, er, ec))
        return true;
    if (pathExists(maze, nRows, nCols, sr, sc+1, er, ec))
        return true;

    return false;
}
Problem 4:
  // Return the number of ways that all n2 elements of a2 appear
  // in the n1 element array a1 in the same order (though not
  // necessarily consecutively).  The empty sequence appears in a
  // sequence of length n1 in 1 way, even if n1 is 0.
  // For example, if a1 is the 7 element array
  //    10 50 40 20 50 40 30
  // then for this value of a2     the function must return
  //    10 20 40                        1
  //    10 40 30                        2
  //    20 10 40                        0
  //    50 40 30                        3
int countIncludes(const double a1[], int n1, const double a2[], int n2)
{
    if (n2 <= 0)
        return 1;
    if (n1 < n2)
        return 0;

      // If we get here, a1 and a2 are nonempty
    int t = countIncludes(a1+1, n1-1, a2, n2);  // rest of a1, all of a2
    if (a1[0] == a2[0])
        t += countIncludes(a1+1, n1-1, a2+1, n2-1);  // rest of a1, rest of a2
    return t;
}

  // Exchange two doubles
void exchange(double& x, double& y)
{
    double t = x;
    x = y;
    y = t;
}

  // Rearrange the elements of the array so that all the elements
  // whose value is > splitter come before all the other elements,
  // and all the elements whose value is < splitter come after all
  // the other elements.  Upon return, firstNotGreater is set to the
  // index of the first element in the rearranged array that is
  // <= splitter, or n if there is no such element, and firstLess is
  // set to the index of the first element that is < splitter, or n
  // if there is no such element.
  // In other words, upon return from the function, the array is a
  // permutation of its original value such that
  //   * for 0 <= i < firstNotGreater, a[i] > splitter
  //   * for firstNotGreater <= i < firstLess, a[i] == splitter
  //   * for firstLess <= i < n, a[i] < splitter
  // All the elements > splitter end up in no particular order.
  // All the elements < splitter end up in no particular order.
void split(double a[], int n, double splitter,
                                    int& firstNotGreater, int& firstLess)
{
    if (n < 0)
        n = 0;

      // It will always be the case that just before evaluating the loop
      // condition:
      //  firstNotGreater <= firstUnknown and firstUnknown <= firstLess
      //  Every element earlier than position firstNotGreater is > splitter
      //  Every element from position firstNotGreater to firstUnknown-1 is
      //    == splitter
      //  Every element from firstUnknown to firstLess-1 is not known yet
      //  Every element at position firstLess or later is < splitter

    firstNotGreater = 0;
    firstLess = n;
    int firstUnknown = 0;
    while (firstUnknown < firstLess)
    {
        if (a[firstUnknown] < splitter)
        {
            firstLess--;
            exchange(a[firstUnknown], a[firstLess]);
        }
        else
        {
            if (a[firstUnknown] > splitter)
            {
                exchange(a[firstNotGreater], a[firstUnknown]);
                firstNotGreater++;
            }
            firstUnknown++;
        }
    }
}

  // Rearrange the elements of the array so that
  // a[0] >= a[1] >= a[2] >= ... >= a[n-2] >= a[n-1]
  // If n <= 1, do nothing.
void order(double a[], int n)
{
    if (n <= 1)
        return;

      // Split using a[0] as the splitter (any element would do).
    int firstNotGreater;
    int firstLess;
    split(a, n, a[0], firstNotGreater, firstLess);

      // sort the elements > splitter
    order(a, firstNotGreater);

      // sort the elements < splitter
    order(a+firstLess, n-firstLess);
}
