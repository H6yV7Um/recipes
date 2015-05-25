#include <iostream>
using namespace std;

class CComplexObject // a demo class
{
        public:
                void clone() { cout << "in clone" << endl; }
};



template <typename T>
class Traits<true>
{
        public:
                void clone(T* pObj)
                {
                        cout << "before cloning Clonable type" << endl;
                        pObj->clone();
                        cout << "after cloning Clonable type" << endl;
                }
};

template <typename T>
class Traits<false>
{
        public:
                void clone(T* pObj)
                {
                        cout << "cloning non Clonable type" << endl;
                }
};




template <typename T, bool isClonable>
class XContainer
{
        public:
                enum {Clonable = isClonable};

                void clone(T* pObj)
                {
                        Traits<isClonable>().clone(pObj);
                }

};

void main()
{
        int* p1 = 0;
        CComplexObject* p2 = 0;

        XContainer<int, false> n1;
        XContainer<CComplexObject, true> n2;

        n1.clone(p1);
        n2.clone(p2);
}
