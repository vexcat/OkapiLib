/* This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/. */
#ifndef _OKAPI_INTEGRATEDENCODER_HPP_
#define _OKAPI_INTEGRATEDENCODER_HPP_

#include "okapi/device/rotarySensor.hpp"

namespace okapi {
class IntegratedEncoder : public RotarySensor {
  public:
  /**
   * Integrated motor encoder. Uses the encoder inside the V5 motor.
   *
   * @param imotor motor
   */
  IntegratedEncoder(const pros::Motor &imotor);

  /**
   * Get the current sensor value.
   *
   * @return current value, PROS_ERR on fail
   */
  int32_t get() const override;

  /**
   * Reset the sensor to zero.
   *
   * @return 1 on suceess, PROS_ERR on fail
   */
  int32_t reset() const override;

  private:
  const pros::Motor &motor;
};
} // namespace okapi

#endif
