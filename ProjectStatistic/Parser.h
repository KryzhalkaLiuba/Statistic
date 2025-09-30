#pragma once

#include <memory>
#include <string>
#include <filesystem>
#include <thread>
#include <vector>
#include "FileAnalyzer.h"


class Parser
{
public:
    Parser();
    ~Parser() = default;

    void CountStatistics();

    void setFolderPath(const std::string& value) noexcept;

    void SearchFiles(const std::string& str);

    void CountStatisticsInFilePackage(const std::vector<std::filesystem::path>& file_names);

    void WriteStatistics(const std::string& file_name) const;

    std::vector<unsigned int> GetStatistics() const;

    unsigned int  GetNumberOfFiles() const;

private:

    FileAnalyzer statistics;

    std::string folderPath;
    std::vector<std::filesystem::path> file_names;

    unsigned int time;
};

