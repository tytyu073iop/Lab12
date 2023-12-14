#include "library.h"
#include <fstream>
#include <ios>
#include <iostream>
#include <iterator>
#include <sstream>
#include <string>

std::string GetNextItem(std::istream& in) {
    std::string result;
    std::getline(in, result, ';');
    // if (result.empty()) { throw 0; }
    std::cout << "DEBUG\t GNI " << result << '\n';
    return result;
}

void PrintLib(const Library& lib) {
    auto book_set = lib.Get();
    std::cout << "Printing set:\n";
    std::for_each(book_set.begin(), book_set.end(), [](const Book& i){ 
        std::cout << i.name << ';';
        auto as = i.authors.Get();
        auto end = as.end();
        end--;
        std::for_each(as.begin(), end, [](const Author& i){ std::cout << i.surname << ' ' << i.name << ' ' << i.dadname << ','; });
        Author const last = *(end);
        std::cout << last.surname << ' ' << last.name << ' ' << last.dadname;
        std::cout << ';';
        std::cout << i.year << ';';
        std::cout << i.UDK;
        std::cout << '\n';
    });
}

int main() {
    std::ifstream in("in.txt");
    if (!in) { std::cout << "Unable to open in.txt"; return 1; }
    Library lib;
    std::cout << "DEBUG\t" << "creating library\n";
    while (in) {
        Book b;
        std::cout << "DEBUG\t" << "creating book\n";
        if (!std::getline(in, b.name, ';'))
        { break; }
        std::stringstream ssa(GetNextItem(in));
        if (ssa.str().empty()) { break; }
        for (std::string temp; std::getline(ssa, temp, ',');) {
            std::cout << "DEBUG\t" << "author " << temp << '\n';
            std::stringstream ss(temp);
            Author a;
            ss >> a.surname >> a.name >> a.dadname;
            b.authors.Add(a);
        }
        // std::cout << "DEBUG\t" << GetNextItem(in);
        b.year = std::stoul(GetNextItem(in));
        // b.UDK = std::stoi(GetNextItem(in));
        in >> b.UDK;
        char c = 0;
        in >> std::noskipws >> c >> std::skipws;
        lib.AddBook(b);
    }
    Book b{"1984", .UDK = 666, .year = 1984};
    b.authors.Add({"Jeorge", "Ourel", "Ivanovich"});
    Author const a{ "Pinda", "Pi", "Pika" };
    b.authors.Add(a);
    PrintLib(lib);
    lib.AddBook(b);
    auto j = lib.SearchBooks("1984");
    auto ja = lib.SearchBooks(a);
    PrintLib(lib);
    lib.DeleteBook(b);
    PrintLib(lib);
    b.authors.Delete(a);
    lib.AddBook(b);
    PrintLib(lib);
    std::cout << "find books:\n";
    std::cout << j.begin()->name << '\n';
    std::cout << ja.begin()-> name << '\n';
    
    return 0;
}
