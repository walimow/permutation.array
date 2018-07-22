#pragma once

#include <array>
#include <iostream>

using std::array;
using std::cout;
using std::pair;

namespace arutl{
  	
    
    /// array<Ty,N> -> array<const Ty*,N> 
        template <typename Ty, unsigned long Len>
	constexpr  array<const Ty*,Len> a2cra(const array<Ty,Len>&arr){
            array<const Ty*,Len>  ret;
            for (unsigned long i=0; i< Len; i++)
                ret[i]=& (arr[i]);
               return    std::move(ret);
                //ret;
        }
    /// copy array in left
	template <typename Ty, unsigned long LenL, unsigned long LenR>
	constexpr unsigned int  ar_cpy(array<Ty, LenL>&left, const array<Ty, LenR>& right) {
		unsigned int k = 0;
		for (; k < LenL && k < LenR; k++)
			left[k] = right[k];
		return k;
	}

    /// appends element  aa+b ->aab
	template <typename Ty, unsigned long Len, unsigned long Z=Len+1>
	constexpr array<Ty, Z> append( const array<Ty, Len>& arr, const Ty& a) {
		array<Ty, Z> res;// { arr };
		ar_cpy(res,arr);
		res[Z-1] = a;
		return std::move(res);
	}
	
    /// appends element  a+bb ->abb	
  	template <typename Ty, unsigned long Len, unsigned long Z=Len+1>
	constexpr array<Ty, Z> append( const Ty& a, const array<Ty, Len>& arr) {
		array<Ty, Z> res;// { arr };
                res[0]=a;
       		ar_cpy( (array<Ty, Len>&) res[1] , arr);		
		return std::move(res);
	}
  

    /// appends array (concat)
	template <typename Ty, unsigned long Len, unsigned long LenR,  unsigned long Z = Len + LenR>
	constexpr array<Ty, Z> append(const array<Ty, Len>& arr, const array<Ty,LenR>& r) {
		array<Ty, Z> res;// { arr };
		unsigned int k = ar_cpy(res, arr); 
		for (; k < Z; k++)
			res[k] = r[k-Len];	
		return std::move(res);
	}
	

	

    /// returns array without position pos
	template <typename Ty, unsigned long Len, unsigned long Z = Len - 1>
	constexpr array<Ty, Z> arest(const array<Ty, Len>& arr, unsigned int pos) {
		assert(pos<Len);
		array<Ty, Z> res;
		unsigned int k = 0;
		for (; k < pos; k++)
			res[k] = arr[k];		
		for (; k < Z; k++)
			res[k] = arr[k + 1];
		return std::move(res);
	}


    /// returns pair <*pos,array without position pos>
	template <typename Ty, unsigned long Len, unsigned long Z = Len - 1>
	constexpr pair<Ty, array<Ty, Z>> arest_pos(const array<Ty, Len>& arr, unsigned int pos) {
		return make_pair(arr[pos], arest(arr, pos));
	}

    /// returns the rest after the first pos (head) as copy
	template <typename Ty, unsigned long Len, unsigned long Z = Len - 1>
	 array<Ty, Z> tail(const array<Ty, Len>& arr) {
		static_assert(Len>0, "head:tail is forbidden on array with size 0");
		return (array<Ty, Z>)&(arr[1]);
	}
    
    /// returns head/tail(copy) as pair
	template <typename Ty, unsigned long Len, unsigned long Z = Len - 1>
	constexpr pair<Ty, array<Ty, Z>> ht(const array<Ty, Len>& arr) {
		static_assert(Len>0,"head:tail is forbidden on array with size 0");
		return make_pair(arr[0],   arest(arr, 0) );
	}

	
    /// helper union for head/tail os (ATT: standardlist-initialing  for init:Last seems impossible)
       template<typename Ty, unsigned long PartLen, unsigned long TotalLen = PartLen+1>
       union _U_array{
             struct {
                    Ty  first;
                    array<Ty, PartLen> second;
                           } _head_tail;
             struct {                  
                    array<Ty, PartLen> first;
                    Ty second;
             }            _init_last;
            array<Ty,  TotalLen>    _array;
       };
 

       template<typename Ty, unsigned long Len>
       using _u_array = _U_array<Ty, Len>;
       

        
        template<typename Ty, unsigned long PartLen, unsigned long TotalLen = PartLen + 1>
	union _U_init_last {
		struct {
			array<Ty, PartLen> first;
			Ty second;
		}		_init_last;
		array<Ty, TotalLen>	  _array;		
	};
	
	template<typename Ty, unsigned long Len>
	using _uil = _U_init_last<Ty, Len>;
        
	template<typename Ty, unsigned long Len, unsigned long Z = Len + 1>
	array<Ty,Z>   init_last(const array<Ty, Len >& init, const  Ty& last) {
		_uil<Ty, Len> res{ init };
		res._init_last.second = last;
		return std::move(res._array);
	}

/// returns reference to tail (the shortened array)
       template <typename Ty, unsigned long Len, unsigned long Z = Len - 1>
	constexpr const array< Ty, Z>& tailref(const array<Ty, Len>& arr) {
		static_assert(Len>0, "head:tail is forbidden on array with size 0");
		return (
                    const array< Ty, Z>&) (     arr[1]  );
	}


	template <typename Ty, unsigned long Len>
	struct _HT_ref {
		const Ty&				_head;
		const array< Ty,Len>&	_tail;
	};
        
        template <typename Ty, unsigned long Len>
	struct _HT {
		Ty		_head;
		array< Ty,Len>&	_tail;
	};
        
        template <typename Ty, unsigned long Len, unsigned long Z=Len+1>
	struct _HTU {
            union _u {
                _HT<Ty, Len>     _ht;
                array<Ty, Z>    _full;
            }; 
        };
        

	///pair (of refs) dont work
	template <typename Ty, unsigned long Len, unsigned long Z = Len - 1>
	constexpr 		
		_HT_ref<Ty,Z>
			htref(const array<Ty, Len>& arr) {
		static_assert(Len>0, "head:tail is forbidden on array with size 0");
		return  _HT_ref<Ty, Z>{ (const Ty&)arr[0], tailref(arr) };
	}


	/*
		template<typename Ty>
	vector<pair<Ty, vector<Ty>>>  depart(const vector<Ty>& v) {
		vector<pair<Ty, vector<Ty>>> res;
		for (unsigned int i = 0; i < v.size(); i++) {
			res.push_back(			
				depart0(v, i)
				);
		}
		return res;
	}
	*/

	/*
	template<typename Ty, int Len, int Z=Len-1>
	constexpr array < pair< Ty, array <Ty, Z>>, Len  > depart(const array<Ty, Len>& arr) {

	}
	*/
        
        
        

	template <typename Ty, unsigned long Len>
	using cref_array = array<const Ty&, Len>;
        
        

        //aaa-> [*a:aa]
	template<typename Ty, unsigned long Len, unsigned long Z = Len - 1>
	constexpr array < 	_HT_ref<Ty, Z>, Len>      depart0(const array<Ty, Len>& arr) {
		array < _HT<Ty, Z>, Len>  res;
		for (unsigned int i =0; i< Len; i++){
                        res[i] = _HT<Ty, Len>{arr[i], arest(arr, i) };
                }                
		return res;
	}



}
