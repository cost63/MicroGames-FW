#include "ErrorLog.h"

#include <iostream>

namespace mg {

// Error message storage
std::string _errorMsg;

namespace priv {

void storeError(const std::string& msg,
                const std::string& prefix /* = "[Error]" */,
                const std::string& prefix2 /* = std::string() */)
{
    // Store error
    _errorMsg = prefix + prefix2 + " " + msg;

    // TODO(Smeky) Change this to some boolean option to enable printing to console
#ifdef MGFW_DEBUG
    std::cerr << _errorMsg << std::endl;
#endif // MGFW_DEBUG
}

} // namespace priv

const std::string& getError() const {
    return _errorMsg;
}

} // namespace mg
