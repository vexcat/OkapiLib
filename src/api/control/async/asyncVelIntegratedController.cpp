/**
 * @author Ryan Benasutti, WPI
 *
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/.
 */
#include "okapi/api/control/async/asyncVelIntegratedController.hpp"
#include "okapi/api/util/mathUtil.hpp"

namespace okapi {
AsyncVelIntegratedControllerArgs::AsyncVelIntegratedControllerArgs(
  std::shared_ptr<AbstractMotor> imotor)
  : motor(imotor) {
}

AsyncVelIntegratedController::AsyncVelIntegratedController(
  std::shared_ptr<AbstractMotor> imotor, std::unique_ptr<SettledUtil> isettledUtil,
  std::unique_ptr<AbstractRate> irate)
  : motor(imotor), settledUtil(std::move(isettledUtil)), rate(std::move(irate)) {
}

AsyncVelIntegratedController::AsyncVelIntegratedController(
  const AsyncVelIntegratedControllerArgs &iparams, std::unique_ptr<SettledUtil> isettledUtil,
  std::unique_ptr<AbstractRate> irate)
  : motor(iparams.motor), settledUtil(std::move(isettledUtil)), rate(std::move(irate)) {
}

void AsyncVelIntegratedController::setTarget(const double itarget) {
  hasFirstTarget = true;

  if (!controllerIsDisabled) {
    motor->moveVelocity((std::int16_t)itarget);
  }

  lastTarget = itarget;
}

double AsyncVelIntegratedController::getError() const {
  return lastTarget - motor->getActualVelocity();
}

bool AsyncVelIntegratedController::isSettled() {
  return settledUtil->isSettled(getError());
}

void AsyncVelIntegratedController::reset() {
  hasFirstTarget = false;
}

void AsyncVelIntegratedController::flipDisable() {
  controllerIsDisabled = !controllerIsDisabled;
  resumeMovement();
}

void AsyncVelIntegratedController::flipDisable(const bool iisDisabled) {
  controllerIsDisabled = iisDisabled;
  resumeMovement();
}

bool AsyncVelIntegratedController::isDisabled() const {
  return controllerIsDisabled;
}

void AsyncVelIntegratedController::resumeMovement() {
  if (controllerIsDisabled) {
    motor->moveVoltage(0);
  } else {
    if (hasFirstTarget) {
      setTarget(lastTarget);
    }
  }
}

void AsyncVelIntegratedController::waitUntilSettled() {
  while (!settledUtil->isSettled(getError())) {
    rate->delayUntil(motorUpdateRate);
  }
}
} // namespace okapi