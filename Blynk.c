#include "Blynk.h"

//611e3000ae04459f8d17caf49776c83a
char auth1[32]={"611e3000ae04459f8d17caf49776c83a"};//Bluetooth
char auth2[32]={"f5a58535a53744b9a640a81f16b740f3"};//GSM
//char auth[32]={"b450813c6d0e47588a2899af834c68c0"};//bluetooth proba
//char auth[32]={"c0ba9baca2be4f59872dd82b530d0c08"};//GSM proba
char apn1[30]={0x1A,0x1D,00,01,19,01,00,01,00,77,77,77,0x2E,61,62,0x2E,0x6B,79,69,76,73,74,61,72,0x2E,0x6E,65,74,0x6E,97};
char apn2[30]={0x1A,0x1D,00,01,23,01,00,01,00,77,77,77,0x2E,61,62,0x2E,0x6B,79,69,76,73,74,61,72,0x2E,0x6E,65,74,0xCA,47};
//#define AUTHOR "611e3000ae04459f8d17caf49776c83a"


void Blynk_main(void)
{
	//GSM=================================>
	if(GSM_POWER==1)
	{
		if(Blynk_server_connection==0)
		{
			
			if(OK_Blynk_GSM>OK_Blynk_old_GSM)
			{
				Blynk_server_connection=1;
				Blynk_data_refresh(1);
			}
			else
			{
				if(i_GSM>1000)
				{
					Blynk_write(1,22,2,0,0,0,0,0);//LOGIN
					i_GSM=0;
				}
			}
		}
		else
		{
			if(i_GSM>5000)//Ping 5 sec delay
			{
				if(OK_Blynk_old_GSM==OK_Blynk_GSM)
				{
					Blynk_server_connection=0;//RESTART???
					OK_Blynk_GSM=0;
					OK_Blynk_old_GSM=0;
					GSM_config_i=0;
					GSM_restart++;
				}
				else
				{
					OK_Blynk_old_GSM=OK_Blynk_GSM;
					Blynk_write(1,6,6,0,0,0,0,0);//PING
					i_GSM=0;
				}
			}
			
			if(i_Blynk_GSM_1000ms>1000)
			{
				i_Blynk_GSM_1000ms=0;
				Variables_buffer[0]=Uakb_high;
				Blynk_write(1,20,3,1,3,48,1,Variables_buffer);//U bat high	
				Variables_buffer[0]=Uakb_low;
				Blynk_write(1,20,4,1,4,48,1,Variables_buffer);//U bat low		
				Variables_buffer[0]=OK_Blynk_GSM;
				Blynk_write(1,20,2,1,2,48,1,Variables_buffer);//OK_GSM
				Variables_buffer[0]=U_akb_controller;
				Blynk_write(1,20,35,1,35,48,1,Variables_buffer);//U_battery
				Variables_buffer[0]=I_akb_controller;
				Blynk_write(1,20,36,1,36,48,1,Variables_buffer);//I_akb		
			}
		}
	}
	//BLE=================================>
	if(Blynk_bluetooth_connection==0)
	{
		if(i_bluetooth>1000)
		{
			Blynk_write(0,21,2,0,0,0,0,0);//LOGIN
			//Blynk_write(0,6,6,0,0,0,0,0);//PING		
			i_bluetooth=0;
		}
		if(OK_Blynk_Bluetooth>OK_Blynk_old_Bluetooth)
		{
			Blynk_bluetooth_connection=1;
			Blynk_data_refresh(0);
		}
	}
	else
	{
		if(i_bluetooth>1000)
		{
			if(OK_Blynk_Bluetooth==OK_Blynk_old_Bluetooth)
			{
				Blynk_bluetooth_connection=0;
				OK_Blynk_old_Bluetooth=0;
				OK_Blynk_Bluetooth=0;
			}
			else
			{
				OK_Blynk_old_Bluetooth=OK_Blynk_Bluetooth;
				//Blynk_write(0,21,2,0,0,0,0,0);//LOGIN
				Blynk_write(0,6,6,0,0,0,0,0);//PING			
				i_bluetooth=0;				
			}
		}
		if((i_Blynk_250ms>250)&&(Blynk_bluetooth_connection==1))
		{
			if(can_devices_connected[0]==1)
			{
				Variables_buffer[0]=U_akb_controller;
				Blynk_write(0,20,35,1,35,48,1,Variables_buffer);//U_battery
				Variables_buffer[0]=I_akb_controller;
				Blynk_write(0,20,36,1,36,48,1,Variables_buffer);//I_akb			
				Variables_buffer[0]=MK_power_W;
				Blynk_write(0,20,41,1,41,48,1,Variables_buffer);//POWER
				Variables_buffer[0]=I_akb_controller/1000;
				Blynk_write(0,20,45,1,45,48,1,Variables_buffer);//I_akb_graph
			}
			else
			{
				Variables_buffer[0]=0;
				Blynk_write(0,20,35,1,35,48,1,Variables_buffer);//U_battery
				Variables_buffer[0]=0;
				Blynk_write(0,20,36,1,36,48,1,Variables_buffer);//I_akb					
				Variables_buffer[0]=0;
				Blynk_write(0,20,41,1,41,48,1,Variables_buffer);//POWER			
				Variables_buffer[0]=0;
				Blynk_write(0,20,45,1,45,48,1,Variables_buffer);//I_akb_graph				
			}
			i_Blynk_250ms=0;
		}		
		if((i_Blynk_500ms>500)&&(Blynk_bluetooth_connection==1))
		{
			i_Blynk_500ms=0;
			Variables_buffer[0]=Uakb_high;
			Blynk_write(0,20,3,1,3,48,1,Variables_buffer);//U bat high	
			Variables_buffer[0]=Uakb_low;
			Blynk_write(0,20,4,1,4,48,1,Variables_buffer);//U bat low		
			Variables_buffer[0]=Battery_percents;
			Blynk_write(0,20,40,1,40,48,1,Variables_buffer);//Battery %	
			Variables_buffer[0]=mileage;
			Blynk_write(0,20,42,1,42,48,1,Variables_buffer);//mileage
			Variables_buffer[0]=ADC_SPI_data;
			Blynk_write(0,20,14,1,14,48,1,Variables_buffer);//ACC	
		}		
		if((i_Blynk_1000ms>1000)&&(Blynk_bluetooth_connection==1))
		{
			i_Blynk_1000ms=0;
			Variables_buffer[0]=OK_Blynk_Bluetooth;
			Blynk_write(0,20,13,1,13,48,1,Variables_buffer);//OK_BLE
			Variables_buffer[0]=Ext_temp;
			Blynk_write(0,20,12,1,12,48,1,Variables_buffer);//HLS temp
			Variables_buffer[0]=TEMP_MK;
			Blynk_write(0,20,30,1,30,48,1,Variables_buffer);//TEMP_MK
			Variables_buffer[0]=TEMP_controller_max;
			Blynk_write(0,20,31,1,31,48,1,Variables_buffer);//TEMP_controller_max
			Variables_buffer[0]=TEMP_AKB_max;
			Blynk_write(0,20,32,1,32,48,1,Variables_buffer);//TEMP_Battery_max
			//LCD
			Variables_buffer[0]=127;
			//Variables_buffer[1]=0;
			//Variables_buffer[2]=127;
			Blynk_write(0,20,43,1,43,0,1,Variables_buffer);//TEMP_Battery_max			
			//LED
			switch (HLS_Blynk_pulse)
				{
					case 1 :
					{
						//Variables_buffer[0]=255;
						//Blynk_write(0,20,0,1,0,0,1,Variables_buffer);//LED ON		
					}
					break;
					case 0 :
					{
						//Variables_buffer[0]=0;//write 0x30...0x39 - log '0' another - log '1'
						//Blynk_write(0,20,0,1,0,0,1,Variables_buffer);//LED OFF
					}
					break;
				}
			//Blynk_terminal();			
		}		
	}
	//(int Channel, int Command, int ID, int variable_type, int variable_number, int variant, int quantity, int massiv[50])
	//&&(Blynk_server_connection==1)
		/*
		Channel					- 0 - Bluetooth, 1 - GSM
		Command 				- like 20 (hardaware)
		ID 							- back the ID that was sended by android, or make own ID
		variable type 	- vr, vw, dr, dw, ar, aw
		variable number - number of the output virtual pin
		variant 				- 0 or 48 (hex or ASCII)
		quantity 				- quantity of output variables
		massiv 					- massiv of the output variables
		*/	

	//Blynk LEDs
	if((HLS_Blynk_pulse!=HLS_Blynk_pulse_state)&&(Blynk_bluetooth_connection==1))
	{
			switch (HLS_Blynk_pulse)
				{
					case 1 :
					{
						Variables_buffer[0]=148;
						Blynk_write(0,20,0,1,0,0,1,Variables_buffer);//LED ON		
					}
					break;
					case 0 :
					{
						Variables_buffer[0]=48;//write 0x30...0x39 - log '0' another - log '1'
						Blynk_write(0,20,0,1,0,0,1,Variables_buffer);//LED OFF
					}
					break;
				}
		HLS_Blynk_pulse_state=HLS_Blynk_pulse;
	}
}

