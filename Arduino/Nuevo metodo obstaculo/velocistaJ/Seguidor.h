#include <Arduino.h>

//#define nSensors 6//----------------------------------------------------------------OJO
#define nSensors 8//----------------------------------------------------------------OJO

#define desired_position (nSensors - 1)*500

#define baud_rate_Serial 9600
#define baud_rate_Bluetooth 115200

#define pwmM1_pin 10
#define pwmM2_pin 11

#define pwm_min 0
//#define pwm_max 70
//#define pwm_ABS 80
//#define pwm_base 35
#define pwm_max 110
#define pwm_ABS 119
#define pwm_base 73
//ADDED
#define pwm_curva 80
#define giro_loco 0.23

#define freno_Curva 0

#define direction_forward_M1_pin 8
#define direction_backward_M1_pin 7
#define direction_forward_M2_pin 6
#define direction_backward_M2_pin 5

#define tiempo_giro 300
#define pwm_giro_recta 50
#define tiempo_recta 400

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
    int pwmM1, pwmM2, PWM_MIN,PWM_MAX, PWM_ABS, PWM_BASE, PWM_ANY_CURVA, FRENO_CURVA;

    int summatory_PWMM1, summatory_PWMM2, ultima_curva;

    bool forward_M1, backward_M1, forward_M2, backward_M2;
    int delay1,delay2, delay_o1,delay_o2,delay_o3,delay_o4;
    float giro_loco_porc, giro_loco_porc2;

    float tolerancia_dinamica;

    long position_encoder_M1, position_encoder_antes_M1;
    long position_encoder_M2, position_encoder_antes_M2;

    unsigned int *sensors_values, line_position;

    double frequency_M1, frequency_M2, frequency_error_M1, frequency_error_M2;
    double v_angular_M1, v_angular_M2, v_angular_M1_antes, v_angular_M2_antes, a_angular_M1, a_angular_M2;

    double k_P, k_I, k_D;
    double proportional, suma_integral, integral, derivative, sumaPID;
    double error, error_antes;

    long loop_time, before_time, actual_time, encoders_time, difference_time, summatory_time;

    bool infrarred_active, distance_active, robot_active;

    bool in_obstaculo;
    
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


    bool comprobar_Sensores_obstaculo();
};
