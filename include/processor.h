#ifndef PROCESSOR_H
#define PROCESSOR_H
#include <atomic>

class Processor {
 public:
  float Utilization();  // TODO: See src/processor.cpp
  float DeltaJiffies() const { return delta_jiffies; }

  // TODO: Declare any necessary private members
 private:
  std::atomic<long> jiffies{0};
  std::atomic<long> jiffies_active{0};
  float delta_jiffies{0};
};

#endif
