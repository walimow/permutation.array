#ifndef __ARRAY_PERMUTAION__HPP__
#define __ARRAY_PERMUTAION__HPP__  1

#include "array_util.hpp"

namespace arutl{
    
        ///////////////////////////
    
	template< int i >
	class FACTOR {
	public:
		enum { value = i * FACTOR<i - 1>::value };
	};

	template<>
	class FACTOR< 1 > {
	public:
		enum { value = 1 };
	};

	/////////////////////////////

	//ht-construct
	template <typename Ty, unsigned long L, unsigned long R = L+1>
	array<Ty, R> constr(const Ty& h, const array<Ty, L>& t) {
		return _u_array<Ty,L>{ h,t }._array;
	}


	template <typename Ty, unsigned long L, unsigned long R = FACTOR<L>::value>
	array<Ty, R>		constr(const Ty& h, const array<const array<Ty, L>, R>& t) {
		array<Ty, R> res;
		for (unsigned int k; k< R; k++)
			res[k]= _u_array<Ty,L>{ h,t[k] }._array;
		return res;
	}

	/////////////////////////////
	template <typename Ty, unsigned long L, unsigned long R= FACTOR<L>::value>
	constexpr array<array<Ty, L>, R >permutate(const array<Ty, L>& aa);   //declaration

	template <typename Ty>
	constexpr array<array<Ty, 2>, 2 >permutate(const array<Ty, 2>& aa) {
		return  array<array<Ty, 2>, 2 > { 
			array<Ty, 2>{aa[0], aa[1]},
			array<Ty, 2>{ aa[1], aa[0] }
		};
	}

	template <typename Ty>
	constexpr array<array<Ty, 1>, 1 >permutate(const array<Ty, 1>& aa) {
		return { { aa[0]  } };
	}

	template <typename Ty>
	constexpr array<array<Ty, 0>, 0 >permutate(const array<Ty, 0>& aa) {
		return { {  } };
	}



	template <typename Ty, unsigned long L, unsigned long R >
	constexpr array<array<Ty, L>, R >permutate(const array<Ty, L>& aa) {
		array<array<Ty, L>, R > res;
		unsigned int pos = 0;
		for (unsigned int k = 0; k < L; k++ ) {  //f?r jede position
			auto hts =   arest_pos(aa,k);  //h: rest		
//			auto parts1 = permutate(hts.second);  //rest permutieren
				for (const auto& e : permutate(hts.second /*parts1*/)) {    //alle Restpermutaionen
					res[pos++] = constr(hts.first, e);   //Kopf + permutierter Reste an den  einf?gen
				}
		}
		return    std::move(res);
	}
	
}



#endif
