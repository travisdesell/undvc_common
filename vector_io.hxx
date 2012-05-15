#ifndef TAO_UTIL_H
#define TAO_UTIL_H

#include <vector>
#include <iostream>
#include <sstream>
#include <cstring>

using namespace std;

template <typename T>  
vector<T>* string_to_vector(string s, T (*convert)(const char*) );

template <typename T>
string vector_to_string(const vector<T> *v);

template <typename T>
string vector_to_string(const vector<T> &v);

#endif
