#include"Global.h"
bool is_empty_file(std::ifstream& pFile)
{
    if (!pFile) return true;
    return pFile.peek() == std::ifstream::traits_type::eof();
}