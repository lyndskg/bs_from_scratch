//
//  inputReader.h
//  black-scholes
//
//  Created by lyndskg on 7/18/23.
//

#ifndef inputReader_h
#define inputReader_h

#include <string>

#include "Program.h"
//#include "libcurl/curl/curl.h"
#include "blackScholesModel.h"

using namespace std;

class blackScholesModel; // Forward declaration of blackScholesModel class

// ----------------------------------------------------------------------------
//                  "inputReader" Class Declarations
// ----------------------------------------------------------------------------

class inputReader {
  private:
/*-------- HELPER FUNCTION VARIABLES (readDoubleInput, readOptionType) -----------*/
    
/*------------------------------  HELPER FUNCTIONS  -------------------------------*/

    
    // Validates and sets the input values for the blackScholesModel.
    //
    // Time complexity: O(1)
    // Space complexity: O(1)
    bool validateAndSetInputValues(blackScholesModel& model, double underlyingPrice, double strikePrice,
                                   double timeToExpiration, double riskFreeRate, double volatility, char optionType);
    
    
  public:
/*------------------------------ CONSTRUCTORS  -------------------------------*/
    string mode;
    string ext;
    // Default constructor.
    inputReader();

/*------------------------ KEY MEMBER FUNCTIONS  -----------------------------*/
   
    // Reads input values from the user interactively.
    //
    // Time complexity: O(1) per input prompt
    //          i.e. time complexity depends on the number of input prompts
    //               and the time it takes for the user to provide valid input.
    // Space complexity: O(1)
    //
    // TODO: Use validateAndSetInputValues()? 
    void readInputFromUser(blackScholesModel& model);
    
    
    // Reads input parameters from a file (e.g. JSON or CSV).
    //
    // Time complexity: O(1) per input read from the file
    // Space complexity: O(1)
    void readInputFromFile(blackScholesModel& model, const string& filename);
    
    
    /* Reads input values from a database.
       It connects to the database, retrieves the input data, validates the
       retrieved values, and sets them in the blackScholesModel object. */
    //
    // Time complexity: O(1) [per input retrieval from the database]
    // Space complexity: O(1)
    //
    // TODO: IMPLEMENT
//    void readInputFromDB(blackScholesModel& model);
    
    
    /* Reads input values from an API by making an HTTP request.
       It initializes libcurl, sets up the HTTP request w/ the API endpoint URL,
       and performs the request. The received response is stored in the 'response' string
       and then parsed to extract the input values. Finally, the retrieved input values
       are validated and set in the blackScholesModel object. */
    //
    // Time complexity: O(1) [per input retrieval from the API]
    // Space complexity: O(1)
    //
    // TODO: IMPLEMENT
//    void readInputFromAPI(blackScholesModel& model);
    
}; // class InputReader


#endif /* inputReader_h */
