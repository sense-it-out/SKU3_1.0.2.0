/*
 * MQTT_Handler.cpp
 *
 * Created: 25-08-2021 15:49:16
 *  Author: Tushar (SIO)
 */ 

#include <Initialize.h>
#include <MQTT_Handler.h>
#include <string.h>
#include <stdio.h>

Subscribe_Topic      _sSubscribe_Topic;
Publish_Topic        _sPublish_Topic;
Broker_Info          _sBroker_Info;
Network_and_Usr_Info _sNetwork_and_Usr_Info;


void Store_MQTT_Pub_Topics(void)
{
	//sprintf(_sPublish_Topic.Ruble_Register,"SICCA/STATE/%s",_sRuble_Parameters.Ruble_ID);    /* ruble registration topic */ // done
	
	//sprintf(_sPublish_Topic.Ruble_Faults, "SICCA/CODES/%s",_sRuble_Parameters.Ruble_ID);                // done
	
	//sprintf(_sPublish_Topic.Ruble_Data, "SICCA/CONTROLLER/DATA/%s",_sRuble_Parameters.Ruble_ID);        // done
	
	//sprintf(_sPublish_Topic.Timer_FeedBack, "SICCA/TIMER/FEEDBACK/%s",_sRuble_Parameters.Ruble_ID);     // done
	
	//sprintf(_sPublish_Topic.Ruble_Restart, "SICCA/CONTROLLER/RESTART/%s",_sRuble_Parameters.Ruble_ID);  // done

	//sprintf(_sPublish_Topic.General_Feedback, "SICCA/FEEDBACK/%s",_sRuble_Parameters.Ruble_ID);         // done
    
	//strcpy(_sPublish_Topic.Lira_Node_Data,"SICCA/SENSOR/DATA");                                         // done
	
	//sprintf(_sPublish_Topic.Euro_Valve_Data, "%s","SICCA/VALVE/DATA");
	
	//sprintf(_sPublish_Topic.Hardware_Faults, "SICCA/HARDWARE/FAULTS/%s",_sRuble_Parameters.Ruble_ID);
	
	//sprintf(_sPublish_Topic.Electricity_Status_Topic, "SICCA/Elect_Stat/%s",_sRuble_Parameters.Ruble_ID);        // done
	
	//sprintf(_sPublish_Topic.Wired_Valve_Fail, "SICCA/Wired_Fail/%s",_sRuble_Parameters.Ruble_ID);                // done
	
	//sprintf(_sPublish_Topic.Calibration_FeedBack, "SICCA/CALIBRATE/FEEDBACK/%s",_sRuble_Parameters.Ruble_ID);
	
	//sprintf(_sPublish_Topic.Extra_Plot_Feedback, "SICCA/EX_Timer/FB/%s",_sRuble_Parameters.Ruble_ID);
	
	//sprintf(_sPublish_Topic.One_Touch_Monitor,"SICCA/DEVICE/FEEDBACK/%s",_sRuble_Parameters.Ruble_ID);
		
}