void Blynk_data_refresh(int CH)
{
	Variables_buffer[0]=CTRL_POWER;
	Blynk_write(CH,20,1,1,1,48,1,Variables_buffer);//Controller_power
	Variables_buffer[0]=GSM_POWER;
	Blynk_write(CH,20,5,1,5,48,1,Variables_buffer);//GSM_POWER
	Variables_buffer[0]=GPS_POWER;
	Blynk_write(CH,20,6,1,6,48,1,Variables_buffer);//GPS_POWER
	Variables_buffer[0]=WiFi_POWER;
	Blynk_write(CH,20,7,1,7,48,1,Variables_buffer);//WiFi_POWER
	Variables_buffer[0]=Charge;
	Blynk_write(CH,20,8,1,8,48,1,Variables_buffer);//Charge
	Variables_buffer[0]=HLS_POWER;
	Blynk_write(CH,20,9,1,9,48,1,Variables_buffer);//HLS_POWER 
	Variables_buffer[0]=I_akb_MAX;
	Blynk_write(CH,20,33,1,33,48,1,Variables_buffer);//I_akb_MAX
	Variables_buffer[0]=I_faza_MAX;
	Blynk_write(CH,20,34,1,34,48,1,Variables_buffer);//I_faza_MAX
	Variables_buffer[0]=Charger_5_10_controller;
	Blynk_write(CH,20,37,1,37,48,1,Variables_buffer);//Charge 5_10
	Variables_buffer[0]=Mode;
	Blynk_write(CH,20,44,1,44,48,1,Variables_buffer);//Mode_speed
}

