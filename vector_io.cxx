#include <vector>
#include <iostream>
#include <sstream>
#include <cstring>
#include <string>

#include "stdint.h"

using namespace std;

template <typename T>  
void string_to_vector_2d(string s, T (*convert)(const char*), vector< vector<T> > &v) { 
    v.clear();

    uint32_t begin = 1;
    uint32_t v_start = 0, v_end = 0;

    while (v_start != string::npos) {
        v_start = s.find('[', begin);
        v_end = s.find(']', v_start);

        cout << "v_start: " << v_start << ", v_end: " << v_end << endl;

        vector<T> current;
        string_to_vector(s.substr(v_start, v_end - v_start), convert, current);

        v.push_back(current);
        cout << "pushed vector: " << vector_to_string( *(v.end()) );
    }
}

template <typename T>
string vector_2d_to_string(const vector< vector<T> > &v) {
    ostringstream oss;
    
    oss << "[ ";
    for (uint32_t i = 0; i < v.size(); i++) {
        if (i > 0) oss << ", ";
        oss << vector_to_string(v[i]);
    }
    oss << "]";

    return oss.str();
}


template <typename T>  
void string_to_vector(string s, T (*convert)(const char*), vector<T> &v) { 
    v.clear();

    const char *cstr = s.c_str();
    char *pch = strtok((char*)cstr, "[], ");
    while (pch != NULL) {
        //cout << "element: " << pch << endl;
        v.push_back( (*convert)(pch) );

        pch = strtok(NULL, "[], ");
    }   
}

template <typename T>
string vector_to_string(const vector<T> &v) {
    ostringstream oss;

    oss.precision(15);
    oss << "[";
    for (unsigned int i = 0; i < v.size(); i++) {
        if (i > 0) oss << ", ";
        oss << v[i];
    }   
    oss << "]";

    return oss.str();
}

template <typename T>
string vector_to_string(const vector<T> *v) {
    return vector_to_string(*v);
}

template
string vector_to_string(const vector<double> *v);

template
string vector_to_string(const vector<double> &v);

template
void string_to_vector(string s, double (*convert)(const char*), vector<double> &v);