void Store_MQTT_Sub_Topics(void)
{	
	//sprintf(_sSubscribe_Topic.Ruble_Register_Feedback, "SICCA/STATE/FEEDBACK/%s",_sRuble_Parameters.Ruble_ID); // done
	
	//sprintf(_sSubscribe_Topic.Ruble_Plot_Setup, "SICCA/CONFIG/SETUP/PLOT/%s",_sRuble_Parameters.Ruble_ID);     // done
	
	//sprintf(_sSubscribe_Topic.Ruble_Set_Timer, "SICCA/TIMER/%s",_sRuble_Parameters.Ruble_ID);                  // done
	
	//sprintf(_sSubscribe_Topic.Ruble_Soil_Coff, "SICCA/SOIL/COEFF/%s",_sRuble_Parameters.Ruble_ID);             // done 
	
	//sprintf(_sSubscribe_Topic.Ruble_Controller_Setup, "SICCA/CONFIG/SETUP/%s",_sRuble_Parameters.Ruble_ID);    // done
	
	//sprintf(_sSubscribe_Topic.Ruble_Euro_Valve_Set, "SICCA/DELETE/VALVE/%s",_sRuble_Parameters.Ruble_ID);       // done
	
	//sprintf(_sSubscribe_Topic.Mode_Change, "SICCA/Mode_Change/%s",_sRuble_Parameters.Ruble_ID);                // done
	
	//sprintf(_sSubscribe_Topic.Calibration, "SICCA/CALIBRATE/%s",_sRuble_Parameters.Ruble_ID);                // done	
	
	//sprintf(_sSubscribe_Topic.SMS_Alert_ON,"SICCA/SMS_ON/%s",_sRuble_Parameters.Ruble_ID);
	
	//sprintf(_sSubscribe_Topic.Schedule_Topic,"SICCA/SCHEDULE/%s",_sRuble_Parameters.Ruble_ID);
	
	//sprintf(_sSubscribe_Topic.One_Touch_Feedback, "SICCA/DEVICE/%s",_sRuble_Parameters.Ruble_ID);
	
	//sprintf(_sSubscribe_Topic.Tank_Schedule, "SICCA/TANK/SCHEDULE/%s",_sRuble_Parameters.Ruble_ID);
	
	//sprintf(_sSubscribe_Topic.Delete_Plot_Devices,"SICCA/PLT_DEL/%s", _sRuble_Parameters.Ruble_ID);
	
	//sprintf(_sSubscribe_Topic.Kill_Switch_Topic, "SICCA/KILL/%s",_sRuble_Parameters.Ruble_ID);
	
}


