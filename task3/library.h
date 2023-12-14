#include <set>
#include <string>
#include <tuple>

struct Author {
    std::string name, surname, dadname;
    bool operator==(const Author&) const;
};


struct Book {
    private:
        class AuthorList {
            struct AuthorLess {
                bool operator()(const Author&, const Author&);
            };
            std::set<Author, AuthorLess> authors_;
            public:
                std::set<Author, AuthorLess> Get() const;
                void Add(const Author&);
                void Delete(const Author&);
                bool Contains(const Author&) const;
        };
    public:
    using AuthorList = AuthorList;
    std::string name;
    AuthorList authors;
    int UDK;
    size_t year;
    // Book& operator=(const Book& other);
    bool operator==(const Book&) const;
};


class Library {
    struct CompBook{
        bool operator()(const Book& l, const Book& r);
    };
    using BookSet = std::set<Book, CompBook>;
    BookSet books_;
    public:
        void AddBook(const Book&);
        void DeleteBook(const Book&);
        BookSet SearchBooks(std::string name) const;
        BookSet SearchBooks(const Author& author) const;
        BookSet Get() const;
        // void AddAuthor(const Book&, const Author&);
        // void DeleteAuthor(const Book&, const Author&);
};
