#pragma once

#include <string>
#include "Task.h"

namespace PriorityUtils {

// Priority → string
std::string toString(Priority priority);

// string → Priority
Priority fromString(const std::string& text);

}