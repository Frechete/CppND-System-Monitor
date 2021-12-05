#include "linux_parser.h"

#include <dirent.h>
#include <unistd.h>

#include <cmath>
#include <sstream>
#include <string>
#include <vector>

using std::stof;
using std::string;
using std::to_string;
using std::vector;

// DONE: An example of how to read data from the filesystem
string LinuxParser::OperatingSystem() {
  string line;
  string key;
  string value;
  std::ifstream filestream(kOSPath);
  if (filestream.is_open()) {
    while (std::getline(filestream, line)) {
      std::replace(line.begin(), line.end(), ' ', '_');
      std::replace(line.begin(), line.end(), '=', ' ');
      std::replace(line.begin(), line.end(), '"', ' ');
      std::istringstream linestream(line);
      while (linestream >> key >> value) {
        if (key == "PRETTY_NAME") {
          std::replace(value.begin(), value.end(), '_', ' ');
          return value;
        }
      }
    }
  }
  return value;
}

// DONE: An example of how to read data from the filesystem
string LinuxParser::Kernel() {
  string os, kernel, version;
  string line;
  std::ifstream stream(kProcDirectory + kVersionFilename);
  if (stream.is_open()) {
    std::getline(stream, line);
    std::istringstream linestream(line);
    linestream >> os >> version >> kernel;
  }
  return kernel;
}

// BONUS: Update this to use std::filesystem
vector<int> LinuxParser::Pids() {
  vector<int> pids;
  DIR* directory = opendir(kProcDirectory.c_str());
  struct dirent* file;
  while ((file = readdir(directory)) != nullptr) {
    // Is this a directory?
    if (file->d_type == DT_DIR) {
      // Is every character of the name a digit?
      string filename(file->d_name);
      if (std::all_of(filename.begin(), filename.end(), isdigit)) {
        int pid = stoi(filename);
        pids.push_back(pid);
      }
    }
  }
  closedir(directory);
  return pids;
}

// Read and return the system memory utilization
float LinuxParser::MemoryUtilization() {
  string line;
  string memTotal;
  string memFree;
  float memTotalValue = 0.0;
  float memFreeValue = 0.0;
  float memoryUtilization = 0.0;
  std::ifstream stream(kProcDirectory + kMeminfoFilename);
  if (stream.is_open()) {
    std::getline(stream, line);
    std::istringstream linestream(line);
    linestream >> memTotal >> memTotalValue;
    std::getline(stream, line);
    std::istringstream linestream_free(line);
    linestream_free >> memFree >> memFreeValue;
    memoryUtilization = (memTotalValue - memFreeValue) / memTotalValue;
  }
  return memoryUtilization;
}

// system uptime
long LinuxParser::UpTime() {
  string line;
  long seconds = 0;
  std::ifstream stream(kProcDirectory + kUptimeFilename);
  if (stream.is_open()) {
    std::getline(stream, line);
    std::istringstream linestream(line);
    linestream >> seconds;
  }
  return seconds;
}

// Update jiffies for the system
std::pair<long, long> LinuxParser::UpdateJiffies() {
  string line;
  long jiffies = 0;
  long jiffies_idle = 0;
  long value = 0;
  short it = 0;
  std::ifstream stream(kProcDirectory + kStatFilename);
  if (stream.is_open()) {
    std::getline(stream, line);
    std::istringstream linestream(line);
    string dummy;
    linestream >> dummy;
    while (linestream >> value) {
      if (it == kIdle_) jiffies_idle = value;
      jiffies += value;
      it++;
    }
  }
  return std::make_pair(jiffies, jiffies - jiffies_idle);
}

// Read and return the number of active jiffies for a PID
long LinuxParser::ActiveJiffies(int pid) {
  string line;
  long utime = 0;
  long stime = 0;
  long child_time_a = 0;
  long child_time_b = 0;
  std::ifstream stream(kProcDirectory + std::to_string(pid) + kStatFilename);
  if (stream.is_open()) {
    std::getline(stream, line);
    std::istringstream linestream(line);
    string dummy;
    for (int i = 0; i < 12; i++) linestream >> dummy;
    linestream >> utime;
    linestream >> stime;
    linestream >> child_time_a;
    linestream >> child_time_b;
  }
  return (utime + stime + child_time_a + child_time_b);
}

