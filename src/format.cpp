#include "format.h"

#include <iomanip>
#include <string>

using std::string;
#include <sstream>

// INPUT: Long int measuring seconds
// OUTPUT: HH:MM:SS
string Format::ElapsedTime(long seconds) {
  std::stringstream ss;
  // convert to milliseconds

  long h = seconds / (60 * 60);
  seconds -= h * (60 * 60);

  long m = seconds / (60);
  seconds -= m * (60);

  ss << std::setfill('0') << std::setw(2) << h << ':' << std::setw(2) << m
     << ':' << std::setw(2) << seconds;
  return ss.str();
}