void Blynk_terminal(void)
{
	Variables_buffer[0]='P';
	Variables_buffer[1]='I';
	Variables_buffer[2]='N';
	Variables_buffer[3]='G';
	Variables_buffer[4]=0x0D;
	Variables_buffer[5]=0x0A;
	Blynk_write(Blynk_channel,20,20,1,20,0,6,Variables_buffer);//U bat high	
}

void Recognizing_Blynk_Bluetooth_incoming_data(void)//Clear variable temp buffer!!!
{
			switch (Blynk_BLE_Rx_buffer_switcher)
			{
				case 1 :
				{
					int i_temp=5;
					while(Blynk_BLE_Rx_buffer_2[i_temp]!=0)
					{
						Blynk_variable_temp_buffer[i_temp-5]=Blynk_BLE_Rx_buffer_2[i_temp];//check i_temp right!!!
						i_temp++;
					}
					for (int i=0; i<Blynk_type_variables_number; i++)
					{
						if (strcmp(Blynk_type_variable[i],Blynk_variable_temp_buffer)==0)
						{
							Blynk_incoming_variable_type=i;//Found variable before numbers
						}
					}
					i_temp++;//i_temp==8  ==number
					int i_temp_old=i_temp;//i_temp==8  ==number  i_temp_old==8
					while (Blynk_BLE_Rx_buffer_2[i_temp]!=0)
					{
						i_temp++;
					}
					int i_number=0;
					for(int i=i_temp_old; i<i_temp; i++)//i_temp==11  ==0  i_temp_old==8   
					{
						i_number=Blynk_BLE_Rx_buffer_2[i]-48;
						for (int k=i_temp-i-1; k>0; k--)//k==2
						{
							i_number=i_number*10;
						}
						Blynk_incoming_variable_number=Blynk_incoming_variable_number+i_number;
					}
					i_temp++;//i_temp==12
					i_temp_old=i_temp;//i_temp_old==12
					while (Blynk_BLE_Rx_buffer_2[i_temp]!=0)
					{
						i_temp++;
					}
					i_number=0;
					for(int i=i_temp_old; i<i_temp; i++)//i_temp==13  ==0  i_temp_old==12   
					{
						i_number=Blynk_BLE_Rx_buffer_2[i]-48;
						for (int k=i_temp-i-1; k>0; k--)//k==0
						{
							i_number=i_number*10;
						}
						Blynk_incoming_number=Blynk_incoming_number+i_number;
					}
					Blynk_responce_command=Blynk_BLE_Rx_buffer_2[0];
					Clean_some_buffers=122;
				}
				break;
				case 2 :
				{
					int i_temp=5;
					while(Blynk_BLE_Rx_buffer_1[i_temp]!=0)
					{
						Blynk_variable_temp_buffer[i_temp-5]=Blynk_BLE_Rx_buffer_1[i_temp];//check i_temp right!!!
						i_temp++;
					}
					for (int i=0; i<Blynk_type_variables_number; i++)
					{
						if (strcmp(Blynk_type_variable[i],Blynk_variable_temp_buffer)==0)
						{
							Blynk_incoming_variable_type=i;//Found variable before numbers
						}
					}
					i_temp++;//i_temp==8  ==number
					int i_temp_old=i_temp;//i_temp==8  ==number  i_temp_old==8
					while (Blynk_BLE_Rx_buffer_1[i_temp]!=0)
					{
						i_temp++;
					}
					int i_number=0;
					for(int i=i_temp_old; i<i_temp; i++)//i_temp==11  ==0  i_temp_old==8   
					{
						i_number=Blynk_BLE_Rx_buffer_1[i]-48;
						for (int k=i_temp-i-1; k>0; k--)//k==2
						{
							i_number=i_number*10;
						}
						Blynk_incoming_variable_number=Blynk_incoming_variable_number+i_number;
					}
					i_temp++;//i_temp==12
					i_temp_old=i_temp;//i_temp_old==12
					while (Blynk_BLE_Rx_buffer_1[i_temp]!=0)
					{
						i_temp++;
					}
					i_number=0;
					for(int i=i_temp_old; i<i_temp; i++)//i_temp==13  ==0  i_temp_old==12   
					{
						i_number=Blynk_BLE_Rx_buffer_1[i]-48;
						for (int k=i_temp-i-1; k>0; k--)//k==0
						{
							i_number=i_number*10;
						}
						Blynk_incoming_number=Blynk_incoming_number+i_number;
					}	
					Blynk_responce_command=Blynk_BLE_Rx_buffer_1[0];							
					Clean_some_buffers=121;			
				}
				break;
			}		
		//Blynk_channel=0;		
			
		//Recognize data!!! BLE
		switch (Blynk_responce_command)//Hardware or another
		{//(Command, ID, variable_type, variable_number, number)
			case 20 :
			{
				if((Blynk_incoming_variable_type==1)&&(Blynk_incoming_variable_number==1))//Virtual write Controller power
				{
					CTRL_POWER=Blynk_incoming_number;
				}
				if ((Blynk_incoming_variable_type==1)&&(Blynk_incoming_variable_number==5))//GSM PWR
				{
					GSM_POWER_READY=Blynk_incoming_number;
					GSM_config_i=0;
				}
				if ((Blynk_incoming_variable_type==1)&&(Blynk_incoming_variable_number==6))//GPS PWR
				{
					GPS_POWER_READY=Blynk_incoming_number;
					GPS_config_i=0;
				}
				if ((Blynk_incoming_variable_type==1)&&(Blynk_incoming_variable_number==7))//WiFi PWR
				{
					WiFi_POWER_READY=Blynk_incoming_number;
					WiFi_config_i=0;
				}
				if ((Blynk_incoming_variable_type==1)&&(Blynk_incoming_variable_number==8))//Charge
				{
					Charge=Blynk_incoming_number;
				}
				if ((Blynk_incoming_variable_type==1)&&(Blynk_incoming_variable_number==9))//HLS PWR
				{
					HLS_POWER=Blynk_incoming_number;
					if (HLS_POWER==0)
					{
						GPIO_ResetBits(GPIOC, GPIO_Pin_2);
					}
					else
					{
						GPIO_SetBits(GPIOC, GPIO_Pin_2);
					}							
				}
				if ((Blynk_incoming_variable_type==1)&&(Blynk_incoming_variable_number==15))//Refresh
				{
					Blynk_data_refresh(0);
				}
				if ((Blynk_incoming_variable_type==1)&&(Blynk_incoming_variable_number==33))//I_akb_MAX
				{
					I_akb_MAX=Blynk_incoming_number;
				}
				if ((Blynk_incoming_variable_type==1)&&(Blynk_incoming_variable_number==34))//I_faza_MAX
				{
					I_faza_MAX=Blynk_incoming_number;
				}
				if ((Blynk_incoming_variable_type==1)&&(Blynk_incoming_variable_number==37))//Charge 5_10
				{
					Charger_5_10_controller=Blynk_incoming_number;
				}
				if ((Blynk_incoming_variable_type==1)&&(Blynk_incoming_variable_number==44))//Mode_speed
				{
					Mode=Blynk_incoming_number;
				}
			}
			break;
		}
		Blynk_incoming_variable_type=0;
		Blynk_incoming_variable_number=0;
		Blynk_incoming_number=0;
}

