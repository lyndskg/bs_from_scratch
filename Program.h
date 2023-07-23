//
//  Program.h
//  black-scholes
//
//  Created by lyndskg on 7/18/23.

#ifndef Program_h
#define Program_h

#include "inputReader.h"
#include "blackScholesModel.h"

using namespace std;

// Define the fast_io lambda function
static auto fast_io = []() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
}; // fast_io

// ----------------------------------------------------------------------------
//                      "Program" Class Declarations
// ----------------------------------------------------------------------------

class Program {
  public:
/*--------------------------- MEMBER VARIABLES  ------------------------------*/
    string inputMode; // Program mode (i.e. USER, FILE, DB, or API)
    bool invalidMode;
    static constexpr int MAX_BUFFER_SIZE = 10000;
    
/*------------------------------  CONSTRUCTORS  ------------------------------*/
    // Default constructor.
    Program();

    // TODO: Implement any relevant custom constructors.

    
/*--------------------------- KEY MEMBER FUNCTIONS  ---------------------------*/
    /* Processes the command line arguments.
       Uses getopt_long to parse the options and their arguments.
     
       Based on the specified mode, it calls the corresponding functions to read input values
       from different sources (e.g. user input, a file, a database, or an API). */
    //
    // Time complexity: O(n), where n = # of command line options
    // Space complexity: O(1)
    void get_options(int argc, char* argv[]);

    const string& getInputMode() const;

    void setInputMode(const string& inputMode_);

    
    // Prints a helpful message about how to use the program for the user when requested.
    //
    // Time complexity: O(1)
    // Space complexity: O(1)
    void printHelp(char* argv[]);
    
    
    // Launches the algorithm by reading input values based on the specified input mode.
    //
    // Time complexity: O(1)
    // Space complexity: O(1)
    void launchAlgo(blackScholesModel* model);
    
    
    // Reads and validates the input mode from the user.
    //
    // @Return: Returns the validated input mode as a string.
    //
    // Time complexity: O(1)
    // Space complexity: O(1)
    string readInputMode();
    
    
private:
    // TODO: Implement any/all private and/or protected member variables.
    mutable string inputMode_;
    
}; // class Program


#endif /* Program_h */
