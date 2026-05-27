
#include <iostream>

#include "ExternalPort.h"
#include "../utils/printing.h"

std::string *ExternalPort::printTableHLine() {
    std::string *result = getTableHLine();
    std::cout << result;
    return result;
}
