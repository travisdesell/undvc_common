#ifndef UNDVC_COMMON_FILE_IO_H
#define UNDVC_COMMON_FILE_IO_H

#include <cstdlib>
#include <iostream>
#include <string>

using namespace std;

string get_file_as_string(string file_path) throw (int);

#ifdef _BOINC_
void copy_file_to_download_dir(string filename);
#endif

#endif
