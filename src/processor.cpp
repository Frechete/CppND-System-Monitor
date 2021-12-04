#include "processor.h"

#include "linux_parser.h"

// TODO: Return the aggregate CPU utilization
float Processor::Utilization() {
  std::pair<long, long> result = LinuxParser::UpdateJiffies();
  const float active_time_delta = result.second - jiffies_active;
  jiffies_active = result.second;
  delta_jiffies = result.first - jiffies;
  jiffies = result.first;
  return ((active_time_delta * 1.0) / (delta_jiffies * 1.0));
}