// Not Used: Read and return CPU utilization
vector<string> LinuxParser::CpuUtilization() { return {}; }

// Not Used: Read and return the total number of processes
int LinuxParser::TotalProcesses() {
  string line;
  string key;
  int value = 0;
  std::ifstream filestream(kProcDirectory + kStatFilename);
  if (filestream.is_open()) {
    while (std::getline(filestream, line)) {
      std::istringstream linestream(line);
      while (linestream >> key >> value) {
        if (key == "processes") {
          return value;
        }
      }
    }
  }
  return value;
}

// Read and return the number of running processes
int LinuxParser::RunningProcesses() {
  string line;
  string key;
  int value = 0;
  std::ifstream filestream(kProcDirectory + kStatFilename);
  if (filestream.is_open()) {
    while (std::getline(filestream, line)) {
      std::istringstream linestream(line);
      while (linestream >> key >> value) {
        if (key == "procs_running") {
          return value;
        }
      }
    }
  }
  return value;
}

// Read and return the command associated with a process
string LinuxParser::Command(int pid) {
  string line;
  string command;
  std::ifstream stream(kProcDirectory + std::to_string(pid) + kCmdlineFilename);
  if (stream.is_open()) {
    std::getline(stream, line);
    command = line;
    if (!command.empty()) {
      std::istringstream linestream(line);
      string temp;
      linestream >> temp;
      std::size_t found = temp.find_last_of("\\/");
      if (found > 0 && found < (temp.size() - 2))
        command = command.substr(found + 1);
      std::string s = command;
      s.erase(s.find_last_not_of(" \n\r\t") + 1);
      if (s.empty()) command = line;
    }
  }
  return command;
}

// Read and return the memory used by a process
string LinuxParser::Ram(int pid) {
  string line;
  float ram = 0;
  string key;
  std::ifstream stream(kProcDirectory + std::to_string(pid) + kStatusFilename);
  if (stream.is_open()) {
    while (std::getline(stream, line)) {
      std::istringstream linestream(line);
      linestream >> key >> ram;
      // This seems what is actually in RAM
      if (key == "VmRSS:") {
        ram /= 1024;
        break;
      }
    }
  }

  return std::to_string((std::lround(ram)));
}

// Read and return the user ID associated with a process
string LinuxParser::Uid(int pid) {
  string line;
  string uid;
  string key;
  std::ifstream stream(kProcDirectory + std::to_string(pid) + kStatusFilename);
  if (stream.is_open()) {
    while (std::getline(stream, line)) {
      std::istringstream linestream(line);
      linestream >> key >> uid;
      if (key == "Uid:") {
        break;
      }
    }
  }

  return uid;
}

// Read and return the user associated with a process
string LinuxParser::User(int pid) {
  string line;
  string username;
  string uid = LinuxParser::Uid(pid);

  std::ifstream pwd_stream(kPasswordPath);
  if (pwd_stream.is_open()) {
    while (std::getline(pwd_stream, line)) {
      std::replace(line.begin(), line.end(), ':', ' ');
      std::istringstream linestream(line);
      string dummy;
      string uid_pwd_file;
      linestream >> username >> dummy >> uid_pwd_file;
      if (uid_pwd_file == uid) {
        break;
      }
    }
  }
  return username;
}

// Read and return the uptime of a process
long LinuxParser::UpTime(int pid) {
  string line;
  string uptime;
  std::ifstream stream(kProcDirectory + std::to_string(pid) + kStatFilename);
  if (stream.is_open()) {
    std::getline(stream, line);
    std::istringstream linestream(line);
    // string dummy;
    for (int i = 0; i < 22; i++) linestream >> uptime;
    // linestream >> uptime;
    return stol(uptime) / sysconf(_SC_CLK_TCK);
  }
  return 0;
}