bool Init_Broker(void)
{
	static unsigned char connect_count;
	static unsigned int loop_count;
	unsigned long previous;
	
	if(_sRuble_Parameters.Ruble_Registration_Status == _eRUBLE_REGISTERED)
	{
		 if(Ping_to_Server())
		 {
			 if(_sRuble_Parameters.Debug_Mode == _kSET)
			 {
				 _kSERAIL_MON_WRITE("Ping to server 0");                /* for debugging purpose */
				 _kSERIAL_MON_CLEAR();
			 }
		 }
		 else
		 {
			 if(_sRuble_Parameters.Debug_Mode == _kSET)
			 {
				 _kSERAIL_MON_WRITE("Fail to Ping server 0");                /* for debugging purpose */
				 _kSERIAL_MON_CLEAR();
			 }
		 }
	}

	
	//_kLCD_CLEAR();
	
	unsigned char temp_topic[40];   
	
	while(_sRuble_Parameters.Ruble_Registration_Status != _eRUBLE_REGISTERED )  /* wait till Ruble controller connect to server */ // now
	{
 		//_sRuble_Parameters.Display_Update |= _eREGISTERING_TO_SERVER;
 		Display_Update_1();   // 20/1/2022
		 
		memset((char *)_gRecvd_Data,0,sizeof(_gRecvd_Data));
		memset((char *)temp_topic,0,sizeof(temp_topic));                                        /* clear the publish buff */
		
		sprintf((char *)_gRecvd_Data,"{\"status\": \"true\"}");
		sprintf((char *)temp_topic,"SICCA/STATE/%s",_sRuble_Parameters.Ruble_ID);
		//MQTT_Publish((unsigned char *)temp_topic,(unsigned char *)_gPub_Buff);   /* published to data to monitor registration */
		MQTT_Publish((unsigned char *)_gRecvd_Data,(unsigned char *)_gRecvd_Data); 
		
		previous = millis();
		while(((millis() - previous) < 15000) && _sRuble_Parameters.Ruble_Registration_Status != _eRUBLE_REGISTERED)
		{
			if(Subscribed_data_check())
			{
				if(Seperate_Out_Sub_Data())
				{
					//mqttCallback((char *)_gRecvd_Data, (unsigned char *)_gPub_Buff, strlen((const char*)_gPub_Buff));
					Pub_Sub_Data((char *)_gRecvd_Data, (unsigned char *)_gPub_Buff, strlen((const char*)_gPub_Buff),_eSUBSCRIBE_DATA);
				}
			}
		}
		
		connect_count = _kRESET;   /* connect cont should reset after sending the published request to server */
		
		
		while(connect_count < 3 && (_sRuble_Parameters.Ruble_Registration_Status != _eRUBLE_REGISTERED))  // now
		{
			connect_count++;                               /* increase each time to maintain the 30 count */                                
			 if(Ping_to_Server())
			 {
				 _sRuble_Parameters.Display_Update |= _eREGISTERING_TO_SERVER;
				 Display_Update_1();   // 20/1/2022
				 
				 //memset((char *)_gPub_Buff,0,sizeof(_gPub_Buff));
				 memset((char *)_gRecvd_Data,0,sizeof(_gRecvd_Data));
				 memset((char *)temp_topic,0,sizeof(temp_topic));                                        /* clear the publish buff */
				 
				 //sprintf((char *)_gPub_Buff,"{\"status\": \"true\"}");                    /* store the payload */
				 sprintf((char *)_gRecvd_Data,"{\"status\": \"true\"}");
				 sprintf((char *)temp_topic,"SICCA/STATE/%s",_sRuble_Parameters.Ruble_ID);
				 //MQTT_Publish((unsigned char *)temp_topic,(unsigned char *)_gPub_Buff);   /* published to data to monitor registration */
				 MQTT_Publish((unsigned char *)temp_topic,(unsigned char *)_gRecvd_Data);
				 
				previous = millis();
				while(((millis() - previous) < 15000) && _sRuble_Parameters.Ruble_Registration_Status != _eRUBLE_REGISTERED)
				{ 
					 if(Subscribed_data_check())
					 {
						 if(Seperate_Out_Sub_Data())
						 {
							 //mqttCallback((char *)_gRecvd_Data, (unsigned char *)_gPub_Buff, strlen((const char*)_gPub_Buff));
							Pub_Sub_Data((char *)_gRecvd_Data, (unsigned char *)_gPub_Buff, strlen((const char*)_gPub_Buff),_eSUBSCRIBE_DATA);
						 }
					 }
				}
				 
				 connect_count = _kRESET;   /* connect cont should reset after sending the published request to server */
				 if(_sRuble_Parameters.Debug_Mode == _kSET)
				 {
					 _kSERAIL_MON_WRITE("Ping to server");                /* for debugging purpose */
					 _kSERIAL_MON_CLEAR();
				 }
			 }
			 else
			 {
				 if(_sRuble_Parameters.Debug_Mode == _kSET)
				 {
					_kSERAIL_MON_WRITE("Fail to Ping server");                /* for debugging purpose */
					_kSERIAL_MON_CLEAR();
				 }
				 continue;
			 }
			 
			loop_count = 0;
			
			while(loop_count < 10 && (_sRuble_Parameters.Ruble_Registration_Status != _eRUBLE_REGISTERED))
			{	
				 //memset((char *)_gPub_Buff,0,sizeof(_gPub_Buff));
				 
				 memset((char *)_gRecvd_Data,0,sizeof(_gRecvd_Data));
				 memset((char *)temp_topic,0,sizeof(temp_topic));                                        /* clear the publish buff */
				 
				 //sprintf((char *)_gPub_Buff,"{\"status\": \"true\"}");                    /* store the payload */
				 sprintf((char *)_gRecvd_Data,"{\"status\": \"true\"}");
				 sprintf((char *)temp_topic,"SICCA/STATE/%s",_sRuble_Parameters.Ruble_ID);
				// MQTT_Publish((unsigned char *)temp_topic,(unsigned char *)_gPub_Buff);   /* published to data to monitor registration */
				 MQTT_Publish((unsigned char *)temp_topic,(unsigned char *)_gRecvd_Data);
				
				loop_count++;
				
				previous = millis();
				while(((millis() - previous) < 25000) && _sRuble_Parameters.Ruble_Registration_Status != _eRUBLE_REGISTERED)
				{
					if(Subscribed_data_check())
					{
						if(Seperate_Out_Sub_Data())
						{
							//mqttCallback((char *)_gRecvd_Data, (unsigned char *)_gPub_Buff, strlen((const char*)_gPub_Buff));
							Pub_Sub_Data((char *)_gRecvd_Data, (unsigned char *)_gPub_Buff, strlen((const char*)_gPub_Buff),_eSUBSCRIBE_DATA);
						}
					}
				}
				if(_sRuble_Parameters.Debug_Mode == _kSET)
				{
					_kSERAIL_MON_WRITE_NO_LN("wait registering status : ");
					_kSERIAL_MON_PRINT_NUM_NO_NEW_LINE(loop_count);
					_kSERIAL_MON_CLEAR();
				}
			}
			loop_count =0;
		}
	}
	if(_sRuble_Parameters.Debug_Mode == _kSET)
	{
		_kSERAIL_MON_WRITE("Ruble controller is registered");                /* for debugging purpose */
 		_kSERIAL_MON_CLEAR();
	}

	/******************* published the topic that Ruble is Restarted ********************/
	//unsigned char temp[33];
	//memset((char *)_gPub_Buff,0,sizeof(_gPub_Buff));
	
	memset((char *)_gRecvd_Data,0,sizeof(_gRecvd_Data));
	sprintf((char *)_gRecvd_Data,"{\"sicca_start\": \"true\"}");
	memset((char *)temp_topic, 0, sizeof(temp_topic));
	
	sprintf((char *)temp_topic,"SICCA/CONTROLLER/RESTART/%s",_sRuble_Parameters.Ruble_ID);
	
	//MQTT_Publish((unsigned char *)temp_topic,(unsigned char *)_gPub_Buff);
	
	MQTT_Publish((unsigned char *)temp_topic,(unsigned char *)_gRecvd_Data);
	
	_sRuble_Parameters.Publish_Topic |= _ePUB_RUBLE_DATA;
	
}


