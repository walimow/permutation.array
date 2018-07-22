#ifndef __PERMUTION_STATIC_HPP___
#define __PERMUTION_STATIC_HPP___  1

using std::vector;
using std::pair;
using std::cout;

using std::array;


///permutate (dirty, unorganized vector implementation)

	template<typename Ty>
	vector<vector<Ty>>  tovv(const Ty& a) {
		vector<vector<Ty>> res{ {a} };
		return res;
	}

	template<typename Ty>
	vector<vector<Ty>>  tovv(const Ty& a, const vector<Ty>&v) {
		vector<Ty> vres{ a };		
		for (const auto& e : v)
			vres.push_back(e);
		return vector<vector<Ty>>{vres};
	}

	template<typename Ty>
	vector<vector<Ty>>  tovv(const Ty& a, const Ty& b) {
		vector<vector<Ty>> vres{ {a,b} /*,{b,a}*/ };
		return std::move(vres);
	}

	template<typename Ty>
	vector<vector<Ty>>  tovv(const Ty& a, const vector<vector<Ty>>&vv) {
		vector<vector<Ty>> vres;
		for (const auto& v : vv) {
			vector<Ty> rv{a};
			for (const auto& e : v) {
				rv.push_back(e);
			}
			vres.push_back(std::move(rv));
		}
		return vres;
	}
	
	template<typename Ty>
	void	trace_vector(const vector<Ty> &v){
		for (const auto& e : v) {
			cout << e << '\t';
		}
		cout << std::endl;
    }

	template<typename Ty>
	void	trace_evector(const pair<Ty,vector<Ty>> &v) {
		cout << v.first << " :\t";
		for (const auto& e : v.second) {
			cout << e << '\t';
		}
		cout << std::endl;
	}

	template<typename Ty>
	void	trace_vector2(const vector< vector<Ty> > &v) {
		for (const auto& e : v) {
			trace_vector(e);
			cout << '\n';
		}
	}

	template<typename Ty>
	void	trace_rpair(vector<pair<Ty, vector<Ty>>> &vv) {
		
		for (const auto& e : vv) {
			cout << e.first << " : ";
			trace_vector(e.second);
			cout <<  '\n';
		}
	}
	
	
	/////testweise
//#include <set>
	template <typename Ty>
		bool test_contains(vector<vector<Ty>> &dest, const  vector<Ty> & e) {
			for (unsigned int x = 0; x < dest.size(); x++)
				if (dest[x] == e)
					return true;
			return false;			
		}


	
	///gibt es das schon?
	template<typename Ty>
	const vector<vector<Ty>>& vvr2l( vector<vector<Ty>> &dest,  vector<vector<Ty>> &&vv) {
		for (const auto& v : vv) {
			//bool btest = test_contains(dest,v);		
			dest.push_back(move(v));
		}
		return dest;
	}

	///pos(x) : allesonst
	template<typename Ty>
	pair<Ty,vector<Ty> >		depart0(const vector<Ty> &v , unsigned int pos) {
		assert(v.size());
		assert(pos < v.size());
		vector<Ty> res;		
		for (unsigned int i = 0; i < pos; i++)
			res.push_back( v[i]);
		for (unsigned int i = pos+1; i < v.size(); i++)
			res.push_back(v[i]);
		return  make_pair(v[pos], res);
	}

	///alle (x) : allesonst 
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

	template<typename Ty>
	vector<vector<Ty>>  permutate(const vector<Ty>& v) {
		vector< vector<Ty>> res;

		for (const auto& evv : depart(v))
		{
			switch (evv.second.size()) {
			case 0:
				break;
			case 1:
			{
				vvr2l(		res,		tovv(evv.first, evv.second[0])				);
			}
			default:
				vvr2l(res, tovv(evv.first, permutate(evv.second)));
			}
		}
		return res;
	}




#endif
