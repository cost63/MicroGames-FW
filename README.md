# MicroGames Game Framework

**Project is in its initial development phases**

The purpose of this framework is to develop mainly 2D games with complete control over the process with minimal dependencies. Framework is build on SDL2 2.0.4 and OpenGL 3.3. We also support Lua for scripts with our own binding. Framework also supports use of XML for data storage.

The framework is written purely in C++ (C++14) and is currently compiled only for Windows, other platforms are not supported **yet**. Main compiler is MinGW. (gcc 5.1.0)

### Dependecies
Current dependencies are all included inside the dependecies/* folder.

* SDL2 ( 2.0.4 )
* SDL2_image (2.0.1)
* SDL2_ttf (2.0.14)
* Glew 
* Box2D (currently not pre-compiled)

For more info about including these dependencies in your IDE, see our [wiki page](https://github.com/MicroGamesDev/MicroGames-FW/wiki/Setup-of-dependencies/)

### Coding conventions
All code should be refactored to follow our coding conventions. You can find them [here](https://github.com/MicroGamesDev/MicroGames-FW/wiki/Coding-Conventions)
