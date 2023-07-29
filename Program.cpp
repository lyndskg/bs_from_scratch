//
//  Program.cpp
//  black-scholes
//
//  Created by lyndskg on 7/17/23.

#include <iostream>
#include <getopt.h>

#include "Program.h"
#include "inputReader.h"
#include "blackScholesModel.h"

using namespace std;

// ----------------------------------------------------------------------------
//              "Program" Class Member Function Implementations
// ----------------------------------------------------------------------------

/*------------------------------  CONSTRUCTORS  ------------------------------*/
// Default constructor.
Program::Program() : inputMode(""), external(""){
    fast_io();

    ios_base::sync_with_stdio(false);

    getInputMode();
    getExternal();
}


/*--------------------------- KEY MEMBER FUNCTIONS  ---------------------------*/

// Processes the command line arguments.
void Program::get_options(int argc, char* argv[]) {
    int optIndex = 0, option = 0;
    invalidMode = false; // Tracks invalid mode provision(s)
    
    // Define an array of the structures describing each long option.
    struct option longOpts[] = {{"mode", required_argument, nullptr, 'm'}, // Option: --mode or -m
                                {"help", no_argument, nullptr, 'h'},       // Option: --help or -h
                                {nullptr, no_argument, nullptr, '\0'}};    // End of options
    
    // Loop over all the options.
    while ((option = getopt_long(argc, argv, "m:h", longOpts, &optIndex)) != -1) {
        switch (option) {
            // If the "mode" option is flagged:
            case 'm':
                inputMode = optarg; // Set the program mode to the provided argument.

                setInputMode(inputMode); // Set the input mode.

                if (argc < 4 && inputMode != "USER") {
                    cerr << "Must provide valid external source file\n";
                    exit(-1);
                }

                if (inputMode == "USER") {
                    break;
                }

                if (inputMode == "FILE" || inputMode == "DB" || inputMode == "API") {
                    external = argv[3]; // Set the external file name.
                    break;
                } else {
                    cerr << "Invalid mode \"" + inputMode + "\""; // Print to standard error.
                    invalidMode = true; // Set invalidMode to true.
                    break;
                }

                // TODO: Give user option to retype input mode.

            // If the "help" option is flagged:
            case 'h':
                printHelp(argv); // Print a helpful message.
                exit(0); // Exit.
            
            // Default case:
            default:
                cerr << "Invalid command line option"; // TODO: fix
                invalidMode = true; // Set invalidMode to true.
                break; // Break out of the switch statement.
        } // switch
    } // while
    
    // Check if an invalid mode was encountered:
    if (invalidMode) {
        cerr << " was provided as a command line option.\n";
        exit(1); // Exit with an error code
    } // if
    
    // Check if a mode was specified:
    if (inputMode.empty()) {
        cerr << "Error: no mode specified.\n";
        cerr << "Please re-run the program with your input mode of choice.\n";
        exit(1); // Exit with an error code
    } // if
} // get_options()


// TODO: Make sure external file ends in .JSON or .CSV.
//void Program::validateExternalFile(string fileName) {

//}

const string& Program::getInputMode() const {
    return inputMode;
}


const string& Program::getExternal() const {
    return external;
}

void Program::setInputMode(const string& inputMode_) {
    inputMode = inputMode_;
}


// Prints a helpful message about how to use the program for the user when requested.
void Program::printHelp(char* argv[]) {
    // Usage (HINT: 'argv[0]' is the name of the currently executing program):
    cout << "Usage: " << argv[0] << " [-m USER|FILE|DB|API]|-h\n";
    cout << "This program is designed to calculate European options pricing\n";
    cout << " using the Black-Scholes formula.\n";
    // Command-Line Options:
    cout << "Options:\n";
    cout << "-m, --mode <mode>: Specify the mode of operation.\n";
    cout << "Valid modes are: USER, FILE, DB, API.\n";
    cout << "-h, --help: Print this help message.\n";
    // Additional details and specifications:
    cout << "Based on the specified mode of operation, the program can read input \n";
    cout << "from its user(s), file(s), database(s), or external datafeed(s)/API(s).\n";
} // printHelp()


// Launches the algorithm by reading input values based on the specified input mode.
void Program::launchAlgo(blackScholesModel* model) {
    // Instantiate a new inputReader class.
    inputReader inputReader;
    
    /* Call the corresponding functions based on the input mode */

    // User input:
    if (inputMode == "USER") {
        inputReader.readInputFromUser(*model);
    } // if

    // File input:
    else if (inputMode == "FILE") {
//        string filename = "option_GS_df.csv";
        string filename = external;
        inputReader.readInputFromFile(*model, filename);
    } // elif

//    // Database input:
//    else if (inputMode == "DB") {
//        inputReader.readInputFromDB(*model);
//    } // elif

//    // External data feed (e.g. API) input:
//    else if (inputMode == "API") {
//        inputReader.readInputFromAPI(*model);
//    } // ...-elif
    
    cerr << "Error: invalid or non-existing mode.\n"; // Display error message.
    exit(-1); // Terminate program with error code.

} // launchAlgo()


// Reads and validates the input mode from the user.
string Program::readInputMode() {
    int i = 15;
    do {
        cout << "Enter input mode (USER, FILE, DB, API): ";
        cin >> inputMode;

        // Convert inputMode to uppercase for case-insensitive comparison
        transform(inputMode.begin(), inputMode.end(), inputMode.begin(), ::toupper);

        // If input is valid:
        if (inputMode == "USER" || inputMode == "FILE" ||
            inputMode == "DB" || inputMode == "API") {
            return inputMode; // inputMode is valid
        // If input is invalid:
        } else {
            cout << "Invalid input mode. Please try again.\n";

            cin.clear(); // Clear the input buffer.
            cin.ignore(MAX_BUFFER_SIZE, '\n');
        } // if-else

        --i; // Decrement i
    } while ((i > 0) && (inputMode.empty() || (inputMode != "USER" && inputMode != "FILE" && inputMode != "DB" && inputMode != "API"))); // do-while

    cerr << "Error: invalid or non-existing mode.\n"; // Display error message.
    exit(-1); // Terminate program with error code.
} // readInputMode()
