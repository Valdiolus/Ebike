#include "stm32f4xx.h"
#include "stm32f4xx_gpio.h"
#include "stm32f4xx_usart.h"
#include "string.h"
#include "flash.h"


#ifndef	__Blynk_H
#define __Blynk_H
void Blynk_main(void);
void Blynk_write(int Channel, int Command, int ID, int variable_type, int variable_number, int variant, int quantity, int massiv[50]);
void GSM_DevConfig(void);
void Read_data_from_Blynk_Bluetooth(int data);
void Read_data_from_Blynk_GSM(int data);
void Recognizing_Blynk_Bluetooth_incoming_data(void);
void Recognizing_Blynk_GSM_incoming_data(void);
void Blynk_data_refresh(int CH);
void Blynk_senddata(int Channel, char data);
void Blynk_terminal(void);

extern int i_GSM;
extern int i_GSM_uart_delay;
extern int i_bluetooth;
extern int i_bluetooth_uart_delay;
extern int GSM_restart;
extern char HLS_POWER;
extern char GSM_POWER;
extern char GPS_POWER;
extern char WiFi_POWER;
extern char GSM_POWER_READY;
extern char WiFi_POWER_READY;
extern char GPS_POWER_READY;
extern int Blynk_channel;
extern int Blynk_server_connection;
extern int Blynk_bluetooth_connection;
extern int i_uart2;
extern int i_uart7;
extern char Blynk_GSM_Rx_buffer_1[50];
extern char Blynk_GSM_Rx_buffer_2[50];
extern char Blynk_GSM_Rx_buffer_switcher;
extern char Blynk_BLE_Rx_buffer_1[50];
extern char Blynk_BLE_Rx_buffer_2[50];
extern char Blynk_BLE_Rx_buffer_switcher;
extern int OK_Blynk_Bluetooth;
extern int OK_Blynk_old_Bluetooth;
extern int OK_Blynk_GSM;
extern int OK_Blynk_old_GSM;
extern int Blynk_number_of_data;
extern int Clean_some_buffers;
extern char Blynk_Bluetooth_incoming_ready;
extern char Blynk_GSM_incoming_ready;
extern char Blynk_type_variable[6][50];
extern int Blynk_type_variables_number;
extern char Blynk_variable_temp_buffer[50];
extern int Blynk_incoming_variable_type;
extern int Blynk_incoming_variable_number;
extern int Blynk_button_1;
extern int Blynk_button_2;
extern int Blynk_button_3;
extern int Blynk_button_4;
extern int Blynk_button_5;
extern int Blynk_incoming_number;
extern int Blynk_error_9;
extern int Blynk_responce_command;
extern int Blynk_write_data;
extern int Uakb_high;
extern int Uakb_low;
extern int Ext_temp;
extern int Controller_power;
extern int U_akb_controller;
extern int I_faza_controller;
extern int I_akb_controller;
extern int Wheel_Speed_controller;
extern int GSM_config_i;
extern int WiFi_config_i;
extern int GPS_config_i;
extern int POWER_bluetooth_show;
extern int Charge;
extern int Variables_buffer[50];
extern char a1_prov[10];
extern char a2_prov[2][10];	
extern char tot_len;
extern char HLS_Blynk_pulse;
extern char HLS_Blynk_pulse_state;
extern int Xaxel, Yaxel, Zaxel, Xgyro, Ygyro, Zgyro, Xmagn, Ymagn, Zmagn, Altitude, Pressure, BMP180_tmp;
extern int GPS_Latitude;
extern int GPS_Latitude_div;
extern int GPS_Longitude;
extern int GPS_Longitude_div;
extern int GPS_speed;
extern int GPS_Course;
extern int Proba_GSM;
extern int i_Blynk_250ms;
extern int i_Blynk_500ms;
extern int i_Blynk_1000ms;
extern int i_Blynk_GSM_1000ms;
extern int TEMP_MK;
extern int TEMP_controller_1;
extern int TEMP_controller_2;
extern int TEMP_controller_max;
extern int TEMP_AKB_1;
extern int TEMP_AKB_2;
extern int TEMP_AKB_3;
extern int TEMP_AKB_max;
extern int Brakes_controller;
extern int X1_controller;
extern int X2_controller;
extern int Charger_5_10_controller;
extern int I_akb_MAX;
extern int I_faza_MAX;
extern int Battery_percents;
extern int CTRL_POWER;
extern int MK_power_W;
extern int mileage;
extern int Mode;
extern int ADC_SPI_data;
extern int can_devices_connected[2];

#endif // __Blynk_H
