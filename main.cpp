#include <cmath>
#include <iostream>
#include <unordered_set>
#include <iomanip>
#include <vector>

using namespace std;

const double pi = 2 * acos(0.0);
typedef long double mytype;

mytype f1(mytype A, mytype x) {
    return A * x * (1 - x);
}

mytype f2(mytype A, mytype x) {
    return A / (4 * sin(pi * x));
}
void print_set(std::unordered_set<mytype> const &s)
{
    for (auto it = s.cbegin(); it != s.cend(); it++) {
        cout << setprecision(10) << *it << ' ';

    }
}

/* The function calculates the length of the cycle for a given parameter a of function "f(y)"
 * it goes through "st_it" iterations f(...f(f(y))) in order to stabilize the value
 * it puts (with precision prec) the results for the successive iterations into the set "my_set"
 * it - the number of iterations while inserting into the set (must be larger than the searched for length of the cycle)
 * Returns the number of elements of the set, which is also the length of the cycle
 */
int cycle_length(mytype (*fun)(mytype, mytype), mytype a, mytype y, int it, int st_it = 5 * 1e6, float prec = 1e8) {
    int i = 0;
    mytype x = y;
    do {
        x = fun(a, x);
        i++;
    } while (i < st_it); // if st_it greater, calculates more exactly but much slower

    unordered_set<mytype> my_set;
    for(int j = 0; j < it; j++) {
        x = fun(a, x);
        my_set.insert((mytype)(round(prec * x)) / prec);
    }

//    cout << "printset: ";
//    print_set(my_set);
//    cout << endl;

    return my_set.size();
}


/* The function does a binsearch for the smallest "a" for which the cycle has length "c_length"
 * l - the left end of the search range
 * r - the right end of the search range
 * x - the argument of the function parametrized by a
 * returns the found a*/
mytype binsearch_bifurc_param(mytype (*f) (mytype, mytype), mytype l, mytype r, mytype x, int c_length) {
    int i = 0;
    int current_len = 0;
    mytype mid = 0;
    mytype smallest_param = r;

    do {
        mid = 0.5 * (l + r);
        current_len = cycle_length(f, mid, x, c_length * 5);
        //cout << "mid to: " << mid << ", l to: " << l << ", r to: " << r << ", current_len to: " << current_len << endl;
        if (current_len >= c_length) {
            if (current_len == c_length && smallest_param > mid) smallest_param = mid;
            r = mid;
        }
        else
            l = mid;
        i++;
    } while(l < r && i < 100);

    if (current_len == c_length) return mid;
    else return smallest_param;
}

int main() {
    mytype x = 0.5;// 0<x<1
    mytype a_param = 0.;
    mytype ratio = 0.;//the approximated Feigenbaum constant
    int max_cycle_len = 64;// ratio doesn't work if this parameter too big

    vector<mytype> p_bifurk; //contains the bifurcation parameters for successive lengths of cycle: 2, 4, 8, ... , max_cycle_len;
    vector<mytype> feigenbaum; //contains the successive approximations of the Feigenbaum constant

    for(int i = 2; i <= max_cycle_len; i *= 2) {
        a_param = binsearch_bifurc_param(f1, 0., 4., x, i); // change here to calculate for f1 or f2
        cout << setprecision(6) << "the bifurcation parameter for a cycle of length a = " << i << ": " << a_param << endl;
        p_bifurk.push_back(a_param);
    }

    for(int j = 2; j < log2(max_cycle_len); j++) {
        ratio = (p_bifurk.at(j-1) - p_bifurk.at(j-2))/(p_bifurk.at(j) - p_bifurk.at(j-1));
        feigenbaum.push_back(ratio);
        //cout << "The approximated Feigenbaum constant: " << ratio << endl;
    }
    cout << "The approximated Feigenbaum constant: " << feigenbaum.back() << endl;

    return 0;
}