void Recognizing_Blynk_GSM_incoming_data(void)//Clear variable temp buffer!!!
{
			switch (Blynk_GSM_Rx_buffer_switcher)
			{
				case 1 :
				{
					int i_temp=5;
					while(Blynk_GSM_Rx_buffer_2[i_temp]!=0)
					{
						Blynk_variable_temp_buffer[i_temp-5]=Blynk_GSM_Rx_buffer_2[i_temp];//check i_temp right!!!
						i_temp++;
					}
					for (int i=0; i<Blynk_type_variables_number; i++)
					{
						if (strcmp(Blynk_type_variable[i],Blynk_variable_temp_buffer)==0)
						{
							Blynk_incoming_variable_type=i;//Found variable before numbers
						}
					}
					i_temp++;//i_temp==8  ==number
					int i_temp_old=i_temp;//i_temp==8  ==number  i_temp_old==8
					while (Blynk_GSM_Rx_buffer_2[i_temp]!=0)
					{
						i_temp++;
					}
					int i_number=0;
					for(int i=i_temp_old; i<i_temp; i++)//i_temp==11  ==0  i_temp_old==8   
					{
						i_number=Blynk_GSM_Rx_buffer_2[i]-48;
						for (int k=i_temp-i-1; k>0; k--)//k==2
						{
							i_number=i_number*10;
						}
						Blynk_incoming_variable_number=Blynk_incoming_variable_number+i_number;
					}
					i_temp++;//i_temp==12
					i_temp_old=i_temp;//i_temp_old==12
					while (Blynk_GSM_Rx_buffer_2[i_temp]!=0)
					{
						i_temp++;
					}
					i_number=0;
					for(int i=i_temp_old; i<i_temp; i++)//i_temp==13  ==0  i_temp_old==12   
					{
						i_number=Blynk_GSM_Rx_buffer_2[i]-48;
						for (int k=i_temp-i-1; k>0; k--)//k==0
						{
							i_number=i_number*10;
						}
						Blynk_incoming_number=Blynk_incoming_number+i_number;
					}
					Blynk_responce_command=Blynk_GSM_Rx_buffer_2[0];
					Clean_some_buffers=22;
				}
				break;
				case 2 :
				{
					int i_temp=5;
					while(Blynk_GSM_Rx_buffer_1[i_temp]!=0)
					{
						Blynk_variable_temp_buffer[i_temp-5]=Blynk_GSM_Rx_buffer_1[i_temp];//check i_temp right!!!
						i_temp++;
					}
					for (int i=0; i<Blynk_type_variables_number; i++)
					{
						if (strcmp(Blynk_type_variable[i],Blynk_variable_temp_buffer)==0)
						{
							Blynk_incoming_variable_type=i;//Found variable before numbers
						}
					}
					i_temp++;//i_temp==8  ==number
					int i_temp_old=i_temp;//i_temp==8  ==number  i_temp_old==8
					while (Blynk_GSM_Rx_buffer_1[i_temp]!=0)
					{
						i_temp++;
					}
					int i_number=0;
					for(int i=i_temp_old; i<i_temp; i++)//i_temp==11  ==0  i_temp_old==8   
					{
						i_number=Blynk_GSM_Rx_buffer_1[i]-48;
						for (int k=i_temp-i-1; k>0; k--)//k==2
						{
							i_number=i_number*10;
						}
						Blynk_incoming_variable_number=Blynk_incoming_variable_number+i_number;
					}
					i_temp++;//i_temp==12
					i_temp_old=i_temp;//i_temp_old==12
					while (Blynk_GSM_Rx_buffer_1[i_temp]!=0)
					{
						i_temp++;
					}
					i_number=0;
					for(int i=i_temp_old; i<i_temp; i++)//i_temp==13  ==0  i_temp_old==12   
					{
						i_number=Blynk_GSM_Rx_buffer_1[i]-48;
						for (int k=i_temp-i-1; k>0; k--)//k==0
						{
							i_number=i_number*10;
						}
						Blynk_incoming_number=Blynk_incoming_number+i_number;
					}	
					Blynk_responce_command=Blynk_GSM_Rx_buffer_1[0];		
					Clean_some_buffers=21;			
				}
				break;		
			//Blynk_channel=1;
			}
		
		//Recognize data!!! GMS
		switch (Blynk_responce_command)//Hardware or another
		{//(Command, ID, variable_type, variable_number, number)
			case 20 :
			{
				if((Blynk_incoming_variable_type==1)&&(Blynk_incoming_variable_number==1))//Virtual write Controller power
				{
					CTRL_POWER=Blynk_incoming_number;
				}
				if ((Blynk_incoming_variable_type==1)&&(Blynk_incoming_variable_number==5))//GSM PWR
				{
					GSM_POWER_READY=Blynk_incoming_number;
					GSM_config_i=0;
				}
				if ((Blynk_incoming_variable_type==1)&&(Blynk_incoming_variable_number==6))//GPS PWR
				{
					GPS_POWER_READY=Blynk_incoming_number;
					GPS_config_i=0;
				}
				if ((Blynk_incoming_variable_type==1)&&(Blynk_incoming_variable_number==7))//WiFi PWR
				{
					WiFi_POWER_READY=Blynk_incoming_number;
					WiFi_config_i=0;
				}
				if ((Blynk_incoming_variable_type==1)&&(Blynk_incoming_variable_number==8))//Charge
				{
					Charge=Blynk_incoming_number;
				}
				if ((Blynk_incoming_variable_type==1)&&(Blynk_incoming_variable_number==9))//HLS PWR
				{
					HLS_POWER=Blynk_incoming_number;
					if (HLS_POWER==0)
					{
						GPIO_ResetBits(GPIOC, GPIO_Pin_2);
					}
					else
					{
						GPIO_SetBits(GPIOC, GPIO_Pin_2);
					}							
				}
				if ((Blynk_incoming_variable_type==1)&&(Blynk_incoming_variable_number==15))//Refresh
				{
					Blynk_data_refresh(1);
				}
			}
			break;
		}
		Blynk_incoming_variable_type=0;
		Blynk_incoming_variable_number=0;
		Blynk_incoming_number=0;
}

