#include <iostream>
#include "FileIO.h"
#include "FileAnalyzer.h"
#include <string>
#include "Parser.h"

int main() {

    Parser parser;

    parser.setFolderPath("C:/Users/lenovo/Desktop/uftrace-master");
    parser.CountStatistics();

    return 0;
}