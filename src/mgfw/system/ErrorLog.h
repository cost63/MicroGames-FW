#pragma once

#include <string>

namespace mg {
namespace priv {

const std::string c_prefError   = "[Error]";
const std::string c_prefWarning = "[Warning]";

// Store error message in internal value so it can be received on request
// This function also handles error printing/logging
void logError(const std::string msg,
              const std::string& prefix1 = c_prefError);

void logError(const std::string msg,
              const std::string& prefix1,
              const std::string& prefix2);

void logError(const std::string& msg,
              const std::string& prefix1,
              const std::string& prefix2,
              const std::string& prefix3);

// This function takes no argument as it only handles logic behind
// error handling (print,write to file, etc.)
void logError();

// Adds message to empty error string. This way we can store
// as many errors as we want in to one error message
void addError(const std::string& msg);

} // namespace priv

// Enables storing error messages in to a string
// This string can then be returned on request
void setErrorStorageEnable(bool enable);

// Enables printing errors in to console
void setErrorToConsoleEnable(bool enable);

// Enables writing errors in to file
void setErrorToFileEnable(bool enable);

// Returns last error message. Empty string if no message was stored yet
const std::string& getError();

// Returns all stored error messages
const std::string& getStoredErrors();
// Empties string with stored messages
void flushStoredErrors();

} // namespace mg
