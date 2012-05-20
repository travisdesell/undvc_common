#include <cstdlib>
#include <iostream>
#include <string>

#include "file_io.hxx"

string get_file_as_string(string file_path) throw (int) {
    //read the entire contents of the file into a string
    ifstream sites_file(file_path.c_str());

    if (!sites_file.is_open()) {
        throw 1;
    }

    std::string fc;

    sites_file.seekg(0, std::ios::end);   
    fc.reserve(sites_file.tellg());
    sites_file.seekg(0, std::ios::beg);

    fc.assign((std::istreambuf_iterator<char>(sites_file)), std::istreambuf_iterator<char>());

//   std::remove( failed_sets.begin(), failed_sets.end(), '\r' );
    while (target < failed_sets.size()) {
        while (failed_sets[target] == '\r') {
            target++;
        }

        if (failed_sets[target] == '\n') {
            failed_sets[current] = ' ';
        } else {
            failed_sets[current] = failed_sets[target];
        }

        current++;
        target++;
    }
    failed_sets.resize(current);

    cout << "FAILED SETS WAS: '" << failed_sets << "'" << endl;

    while (failed_sets[0] == ' ') failed_sets.erase(0, 1);
    while (failed_sets[ failed_sets.size() - 1 ] == ' ') failed_sets.erase( failed_sets.size() - 1, 1);

    cout << "FAILED SETS  IS: '" << failed_sets << "'" << endl;


    return fc;
}


