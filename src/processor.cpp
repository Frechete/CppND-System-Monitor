#include "processor.h"
#include "linux_parser.h"

// TODO: Return the aggregate CPU utilization
float Processor::Utilization() {
    long jiffies = LinuxParser::Jiffies();
    long jiffies_idle = LinuxParser::IdleJiffies();
    LinuxParser::UpdateJiffies();
    const float idle_time_delta = LinuxParser::IdleJiffies() - jiffies_idle;
    const float total_time_delta = LinuxParser::Jiffies() - jiffies;
    return (100.0 * (1.0 - idle_time_delta / total_time_delta));
}
