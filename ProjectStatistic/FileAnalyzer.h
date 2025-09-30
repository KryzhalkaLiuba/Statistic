#pragma once
#include <fstream>
#include <string>
#include "FileIO.h"
#include <iostream>
#include <sstream>


class FileAnalyzer {
public:

    FileAnalyzer();


    void CountStatisticsInFile(const std::filesystem::path& path);

    unsigned int GetCountBlankLines() const;

    unsigned int GetCountCommentLines() const;

    unsigned int GetCountCodeLines() const;

private:

    std::atomic<unsigned int > count_of_blank_lines;
    std::atomic<unsigned int > count_of_comment_lines;
    std::atomic<unsigned int > count_of_code_lines;
};