#include <iostream>
#include <sstream>
#include <string>

class Base {
public:
    static int live;
    Base() { ++live; }
    virtual ~Base() { --live; }
    virtual void myname() { std::cout << "This is class Base\n"; }
};
int Base::live = 0;

class DerA : virtual public Base {
public:
    void myname() override { std::cout << "This is class DerA\n"; }
};
class DerB : virtual public Base {
public:
    void myname() override { std::cout << "This is class DerB\n"; }
};
class DerAB : public DerA, public DerB {
public:
    void myname() override { std::cout << "This is class DerAB\n"; }
};

// Capture the actual virtual call, so checks verify the text being printed.
bool printsName(Base& object, const std::string& expected) {
    std::ostringstream captured;
    std::streambuf* previous = std::cout.rdbuf(captured.rdbuf());
    object.myname();
    std::cout.rdbuf(previous);
    return captured.str() == "This is class " + expected + "\n";
}

int main() {
    bool ok = true;
    {
        Base base;
        DerA a;
        DerB b;
        DerAB ab;
        std::cout << "Automatic objects:\n";
        base.myname(); a.myname(); b.myname(); ab.myname();
        ok = printsName(base,"Base") && printsName(a,"DerA")
          && printsName(b,"DerB") && printsName(ab,"DerAB");
        Base* viaA = static_cast<DerA*>(&ab);
        Base* viaB = static_cast<DerB*>(&ab);
        const bool sharedBase = viaA == viaB;
        std::cout << "Shared Base subobject: " << (sharedBase ? "yes" : "no") << '\n';
        ok = ok && sharedBase && Base::live == 4;

        Base* objects[4] = {new Base, new DerA, new DerB, new DerAB};
        const char* names[4] = {"Base", "DerA", "DerB", "DerAB"};
        ok = ok && Base::live == 8;
        std::cout << "Dynamic objects through Base*:\n";
        for (int i = 0; i < 4; ++i) {
            objects[i]->myname();
            ok = printsName(*objects[i],names[i]) && ok;
        }
        for (Base*& object : objects) { delete object; object = nullptr; }
        const bool deleted = Base::live == 4;
        std::cout << "Dynamic objects deleted: " << (deleted ? "yes" : "no") << '\n';
        ok = ok && deleted;
    }
    ok = ok && Base::live == 0;
    std::cout << "Live objects after scope: " << Base::live << '\n';
    std::cout << "Self-checks: " << (ok ? "PASS" : "FAIL") << '\n';
    return ok ? 0 : 1;
}
