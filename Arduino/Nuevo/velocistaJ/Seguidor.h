#include <Arduino.h>

#define nSensors 6

#define desired_position (nSensors - 1)*500

#define baud_rate_Serial 9600
#define baud_rate_Bluetooth 115200

#define pwmM1_pin 10
#define pwmM2_pin 11

#define pwm_min 0
#define pwm_max 60
#define pwm_ABS 76
#define pwm_base 43
//ADDED
#define pwm_curva 80

#define freno_Curva 1

#define direction_forward_M1_pin 8
#define direction_backward_M1_pin 7
#define direction_forward_M2_pin 6
#define direction_backward_M2_pin 5

#define bypass_time_encoders 100

#define stby_pin 4

#define distance_sensor_pin 13

class Seguidor{
    /*Variables Agregadas*/

    //long rev = 0;
    //double frecuencia;

    /*long t_inicio;
    long t_anterior;
    long t_actual;
    long dif_tiempo;*/
    //long position1 = -999;
    //long position2 = -999;
    /*Variables Agregadas*/
    int pwmM1, pwmM2, PWM_MIN,PWM_MAX, PWM_ABS, PWM_BASE, FRENO_CURVA;
    bool forward_M1, backward_M1, forward_M2, backward_M2;
    int delay1,delay2, delay_o1,delay_o2,delay_o3,delay_o4;
    float giro_loco_porc;

    float tolerancia_dinamica;

    long position_encoder_M1, position_encoder_antes_M1;
    long position_encoder_M2, position_encoder_antes_M2;

    unsigned int *sensors_values, line_position;

    double frequency_M1, frequency_M2, frequency_error_M1, frequency_error_M2;
    double v_angular_M1, v_angular_M2, v_angular_M1_antes, v_angular_M2_antes, a_angular_M1, a_angular_M2;

    double k_P, k_I, k_D;
    double proportional, suma_integral, integral, derivative, sumaPID;
    double error, error_antes;

    long loop_time, before_time, actual_time, encoders_time, difference_time;

    bool infrarred_active, distance_active, robot_active;
    int distance_sensor;

  public:
    Seguidor(double kp,double ki,double kd);

    void change_Direction(int M1,int M2);
    void PID_processing();
    void adjust_velocities();
    void set_SensorsValues_LinePosition(unsigned int* values, unsigned int lineP);
    void set_Positions_Encoders(long pem1, long pem2);
    void calculate_angular_values();
    void init();//like python
    void emergency_stop();
    void frenoABS(int times);
    void change_Velocity(int vm1,int vm2);

    void communication_principal();
    void communication_Read();
    void communication_Write();
    void onOffSensors(bool estado);
    void status();

    void runing_Seguidor();

    bool isRobot_active();

    //ADDED
    void avoid();
};
