
#include <iostream>

#include "printing.h"

std::string* getTableHLine() {
    std::string *result = new std::string(LINE_SIZE, '-');
    std::cout << result;
    return result;
}


