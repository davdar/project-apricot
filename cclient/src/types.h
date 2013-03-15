/*
	types.h

	Defines generalizations for certain types

*/

#ifndef TYPES_H
#define TYPES_H

#include <boost/shared_ptr.hpp>
#include <boost/static_assert.hpp>

//Types used by Matrix and Vector classes, (possibly others)
typedef double Real;
typedef unsigned int uint;

//Map boost names to common names, so we don't have boost-specific names
// strewn throughout our code
using boost::shared_ptr;
using boost::static_pointer_cast;
#define STATIC_ASSERT BOOST_STATIC_ASSERT

#endif

