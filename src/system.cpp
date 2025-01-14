#include "system.h"

#include <bits/stdc++.h>
#include <unistd.h>

#include <cstddef>
#include <set>
#include <string>
#include <vector>

#include "linux_parser.h"
#include "process.h"
#include "processor.h"

using std::set;
using std::size_t;
using std::string;
using std::vector;
/*You need to complete the mentioned TODOs in order to satisfy the rubric
criteria "The student will be able to extract and display basic data about the
system."

You need to properly format the uptime. Refer to the comments mentioned in
format. cpp for formatting the uptime.*/

// Return the system's CPU
Processor& System::Cpu() { return cpu_; }

// Return a container composed of the system's processes
vector<Process>& System::Processes() {
  vector<int> pids = LinuxParser::Pids();
  std::map<int, long> prevJiff;
  for (auto proc : processes_) {
    prevJiff.insert(std::make_pair(proc.Pid(), (proc.prevJiff())));
  }
  processes_.clear();
  for (int icpid : pids) {
    std::map<int, long>::iterator i = prevJiff.find(icpid);
    if (i == prevJiff.end()) {
      Process process(icpid, cpu_.DeltaJiffies());
      process.CpuUtilUpdate();
      processes_.emplace_back(process);
    } else {
      Process process(icpid, cpu_.DeltaJiffies(), i->second);
      process.CpuUtilUpdate();
      processes_.emplace_back(process);
    }
  }
  std::sort(processes_.begin(), processes_.end());
  return processes_;
}

std::string System::Kernel() { return LinuxParser::Kernel(); }

float System::MemoryUtilization() { return LinuxParser::MemoryUtilization(); }

std::string System::OperatingSystem() { return LinuxParser::OperatingSystem(); }

int System::RunningProcesses() { return LinuxParser::RunningProcesses(); }

int System::TotalProcesses() { return processes_.size(); }

// Number of seconds since the system started running
long int System::UpTime() { return LinuxParser::UpTime(); }