void Read_data_from_Blynk_Bluetooth(int data)//separate variables BLE and GSM in interrupts
{
	if(i_uart7==0)
	{
		i_bluetooth_uart_delay=0;
	}
	if((i_uart7>0)&&(i_bluetooth_uart_delay>100))
	{
		i_bluetooth_uart_delay=0;
		i_uart7=0;
	}
	
			switch(Blynk_BLE_Rx_buffer_switcher)//data->buffer
			{
				case 1 :
				{
					Blynk_BLE_Rx_buffer_1[i_uart7]=data;
				}
				break;
				case 2 :
				{
					Blynk_BLE_Rx_buffer_2[i_uart7]=data;
				}
				break;
			}
			if(Blynk_number_of_data>0)//recognizing end of the data string
			{
				Blynk_number_of_data--;
				if(Blynk_number_of_data==0)
				{
					Blynk_Bluetooth_incoming_ready=1;
					i_uart7=-1;
					switch(Blynk_BLE_Rx_buffer_switcher)
					{
						case 1 :
						{
							Blynk_BLE_Rx_buffer_switcher=2;
						}
						break;
						case 2 :
						{
							Blynk_BLE_Rx_buffer_switcher=1;
						}
						break;				
					}
				}
			}
			if(i_uart7==4)//end of the OK string or duration of data
			{
				switch(Blynk_BLE_Rx_buffer_switcher)//data->buffer
				{
					case 1 :
					{
						if((Blynk_BLE_Rx_buffer_1[0]==0)||(Blynk_BLE_Rx_buffer_1[4]==0))
						{
							if(data==9)
							{
								Blynk_error_9++;
							}
							if((data==200)||(data==0))
							{
								OK_Blynk_Bluetooth++;
							}
							i_uart7=-1;
							Blynk_BLE_Rx_buffer_switcher=2;
							Clean_some_buffers=121;
						}
						else
						{
							Blynk_number_of_data=data;
						}
					}
					break;
					case 2 :
					{
						if((Blynk_BLE_Rx_buffer_2[0]==0)||(Blynk_BLE_Rx_buffer_2[4]==0))
						{
							if(data==9)
							{
								Blynk_error_9++;
							}
							if((data==200)||(data==0))
							{
								OK_Blynk_Bluetooth++;
							}
							i_uart7=-1;
							Blynk_BLE_Rx_buffer_switcher=1;
							Clean_some_buffers=122;
						}
						else
						{
							Blynk_number_of_data=data;
						}
					}
					break;
				}
			}		
}

