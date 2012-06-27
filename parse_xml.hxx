#ifndef FGDO_UTIL_HPP
#define FGDO_UTIL_HPP

#include <iostream>
#include <string>
#include <vector>

#include "stdint.h"

#include "vector_io.hxx"

using namespace std;

template <class T>
T parse_xml(string xml, const char tag[]) throw (string);

template <>
double parse_xml<double> (string xml, const char tag[]) throw (string);

template <>
string parse_xml<string>(string xml, const char tag[]) throw (string);

template <class T>
void parse_xml_vector(string xml, const char tag[], vector<T> &result) throw (string);

#endif
