/*
  Copyright (c) 2019-2023 7701F

  This software is provided 'as-is', without any express or implied warranty. In no event
  will the authors be held liable for any damages arising from the use of this software.

  Permission is granted to anyone to use this software for any purpose, including
  commercial applications, and to alter it and redistribute it freely, subject to the
  following restrictions:

  1. The origin of this software must not be misrepresented; you must not claim that you
  wrote the original software. If you use this software in a product, an acknowledgment
  (see the following) in the product documentation is required.

  Portions Copyright (c) 2019-2023 7701F

  2. Altered source versions must be plainly marked as such, and must not be
  misrepresented as being the original software.

  3. This notice may not be removed or altered from any source distribution.
*/
#ifndef _7701F_SETTINGS_H_
#define _7701F_SETTINGS_H_
#include <string>

namespace deFenestration {

/* Enable Logger */
const bool debug = true;

/* Enable Flywheel Task */
const bool flywheelEnabled = true;

/* Enable Show Screen */
const bool showScreen = true;

/* program version definition */
const std::string version = "0.0.1";

} // namespace deFenestration
#endif // _7701F_SETTINGS_H_