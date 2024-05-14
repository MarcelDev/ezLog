# ezLog

ezLog is a simple header-only C++11 logging library.
It doesn't have any dependencies except for the standard C++ library

# Usage:
Simply move the includes into your project's include directory

A simple example is available in the "example" directory
```cpp
#include <ezlog/logger.h>

int main() {
    ezlog::ezLogger logger("Example", true, "hello.log", true, EZLOG_LEVEL_DEBUG, "%y-%m-%d %H:%M:%S %lL %lN: %lM"); // Specify all parameters
    // Log messages
    logger.debug("Debug message");
    logger.info("Info message");
    logger.warn("Warning message");
    logger.error("Error message");

    return 0;
}
```

# Format
Remember to properly capitalize the characters!!
Year %y

Month %m

Day %d

Hour %H

Minute %M

Second %S

Logger name %lN

Log message %lM

Log level %lL

# Bugs
If you find a bug, just make an issue

# Contributing
Fork this project, make a pull request
