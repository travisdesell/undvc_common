#include <cstdlib>
#include <iostream>
#include <sstream>
#include <fstream>
#include <string>

#include "stdint.h"

#include "file_io.hxx"

#ifdef HAS_BOOST
#include <boost/filesystem.hpp>
#endif

#ifdef _BOINC_

#include "boinc_db.h"
#include "error_numbers.h"
#include "backend_lib.h"
#include "parse.h"
#include "util.h"

#endif


using namespace std;

string get_file_as_string(string file_path) throw (int) {
    //read the entire contents of the file into a string
    ifstream sites_file(file_path.c_str());

    if (!sites_file.is_open()) {
        throw 1;
    }

    string fc;

    sites_file.seekg(0, ios::end);   
    fc.reserve(sites_file.tellg());
    sites_file.seekg(0, ios::beg);

    fc.assign((istreambuf_iterator<char>(sites_file)), istreambuf_iterator<char>());

    ostringstream oss;
    for (uint32_t i = 0; i < fc.size(); i++) {
        if (fc[i] != '\r') oss << fc[i];
    }

    return oss.str();
}

#ifdef _BOINC_
#ifdef HAS_BOOST
void copy_file_to_download_dir(string filename) {
    char path[256];

    string short_name = filename.substr(filename.find_last_of('/') + 1);

    if ( !boost::filesystem::exists( filename ) ) { 
        log_messages.printf(MSG_CRITICAL, "input filename '%s' does not exist, cannot copy to download directory.\n", filename.c_str());
        exit(1);
    }   

    int retval = config.download_path( short_name.c_str(), path );
    if (retval) {
        log_messages.printf(MSG_CRITICAL, "can't get download path for file '%s', error: %s\n", short_name.c_str(), boincerror(retval));
        exit(1);
    }   

    if ( boost::filesystem::exists(path) ) { 
        log_messages.printf(MSG_CRITICAL, "\033[1minput file '%s' already exists in download directory hierarchy as '%s', not copying.\033[0m\n", short_name.c_str(), path);
    } else {
        log_messages.printf(MSG_CRITICAL, "input file '%s' does not exist in downlaod directory hierarchy, copying to '%s'\n", short_name.c_str(), path);

        //open the first filename and copy it to the target here
        std::ifstream src(filename.c_str());
        if (!src.is_open()) {
            log_messages.printf(MSG_CRITICAL, "could not open file for reading '%s', error: %s\n", path, boincerror(ERR_FOPEN));
            exit(1);
        }   

        std::ofstream dst(path);
        if (!dst.is_open()) {
            log_messages.printf(MSG_CRITICAL, "could not open file for writing '%s', error: %s\n", path, boincerror(ERR_FOPEN));
            exit(1);
        }   

        dst << src.rdbuf();

        src.close();
        dst.close();
    }   
}
#endif
#endif
