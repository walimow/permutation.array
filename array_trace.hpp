
#ifndef __ARRAY_UTIL_TRACE_HPP__
#define __ARRAY_UTIL_TRACE_HPP__  1

#include <array>
#include <iostream>

using std::array;
using std::cout;


namespace arutl{
    
    
    template <typename Ty, unsigned long Len>
	void trace_array(const array<Ty, Len>& arr) {

		for (const auto&e : arr) 
			cout << e<< ',';	
		cout << std::endl;
	}

	template <typename Ty, unsigned long Len>
	void trace_array_pos(const array<Ty, Len>& arr) {
				
		for (const auto&e : arr)

			cout << std::dec << e << " (" << std::hex << &e << "), " << std::dec;
		cout << std::endl;
	}
	
	template <typename Ty, unsigned long Len>
	void trace_array_pos(const array<const Ty*, Len>& arr) {
		
            for (unsigned int i =0; i< Len ;
                 i++){
                                const Ty*e = arr[i];
		//for (const Ty *e : arr){

                        if (e!= nullptr){
                            cout << std::dec << 
                            (const Ty) *
                            e 
                            << 
                            " (" << std::hex << e << "), " << std::dec;
                        }
                        else    
                            cout << " null! ";
                }
		cout << std::endl;
	}

}



#endif
