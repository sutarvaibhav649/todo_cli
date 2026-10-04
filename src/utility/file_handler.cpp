#include "utility/file_handler.hpp"

#include <fstream>
#include <sstream>

namespace utility{
    FileHandler::FileHandler(std::string filepath): filepath(std::move(filepath)){}

    std::vector<std::string> FileHandler::readLine() const{
        std::vector<std::string> lines;
        std::ifstream file(filepath);

        if(!file.is_open()) return lines;

        std::string line;

        while(std::getline(file,line)){
            if(!line.empty()){
                lines.push_back(line);
            }
        }

        return lines;
    }

    bool FileHandler::writeLines( const std::vector<std::string>& lines ) const{
        std::ofstream file(filepath, std::ios::trunc);
        
        if(!file.is_open()) return false;

        for(const auto& line : lines){
            file << line << "\n";
        }

        return true;
    }

    bool FileHandler::appendLines(const std::string& line) const{
        std::ofstream file(filepath,std::ios::app);

        if(!file.is_open()) return false;

        file << line << "\n";

        return true;
    }

    std::string FileHandler::escapeCsv(const std::string& field){
        std::string result = field;
        size_t pos = 0;

        while((pos = result.find('"',pos)) != std::string::npos){
            result.replace(pos,1,"\"\"");
            pos += 2;
        }

        if(result.find(',')!= std::string::npos || result.find('"') != std::string::npos || result.find('\n') != std::string::npos){
            result = "\"" + result + "\"";
        }

        return result;
    } 

    std::vector<std::string> FileHandler::parseCsvLine(const std::string& line){
        std::vector<std::string> fields;
        std::string current;
        bool inQuotes = false;

        for(size_t i = 0; i < line.size(); ++i){
            char c = line[i];

            if(c == '"'){
                if(inQuotes && i + 1 < line.length() && line[i+1] == '"'){
                    current += '"';
                    ++i;
                }else{
                    inQuotes = !inQuotes;
                }
            }else if(c == ',' && !inQuotes){
                fields.push_back(current);
                current.clear();
            }else{
                current += c;
            }
        }

        fields.push_back(current);
        return fields;
    }
};