bool Ping_to_Server(void)
{
	if(_gdo_not_perform_4g_oper)
	{
		return 0;
	}
	
	Reset_Buffer();
   _kSERIAL_AT.println(F("ATE0"));
   Send_AT_Command(NULL, "OK",  NULL,3000,2);
	
	
	if (!Check_Sim(_eDIRESCT_CHECK))
	{
		if(_sRuble_Parameters.Debug_Mode == _kSET)
		{
			_kSERAIL_MON_WRITE("Sim is not there");                /* for debugging purpose */
			_kSERIAL_MON_CLEAR();
		}
		return 0;
	}
	
	
	Reset_Buffer();
	 _kSERIAL_AT.println(F("AT+QMTCLOSE=0"));
	if(_kSEND_AT_COMMAND(NULL,"OK",NULL,3000,1))
	{
		if(_sRuble_Parameters.Debug_Mode == _kSET)
		{
			_kSERAIL_MON_WRITE("AT+QMTCLOSE");                /* for debugging purpose */
			_kSERIAL_MON_CLEAR();
		}
	}
	else
	{
		if(_sRuble_Parameters.Debug_Mode == _kSET)
		{
			_kSERAIL_MON_WRITE("AT+QMTCLOSE NOT CLOSE ");                /* for debugging purpose */
			_kSERIAL_MON_CLEAR();
		}
	}
	
	if(!Gsm_Gprs_Network())
	{
		_sRuble_Parameters.lndications &= ~_eRUBL_INDI_SERVER_CONN;
		return 0;
		
	}
	
	_sRuble_Parameters.Display_Update |= _eNETWORK_SELECTED;
	 Display_Update_1();  // 20/1/2022
	
	
	if(!_kIS_MQTT_CONNECTED() ||  _sRuble_Parameters.Subscribe_Topic_Status == _eALL_TOPIC_NOT_SUBCRIBED)      /* check weather already connected to server */
	{
		if(_sRuble_Parameters.Debug_Mode == _kSET)
		{
			_kSERAIL_MON_WRITE("Try to connect the server");                /* for debugging purpose */
			_kSERIAL_MON_CLEAR();
		}
		
		_sRuble_Parameters.Display_Update =  _eCONNECTING_TO_SERVER;
		Display_Update_1();    // 20/1/2022
		
		
		if(_kMQTT_CONNCET(_kMQTT_CLIENT_ID,_kMQTT_USER,_kMQTT_PASSWORD))
		{
			_gdo_not_perform_4g_oper = _kRESET;
			reconnection_retry_count = _kRESET;
			
			if(_sRuble_Parameters.Debug_Mode == _kSET)
			{
				_kSERAIL_MON_WRITE("Connected To server");                /* for debugging purpose */
				_kSERIAL_MON_CLEAR();
			}
			_sRuble_Parameters.Display_Update |= _kDISP_RANGE_3;
			
			_sRuble_Parameters.Display_Update |=  _eCONNECTED_TO_SERVER;
			Display_Update_1();   // 20/1/2022
			
			 if(Subscribe_MQTT_Topics())
			 {
				 if(_sRuble_Parameters.Debug_Mode == _kSET)
				 {
					 _kSERAIL_MON_WRITE("all topic subscribed");                /* for debugging purpose */
					 _kSERIAL_MON_CLEAR();
				 }
				  _sRuble_Parameters.lndications   |= _eRUBL_INDI_SERVER_CONN;
			 }
			 else
			 {
				 if(_sRuble_Parameters.Debug_Mode == _kSET)
				 {
					 _kSERAIL_MON_WRITE("all topic not subscribed");                /* for debugging purpose */
				 }
			 }
			 
			
			 _sRuble_Parameters.Publish_Topic |=  _ePUB_RUBLE_DATA;
			 
			 if(_sRuble_Parameters.Ruble_Registration_Status != _eRUBLE_REGISTERED)
			 {
				  _sRuble_Parameters.Display_Update |= _eREGISTERING_TO_SERVER;
				  Display_Update_1();   // 20/1/2022
			 }
			 else
			 {
				  _sRuble_Parameters.Display_Update |= _eTHANK_YOU_FOR_WAITING;
				  Display_Update_1();   // 20/1/2022
			 }
			 
			 return 1;
		}
		else
		{
			reconnection_retry_count++;
			if(reconnection_retry_count > 2)
			{
				reconnection_retry_count = _kRESET;
				_gdo_not_perform_4g_oper = 50 * 60;
			}
			else
			{
				_sRuble_Parameters.lndications &= ~_eRUBL_INDI_SERVER_CONN;
				_sRuble_Parameters.Display_Update |= _kDISP_NO_RANGE;
				if(_sRuble_Parameters.Debug_Mode == _kSET)
				{
					_kSERAIL_MON_WRITE("Fail To connect the server");                /* for debugging purpose */
					_kSERIAL_MON_CLEAR();
				}
				
				Reset_Buffer();
				_kSERIAL_AT.println(F("AT+CFUN=1,1"));
				Send_AT_Command(NULL, "Call Ready",  NULL,10000,1);
				_kDELAY_MS(10000);
				/*}*/
				
				if(_sRuble_Parameters.Ruble_Registration_Status != _eRUBLE_REGISTERED)
				{
					_kDELAY_MS(12000);
				}
				
				Reset_Buffer();
				_kSERIAL_AT.println(F("ATE0"));
				Send_AT_Command(NULL, "OK",  NULL,3000,2);
			}
			
			return 0;
		}
	}
	else
	{
		reconnection_retry_count = _kRESET;
		_gdo_not_perform_4g_oper = _kRESET;
		return 1;
	}
}


