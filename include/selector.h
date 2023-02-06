#ifndef _DEF_SELECTOR_H_
#define _DEF_SELECTOR_H_

#include <string>

namespace deFenestration::selector {

extern int auton;
extern int discs;
void init(int hue, int default_auton, const char** autons);

void destroy();

} // namespace deFenestration::selector

namespace deFenestration {
/* Enable Logger */
const bool debug = true;

/* Enable Flywheel Task */
const bool flywheelEnabled = true;

/* Enable Show Screen */
const bool showScreen = true;

/* program version definition */
const std::string version = "0.0.1";

/* Auton selector configuration constants */
#define AUTONS "Short", "Long", "SAWP", "LAWP", "Sit." // Names of autonomi, up to 10
#define HUE 0                                // Color of theme from 0-359(H part of HSV)
#define DEFAULT 0                            // Default auton selected

inline const char* autons[] = {AUTONS, ""};

inline void init() {
	const char* b[] = {AUTONS, ""};
	selector::init(HUE, DEFAULT, b);
}
}

#endif
