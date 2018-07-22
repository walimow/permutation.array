#include <array>
#include <vector>

#include <iostream>
#include <cassert>

#include "array_util.hpp"
#include "array_trace.hpp"

#include "permutat.hpp"
#include "array_permutation.hpp"



//using std::vector;
using std::pair;
using std::cout;


array<int, 3>  getf3() {
    return  array<int, 3> {1, 2, 3};
}

void test_arrays() {
    cout << "\n---------------a(1,2,3,4)------------------------\n";
    std::array<int, 3> a3 { 1,2,3 };

    auto a4 = arutl::append(a3, 4);
    arutl::trace_array(a4);
    cout << "\n---------------------------------------\n";
    std::array<int, 3> a2 { 4, 5,6 };

    auto a6 = arutl::append(a3, a2);
    arutl::trace_array(a6);
    cout << "\n--------------a(1,2,3,4,5,6)-------------------------\n";

    auto a5 = arutl::arest(a6, 4);
    arutl::trace_array(a5);
    cout << "\n--------------anon array:(1,2,3,4,6)-------------------------\n";

    arutl::trace_array(arutl::arest(array<int, 6> {1, 2, 3, 4, 5, 6}, 4));
    cout << "\n--------------f3:(1,2,3,4,6)-------------------------\n";
    arutl::trace_array(getf3());
    cout << "\n--------------ht-------------------------\n";

    arutl::trace_array_pos(a3);

    auto xr = arutl::ht(a3);
    {
        cout << "\n--------------ht(1:23)-------------------------\n" << xr.first << '\t';

        arutl::trace_array(xr.second);
        arutl::trace_array_pos(xr.second);
        auto xxr = arutl::ht(xr.second);
        cout << "\n--------------ht(2:3)-------------------------\n" << xxr.first << '\t';
        arutl::trace_array(xxr.second);
        arutl::trace_array_pos(xxr.second);
    }
    //  std::array<int, 3> a3{ 1,2,3 };
    {
        cout << "\n--------------trf(1:23)->(2:3)?-------------------------\n" << xr.first << '\t';

        arutl::trace_array_pos(a3);
        const auto & r2 = arutl::tailref(a3);
        arutl::trace_array_pos(r2);
    }


    {
        std::array<int, 3> a3 { 1,2,3 };

        cout << "\n--------------htr(1:23)-------------------------\n" << xr.first << '\t';
        arutl::trace_array(a3);

        const auto& xr = arutl::htref(a3);

        //arutl::trace_array(xr.second);
//			arutl::trace_array_pos(xr.second);
        auto xxr = arutl::htref(xr._tail);
        cout << "\n--------------htr(2:3)-------------------------\n" << xxr._head<< '\t';
        //		arutl::trace_array(xxr.second);
        arutl::trace_array_pos(xxr._tail);
        auto t1 = xr._head;
        cout << "\n--------------extra-------------------------\n" << t1 << '\t';
    }
    {
        cout << "\n------------a2cra/trace----------------------\n" ;
        std::array<int, 3> a3 { 1,2,3 };
        auto ap3 = arutl::a2cra(a3);
        arutl::trace_array_pos(a3) ;
        arutl::trace_array_pos(ap3) ;
        cout << "\n----------------------------------\n";

    }

    {
        cout << "\n------------a:arr----------------------\n" ;

        std::array<int, 3> a3 { 1,2,3 };

        auto aa =  arutl::append(0, a3);
        arutl::trace_array_pos(aa) ;
        //arutl::trace_array_pos(ap3) ;
        cout << "\n----------------------------------\n";

    }

    {
        arutl::_u_array<int,2> ua1 {1, {2,3}};

        ///    arutl::_u_array<int,2> ua2{{1, 2},3}};


    }
    {
     //   arutl::_u_array<int,2> ua1 { {1, 2},3};
        cout << "\n-----------init/last (1,2,3)-----------------------\n";
        auto res =  arutl::init_last(a6,3) ;
        arutl::trace_array(res);
        cout << "\n----------------------------------\n";

    }

    {

        array<int, 5> a5 = {1,2,3,4,5};
        arutl::trace_array(a5);
        ///test FACT
        cout<<"----\n";

        auto p5 = arutl::permutate(a5);
        for (const auto& e: p5)
            arutl::trace_array(e);

    }
    /**/

}

int main()
{
    /*
    vector<int>  vTest{1,2,3, 4, 5};
    trace_vector(vTest);

    auto r2= depart0(vTest, 1);
    cout << r2.first<<":\t";
    trace_vector(r2.second);

    //auto rr2 = depart(vTest);
    cout << "\n---------------------------------------\n";
    trace_rpair(rr2);
    cout << "\n-------------------2--------------------\n";

    //	auto rr3 = reperm(vTest);
    //	trace_vector2(rr3);
    */

    /*
    	cout << "\n------------------3---------------------\n";

    	auto rr4 = parts(vTest);
    	trace_vector2(rr4);
    	cout << "\n------------------5---------------------\n";
    	*/

    test_arrays();

    return 0;
}

