/* [ DC motor control with Locked anti phase PWM type motor driver ]
 *  version : 1.0 (20220422)
 *  Auther  : Kazuki Ito
 */

#undef   ESP32
#include <ros.h> //ESP32 USB serial mode
#define  ESP32
#include <docking_robot/Motor>

/* ==== User setting ==== */
//motor driver property
#define PWM_FREQUENCY  3000     //PWM pulse frequency
#define PWM_RESOLUTION 10       //Duty ratio resolution, 10bit (0~1023)

//ESP32 pin number setting
#define PWM_PIN_A      17         //pin number connect with PWM input channel
#define PWM_PIN_B	X
#define PWM_DIR_A1	X
#define PWM_DIR_A2	X
#define PWM_DIR_B1	X
#define PWM_DIR_B2	X

/* ======================== */

#define MOTOR_0 0           //PWM channel
int motor_cmd[2] = {0,0};          // motor command speed, specified as an integer value from -100 to 

//ros setting
ros::NodeHandle nh;

void messageCb( const docking_robot::Motor& ctrl_msg ){
  motor_cmd[0] = ctrl_msg.motor_1;
  motor_cmd[1] = ctrl_msg.motor_2;
}

//subscriber
  ros::Subscriber<docking_robot::Motor> sub( "cmd_pwm", &messageCb );

void setup() {
  //ros mode
  nh.getHardware()->setBaud( 57600 );
  nh.initNode();
  nh.subscribe( sub );
  //nh.advertise(pub);

  //pin setting
  pinMode( PWM_DIR_A1, OUTPUT );
  pinMode( PWM_DIR_A2, OUTPUT );
  pinMode( PWM_DIR_B1, OUTPUT );
  pinMode( PWM_DIR_B2, OUTPUT );

  //pwm setting
  ledcSetup( MOTOR_A, PWM_FREQUENCY, PWM_RESOLUTION );
  ledcSetup( MOTOR_B, PWM_FREQUENCY, PWM_RESOLUTION );
  ledcAttachPin( PWM_PIN_A, MOTOR_A );
  ledcAttachPin( PWM_PIN_B, MOTOR_B );
  
}

void loop() {
  if ( nh.connected() ){
    //convert motor command to duty ratio
    //motor A
    if(motor_cmd[0]<0){
	//ccw
	digitalWrite( PWM_DIR_A1, HIGH );
	digitalWrite( PWM_DIR_A2, LOW );
        ledcWrite( MOTOR_0, abs(motor_cmd) );
    }else{
	//cw
	digitalWrite( PWM_DIR_A1, LOW );
	digitalWrite( PWM_DIR_A2, HIGH );
        ledcWrite( MOTOR_0, abs(motor_cmd) );
    }

  }else{
    //safety motor drivre off
    digitalWrite( PWM_DIR_A1, LOW );
    digitalWrite( PWM_DIR_A2, LOW );
    digitalWrite( PWM_DIR_B1, LOW );
    digitalWrite( PWM_DIR_B2, LOW );
  }

  nh.spinOnce();
  delay(5);

}
