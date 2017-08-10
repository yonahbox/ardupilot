/*
   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include <AP_HAL/AP_HAL.h>

#include "RPM_External.h"

extern const AP_HAL::HAL& hal;

/* 
   This backend is a shell, and receives its RPM from elsewhere
*/
AP_RPM_External::AP_RPM_External(AP_RPM &_ap_rpm, uint8_t _instance, AP_RPM::RPM_State &_state) :
	AP_RPM_Backend(_ap_rpm, _instance, _state)
{
    instance = _instance;
}

void AP_RPM_External::update(void)
{
    // Do NOTHING during update - someone else will set our frontend state
}

