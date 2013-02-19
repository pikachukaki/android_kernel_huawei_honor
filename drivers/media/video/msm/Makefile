GCC_VERSION      := $(shell $(CONFIG_SHELL) $(PWD)/scripts/gcc-version.sh $(CROSS_COMPILE)gcc)
ifeq ($(GCC_VERSION),0404)
CFLAGS_REMOVE_msm_vfe8x.o = -Wframe-larger-than=1024
endif

ifeq ($(CONFIG_MSM_CAMERA_V4L2),y)
  EXTRA_CFLAGS += -Idrivers/media/video/msm/csi
  EXTRA_CFLAGS += -Idrivers/media/video/msm/io
  EXTRA_CFLAGS += -Idrivers/media/video/msm/sensors
  obj-$(CONFIG_MSM_CAMERA) += msm_isp.o msm.o msm_mem.o msm_mctl.o msm_mctl_buf.o msm_mctl_pp.o
  obj-$(CONFIG_MSM_CAMERA) += io/ sensors/ actuators/ csi/
else
  obj-$(CONFIG_MSM_CAMERA) += msm_camera.o
endif
obj-$(CONFIG_MSM_CAMERA) += msm_axi_qos.o gemini/
obj-$(CONFIG_MSM_CAMERA_FLASH) += flash.o
#/*< DTS2011091402372   yuguangcai 20110914 begin */
obj-$(CONFIG_HUAWEI_FEATURE_TPS61310) += tps61310.o
#/* DTS2011091402372   yuguangcai 20110914 end > */
#/* < DTS2011072705129 xiangxu 20110728 begin */
obj-$(CONFIG_HW_TORCH) += torch.o
#/*   DTS2011072705129  xiangxu 20110728 end > */
obj-$(CONFIG_ARCH_MSM_ARM11) += msm_vfe7x.o msm_io7x.o
ifeq ($(CONFIG_MSM_CAMERA_V4L2),y)
  obj-$(CONFIG_ARCH_MSM7X27A) += msm_vfe7x27a_v4l2.o msm_io_7x27a_v4l2.o
else
  obj-$(CONFIG_ARCH_MSM7X27A) += msm_vfe7x27a.o msm_io_7x27a.o
endif
obj-$(CONFIG_ARCH_MSM7X30) += msm_vfe31.o msm_io_vfe31.o msm_vpe1.o
obj-$(CONFIG_ARCH_QSD8X50) += msm_vfe8x.o msm_vfe8x_proc.o msm_io8x.o
obj-$(CONFIG_ARCH_MSM8X60) += msm_vfe31.o msm_io_8x60.o msm_vpe1.o
obj-$(CONFIG_ARCH_MSM8960) += msm_io_8960.o msm_vfe32.o msm_vpe.o
obj-$(CONFIG_MT9T013) += mt9t013.o mt9t013_reg.o
obj-$(CONFIG_SN12M0PZ) += sn12m0pz.o sn12m0pz_reg.o

#/* < DTS2011061801881 zhangyu 20110620 BEGIN */
obj-$(CONFIG_HUAWEI_SENSOR_MT9V114) += mt9v114.o
#/* DTS2011061801881 zhangyu 20110620 END > */ 

#/*< DTS2011051400258   songxiaoming 20110514 begin */
obj-$(CONFIG_HUAWEI_SENSOR_HI701) += hi701.o
#/* DTS2011051400258   songxiaoming 20110514 end > */

#/* < DTS2011081301650 liwei 20110813 begin */
obj-$(CONFIG_HUAWEI_SENSOR_OV7690) += ov7690.o
#/* DTS2011081301650 liwei 20110813 end > */
#/*< DTS2011072600848   songxiaoming 20110726 begin */
obj-$(CONFIG_HUAWEI_SENSOR_OV7736) += ov7736.o
#/* DTS2011072600848   songxiaoming 20110726 end > */
#/*<BU5D10275  liyuping 00166065  20100529 begin*/
obj-$(CONFIG_HUAWEI_SENSOR_HIMAX0356) += himax0356.o
#/* BU5D10275  liyuping 00166065  20100529 end> */

#/*< DTS2012020400396 zhangyu 20120206 begin */
#/* delete lines */
#/* DTS2012020400396 zhangyu 20120206 end > */

