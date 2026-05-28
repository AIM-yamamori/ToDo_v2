#include "PriorityUtils.h"

namespace PriorityUtils {

// Priority → string
std::string toString(Priority priority) {

	switch (priority) {
	case Priority::LOW:
		return "LOW";

	case Priority::MEDIUM:
		return "MEDIUM";

	case Priority::HIGH:
		return "HIGH";

	default:
		return "UNKNOWN";
	}
}

// string → Priority
Priority fromString(const std::string& text) {

	if (text == "LOW") {
		return Priority::LOW;
	}

	if (text == "MEDIUM") {
		return Priority::MEDIUM;
	}

	if (text == "HIGH") {
		return Priority::HIGH;
	}

	return Priority::LOW;
}

}