void Read_data_from_Blynk_GSM(int data)
{
	if(i_uart2==0)
	{
		i_GSM_uart_delay=0;
	}
	if((i_uart2>0)&&(i_GSM_uart_delay>100))
	{
		i_GSM_uart_delay=0;
		i_uart2=0;
	}
	
			switch(Blynk_GSM_Rx_buffer_switcher)//data->buffer
			{
				case 1 :
				{
					Blynk_GSM_Rx_buffer_1[i_uart2]=data;
				}
				break;
				case 2 :
				{
					Blynk_GSM_Rx_buffer_2[i_uart2]=data;
				}
				break;
			}
			if(Blynk_number_of_data>0)//recognizing end of the data string
			{
				Blynk_number_of_data--;
				if(Blynk_number_of_data==0)
				{
					Blynk_GSM_incoming_ready=1;
					i_uart2=-1;
					switch(Blynk_GSM_Rx_buffer_switcher)
					{
						case 1 :
						{
							Blynk_GSM_Rx_buffer_switcher=2;
						}
						break;
						case 2 :
						{
							Blynk_GSM_Rx_buffer_switcher=1;
						}
						break;				
					}
				}
			}
			if(i_uart2==4)//end of the OK string or duration of data
			{
				switch(Blynk_GSM_Rx_buffer_switcher)//data->buffer
				{
					case 1 :
					{
						if(Blynk_GSM_Rx_buffer_1[0]==0)
						{
							if(data==9)
							{
								Blynk_error_9++;
							}
							if((data==200)||(data==4))
							{
								OK_Blynk_GSM++;
							}
							i_uart2=-1;
							Blynk_GSM_Rx_buffer_switcher=2;
							Clean_some_buffers=21;
						}
						else
						{
							Blynk_number_of_data=data;
						}
					}
					break;
					case 2 :
					{
						if(Blynk_GSM_Rx_buffer_2[0]==0)
						{
							if(data==9)
							{
								Blynk_error_9++;
							}
							if((data==200)||(data==4))
							{
								OK_Blynk_GSM++;
							}
							i_uart2=-1;
							Blynk_GSM_Rx_buffer_switcher=1;
							Clean_some_buffers=22;
						}
						else
						{
							Blynk_number_of_data=data;
						}
					}
					break;
				}
			}			
}



