/**
 * @author Ryan Benasutti, WPI
 *
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/.
 */
#ifndef _OKAPI_ASYNCPOSINTEGRATEDCONTROLLER_HPP_
#define _OKAPI_ASYNCPOSINTEGRATEDCONTROLLER_HPP_

#include "okapi/api/control/async/asyncPositionController.hpp"
#include "okapi/api/control/util/settledUtil.hpp"
#include "okapi/api/device/motor/abstractMotor.hpp"
#include "okapi/api/util/abstractRate.hpp"

namespace okapi {
class AsyncPosIntegratedControllerArgs : public AsyncPositionControllerArgs {
  public:
  explicit AsyncPosIntegratedControllerArgs(std::shared_ptr<AbstractMotor> imotor);

  std::shared_ptr<AbstractMotor> motor;
};

/**
 * Closed-loop controller that uses the V5 motor's onboard control to move. Input units are whatever
 * units the motor is in.
 */
class AsyncPosIntegratedController : public AsyncPositionController {
  public:
  AsyncPosIntegratedController(std::shared_ptr<AbstractMotor> imotor,
                               std::unique_ptr<SettledUtil> isettledUtil,
                               std::unique_ptr<AbstractRate> irate);

  AsyncPosIntegratedController(const AsyncPosIntegratedControllerArgs &iparams,
                               std::unique_ptr<SettledUtil> isettledUtil,
                               std::unique_ptr<AbstractRate> irate);

  /**
   * Sets the target for the controller.
   */
  void setTarget(double itarget) override;

  /**
   * Returns the last error of the controller.
   */
  double getError() const override;

  /**
   * Returns whether the controller has settled at the target. Determining what settling means is
   * implementation-dependent.
   *
   * @return whether the controller is settled
   */
  bool isSettled() override;

  /**
   * Resets the controller so it can start from 0 again properly. Keeps configuration from
   * before.
   */
  void reset() override;

  /**
   * Changes whether the controller is off or on. Turning the controller on after it was off will
   * cause the controller to move to its last set target, unless it was reset in that time.
   */
  void flipDisable() override;

  /**
   * Sets whether the controller is off or on. Turning the controller on after it was off will
   * cause the controller to move to its last set target, unless it was reset in that time.
   *
   * @param iisDisabled whether the controller is disabled
   */
  void flipDisable(bool iisDisabled) override;

  /**
   * Returns whether the controller is currently disabled.
   *
   * @return whether the controller is currently disabled
   */
  bool isDisabled() const override;

  /**
   * Blocks the current task until the controller has settled. Determining what settling means is
   * implementation-dependent.
   */
  void waitUntilSettled() override;

  protected:
  std::shared_ptr<AbstractMotor> motor;
  double lastTarget = 0;
  bool controllerIsDisabled = false;
  bool hasFirstTarget = false;
  std::unique_ptr<SettledUtil> settledUtil;
  std::unique_ptr<AbstractRate> rate;

  /**
   * Resumes moving after the controller is reset. Should not cause movement if the controller is
   * turned off, reset, and turned back on.
   */
  virtual void resumeMovement();
};
} // namespace okapi

#endif