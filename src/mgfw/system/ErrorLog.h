#pragma once

#include <iostream>

#ifndef PRINT_ERROR

#ifdef MGFW_DEBUG
#define PRINT_ERROR(error) \
    std::cout << error << std::endl;
#else
#define PRINT_ERROR(error)
#endif // MGFW_DEBUG

#endif // PRINT_ERROR

