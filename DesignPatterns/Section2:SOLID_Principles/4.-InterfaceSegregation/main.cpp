
/*
Interface Segregation Principle:

Avoid large interfaces that force implementers to implement functions which they do not use.
Instead, separate interfaces son when implementing them we know we will only implement functions that we will need.
*/
using namespace std;

struct Document;

// We want to define an interface for scanning, printing and faxing a document

// Bad example, put all these operations in one interface
/*
struct IMachine
{
    virtual void print(Document& doc) = 0;
    virtual void scan(Document& doc) = 0;
    virtual void fax(Document& doc) = 0;

};

struct MFP : IMachine // Multi-Function Printer
{
    void print(Document& doc) override {
        //ok
    }

    void scan(Document& doc) override {
        //ok
    }

    void fax(Document &doc) override {
        //ok
    }
};

// What if we want to implement just a printer or a scanner?


struct Scanner : IMachine
{
    void print(Document& doc) override {
        //not useful - We usually solve it by throwing an exception or do a no-op: not ok
    }

    void scan(Document& doc) override {
        //ok
    }

    void fax(Document &doc) override {
        //not useful - We usually solve it by throwing an exception or do a no-op: not ok
    }
};
*/

// We need to segregate the interface

struct IPrinter
{
    virtual void print(Document& doc) = 0;
};

struct IScanner
{
    virtual void scan(Document& doc) = 0;
};

struct IFaxMachine
{
    virtual void fax(Document& doc) = 0;
};

struct Scanner : IScanner
{
    void scan(Document& doc) {
        //ok
    }
};

struct Printer : IPrinter
{
    void print(Document& doc) override {
        //ok
    }
};

struct IMachine : IPrinter, IScanner {};

struct Machine : IMachine
{
    // Decorator pattern*

    IPrinter& printer;
    IScanner& scanner;

    Machine(IPrinter &printer, IScanner &scanner) : printer(printer), scanner(scanner) {}

    void print(Document& doc) override {
        //ok
        printer.print(doc);
    }

    void scan(Document& doc) override {
        //ok
        scanner.scan(doc);
    }
};

int main() {

    return 0;
}