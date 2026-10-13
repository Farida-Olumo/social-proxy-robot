/* SYDE 263 Final Project Skeleton
    Copyright (C) 2023  Calvin Young

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License version 3 (GNU-GPLv3)
    as published by the Free Software Foundation.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <https://www.gnu.org/licenses/>. 
*/

#include <Servo.h>

Servo gripper; 
Servo ax1;
Servo ax2;

//Variables to store the servo angle associated with the gripper open and closed positions
int gr_open;
int gr_close;

//Variables to store the servo angles associated with the home location
float ax1_home;
float ax2_home;

//Variables to store the servo angles associated with the current location
float ax1_current;
float ax2_current;

void moveTopos(float ax1s, float ax1e, float ax2s, float ax2e) {
  /*
   This function taskes the starting and ending angles for both axes and
   divides them into an even number of steps. This ensures that the movement
   from both motors occurs simultaneously. It also reduces the speed of
   movement to help protect the mechanism. This is a workable but sub-optimal
   way of moving the mechanism.

   ax1s -> Axis 1 Start Position
   ax1e -> Axis 1 End Position
   ax2s -> Axis 2 Start Position
   ax2e -> Axis 2 End Position
   */
  float num_steps_1 = ax1e - ax1s;
  float num_steps_2 = ax2e - ax2s;
  float num_steps = 0;

  if (abs(num_steps_1) >= abs(num_steps_2)){
    num_steps = abs(num_steps_1);
  }
  else {
     num_steps = abs(num_steps_2);
  }
  float inc1 = num_steps_1 / num_steps;
  float inc2 = num_steps_2 / num_steps;
  float stp = 0;
  for(stp = 0; stp<=num_steps; stp += 1){
    ax1_current += inc1;
    ax1.write(ax1_current);
    ax2_current += inc2;
    ax2.write(ax2_current);
    delay(25);
  }
  ax1_current = ax1e;
  ax1.write(ax1_current);
  ax2_current = ax2e;
  ax2.write(ax2_current);
  delay(25);
}
void setup() {
  //What pins are the servos attached to?
  gripper.attach(?); 
  ax1.attach(?);
  ax2.attach(?);

  //Setting the axes to the home position
  ax1_current = ax1_home;
  ax2_current = ax2_home;

  ax1.write(ax1_current);
  ax2.write(ax2_current);
}

void loop() {
  //Write your actuation code here!


}
