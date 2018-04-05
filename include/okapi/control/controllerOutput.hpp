/**
 * @author Ryan Benasutti, WPI
 *
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/.
 */
#ifndef _OKAPI_CONTROLLEROUTPUT_HPP_
#define _OKAPI_CONTROLLEROUTPUT_HPP_

namespace okapi {
class ControllerOutput {
  public:
  /**
   * Writes the value of the controller output. This method might be automatically called in another
   * thread by the controller.
   *
   * @param ivalue the controller's output
   */
  virtual void controllerSet(const double ivalue) = 0;
};
} // namespace okapi

#endif
