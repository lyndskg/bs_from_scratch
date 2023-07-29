//
//  inputReader.cpp
//  black-scholes
//
//  Created by lyndskg on 7/18/23.
//
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <cmath>
#include <vector>
#include <stdexcept> // For exception handling
#include <limits> // For numeric_limits
//#include <curl/curl.h> // Example library for making HTTP requests
// Include necessary database libraries

//#include "csv.h" // Include the csv-parser library header
#include "blackScholesModel.h"
#include "inputReader.h"
#include "Program.h"


using namespace std;

// Serves as a callback for receiving the API response during an HTTP request.
// It is typically used with a library like 'libcurl' to handle the response data.
//
// Time complexity: O(1)
// Space complexity: O(1)
size_t responseCallback(void* contents, size_t size, size_t nmemb, string* response);

// ----------------------------------------------------------------------------
//                   "inputReader" Class Helper Functions
// ---------------------------------------------------------------------------


// Validates and sets the input values for the blackScholesModel.
bool inputReader::validateAndSetInputValues(blackScholesModel& model, double underlyingPrice,
                                            double strikePrice, double timeToExpiration,
                                            double riskFreeRate, double volatility, char optionType) {
    // Validate the retrieved input values
    
    // Check if the underlying price is positive:
    if (underlyingPrice <= 0.0 ||  strikePrice <= 0.0 ||
    	timeToExpiration <= 0.0 ||  riskFreeRate <= 0.0 ||
        volatility <= 0.0 || (optionType != 'C' && optionType != 'P') || (strikePrice > underlyingPrice)) {
        throw runtime_error("Invalid input. For this algorithm to work its best, please only "
                            " supply valid input values.");
        return false;
    } // if
    
    // Set the validated input values:
    model.setUnderlyingPrice(underlyingPrice);
    model.setStrikePrice(strikePrice);
    model.setTTE(timeToExpiration);
    model.setRFR(riskFreeRate);
    model.setVolatility(volatility);
    model.setOptionType(optionType);
    
    return true;
} // validateAndSetInputValues()


// Serves as a callback for receiving the API response during an HTTP request.
size_t responseCallback(void* contents, size_t size, size_t nmemb, string* response) {
    // Calculate the total size of the response data.
    size_t totalSize = size * nmemb;
    
    // Append the received data to the response string.
    response->append(static_cast<char*>(contents), totalSize);
    
    return totalSize;
} // responseCallback()


// ----------------------------------------------------------------------------
//            "inputReader" Class Member Function Implementations
// ----------------------------------------------------------------------------

// Default constructor.
inputReader::inputReader() : mode("USER") {
    // To speed up I/O.
    fast_io();
    ios_base::sync_with_stdio(false);

    Program program;
    mode = program.getInputMode();
	ext = program.getExternal();
}


// Reads input values from the user interactively.
void inputReader::readInputFromUser(blackScholesModel& model) {
    double underlyingPriceVal, strikePriceVal, timeVal, rateVal, volatilityVal;
    char optionTypeVal;

    // To speed up I/O.
    fast_io();

    ios_base::sync_with_stdio(false);

    // Prompt user via the CLI
    cout << "Please enter the following input values:\n";

    try {
		cout << "Underlying price: ";
        cin >> underlyingPriceVal;

        cout << "Strike price: ";
       	cin >> strikePriceVal;

        cout << "Time until expiration: ";
        cin >> timeVal;

        cout << "Risk-free rate: ";
        cin >> rateVal;

        cout << "Volatility: ";
        cin >> volatilityVal;

        cout << "Option Type (C/P): ";
        cin >> optionTypeVal;

        // Set the values in the blackScholesModel object
        model.setUnderlyingPrice(underlyingPriceVal);
        model.setStrikePrice(strikePriceVal);
        model.setTTE(timeVal);
        model.setRFR(rateVal);
        model.setVolatility(volatilityVal);
        model.setOptionType(optionTypeVal);

        if (validateAndSetInputValues(model, underlyingPriceVal, strikePriceVal,
                                      timeVal, rateVal, volatilityVal, optionTypeVal)) {
            cout << "Input values entered successfully.\n";
        } // if

    } catch (const exception& e) {
        cerr << "Error: " << e.what() << "\n";
    } // try-catch
    
} // readInputFromUser()



