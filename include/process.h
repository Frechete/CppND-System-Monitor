#ifndef PROCESS_H
#define PROCESS_H

#include <string>
/*
Basic class for Process representation
It contains relevant attributes as shown below
*/
class Process {
 public:
  Process(int pid = 0, long totJiffies = 0, long prevJiffies = 0)
      : pid_(pid), totJiffies_(totJiffies), prevJiffies_(prevJiffies) {}
  int Pid();               // TODO: See src/process.cpp
  std::string User();      // TODO: See src/process.cpp
  std::string Command();   // TODO: See src/process.cpp
  float CpuUtilization();  // TODO: See src/process.cpp
  std::string Ram();       // TODO: See src/process.cpp
  long int UpTime();       // TODO: See src/process.cpp
  long prevJiff() const { return prevJiffies_; }
  bool operator<(Process const& a) const { return a.cpuUt < cpuUt; }
  void CpuUtilUpdate();

  // TODO: Declare any necessary private members
 private:
  int pid_;
  long totJiffies_;
  long prevJiffies_{0};
  float cpuUt{0};
};

#endif