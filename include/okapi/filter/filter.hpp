/**
 * @author Ryan Benasutti, WPI
 *
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/.
 */
#ifndef _OKAPI_FILTER_HPP_
#define _OKAPI_FILTER_HPP_

namespace okapi {
class Filter {
  public:
  virtual ~Filter();

  /**
   * Filters a value, like a sensor reading.
   *
   * @param ireading new measurement
   * @return filtered result
   */
  virtual double filter(const double ireading) = 0;

  /**
   * Returns the previous output from filter.
   *
   * @return the previous output from filter
   */
  virtual double getOutput() const = 0;
};
} // namespace okapi

#endif
