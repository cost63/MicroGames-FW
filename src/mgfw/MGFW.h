#pragma once

namespace mg
{

/* Global variables */
extern bool g_isGlewInit;

/* Functions */
bool init();
void close();

bool initGlew();

} // namespace mg
