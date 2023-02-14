/*
 * main.cpp

 *
 *  Created on: 2018/01/17
 *      Author: yoneken
 */
#include <mainpp.h>
#include <ros.h>
#include <std_msgs/String.h>

ros::NodeHandle nh;

uint16_t counter = 0;

std_msgs::String str_msg;
ros::Publisher chatter("chatter", &str_msg);

char hello[50] = "Hello world from STM32!";

void HAL_UART_TxCpltCallback(UART_HandleTypeDef *huart){
  nh.getHardware()->flush();
}

void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart){
  nh.getHardware()->reset_rbuf();
}

void setup(void)
{
  nh.initNode();
  nh.advertise(chatter);
}

void loop(void)
{
	sprintf(hello, "Hello world from STM32! - %d", counter);
	counter++;
	str_msg.data = hello;
	chatter.publish(&str_msg);
	nh.spinOnce();
	HAL_Delay(1000);
}

