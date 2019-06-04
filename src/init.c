#include "stm32l476xx.h"
#include "helper_functions.h"
#include "7seg.h"
#include "keypad.h"
#include "led_button.h"
#include "timer.h"
#include "hc_sr04.h"
#include "beeper.h"
#include "init.h"

// Define pins for 7seg
#define SEG_gpio GPIOC
#define DIN_pin 3
#define CS_pin 4
#define CLK_pin 5

// Define pins for led (default use on-board led PA5)
#define LED_gpio GPIOA
#define LED_pin 6      // 6 7 8 9 10

// Define pins for button (default use on-board button PC13)
#define BUTTON_gpio GPIOC
#define BUTTON_pin 13

// Define pins for motor
#define LF_MOTOR_gpio_pos GPIOB
#define LF_MOTOR_pin_pos 8
#define LF_MOTOR_gpio_neg GPIOB
#define LF_MOTOR_pin_neg 9
#define RF_MOTOR_gpio_pos GPIOB
#define RF_MOTOR_pin_pos 10
#define RF_MOTOR_gpio_neg GPIOB
#define RF_MOTOR_pin_neg 11
#define LB_MOTOR_gpio_pos GPIOB
#define LB_MOTOR_pin_pos 12
#define LB_MOTOR_gpio_neg GPIOB
#define LB_MOTOR_pin_neg 13
#define RB_MOTOR_gpio_pos GPIOB
#define RB_MOTOR_pin_pos 14
#define RB_MOTOR_gpio_neg GPIOB
#define RB_MOTOR_pin_neg 15

#define TRIG_gpio GPIOC
#define TRIG_pin 0
#define ECHO_gpio GPIOC
#define ECHO_pin 1

// Define Counter timer
#define COUNTER_timer TIM2


int initialize(){
	FPU_init();
	SystemClock_Config(10);

	for (int i = 0; i < 5; i++){
		if(init_led(LED_gpio, LED_pin + i) != 0){
			return -1;
		}
	}
	for (int i = 0; i < 8; i++){
		if(init_led(LF_MOTOR_gpio_pos, LF_MOTOR_pin_pos + i) != 0){
			return -1;
		}
	}
	if(init_led(TRIG_gpio, TRIG_pin) != 0){
		return -1;
	}
	if(init_button(ECHO_gpio, ECHO_pin) != 0){
		return -1;
	}
	if(init_button(BUTTON_gpio, BUTTON_pin) != 0){
		return -1;
	}
	if(init_7seg_number(SEG_gpio, DIN_pin, CS_pin, CLK_pin) != 0){
		// Fail to init 7seg
		return -1;
	}

	return 0;
}
