#include <algorithm>
#include <cctype>
#include <fstream>
#include <ios>
#include <iostream>
#include <map>
#include <set>
#include <string>

std::string GetWord(std::istream& in) {
    char c = 0;
    in >> std::noskipws >> c;
    std::string result;
    while (in && (std::isalpha(c) || c == '\'')) {
        result += c;
        in >> c;
    }
    in >> std::skipws;
    return result;
}

void ConvertToLow(std::string& s) {
    std::transform(s.begin(), s.end(), s.begin(), [](const char& i){ return std::tolower(i); });
}

int main() {
    std::ifstream in("in.txt");
    if (!in) { std::cout << "Cannot open in.txt\n"; return 1; }
    std::set<std::string> s;
    std::map<std::string, size_t> m;
    // std::cout << "DEBUG\t" << std::isalpha(' ');
    while (in) {
        std::string temp;
        // in >> temp;
        temp = GetWord(in);
        // std::cout << "DEBUG:\t the word is " << temp << temp.size() << '\n';
        if (temp.empty()) { continue; }
        ConvertToLow(temp);
        m[temp]++;
        s.insert(temp);
    }
    in.close();
    std::cout << "Unicue words:\n";
    std::for_each(s.begin(), s.end(), [](const std::string& i){ std::cout << i << '\n'; });
    std::cout << "Number\n";
    for (const auto& [i, j] : m) {
        std::cout << i << ": " << j << '\n';
    }
    return 0;
}
