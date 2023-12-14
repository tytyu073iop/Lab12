#include "library.h"
#include <algorithm>
#include <functional>

std::set<Book, Library::CompBook> Library::Get() const {
    return books_;
}

bool Author::operator==(const Author& l) const {
    return std::tie(l.surname, l.name, l.dadname) == std::tie(surname, name, dadname);
}

bool Book::AuthorList::AuthorLess::operator()(const Author& l, const Author& r) {
    return std::tie(l.surname, l.name, l.dadname) < std::tie(r.surname, r.name, r.dadname);
}

bool Library::CompBook::operator()(const Book &l, const Book &r) {
    return l.name < r.name;
}

bool Book::operator==(const Book &r) const {
    return UDK == r.UDK;
}

std::set<Author, Book::AuthorList::AuthorLess> Book::AuthorList::Get() const {
    return authors_;
}

void Book::AuthorList::Add(const Author &a) {
    authors_.insert(a);
}

void Book::AuthorList::Delete(const Author &a) {
    authors_.erase(a); //?
}

bool Book::AuthorList::Contains(const Author &a) const {
    return std::any_of(authors_.begin(), authors_.end(), [a](auto && p_h1) { return a == p_h1; });
}

void Library::AddBook(const Book &b) {
    books_.insert(b);
}

void Library::DeleteBook(const Book &b) {
    books_.erase(b);
}

std::set<Book, Library::CompBook> Library::SearchBooks(std::string name) const {

    std::vector result(books_.begin(), books_.end());
    auto end = std::copy_if(books_.begin(), books_.end(), result.begin(), [&name](const Book& i) { return i.name == name; });
    std::set<Book, CompBook> a(result.begin(), end);
    return a;
}

std::set<Book, Library::CompBook> Library::SearchBooks(const Author& a) const {
    std::vector result(books_.begin(), books_.end());
    auto end = std::copy_if(books_.begin(), books_.end(), result.begin(), [a](const Book& i){ return i.authors.Contains(a); });
    std::set<Book, CompBook> b(result.begin(), end);
    return b;
}