// Reads input parameters from a file (e.g. JSON or CSV).
// NOTE: CURRENTLY ONLY SUPPORTS CSV.
// TODO: Support .JSON input files.
void inputReader::readInputFromFile(blackScholesModel& model, const string& filename) {
    
    // Open the input file.
    ifstream inputFile(filename);
    
    if (!inputFile.is_open()) {
        cerr << "Failed to open input file: " << filename << endl; // Display error message.
        return;
    } // if
    
    vector<vector<string>> data;
    
    string line;
    
    while (getline(inputFile, line)) {
        stringstream ss(line);
        vector<string> row;
        
        string cell;
        while (getline(ss, cell, ',')) {
            row.push_back(cell);
        } // while
        
        data.push_back(row);
    } // while
    
    // Close the input file.
    inputFile.close();
    
    
    // Process the read data
    for (const auto& row : data) {
        if (row.size() < 6) {
            // Skip rows with insufficient columns
            cerr << "Invalid number of columns in CSV file.\n";
            continue;
        } // if
        
        // Access each column value by index
        string underlyingPrice = row[0];
        string strikePrice = row[1];
        string timeToExpiration = row[2];
        string riskFreeRate = row[3];
        string optionType = row[4];
        string volatility = row[5];
        
        // Validate the column values
        if (underlyingPrice.empty() || strikePrice.empty() || timeToExpiration.empty() ||
            riskFreeRate.empty() || optionType.empty() || volatility.empty()) {
            cerr << "Missing values in CSV file.\n";
            continue;
        } // if
        
        // Convert the column values to appropriate data types
        double underlyingPriceValue, strikePriceValue, timeToExpirationValue,
               riskFreeRateValue, volatilityValue;
        char optionTypeValue;
        
        try {
            underlyingPriceValue = stod(underlyingPrice);
            strikePriceValue = stod(strikePrice);
            timeToExpirationValue = stod(timeToExpiration);
            riskFreeRateValue = stod(riskFreeRate);
            volatilityValue = stod(volatility);
            optionTypeValue = optionType[0];

        } catch (const exception& e) {
            cerr << "Error converting values in CSV file: " << e.what() << "\n";
            continue;
        } // try-catch
        
        // Validate the converted values if needed
        if (!(validateAndSetInputValues(model,underlyingPriceValue, strikePriceValue,
                                       timeToExpirationValue, riskFreeRateValue,
                                       volatilityValue, optionTypeValue))) {
            cerr << "Invalid values in CSV file.\n";
            continue;
        } // if
    } // for
} // readInputFromFile()
         
//
//// Reads input values from a database.
//void inputReader::readInputFromDB(blackScholesModel& model) {
//    try {
//        // Connect to the database.
//        cout << "Connecting to the database..\n";
//
//        // Perform database query to retrieve the input values
//        double retrievedUnderlyingPrice = 0.0;
//        double retrievedStrikePrice = 0.0;
//        double retrievedTimeToExpiration = 0.0;
//        double retrievedRiskFreeRate = 0.0;
//        double retrievedVolatility = 0.0;
//        char retrievedOptionType = 'C';
//
//        // Handle any exceptions that may occur during database operations
//        // throw std::runtime_error("Failed to connect to the database.");
//
//        // Validate and set the retrieved input values
//        if (validateAndSetInputValues(model, retrievedUnderlyingPrice, retrievedStrikePrice,
//                                      retrievedTimeToExpiration, retrievedRiskFreeRate,
//                                      retrievedVolatility, retrievedOptionType)) {
//            cout << "Input values retrieved from the database.\n";
//        } // if
//
//    } catch (const exception& e) {
//        cerr << "Error: " << e.what() << "\n";
//    } // try-catch
//
//} // readInputFromDB()


//// Reads input values from an API by making an HTTP request.
//void inputReader::readInputFromAPI(blackScholesModel& model) {
//    cout << "Making API request...\n";
//
//    // Initialize libcurl.
//    CURL* curl = curl_easy_init();
//
//    if (curl) {
//        string url = "https://api.example.com/data"; // Example API endpoint URL
//
//        // Set up the HTTP request:
//
//        // Specify the URL of the API endpoint to which the request will be sent.
//        curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
//        // Handle the received data and append it to the 'response' string.
//        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, responseCallback);
//
//        string response; // Store the API response
//
//        // Specify the address of the 'response' string
//        // as the data storage location for the received response.
//        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &response);
//
//        // Perform the HTTP request:
//        CURLcode res = curl_easy_perform(curl);
//
//        // The API request was successful.
//        if (res == CURLE_OK) {
//            // The response is stored in the 'response' string.
//
//            // Example: Parse the API response and extract the input values.
//            double retrievedUnderlyingPrice = 100.0;
//            double retrievedStrikePrice = 110.0;
//            double retrievedTimeToExpiration = 30.0;
//            double retrievedRiskFreeRate = 0.05;
//            double retrievedVolatility = 0.2;
//            char retrievedOptionType = 'C';
//
//            // Validate and set the retrieved input values.
//            if (validateAndSetInputValues(model, retrievedUnderlyingPrice, retrievedStrikePrice, retrievedTimeToExpiration, retrievedRiskFreeRate,
//                                          retrievedVolatility, retrievedOptionType)) {
//                cout << "Input values retrieved from the API.\n";
//            } // if
//        } // if
//
//        // An error occurred during the API request.
//        else {
//            cerr << "Failed to retrieve input values from the API. Error: " << curl_easy_strerror(res) << endl;
//        } // if-else
//
//        // Clean up libcurl resources.
//        curl_easy_cleanup(curl);
//
//    } //if
//
//    // Failed to initialize libcurl.
//    else {
//        cerr << "Failed to initialize libcurl.\n"; // Print error message.
//        exit(-1); // Terminate program with error code.
//    } // if-else
//
//} // readInputFromAPI()
