#include <iostream>
#include <chrono>
#include <format>

using namespace std::chrono;

void print_time(const zoned_time<system_clock::duration>& zt, const std::string& label) {
    auto local_time = zt.get_local_time();
    auto dp = floor<days>(local_time); // Date part of the time
    auto ymd = year_month_day{dp}; // Year, month, day part of the time
    auto time = hh_mm_ss{local_time - dp}; // Time part of the time

    std::cout << std::format("{}: {}-{:02}-{:02} {:02}:{:02}:{:02}\n",
                        label,
                        static_cast<int>(ymd.year()), static_cast<unsigned>(ymd.month()), static_cast<unsigned>(ymd.day()),
                        time.hours().count(), time.minutes().count(), time.seconds().count());
}

int main() {
    // Get the current system time
    auto now = system_clock::now();

    // Convert to different time zones
    auto local_time = zoned_time{current_zone(), now};
    auto utc_time = zoned_time{"UTC", now};
    auto ny_time = zoned_time{"America/New_York", now};
    auto tokyo_time = zoned_time{"Asia/Tokyo", now};

    // Display the date and time in each time zone
    std::cout << "Current Date and Time:\n";
    print_time(local_time, "Local Time");
    print_time(utc_time, "UTC Time");
    print_time(ny_time, "New York Time");
    print_time(tokyo_time, "Tokyo Time");

    return 0;
}