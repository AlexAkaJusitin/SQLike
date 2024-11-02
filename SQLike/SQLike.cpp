#include <iostream>
#include "SQLikeHeader.h"

int main() {
    Data dataInt(42);
    Data dataDouble(3.14);
    Data dataConstStr("Constant String");
    Data dataDynamicStr("Dynamic String", 20);

    dataInt.print();
    dataDouble.print();
    dataConstStr.print();
    dataDynamicStr.print();

    Data copy1 = dataInt;
    Data copy2 = dataDouble;
    Data copy3 = dataConstStr;
    Data copy4 = dataDynamicStr;

    copy1.print();
    copy2.print();
    copy3.print();
    copy4.print();

    // Destructor called automatically for each Data instance
}
