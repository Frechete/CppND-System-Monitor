#include "processor.h"
#include "linux_parser.h"

// TODO: Return the aggregate CPU utilization
float Processor::Utilization() {
    std::pair<long, long> result = LinuxParser::UpdateJiffies();
    const float active_time_delta = result.second - jiffies_active;
    jiffies_active = result.second;
    const float total_time_delta = result.first - jiffies;
    jiffies = result.first;
    return (100.0 * (active_time_delta / total_time_delta));
}
