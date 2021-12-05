#ifndef PROCESSOR_H
#define PROCESSOR_H
#include <atomic>

class Processor {
 public:
  float Utilization();
  float DeltaJiffies() const { return delta_jiffies; }


 private:
  std::atomic<long> jiffies{0};
  std::atomic<long> jiffies_active{0};
  float delta_jiffies{0};
};

#endif
