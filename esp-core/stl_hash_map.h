#ifndef __STL_HASH_MAP_H__
#define __STL_HASH_MAP_H__

#ifdef __GNUC__
	#include <ext/hash_map> //using GCC STL
	#define STL_HASH_MAP(key,val) __gnu_cxx::hash_map<key,val,stl_hash_string>

class stl_hash_string
{
public:
	size_t operator() (const std::string& s) const
	{
		return __gnu_cxx::__stl_hash_string(s.c_str());
	}
};

#else
	#include <hash_map> //using local SGI STL
	#define STL_HASH_MAP(key,val) std::hash_map<key,val>
#endif

#endif //__STL_HASH_MAP_H__