bool Subscribe_MQTT_Topics(void)
{
	char temp_flag = _kRESET;
	
	unsigned char temp_sub_topic[40];
	
	
	
	memset((char *)temp_sub_topic,0,sizeof(temp_sub_topic));
	sprintf((char *)temp_sub_topic,"SICCA/DELETE/VALVE/%s",_sRuble_Parameters.Ruble_ID);
	
	if(!_kMQTT_SUB((char *)temp_sub_topic))
	{
		if(_sRuble_Parameters.Debug_Mode == _kSET)
		{
			_kSERAIL_MON_WRITE("_sSubscribe_Topic.Ruble_Euro_Valve_Set fail");                /* for debugging purpose */
			_kSERIAL_MON_CLEAR();
		}
		temp_flag = _kSET;
	}
	
	memset((char *)temp_sub_topic,0,sizeof(temp_sub_topic));
	sprintf((char *)temp_sub_topic,"SICCA/CONFIG/SETUP/PLOT/%s",_sRuble_Parameters.Ruble_ID);
	
	//SICCA/CONFIG/SETUP/PLOT/
		
	if(!_kMQTT_SUB((char *)temp_sub_topic))
	{
		temp_flag = _kSET;
	}
	
	
	memset((char *)temp_sub_topic,0,sizeof(temp_sub_topic));
	sprintf((char *)temp_sub_topic,"SICCA/STATE/FEEDBACK/%s",_sRuble_Parameters.Ruble_ID);
	
	
	if(!_kMQTT_SUB((char *)temp_sub_topic))
	{
		temp_flag = _kSET;
	}
	
	
	memset((char *)temp_sub_topic,0,sizeof(temp_sub_topic));
	sprintf((char *)temp_sub_topic,"SICCA/TIMER/%s",_sRuble_Parameters.Ruble_ID);
	if(!_kMQTT_SUB((char *)temp_sub_topic))
	{
		temp_flag = _kSET;
	}
	
	memset((char *)temp_sub_topic,0,sizeof(temp_sub_topic));
	sprintf((char *)temp_sub_topic,"SICCA/SOIL/COEFF/%s",_sRuble_Parameters.Ruble_ID);
	
	if(!_kMQTT_SUB((char *)temp_sub_topic))
	{
		temp_flag = _kSET;
	}
	
	
	memset((char *)temp_sub_topic,0,sizeof(temp_sub_topic));
	sprintf((char *)temp_sub_topic,"SICCA/CONFIG/SETUP/%s",_sRuble_Parameters.Ruble_ID);
	
	if(!_kMQTT_SUB((char *)temp_sub_topic))
	{
		temp_flag = _kSET;
	}
	
// 	if(!_kMQTT_SUB(_sSubscribe_Topic.Mode_Change))
// 	{
// 		temp_flag = _kSET;
// 	}



	memset((char *)temp_sub_topic,0,sizeof(temp_sub_topic));
	sprintf((char *)temp_sub_topic,"SICCA/CALIBRATE/%s",_sRuble_Parameters.Ruble_ID);
	
	if(!_kMQTT_SUB((char *)temp_sub_topic))
	{
		temp_flag = _kSET;
	}
	
// 	if(!_kMQTT_SUB(_sSubscribe_Topic.SMS_Alert_ON))
// 	{
// 		temp_flag = _kSET;
// 	}

	
	
	memset((char *)temp_sub_topic,0,sizeof(temp_sub_topic));
	sprintf((char *)temp_sub_topic,"SICCA/SCHEDULE/%s",_sRuble_Parameters.Ruble_ID);
	
	if(!_kMQTT_SUB((char *)temp_sub_topic))
	{
		temp_flag = _kSET;
	}
	
	memset((char *)temp_sub_topic,0,sizeof(temp_sub_topic));
	sprintf((char *)temp_sub_topic,"SICCA/DEVICE/%s",_sRuble_Parameters.Ruble_ID);
	
	if(!_kMQTT_SUB((char *)temp_sub_topic))
	{
		temp_flag = _kSET;
	}
	
	
	
	memset((char *)temp_sub_topic,0,sizeof(temp_sub_topic));
	sprintf((char *)temp_sub_topic,"SICCA/TANK/SCHEDULE/%s",_sRuble_Parameters.Ruble_ID);
	
	if(!_kMQTT_SUB((char *)temp_sub_topic))
	{
		temp_flag = _kSET;
	}
	
// 	if(!_kMQTT_SUB(_sSubscribe_Topic.Delete_Plot_Devices))
// 	{
// 		temp_flag = _kSET;
// 	}
	
// 	if(!_kMQTT_SUB(_sSubscribe_Topic.Kill_Switch_Topic))
// 	{
// 		temp_flag = _kSET;
// 	}
	
	
	if(temp_flag)
	{
		_sRuble_Parameters.Subscribe_Topic_Status = _eALL_TOPIC_NOT_SUBCRIBED;
	}
	else
	{
		_sRuble_Parameters.Subscribe_Topic_Status = _eALL_TOPIC_SUBSCRIBED;
	}
	
	return !temp_flag;
}

