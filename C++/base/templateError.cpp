# include <iostream>
using namespace std;

extern double foo( double );

extern double foo(double t){
    cout << "extern foo" <<endl;
}

template < class type >
class ScopeRules{
public:
    void invariant() {
        _member = foo( _val );
    }
    type type_dependent() {
        return foo( _member );
    }
private:
    int _val;
    type _member;
};

// 第二种情况 scope of the template instantiation
int main(){
    extern int foo( int );
    ScopeRules< int > sr0;
    sr0.invariant();
    sr0.type_dependent();

    return 0;
}
