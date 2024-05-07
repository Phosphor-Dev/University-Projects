// Libraries 
#include <Pixy2.h>              // Pixy2 Cam Library NOTE:uses digital pins 11, 12, and 13
#include <CytronMotorDriver.h>  // Motor Driver Library 

// Object names 
Pixy2 pixy;                          // Pixy object named "pixy"
CytronMD left_motor(PWM_DIR, 5, 8);  // Cytron motor driver object named "left_motor" | PWM 1 = Pin 5, DIR 1 = Pin 8
CytronMD right_motor(PWM_DIR, 6, 7); // Cytron motor driver object named "right_motor" | PWM 2 = Pin 6, DIR 2 = Pin 7

// Global variables 

// Pixy2
int left_bound = 147;           // Decrease to increase size of forward area.
int right_bound = 167;          // Increase to increase size of forward area.
int frame_width = 315;          // Modify base on horizontal camera resolution.
int frame_height = 207;         // Modify base on vertical camera resolution.
int max_block_width = 200;      // Increase to lower the distance from the flag that the robot will stop at.
int min_block_height = 25;      // Decrease to raise the distance from the flag that the robot will follow from.
int x_center = frame_width/2;   // Horizontal center of the frame is at pixel 157
int y_center = frame_height/2;  // Vertical center of frame is at pixel 203

// Constants
int state = 1;                  // State = 1 -> Pixy Color tracking
int base_speed = 125;           // CHANGE TO BETWEEN 0 AND 255 TO MODIFY SPEED.
int total_left_motor_speed;     // (base_speed - pixy.ccc.blocks[i].m_x - x_center)
int total_right_motor_speed;    // -(base_speed - pixy.ccc.blocks[i].m_x - x_center)

void setup() {
  Serial.print("Initializing Serial COM...\n");    // Serial Monitor Communication 
  Serial.begin(115200);                            // Open serial port with 115200 baud rate.

  Serial.print("Initializing Pixy2 Cam...\n");     // Pixy2 Camera
  pixy.init();                                     // Initialize the Pixy2 cam.
  //pixy.setLamp(1,1)                              // Optional: Turn on pixy lights.

  Serial.print("Initializing Motor Driver...\n");  // Cytron Motor Driver 
  left_motor.setSpeed(0);                          // Stop left motor.
  right_motor.setSpeed(0);                         // Stop right motor.
}

void loop() {                                           // Main Loop
  switch (state) {                                      // Output state to serial port.
    case 1:                                             // Color Detection Case
      Serial.print("Entering Color Detection Mode\n");  // Output state to serial port.
      color_detection();                                // Enter color detection.
      break;

    default:                                            // Default Case
    Serial.print("Entering Default Mode\n");            // Output state to serial port.
      move_stop();                                      // Stop motors.
      break; 
  }
}

void color_detection() {  // Color Detection
  move_stop();            // Stop motors.
  pixy.ccc.getBlocks();   // Poll for blocks.
  if (pixy.ccc.numBlocks) {            // Check if blocks are detected
    Serial.print("Blocks Detected\n"); // Output state to serial port.
    for (int i=0; i<pixy.ccc.numBlocks; i++) {  // Loop for each block detected.
      while (pixy.ccc.blocks[i].m_signature == 1               // Loop while block of specified color is detected,
          && pixy.ccc.blocks[i].m_height >= min_block_height   // block is not too far away,
          && pixy.ccc.blocks[i].m_width <= max_block_width) {  // and block is not too close.
        if (pixy.ccc.blocks[i].m_x <= right_bound && pixy.ccc.blocks[i].m_x >= left_bound){                 // Block Centered Case
          Serial.print("FORWARD\n");                                                                        // Output state to serial port.
          total_left_motor_speed = constrain((base_speed - pixy.ccc.blocks[i].m_x - x_center),-255,255);    // Calculate left motor speed.
          total_right_motor_speed = constrain(-(base_speed - pixy.ccc.blocks[i].m_x - x_center),-255,255);  // Calculate right motor speed.
          move_forward(total_left_motor_speed, total_right_motor_speed);                                    // Move forward at given speed.
          pixy.ccc.getBlocks();                                                                             // Update detected blocks to see if exit condition is met.
        } else if (pixy.ccc.blocks[i].m_x <= left_bound && pixy.ccc.blocks[i].m_x != 0){  // Block Left of Center Case
          while(pixy.ccc.blocks[i].m_x <= left_bound && pixy.ccc.blocks[i].m_x != 0){     // Turn to the left while block is not centered.
            Serial.print("LEFT\n");                                                       // Output state to serial port.
            move_left();                                                                  // Turn left in place.
            pixy.ccc.getBlocks();                                                         // Update detected blocks to see if exit condition is met.
          }
        } else if (pixy.ccc.blocks[i].m_x >= right_bound) {  // Block Right of Center Case
          while (pixy.ccc.blocks[i].m_x >= right_bound) {    // Turn to the right while block is not centered.
            Serial.print("RIGHT\n");                         // Output state to serial port.
            move_right();                                    // Turn right in place.
            pixy.ccc.getBlocks();                            // Update detected blocks to see if exit condition is met.
          } 
        } else {        // Saftey Stop Case
          move_stop();  // Stop motors.
        }
      }
      break;  // Stop check all blocks.
    }
  }
}

void move_stop() {          // Stop Motors
  left_motor.setSpeed(0);   // Stop left motor.
  right_motor.setSpeed(0);  // Stop right motor.
}

void move_left() {                      // Turn Left
  left_motor.setSpeed(base_speed*-1);   // Enable motor at base speed.
  right_motor.setSpeed(base_speed*-1);  // Enable motor at base speed.
}

void move_right() {                  // Turn Right
  left_motor.setSpeed(base_speed);   // Enable motor at base speed.
  right_motor.setSpeed(base_speed);  // Enable motor at base speed.
}

void move_forward(int l_motor_speed, int r_motor_speed) {  // Move Forward
  left_motor.setSpeed(l_motor_speed);                      // Set to given left motor speed.
  right_motor.setSpeed(r_motor_speed);                     // Set to given right motor speed.
}


