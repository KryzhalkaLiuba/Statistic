#include "Parser.h"
#include <thread>
#include <chrono>
#include "FileAnalyzer.h"

Parser::Parser():statistics(){
}

void Parser::CountStatisticsInFilePackage(const std::vector<std::filesystem::path>& file_names)
{
    for (size_t i = 0; i < file_names.size(); i++)
    {
        statistics.CountStatisticsInFile(file_names[i]);
    }
}

void Parser::CountStatistics()
{
    SearchFiles(folderPath);

    const unsigned best_threads_quantity = std::thread::hardware_concurrency();
    std::vector<std::thread> threads_for_parsing;

    std::vector<std::vector<std::filesystem::path>> packages(best_threads_quantity);

    unsigned subvector_to_push = 0;
    for (const auto& element : file_names)
    {
        packages[subvector_to_push % best_threads_quantity].push_back(element);
        subvector_to_push++;
    }

    auto startTimer = std::chrono::high_resolution_clock::now();
    
    for (size_t i = 0; i < best_threads_quantity; i++)
    {
        threads_for_parsing.emplace_back(std::thread(&Parser::CountStatisticsInFilePackage, this, packages[i]));
    }
    for (size_t i = 0; i < best_threads_quantity; i++)
    {
        threads_for_parsing[i].join();
    }

    auto stopTimer = std::chrono::high_resolution_clock::now();
    time = std::chrono::duration_cast<std::chrono::milliseconds>(stopTimer - startTimer).count();


    WriteStatistics("statistic1.txt");

}

void Parser::setFolderPath(const std::string& value) noexcept
{
    folderPath = value;
}

void Parser::SearchFiles(const std::string& str)
{
    for (std::filesystem::recursive_directory_iterator it(str), end; it != end; ++it)
    {
        std::string extension = it->path().extension().string();
        if (extension == ".cpp" || extension == ".c" || extension == ".hpp" || extension == ".h")
        {
            file_names.push_back(*it);
        }
    }

}

void Parser::WriteStatistics(const std::string& file_name) const{

    std::string text_statistics;

    text_statistics = "Files quantity: " + std::to_string(static_cast<unsigned int>(file_names.size())) + "\n";
    text_statistics += "Blank lines : " + std::to_string(statistics.GetCountBlankLines()) + "\n";
    text_statistics += "Comment lines : " + std::to_string(statistics.GetCountCommentLines()) + "\n";
    text_statistics += "Code lines: " + std::to_string(statistics.GetCountCodeLines()) + '\n';
    text_statistics += "Time: " + std::to_string(time) + "\n";

    FileIO::saveTextTo(file_name, text_statistics);

}


std::vector<unsigned int> Parser::GetStatistics() const {
    std::vector<unsigned int > count_variables;
    count_variables.push_back(statistics.GetCountBlankLines());
    count_variables.push_back(statistics.GetCountCommentLines());
    count_variables.push_back(statistics.GetCountCodeLines());
    return count_variables;
}

std::uint32_t Parser::GetNumberOfFiles() const {
    return static_cast<unsigned int>(file_names.size());
}