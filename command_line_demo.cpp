//------------------------------------------------------------------------------
// command_line_demo.cpp
// 
//  - command line argument demo
//  - string manipulation with folder paths, file names
//  - text file to stringstream 
// 
// Author: https://www.learncpp.com/cpp-tutorial/command-line-arguments/
// Modified by: Prof. Linda C
//------------------------------------------------------------------------------

#include <fstream>
#include <iostream>
#include <sstream>

//------------------------------------------------------------------------------
// using symbols
//------------------------------------------------------------------------------
using std::cout;
using std::ifstream;
using std::istreambuf_iterator;
using std::string;
using std::stringstream;

//------------------------------------------------------------------------------
// constants
//------------------------------------------------------------------------------
constexpr int FILE_OK = 0;
constexpr int FILE_ERROR = -1;

//------------------------------------------------------------------------------
// local function prototypes
//------------------------------------------------------------------------------
string getFilename(char*);
void displayIntArg1(int, char*, string&);
string makeCpp(const string&);
int displayCpp(const string&);

//------------------------------------------------------------------------------
// entry point
//------------------------------------------------------------------------------
int main(int argc, char* argv[]) {

    cout << "\nCommand line argument count: " << argc << "\n\n";

    // Loop through each argument and print its number and value
    for (int count { 0 }; count < argc; ++count) {
        cout << "arg " << count << ": " << argv[count] << "\n";
    }
    cout << '\n';

    // put our executable (.exe ) file name in a C++ string
    string filename = getFilename(argv[0]);

    // display integer argument at *(argv[1]), or usage help
    displayIntArg1(argc, argv[1], filename);

    //-----------------------------------------------------------------------------
    // display the C++ source code in the .cpp file for this program
    // >>> the .cpp file and the .exe must be in the same folder <<<
    //-----------------------------------------------------------------------------
    return displayCpp(makeCpp(filename));
}

//------------------------------------------------------------------------------
// - splits argv[0] char buffer into path and file name
// - returns file name
//------------------------------------------------------------------------------
string getFilename(char* pArgv0) {

    // use hard-coded file name on empty parameter (null pointer)
    if (!pArgv0) {
        return "command_line_demo.exe";
    }

    // convert char buffer to C++ string and use string functions
    string str = pArgv0;

    // Windows uses \ in folder paths, Linux and macOS use /
#ifdef _WIN32
    string divider = "/\\";
#else
    string divider = "/";
#endif

    // find last folder name divider before file name
    size_t found = str.find_last_of(divider);

    // substring before last divider is the folder path
    string path = str.substr(0, found);
    cout << "\tpath: " << path << '\n';

    // substring after last divider is the file name
    string fname = str.substr(found + 1);
    cout << "\tfile name with suffix: " << fname << '\n';

    // return a copy of local variable fname
    return fname;
}

//-----------------------------------------------------------------------------
// display integer at *pArg1, or display usage help
//-----------------------------------------------------------------------------
void displayIntArg1(int argCount, char* pArg1, string& filename) {

    if (argCount > 1) {

        // put the char* input from argv[1] in a stringstream variable
        stringstream convertStr { pArg1 };

        // try conversion to int
        int intArg1;
        if (convertStr >> intArg1) {
            cout << "\nInteger command line argument: " << intArg1 << '\n';
        }
        else {
            cout << "\nUsage: " << filename << " <integer>\n";
        }
    }
}

//------------------------------------------------------------------------------
// convert .exe filename string to .cpp
//------------------------------------------------------------------------------
string makeCpp(const string& str) {

    cout << "\nChanging " << str << " filename suffix to.cpp\n";

    // get position before suffix starts
    size_t found = str.find_last_of(".");

    // substring before that position is the file name
    string filename = str.substr(0, found);
    cout << "\tfilename: " << filename << '\n';

    // substring after that position is the file name suffix
    string suffix = str.substr(found + 1);
    cout << "\tsuffix: " << suffix << '\n';

    // build a new string that replaces suffix with cpp
    string retStr = filename + ".cpp";

    cout << "\tcpp filename: " << retStr << "\n\n";

    return retStr;
}

//------------------------------------------------------------------------------
// display cpp file data
//------------------------------------------------------------------------------
int displayCpp(const string& cppFile) {

    ifstream ifs(cppFile);

    if (!ifs.is_open()) {
        cout << "\nCould not open file " << cppFile << "\n\n";
        return FILE_ERROR;
    }

    cout << "\nC++ source code in this file:\n\n";

    string content((istreambuf_iterator<char>(ifs)),
        (istreambuf_iterator<char>()));

    ifs.close();

    cout << content << '\n';

    return FILE_OK;
}

