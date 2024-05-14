/*
    MIT License

Copyright (c) 2024 Marcelsky

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
*/

#include <cstring>
#include <ctime>
#include <fstream>
#include <iostream>

#define EZLOG_LEVEL_DEBUG 0
#define EZLOG_LEVEL_INFO 1
#define EZLOG_LEVEL_WARN 2
#define EZLOG_LEVEL_ERROR 3
#define RED "\e[0;31m"
#define YEL "\e[0;33m"
#define MAG "\e[0;35m"
#define CYN "\e[0;36m"
#define CRESET "\e[0m"

namespace ezlog {
class ezLogger {
private:
  bool color;
  int logLevel;
  const char *name;
  std::ofstream outFile;
  bool logToConsole;
  std::string format;

  // Function to get the current timestamp as a string
  std::string getTimeStamp(const std::string &timeFormat) const {
    char buffer[80];
    std::time_t now = std::time(nullptr);
    std::strftime(buffer, sizeof(buffer), timeFormat.c_str(),
                  std::localtime(&now));
    return buffer;
  }

  // Function to get just the hours, minutes, and seconds
  std::string getTimeComponent(const std::string &format) const {
    char buffer[3];
    std::time_t now = std::time(nullptr);
    std::strftime(buffer, sizeof(buffer), format.c_str(), std::localtime(&now));
    return buffer;
  }

public:
  ezLogger(const char *name, bool color = false, const char *logFileName = "",
           bool logToConsole = true, int logLevel = EZLOG_LEVEL_INFO,
           const std::string &format = "%y-%m-%d %H:%M:%S %lN %lL %lM")
      : color(color), logLevel(logLevel), name(name),
        logToConsole(logToConsole), format(format) {
    try {
      if (logFileName && std::strlen(logFileName) > 0) {
        outFile.open(logFileName);
        if (!outFile.is_open()) {
          throw std::ios_base::failure("Failed to open log file!");
        }
      }
    } catch (const std::exception &e) {
      std::cerr << "error: " << e.what() << std::endl;
    }
  }

  void debug(const char *text) {
    if (!(logLevel <= EZLOG_LEVEL_DEBUG))
      return;
    std::string formattedMsg = formatMessage("DEBUG", text);
    if (outFile.is_open())
      outFile << formattedMsg << "\n";
    if (logToConsole)
      std::cout << ((color) ? MAG : "") << formattedMsg << "\n"
                << ((color) ? CRESET : "");
  }

  void info(const char *text) {
    if (!(logLevel <= EZLOG_LEVEL_INFO))
      return;
    std::string formattedMsg = formatMessage("INFO", text);
    if (outFile.is_open())
      outFile << formattedMsg << "\n";
    if (logToConsole)
      std::cout << ((color) ? CYN : "") << formattedMsg << "\n"
                << ((color) ? CRESET : "");
  }

  void warn(const char *text) {
    if (!(logLevel <= EZLOG_LEVEL_WARN))
      return;
    std::string formattedMsg = formatMessage("WARN", text);
    if (outFile.is_open())
      outFile << formattedMsg << "\n";
    if (logToConsole)
      std::cout << ((color) ? YEL : "") << formattedMsg << "\n"
                << ((color) ? CRESET : "");
  }

  void error(const char *text) {
    if (!(logLevel <= EZLOG_LEVEL_ERROR))
      return;
    std::string formattedMsg = formatMessage("ERROR", text);
    if (outFile.is_open())
      outFile << formattedMsg << "\n";
    if (logToConsole)
      std::cout << ((color) ? RED : "") << formattedMsg << "\n"
                << ((color) ? CRESET : "");
  }

  int getLevel() const { return logLevel; }

private:
  std::string formatMessage(const std::string &level, const char *text) const {
    std::string formattedMsg = format;

    // Replace placeholders with actual values
    size_t pos;

    pos = formattedMsg.find("%y");
    if (pos != std::string::npos)
      formattedMsg.replace(pos, 2, getTimeStamp("%Y"));

    pos = formattedMsg.find("%m");
    if (pos != std::string::npos)
      formattedMsg.replace(pos, 2, getTimeStamp("%m"));

    pos = formattedMsg.find("%d");
    if (pos != std::string::npos)
      formattedMsg.replace(pos, 2, getTimeStamp("%d"));

    pos = formattedMsg.find("%H");
    if (pos != std::string::npos)
      formattedMsg.replace(pos, 2, getTimeComponent("%H"));

    pos = formattedMsg.find("%M");
    if (pos != std::string::npos)
      formattedMsg.replace(pos, 2, getTimeComponent("%M"));

    pos = formattedMsg.find("%S");
    if (pos != std::string::npos)
      formattedMsg.replace(pos, 2, getTimeComponent("%S"));

    pos = formattedMsg.find("%lN");
    if (pos != std::string::npos)
      formattedMsg.replace(pos, 3, name);

    pos = formattedMsg.find("%lL");
    if (pos != std::string::npos)
      formattedMsg.replace(pos, 3, level);

    pos = formattedMsg.find("%lM");
    if (pos != std::string::npos)
      formattedMsg.replace(pos, 3, text);

    return formattedMsg;
  }
};
} // namespace ezlog