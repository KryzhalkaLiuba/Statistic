#include "pch.h"
#include <vector>
#include "../ProjectStatistic/Parser.h"


TEST(Parser, Statistics) {
    Parser parser;

    parser.setFolderPath("C:/Users/lenovo/Desktop/My_life/work/softserveAcademy/ProjectStatistic/TestFiles");
    parser.CountStatistics();

    std::vector<std::uint32_t> statistics = parser.GetStatistics();

    ASSERT_EQ(statistics[0], 14);
    ASSERT_EQ(statistics[1], 19);
    ASSERT_EQ(statistics[2], 20);

    ASSERT_EQ(parser.GetNumberOfFiles(), 4);

}