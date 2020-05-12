#include "Header.h"

using namespace trek;

Header::Header(uint32_t size) : size(size) { }
uint32_t Header::getSize() const { return size; }
