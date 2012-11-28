#ifndef _LIST_H_
#define _LIST_H_

#include <algorithm>
#include <cstring>
#include <vector>

template<class T>
inline int IndexOf( const std::vector<T> &v, const T &o )
{
	using namespace std;

	vector<T>::const_iterator i = find( v.begin(), v.end(), o );
	return i - v.begin();
}

template<class T>
inline void AddRange( std::vector<T> &dst, const std::vector<T> &src )
{
	using namespace std;
	vector<T>::const_iterator i;
	for( i = src.begin(); i != src.end(); ++i )
		dst.push_back( *i );
}

template<class T>
inline void Remove( std::vector<T> &v, const T &o )
{
	using namespace std;
	vector<T>::iterator i = std::remove( v.begin(), v.end(), o );
	v.erase( i, v.end() );
}

#endif
