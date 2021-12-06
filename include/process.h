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
  int Pid();
  std::string User();
  std::string Command();
  float CpuUtilization();
  std::string Ram();
  long int UpTime();
  long prevJiff() const { return prevJiffies_; }
  bool operator<(Process const& a) const { return a.cpuUt < cpuUt; }
  void CpuUtilUpdate();

 private:
  int pid_;
  long totJiffies_;
  long prevJiffies_{0};
  float cpuUt{0};
};

#endif