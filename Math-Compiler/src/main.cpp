#include <fstream>
#include <vector>
#include <filesystem>
#include <iostream>

std::string readFile(std::filesystem::path path)
{
    std::ifstream in { path };
    std::stringstream buffer;
    buffer << in.rdbuf();
    return buffer.str();
}

int main(int argc, char ** argv)
{
    std::string src = readFile(argv[1]);
    std::cout << src;
}