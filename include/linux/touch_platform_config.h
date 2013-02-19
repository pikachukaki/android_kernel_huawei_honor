/*
 * include/linux/touch_platfrom_config.h - platform data structure for touchscreen
 *
 * Copyright (C) 2010 Google, Inc.
 *
 * This software is licensed under the terms of the GNU General Public
 * License version 2, as published by the Free Software Foundation, and
 * may be copied, distributed, and modified under those terms.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 */
/*<DTS2011042602009 fengwei 20110426 begin*/
#ifndef _TOUCH_PLATFORM_CONFIG_H
#define IRQ_GPIO_START 64
#define irq_to_gpio(irq)	((irq) - IRQ_GPIO_START)
/*define some tp type*/
#define LCD_X_QVGA  	   240
#define LCD_Y_QVGA    	   320
/* < DTS2012020907660 sunlibin 20120213 begin */
/*Replaced by LCD_ALL_QVGA*/
/* DTS2012020907660 sunlibin 20120213 end > */
#define LCD_X_HVGA     320
#define LCD_Y_HVGA     480
#define LCD_X_WVGA     480
#define LCD_Y_WVGA     800
/* < DTS2012020907660 sunlibin 20120213 begin */
/*Replaced by LCD_ALL_WVGA_4INCHTP*/
/* DTS2012020907660 sunlibin 20120213 end > */
/* < DTS2012020907660 sunlibin 20120213 begin */
/* Change name */
/*< DTS2012050201759 duanfei 20120502 begin */
/* Calibrate the coordinate values */
#define LCD_ALL_WVGA_4INCHTP1     859
/* DTS2012050201759 duanfei 20120502 end >*/
/* DTS2012020907660 sunlibin 20120213 end > */
/*<DTS2011051601005 fengwei 20110516 begin*/
#define LCD_X_FWVGA 480
#define LCD_Y_FWVGA 854
/* < DTS2012020907660 sunlibin 20120213 begin */
/*Replaced by LCD_ALL_FWVGA*/
/* DTS2012020907660 sunlibin 20120213 end > */
/*DTS2011051601005  fengwei 20110516 end>*/
/* < DTS2012020907660 sunlibin 20120213 begin */
/*Replaced by LCD_ALL_HVGA_35INCHTP*/
/* DTS2012020907660 sunlibin 20120213 end > */
/*< DTS2012011904543 lijianzhao 20120119 begin */
#define LCD_ALL_QVGA        347
#define LCD_ALL_HVGA_35INCHTP     538 /* 3.5 INCH TP */
#define LCD_ALL_HVGA_32INCHTP     521  /* 3.2 INCH TP */
#define LCD_ALL_FWVGA 958
#define LCD_ALL_WVGA_4INCHTP     882  /* U8610 use this TP */
/*add this function for judge the tp type*/
struct tp_resolution_conversion{
    int lcd_x;
    int lcd_y;
    int lcd_all;
};
/* DTS2012011904543 lijianzhao 20120119 end >*/
struct touch_hw_platform_data {
	int (*touch_power)(int on);	/* Only valid in first array entry */
	int (*touch_gpio_config_interrupt)(void);/*it will config the gpio*/
    void (*set_touch_probe_flag)(int detected);/*we use this to detect the probe is detected*/
    int (*read_touch_probe_flag)(void);/*when the touch is find we return a value*/
	int (*touch_reset)(void);
	int (*get_touch_reset_pin)(void);
    int (*get_phone_version)(struct tp_resolution_conversion *tp_resolution_type);/*add this function for judge the tp type*/
};
/*< DTS2012051004932 huzheng 20120509 begin */
/* move this to hardware_self_adapt.h */
/*< DTS2012031203104 duanfei 20120313 begin */
/* named Rule
 * 2202 3200 : syanptics-IC-Module.ver
 * for example: syanptics-3200-tpk.2
 *
 * 2000 2100 3000 :syanptics-Module.ver
 * for example: syanptics-tpk.2
 *
 * melfas :melfas-Module.ver
 * for example: melfas-tpk.2
 *
 * return touch info
 */
/* char * get_touch_info(void); */
/* DTS2012031203104 duanfei 20120313 end >*/
/* DTS2012051004932 huzheng 20120509 end >*/

/*DTS2011042602009  fengwei 20110426 end>*/
#endif /*_TOUCH_PLATFORM_CONFIG_H */
