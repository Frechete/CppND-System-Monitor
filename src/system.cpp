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

// TODO: Return the system's CPU
Processor& System::Cpu() { return cpu_; }

// TODO: Return a container composed of the system's processes
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
      processes_.emplace_back(process);
    } else {
      Process process(icpid, cpu_.DeltaJiffies(), i->second);
      processes_.emplace_back(process);
    }

    // process.CpuUtilization();
    // processes_.emplace_back(process);
  }
  std::sort(processes_.begin(), processes_.end());
  return processes_;
}

// TODO: Return the system's kernel identifier (string)
std::string System::Kernel() { return LinuxParser::Kernel(); }

// TODO: Return the system's memory utilization
float System::MemoryUtilization() { return LinuxParser::MemoryUtilization(); }

// TODO: Return the operating system name
std::string System::OperatingSystem() { return LinuxParser::OperatingSystem(); }

// TODO: Return the number of processes actively running on the system
int System::RunningProcesses() { return LinuxParser::RunningProcesses(); }

// TODO: Return the total number of processes on the system
int System::TotalProcesses() { return processes_.size(); }

// Number of seconds since the system started running
long int System::UpTime() { return LinuxParser::UpTime(); }