#/*< DTS2012031604390 yuguangcai 20120316 begin */
obj-$(CONFIG_HUAWEI_CAMERA_SENSOR_S5K5CA) +=  s5k5ca.o s5k5ca_sunny_reg.o
#/* DTS2012031604390 yuguangcai 20120316 end > */
#/* <DTS2012032603420 sibingsong 20120326 begin */
#/* don't compile s5k4e1gx.c and s5k4e1gx_reg.c any more */
#/* DTS2012032603420 sibingsong 20120326 end> */
#/* < DTS2012041003147 liuxin 20120223 begin */
obj-$(CONFIG_HUAWEI_SENSOR_S5K4E1GX_P) += s5k4e1gx_p.o
#/* DTS2012041003147 liuxin 20120223 end > */
#/* < DTS2011090701903 zhangyu 20110907 begin */
obj-$(CONFIG_HUAWEI_SENSOR_MT9P017) += mt9p017.o mt9p017_reg.o
#/* DTS2011090701903 zhangyu 20110907 end > */ 
#/*<BU5D09497  lijuan 00152865  20100514 begin*/
obj-$(CONFIG_HUAWEI_SENSOR_OV5647_SUNNY) += ov5647_sunny.o
#/* BU5D09497  lijuan 00152865  20100514 end> */
#/*<DTS2011042704563 penghai 20110427 begin*/
obj-$(CONFIG_HUAWEI_SENSOR_MT9E013) += mt9e013.o mt9e013_reg.o
#/*DTS2011042704563 penghai 20110427 end>*/
#/*< DTS2012020400396 zhangyu 20120206 begin */
#/*< DTS2012031604390 yuguangcai 20120316 begin */
#/*delete one line*/
#/* DTS2012031604390 yuguangcai 20120316 end > */
#/*< DTS2011100802771   songxiaoming 20111009 begin */ 
obj-$(CONFIG_HUAWEI_CAMERA_SENSOR_MT9T113) +=  mt9t113.o mt9t113_byd_reg.o
#/* DTS2011100802771   songxiaoming 20111009 end > */
#/* DTS2012020400396 zhangyu 20120206 end > */
#/* < DTS2010092501047 luojianhong 201000926 begin*/
obj-$(CONFIG_HUAWEI_FEATURE_RIGHT_TPA2028D1_AMPLIFIER)	+= tpa2028d1_r.o
#/*  DTS2010092501047 luojianhong 201000926 end > */
obj-$(CONFIG_MT9P012) += mt9p012_reg.o
obj-$(CONFIG_MSM_CAMERA_AF_FOXCONN) += mt9p012_fox.o
obj-$(CONFIG_MSM_CAMERA_AF_BAM) += mt9p012_bam.o
obj-$(CONFIG_MT9P012_KM) += mt9p012_km.o mt9p012_km_reg.o
#/*<DTS2011042704563 penghai 20110427 begin*/
#/*deletes some lines*/
#/*DTS2011042704563 penghai 20110427 end>*/
obj-$(CONFIG_S5K3E2FX) += s5k3e2fx.o
#/*< DTS2012020400396 zhangyu 20120206 begin */
obj-$(CONFIG_HUAWEI_SENSOR_S5K4E1) += s5k4e1.o s5k4e1_reg.o
#/* DTS2012020400396 zhangyu 20120206 end > */
#FIXME: Merge the two ifeq causes VX6953 preview not coming up.
ifeq ($(CONFIG_MSM_CAMERA_V4L2),y)
  obj-$(CONFIG_VX6953) += vx6953_v4l2.o vx6953_reg_v4l2.o
else
  obj-$(CONFIG_VX6953) += vx6953.o vx6953_reg.o
  obj-$(CONFIG_IMX074) += imx074.o imx074_reg.o
  obj-$(CONFIG_MT9E013) += mt9e013.o mt9e013_reg.o
  obj-$(CONFIG_WEBCAM_OV9726) += ov9726.o ov9726_reg.o
  obj-$(CONFIG_S5K4E1) += s5k4e1.o s5k4e1_reg.o
endif
obj-$(CONFIG_QS_S5K4E1) += qs_s5k4e1.o qs_s5k4e1_reg.o
obj-$(CONFIG_VB6801) += vb6801.o
obj-$(CONFIG_IMX072) += imx072.o imx072_reg.o
obj-$(CONFIG_WEBCAM_OV7692) += ov7692.o
obj-$(CONFIG_WEBCAM_OV7692_QRD) += ov7692_qrd.o
obj-$(CONFIG_OV5640) += ov5640.o
obj-$(CONFIG_MT9D112) += mt9d112.o mt9d112_reg.o
#/* <DTS2012041003722 sibingsong 20120410 begin */
#/* < DTS2012030604199 tangying 20120306 begin */
obj-$(CONFIG_HW_TORCH) += torch.o
#/* DTS2012030604199 tangying 20120306 end > */
#/* DTS2012041003722 sibingsong 20120410 end> */
#/*< DTS2012020400396 zhangyu 20120206 begin */
#/*< DTS2011112401319 yuguangcai 20111124 begin */
obj-$(CONFIG_HUAWEI_CAMERA_SENSOR_MT9D113) += mt9d113.o mt9d113_reg.o
#/* DTS2011112401319 yuguangcai 20111124 end > */
obj-$(CONFIG_FB_MSM_WRITEBACK_MSM_PANEL) += wfd/
#/* < DTS2011123001368 zhouqiwei 20111219 begin */
obj-$(CONFIG_HUAWEI_CAMERA_SENSOR_MT9V113) += mt9v113.o 
#/* DTS2011123001368 zhouqiwei 20111219 end > */
#/* DTS2012020400396 zhangyu 20120206 end > */

