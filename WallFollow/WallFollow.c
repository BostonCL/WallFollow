/*
 * File:          WallFollow.c
 * Date:9/30/22
 * Description:Follow the walls
 * Author:Boston Learned
 * Modifications:
 */

/*
 * You may need to add include files like <webots/distance_sensor.h> or
 * <webots/motor.h>, etc.
 */
#include <webots/robot.h>
#include <webots/motor.h>
#include <webots/distance_sensor.h>
#include <stdio.h>
#include <webots/pen.h>

void wb_pen_write(WbDeviceTag tag, bool write);

/*
 * You may want to add macros here.
 */
#define TIME_STEP 64
#define SPEED 6.28
/*
 * This is the main program.
 * The arguments of the main function can be specified by the
 * "controllerArgs" field of the Robot node
 */
int main(int argc, char **argv) {
  /* necessary to initialize webots stuff */
  wb_robot_init();
  
  

  /*
   * You should declare here WbDeviceTag variables for storing
   * robot devices like this:
   *  WbDeviceTag my_sensor = wb_robot_get_device("my_sensor");
   *  WbDeviceTag my_actuator = wb_robot_get_device("my_actuator");
   */
   //TAG Device left motor, right motor, and pen.
    WbDeviceTag left = wb_robot_get_device("left wheel motor");
    WbDeviceTag right = wb_robot_get_device("right wheel motor");
    WbDeviceTag pen = wb_robot_get_device("pen");

    //pen color
    wb_pen_set_ink_color(pen,0xF01010,0.9);

    //pen 
    wb_pen_write(pen,1);
    
    wb_motor_set_position(left, INFINITY);
    wb_motor_set_position(right, INFINITY);

    wb_motor_set_velocity(left, 0.0);
    wb_motor_set_velocity(right, 0.0);
    
    //Read sensors
    WbDeviceTag prox_sensors[8];
    char prox_sensor_name[50];
    for (int ind =0; ind < 8; ++ind)
    {
      sprintf(prox_sensor_name, "ps%d", ind);
      prox_sensors[ind] = wb_robot_get_device(prox_sensor_name);
      wb_distance_sensor_enable(prox_sensors[ind], TIME_STEP);

    }
  /* main loop
   * Perform simulation steps of TIME_STEP milliseconds
   * and leave the loop when the simulation is over
   */
   
   double left_speed = SPEED;
   double right_speed = SPEED;


  while (wb_robot_step(TIME_STEP) != -1) {
    /*
     * Read the sensors :
     * Enter here functions to read sensor data, like:
     *  double val = wb_distance_sensor_get_value(my_sensor);
     */
     bool left_wall = wb_distance_sensor_get_value(prox_sensors[5]) > 80;
     bool left_corner = wb_distance_sensor_get_value(prox_sensors[6]) > 80;
     bool front_wall = wb_distance_sensor_get_value(prox_sensors[7]) > 80;


    /* Process sensor data here */
    
    if (front_wall == true)
    {
      left_speed = SPEED;
      right_speed = -SPEED;
     }
     else
     {
       if(left_wall == true)
       {
         left_speed = SPEED;
         right_speed = SPEED;
       }
       
       else
       {
         left_speed = SPEED/6;
         right_speed = SPEED;
       }
       
       if(left_corner == true)
       {
         left_speed = SPEED;
         right_speed = SPEED/6;
       }
       
      }

    /*
     * Enter here functions to send actuator commands, like:
     * wb_motor_set_position(my_actuator, 10.0);
     */
     wb_motor_set_velocity(left, left_speed);
     wb_motor_set_velocity(right, right_speed);
  };

  /* Enter your cleanup code here */

  /* This is necessary to cleanup webots resources */
  wb_robot_cleanup();

  return 0;
}
