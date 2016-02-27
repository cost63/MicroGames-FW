#include "ErrorLog.h"

#include <iostream>

namespace mg {

// Last error message
std::string _errorMsg;
// Storage for all error messages
std::string _errorStorage;

bool _isErrorStorage     = false;
bool _isFileOutput       = false;

// In case of MG development debug version, we always want to console output
#ifdef MGFW_DEBUG
bool _isConsoleOutput = true;
#else
bool _isConsoleOutput = false;
#endif // MGFW_DEBUG

namespace priv {

void logError(const std::string msg,
              const std::string& prefix1 /*= c_prefError*/)
{
    _errorMsg = prefix1 + " " + msg;

    logError();
}

void logError(const std::string msg,
              const std::string& prefix1,
              const std::string& prefix2)
{
    _errorMsg = prefix1 + prefix2 + " " + msg;

    logError();
}

void logError(const std::string& msg,
              const std::string& prefix1,
              const std::string& prefix2,
              const std::string& prefix3)
{
    _errorMsg = prefix1 + prefix2 + prefix3 + " " + msg;

    logError();
}

void logError() {
    // Store last error message in the error storage
    if(_isErrorStorage) {
        _errorStorage += _errorMsg;
    }

    // Output last error message to console
    if(_isConsoleOutput) {
        printf((_errorMsg + '\n').c_str());
    }

    // Output last error message to file
    if(_isFileOutput) {
        // ...
    }
}

void addError(const std::string& msg) {
    _errorMsg += msg;
}

} // namespace priv

void setErrorStorageEnable(bool enable) {
    _isErrorStorage = enable;
}

void setErrorToConsoleEnable(bool enable) {
    _isConsoleOutput = enable;
}

void setErrorToFileEnable(bool enable) {
    _isFileOutput = enable;
}

const std::string& getError() {
    return _errorMsg;
}

const std::string& getStoredErrors() {
    return _errorStorage;
}

void flushStoredErrors() {
    _errorStorage.clear();
}

} // namespace mg
