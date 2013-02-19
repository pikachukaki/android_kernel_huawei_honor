#
# Makefile for the i2c core.
#

obj-$(CONFIG_I2C_BOARDINFO)	+= i2c-boardinfo.o
obj-$(CONFIG_I2C)		+= i2c-core.o
obj-$(CONFIG_I2C_SMBUS)		+= i2c-smbus.o
obj-$(CONFIG_I2C_CHARDEV)	+= i2c-dev.o
obj-$(CONFIG_I2C_MUX)		+= i2c-mux.o
#/*< DTS2011041700393 lijianzhao 20110417 begin */
#modify for 4125 baseline
obj-y				+= algos/ busses/ muxes/ chips/
#/* DTS2011041700393 lijianzhao 20110417 end >*/
#/* < DTS2011042801270 yuezenglong 20110428 begin */
obj-$(CONFIG_HUAWEI_FEATURE_GYROSCOPE_L3G4200DH) += gyroscope/
#/* DTS2011042801270 yuezenglong 20110428 end > */

#/*< DTS2012021003176 yanzhijun 20120210 begin */
# merge DTS2011110800980 fangxinyong  
obj-$(CONFIG_HUAWEI_I2C_DEBUG_TOOL)  += huawei_i2c_debug.o
#/* DTS2012021003176 yanzhijun 20120210 end >*/ 

ccflags-$(CONFIG_I2C_DEBUG_CORE) := -DDEBUG
CFLAGS_i2c-core.o := -Wno-deprecated-declarations
