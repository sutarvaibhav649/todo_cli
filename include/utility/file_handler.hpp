#pragma once

#include <string>
#include <vector>

namespace utility{
    class FileHandler{
        private:
            std::string filepath;

        public:
            explicit FileHandler(std::string filepath);

            std::vector<std::string> readLine() const; 
            bool writeLines( const std::vector<std::string>& lines) const;
            bool appendLines( const std::string& line ) const;

            static std::string escapeCsv(const std::string& field);
            static std::vector<std::string> parseCsvLine(const std::string& line);
    };
};
