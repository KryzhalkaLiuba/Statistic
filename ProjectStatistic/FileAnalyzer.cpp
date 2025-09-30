#include <string>
#include "FileAnalyzer.h"
#include "FileIO.h"
#include <filesystem>

FileAnalyzer::FileAnalyzer() {

    count_of_blank_lines = 0;
    count_of_comment_lines = 0;
    count_of_code_lines = 0;

}


void FileAnalyzer::CountStatisticsInFile(const std::filesystem::path& path) {
    FileIO file_reader(path.string());

    std::string line;
    bool in_block_comment = false;

    while (file_reader.getline(line)) {
        bool code_found = false;
        bool line_counted = false;
        size_t i = 0, n = line.size();

        while (i < n) {
            if (!in_block_comment) {
                if (std::isspace(static_cast<unsigned char>(line[i]))) { i++; continue; }

                if (line[i] == '/' && i + 1 < n && line[i + 1] == '/') {
                    count_of_comment_lines++;
                    if (code_found) count_of_code_lines++;
                    line_counted = true;
                    break;
                }

                if (line[i] == '/' && i + 1 < n && line[i + 1] == '*') {
                    in_block_comment = true;
                    i += 2;
                    size_t end = line.find("*/", i);
                    count_of_comment_lines++;
                    if (code_found) count_of_code_lines++;
                    if (end == std::string::npos) {
                        line_counted = true;
                        break;
                    }
                    else {
                        in_block_comment = false;
                        i = end + 2;
                        continue;
                    }
                }

                code_found = true;
                i++;
            }
            else {
                count_of_comment_lines++;
                if (code_found) count_of_code_lines++;
                size_t end = line.find("*/", i);
                if (end == std::string::npos) {
                    line_counted = true;
                    break;
                }
                else {
                    in_block_comment = false;
                    i = end + 2;
                }
            }
        }

        if (!line_counted) {
            if (code_found) count_of_code_lines++;
            else count_of_blank_lines++;
        }
    }
}


unsigned int FileAnalyzer::GetCountBlankLines() const {
    return count_of_blank_lines;
}

unsigned int FileAnalyzer::GetCountCommentLines() const {
    return count_of_comment_lines;
}

unsigned int FileAnalyzer::GetCountCodeLines() const {
    return count_of_code_lines;
}