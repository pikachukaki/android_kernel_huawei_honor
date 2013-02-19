/*< DTS2012020400396 zhangyu 20120206 begin */
/*< DTS2011100802771   songxiaoming 20111009 begin */ 
/*
 * Copyright (c) 2008-2009 QUALCOMM USA, INC.
 *
 * All source code in this file is licensed under the following license
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * version 2 as published by the Free Software Foundation.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * See the GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, you can find it at http://www.fsf.org
 */

#ifndef MT9T113_H
#define MT9T113_H

#include <mach/board.h>
#include <linux/types.h>
extern struct mt9t113_reg mt9t113_regs;

struct mt9t113_i2c_reg_conf
{
    unsigned short waddr;
    unsigned short wdata;
};

struct mt9t113_reg
{
    const struct mt9t113_i2c_reg_conf * mt9t113_init_reg_config_sunny;
    const unsigned short               mt9t113_init_reg_config_sunny_size;
    /* <DTS2012041003722 sibingsong 20120410 begin */
    /*< DTS2012020307372 cuixuefeng 20120326 begin */
    const struct mt9t113_i2c_reg_conf * mt9t113_init_reg_config_sunny_M660;
    const unsigned short               mt9t113_init_reg_config_sunny_M660_size;
    /* DTS2012020307372 cuixuefeng 20120326 end > */
    const struct mt9t113_i2c_reg_conf * mt9t113_init_reg_config_sunny_2;
    const unsigned short               mt9t113_init_reg_config_sunny_2_size;
    /*< DTS2012020307372 cuixuefeng 20120326 begin */
    const struct mt9t113_i2c_reg_conf * mt9t113_init_reg_config_sunny_2_M660;
    const unsigned short               mt9t113_init_reg_config_sunny_2_M660_size;
    /* DTS2012020307372 cuixuefeng 20120326 end > */
    /* DTS2012041003722 sibingsong 20120410 end> */
    const struct mt9t113_i2c_reg_conf * mt9t113_init_reg_config_sunny_3;
    const unsigned short               mt9t113_init_reg_config_sunny_3_size;
    const struct mt9t113_i2c_reg_conf * mt9t113_init_reg_sensor_start;
    const unsigned short               mt9t113_init_reg_sensor_start_size;
    const struct mt9t113_i2c_reg_conf * mt9t113_effect_off_reg_config;
    const unsigned short               mt9t113_effect_off_reg_config_size;
    const struct mt9t113_i2c_reg_conf * mt9t113_effect_mono_reg_config;
    const unsigned short               mt9t113_effect_mono_reg_config_size;
    const struct mt9t113_i2c_reg_conf * mt9t113_effect_negative_reg_config;
    const unsigned short               mt9t113_effect_negative_reg_config_size;
    const struct mt9t113_i2c_reg_conf * mt9t113_effect_sepia_reg_config;
    const unsigned short               mt9t113_effect_sepia_reg_config_size;
    const struct mt9t113_i2c_reg_conf * mt9t113_effect_aqua_reg_config;
    const unsigned short               mt9t113_effect_aqua_reg_config_size;
    /*< DTS2011111900798 yuguangcai 20111130 begin */
    const struct mt9t113_i2c_reg_conf * mt9t113_effect_solarize_reg_config;
    const unsigned short               mt9t113_effect_solarize_reg_config_size;
    const struct mt9t113_i2c_reg_conf * mt9t113_effect_posterize_reg_config;
    const unsigned short               mt9t113_effect_posterize_reg_config_size;
    /* DTS2011111900798 yuguangcai 20111130 end > */
    const struct mt9t113_i2c_reg_conf * mt9t113_preview_reg_config;
    const unsigned short               mt9t113_preview_reg_config_size;
    const struct mt9t113_i2c_reg_conf * mt9t113_snapshot_reg_config;
    const unsigned short               mt9t113_snapshot_reg_config_size;
    const struct mt9t113_i2c_reg_conf * mt9t113_wb_auto_reg_config;
    const unsigned short               mt9t113_wb_auto_reg_config_size;
    const struct mt9t113_i2c_reg_conf * mt9t113_wb_a_reg_config;
    const unsigned short               mt9t113_wb_a_reg_config_size;
    const struct mt9t113_i2c_reg_conf * mt9t113_wb_tl84_reg_config;
    const unsigned short               mt9t113_wb_tl84_reg_config_size;
    const struct mt9t113_i2c_reg_conf * mt9t113_wb_f_reg_config;
    const unsigned short               mt9t113_wb_f_reg_config_size;
    const struct mt9t113_i2c_reg_conf * mt9t113_wb_d65_reg_config;
    const unsigned short               mt9t113_wb_d65_reg_config_size;
    const struct mt9t113_i2c_reg_conf * mt9t113_wb_d50_reg_config;
    const unsigned short               mt9t113_wb_d50_reg_config_size;
    /*< DTS2012013103283   songxiaoming 20120201 begin */ 
    const struct mt9t113_i2c_reg_conf * mt9t113_mirror_mode_reg_config;
    const unsigned short               mt9t113_mirror_mode_reg_config_size;
    /* DTS2012013103283  songxiaoming 20120201 end > */
    /*< DTS2011111900798 yuguangcai 20111130 begin */
    /*delete antibanding array pointer*/
    /* DTS2011111900798 yuguangcai 20111130 end > */
};

#endif /* MT9T113_H */
/* DTS2011100802771   songxiaoming 20111009 end > */
/* DTS2012020400396 zhangyu 20120206 end > */
