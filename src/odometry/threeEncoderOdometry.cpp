/**
 * @author Ryan Benasutti, WPI
 *
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/.
 */
#include "okapi/odometry/threeEncoderOdometry.hpp"

namespace okapi {
ThreeEncoderOdometryArgs::ThreeEncoderOdometryArgs(std::shared_ptr<SkidSteerModel> imodel,
                                                   const double iscale, const double iturnScale,
                                                   const double imiddleScale)
  : OdometryArgs(imodel, iscale, iturnScale), middleScale(imiddleScale) {
}

ThreeEncoderOdometry::ThreeEncoderOdometry(std::shared_ptr<ThreeEncoderSkidSteerModel> imodel,
                                           const double iscale, const double iturnScale,
                                           const double imiddleScale)
  : Odometry(imodel, iscale, iturnScale), model(imodel), middleScale(imiddleScale) {
}

void ThreeEncoderOdometry::loop() {
  std::uint32_t now = pros::millis();
  std::valarray<std::int32_t> newTicks{0, 0, 0}, tickDiff{0, 0, 0};

  while (true) {
    newTicks = model->getSensorVals();
    tickDiff = newTicks - lastTicks;
    lastTicks = newTicks;

    mm = (static_cast<double>(tickDiff[1] + tickDiff[0]) / 2.0) * scale;

    state.theta += (static_cast<double>(tickDiff[1] - tickDiff[0]) / 2.0) * turnScale;
    if (state.theta > 180)
      state.theta -= 360;
    else if (state.theta < -180)
      state.theta += 360;

    state.x += mm * std::cos(state.theta) + (tickDiff[2] * middleScale) * std::sin(state.theta);
    state.y += mm * std::sin(state.theta) + (tickDiff[2] * middleScale) * std::cos(state.theta);

    pros::c::task_delay_until(&now, 10);
  }
}

void ThreeEncoderOdometry::trampoline(void *context) {
  static_cast<ThreeEncoderOdometry *>(context)->loop();
}
} // namespace okapi