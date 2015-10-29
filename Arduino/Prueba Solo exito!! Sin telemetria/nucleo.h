#include <Arduino.h>
#include <QTRSensors.h>
/**
  *@file nucleo.h
  *@brief Libreria para el control de un velocista
  *@author Gerardo Sánchez
*/
#ifndef ROBOT_NUCLEO_H_
#define ROBOT_NUCLEO_H_

/* Motor1 */
//pwm
#define pin_pwm_m1 3
//input1
#define pin_in1 6
//input2
#define pin_in2 7
/* Motor2 */
//
#define pin_pwm_m2 10
//inpu3
#define pin_in3 4
//inpu4
#define pin_in4 5
/* Obstaculo */
#define pin_dig_obs 8

/* Frecuencia de comunicacion serial */
#define baudios 9600
#define baudRate_const_bluetooth 9600

#define num_sensores 8
#define muestras_sensor 4


/*PINES PARA CAMBIAR LA DIRECCION DE LOS MOTORES CON EL CONTROLADOR*/
#define direccion_forward_M1 10
#define direccion_backward_M1 9

#define direccion_forward_M2 5
#define direccion_backward_M2 4

/*PIN DEL STANDBY DE LOS MOTORES*/
#define pin_STANDBY 8

//pin del led de control
#define pin_led 13

QTRSensorsAnalog qtra((unsigned char[]){0,1,2,3,4,5,6,7},num_sensores,muestras_sensor);
unsigned valores_sensor[num_sensores];

namespace robot{
  class nucleo{
            private:
              /* Configuracion */
              int vel_min;
              int vel_max;
              int vel_base;
              int vel_fre;
              int tim_fre;
              float k_pro;
              float k_der;
              float k_int;
              int centro;
              /* Dinamicas */
              int vel_mot1;
              int vel_mot2;
              int pos_linea;
              int error;
              int err_ant;

              double frecuencia_M1;double frecuencia_M2;
              double errorFrecuenciaM1, errorFrecuenciaM2;
              double v_angularM1, v_angularM2;
              double v_angularM1_anterior, v_angularM2_anterior;
              double a_angularM1, a_angularM2;

              /*PID*/
              double proportional;
              double integral;
              double derivative;
              double sumaPID;
              long tiempo_ciclo;
              long tiempo_antes;
              long tiempo_actual;
              long tiempo_encoders;

              /*comunicacion*/
              bool activo;
              bool infrarrojos_activos;
              bool distancia_activo;
            public:
              nucleo(int v_base,int v_min,int v_max,int v_fre,int t_fre,float k_p,float k_d,float k_i,int cen);
              void inicializar();
              void calibrar_sensores();
              void obtener_posicion_linea();
              void automatizar_velocidades();
              void corregir_velocidades();
              void actualizar_velocidades();
              int  encontro_obstaculo();
              void evadir_obstaculo();
              void run();

              void calcular_v_angulares();

              /*metodos comunicacion*/
              void comunicacion_principal();
              void setupCommunication();
              void readComunicacion();
              void writeComunicacion();
              void onOffSensors(bool estado);
              void status();

              void cambiar_sentido_motores(int M1,int M2);
  };
}
#endif
