#include <string>
#include <sstream>
#include <vector>

template <class T>
std::vector<T> split(const T& str, char split_char)
{
    std::vector<T> parts;
    typename T::size_type start_index = 0;
    typename T::size_type end_index;

    while ((end_index = str.find_first_of(split_char, start_index)) != T::npos) {
        parts.push_back(str.substr(start_index, end_index - start_index));
        start_index = end_index + 1;
    }
    parts.push_back(str.substr(start_index, T::npos));

    return parts;
}

int64_t asInt(const std::string& str) {
    std::stringstream ss;
    int64_t number;
    ss << str;
    ss >> number;
    return number;
}
