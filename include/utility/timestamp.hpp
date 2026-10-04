#pragma once

#include <string>
#include <chrono>
#include <ctime>
#include <iosfwd>

namespace utility{
    class Timestamp{
        public:
            using Clock = std::chrono::system_clock;
            using TimePoint = Clock::time_point;

            TimePoint value;

            Timestamp();

            explicit Timestamp(TimePoint tp);

            explicit Timestamp(std::time_t epoch);

            std::string toString() const;

            std::time_t toEpoch() const;

            bool operator<(const Timestamp& other) const;
            bool operator>(const Timestamp& other) const;
            bool operator==(const Timestamp& other) const;
    };

    std::ostream& operator<<(std::ostream& os, const Timestamp ts);
};