void Blynk_write(int Channel, int Command, int ID, int variable_type, int variable_number, int variant, int quantity, int massiv[50])//1 byte, 2 bytes, 2 bytes, many bytes))
{
	/*
	Channel - 0 - Bluetooth, 1 - GSM
	Command 				- like 20 (hardaware)
	ID 							- back the ID that was sended by android, or make own ID
	variable type 	- vr, vw, dr, dw, ar, aw
	variable number - number of the output virtual pin
	variant 				- 0 or 48 (hex or ASCII)
	quantity 				- quantity of output variables
	massiv 					- massiv of the output variables
	*/
	
	
	char a1_massiv[10]={0,0,0,0,0,0,0,0,0,0};
	char a2_massiv[50][20];
	int a1_order=5;
	int a2_order=10;
	int Total_lenght=0;
	int leng_stat1=0;
	char minus[50]=
	{
	0,0,0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,0,0
	};
	char leng_stat2[50]=
	{
	0,0,0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,0,0
	};
	switch (Command)
	{
		case 21 ://LOGIN_Bluetooth
		{
			Blynk_senddata(Channel, 2);//PING
			Blynk_senddata(Channel, ID>>8);//Message ID_high
			Blynk_senddata(Channel, ID&0x00FF);//Message ID_low
			Total_lenght=32;
			Blynk_senddata(Channel, Total_lenght>>8);//leng_high
			Blynk_senddata(Channel, Total_lenght&0x00FF);//leng_low
			for (int i=0; i<Total_lenght; i++)
				{
					Blynk_senddata(Channel, auth1[i]);//ID auth	
				}
		}
		break;
		case 22 ://LOGIN_GSM
		{
			Blynk_senddata(Channel, 2);//PING
			Blynk_senddata(Channel, ID>>8);//Message ID_high
			Blynk_senddata(Channel, ID&0x00FF);//Message ID_low
			Total_lenght=32;
			Blynk_senddata(Channel, Total_lenght>>8);//leng_high
			Blynk_senddata(Channel, Total_lenght&0x00FF);//leng_low
			for (int i=0; i<Total_lenght; i++)
				{
					Blynk_senddata(Channel, auth2[i]);//ID auth	
				}
		}
		break;
		case 6 : //PING
		{
			Blynk_senddata(Channel, Command);//PING
			Blynk_senddata(Channel, ID>>8);//Message ID_high
			Blynk_senddata(Channel, ID&0x00FF);//Message ID_low
			Total_lenght=0;
			Blynk_senddata(Channel, Total_lenght>>8);//leng_high
			Blynk_senddata(Channel, Total_lenght&0x00FF);//leng_low
		}
		break;
		case 20 ://HARDWARE + led
		{
			//a1_order=5;
			if(variable_number>9999)	
				{
					a1_massiv[a1_order]=variable_number/10000;
					leng_stat1++;
					a1_order++;
				}
			if(variable_number>999)	
				{
					a1_massiv[a1_order]=(variable_number-a1_massiv[a1_order-1]*10000)/1000;
					leng_stat1++;
					a1_order++;
				}
			if(variable_number>99)	
				{
					a1_massiv[a1_order]=(variable_number-a1_massiv[a1_order-2]*10000-a1_massiv[a1_order-1]*1000)/100;
					leng_stat1++;
					a1_order++;
				}
			if(variable_number>9)	
				{
					a1_massiv[a1_order]=(variable_number-a1_massiv[a1_order-3]*10000-a1_massiv[a1_order-2]*1000-a1_massiv[a1_order-1]*100)/10;
					leng_stat1++;
					a1_order++;
				}
			a1_massiv[a1_order]=(variable_number-a1_massiv[a1_order-4]*10000-a1_massiv[a1_order-3]*1000-a1_massiv[a1_order-2]*100-a1_massiv[a1_order-1]*10);	
			leng_stat1++;
			a1_order=5;
			//number
			if(variant==48)	
				{				
				for (int n=0; n<quantity; n++)
					{
						if(massiv[n]<0) //minus enable
						{
							massiv[n]=massiv[n]*(-1);
							minus[n]=1;
							//leng_stat2[n]++;
						}
						if(massiv[n]>99999)	
							{
								a2_massiv[n][a2_order]=massiv[n]/100000;
								leng_stat2[n]++;
								a2_order++;
							}
						if(massiv[n]>9999)	
							{
								a2_massiv[n][a2_order]=(massiv[n]-a2_massiv[n][a2_order-1]*100000)/10000;
								leng_stat2[n]++;
								a2_order++;
							}
						if(massiv[n]>999)	
							{
								a2_massiv[n][a2_order]=(massiv[n]-a2_massiv[n][a2_order-2]*100000-a2_massiv[n][a2_order-1]*10000)/1000;
								leng_stat2[n]++;
								a2_order++;
							}
						if(massiv[n]>99)	
							{
								a2_massiv[n][a2_order]=(massiv[n]-a2_massiv[n][a2_order-3]*100000-a2_massiv[n][a2_order-2]*10000-a2_massiv[n][a2_order-1]*1000)/100;
								leng_stat2[n]++;
								a2_order++;
							}
						if(massiv[n]>9)	
							{
								a2_massiv[n][a2_order]=(massiv[n]-a2_massiv[n][a2_order-4]*100000-a2_massiv[n][a2_order-3]*10000-a2_massiv[n][a2_order-2]*1000-a2_massiv[n][a2_order-1]*100)/10;
								leng_stat2[n]++;
								a2_order++;
							}
						a2_massiv[n][a2_order]=(massiv[n]-a2_massiv[n][a2_order-5]*100000-a2_massiv[n][a2_order-4]*10000-a2_massiv[n][a2_order-3]*1000-a2_massiv[n][a2_order-2]*100-a2_massiv[n][a2_order-1]*10);
						leng_stat2[n]++;
						a2_order=10;
					}
				}
				else
				{
					for (int n=0; n<quantity; n++)
					{				
						a2_massiv[n][a2_order]=massiv[n];
						leng_stat2[n]++;
					}
				}
				Total_lenght=leng_stat1+4;
				for(int n=0; n<quantity; n++)
				{
					Total_lenght+=leng_stat2[n];
				}
			//=============================================================		
				Blynk_senddata(Channel, Command);//Command
				Blynk_senddata(Channel, ID>>8);//Message ID_high
				Blynk_senddata(Channel, ID&0x00FF);//Message ID_low
			//=============================================================		
				Blynk_senddata(Channel, Total_lenght>>8);//leng_high
				Blynk_senddata(Channel, Total_lenght&0x00FF);//leng_low	
			//=============================================================
			
				Blynk_senddata(Channel, Blynk_type_variable[variable_type][0]);//variable_type_first
				Blynk_senddata(Channel, Blynk_type_variable[variable_type][1]);//variable_type_second	
			//=============================================================			
				Blynk_senddata(Channel, 0);
			//=============================================================
				
				//variable_number
				for(char i=5; i<(leng_stat1+5); i++)
					{
						Blynk_senddata(Channel, (48+a1_massiv[i]));
					}
			//=============================================================
				Blynk_senddata(Channel, 0);
			//=============================================================
				for (int n=0; n<quantity; n++)
					{
						if(minus[n]==1)
						{
							//Blynk_senddata(Channel, 0x2D);
						}
						for(int i=10; i<(leng_stat2[n]+10); i++)
						{
							Blynk_senddata(Channel, variant+a2_massiv[n][i]);
						}
					}
		}
		break;
	}
}


void Blynk_senddata(int Channel, char data)
{
	switch (Channel)
	{
		case 0 ://Bluetooth
		{
			USART_SendData(UART7, data);
			while (USART_GetFlagStatus(UART7, USART_FLAG_TC)==RESET);				
		}
		break;
		case 1 ://GSM
		{
			USART_SendData(USART2, data);
			while (USART_GetFlagStatus(USART2, USART_FLAG_TC)==RESET);				
		}
		break;
	}
}


