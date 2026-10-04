#include "utility/timestamp.hpp"

#include <sstream>
#include <iomanip>
#include <ostream>

namespace utility{
    Timestamp::Timestamp():value(Clock::now()){}

    Timestamp::Timestamp(TimePoint tp): value(tp){}

    Timestamp::Timestamp(std::time_t epoch): value(Clock::from_time_t(epoch)){}

    std::string Timestamp::toString()const{
        std::time_t epoch = Clock::to_time_t(value);
        std::tm tm{};

#if defined(_WIN32) || defined(_WIN64)
        gmtime_s(&tm,&epoch);
#else
        gmtime_r(&epoch,&tm);
#endif
        
        std::ostringstream oss;
        oss<< std::put_time(&tm, "%Y-%m-%dT%H:%M:%SZ");
        return oss.str();
    }

    std::time_t Timestamp::toEpoch() const{
        return Clock::to_time_t(value);
    }

    bool Timestamp::operator<(const Timestamp& other) const{
        return value < other.value;
    }

    bool Timestamp::operator>(const Timestamp& other) const{
        return value > other.value;
    }

    bool Timestamp::operator==(const Timestamp& other) const{
        return value == other.value;
    }


    std::ostream& operator<<(std::ostream& os, const Timestamp ts){
        os << ts.toString();

        return os;
    }
};
