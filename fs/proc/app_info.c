/*
 *  linux/fs/proc/app_info.c
 *
 *
 * Changes:
 * mazhenhua      :  for read appboot version and flash id.
 */

#include <linux/types.h>
#include <linux/errno.h>
#include <linux/time.h>
#include <linux/kernel.h>
#include <linux/kernel_stat.h>
#include <linux/fs.h>
#include <linux/tty.h>
#include <linux/string.h>
#include <linux/mman.h>
#include <linux/quicklist.h>
#include <linux/proc_fs.h>
#include <linux/ioport.h>
#include <linux/mm.h>
#include <linux/mmzone.h>
#include <linux/pagemap.h>
#include <linux/interrupt.h>
#include <linux/swap.h>
#include <linux/slab.h>
#include <linux/genhd.h>
#include <linux/smp.h>
#include <linux/signal.h>
#include <linux/module.h>
#include <linux/init.h>
#include <linux/seq_file.h>
#include <linux/times.h>
#include <linux/profile.h>
#include <linux/utsname.h>
#include <linux/blkdev.h>
#include <linux/hugetlb.h>
#include <linux/jiffies.h>
#include <linux/sysrq.h>
#include <linux/vmalloc.h>
#include <linux/crash_dump.h>
#include <linux/pid_namespace.h>
#include <linux/bootmem.h>
#include <asm/uaccess.h>
#include <asm/pgtable.h>
#include <asm/io.h>
#include <asm/tlb.h>
#include <asm/div64.h>
#include "internal.h"
#include <asm/setup.h>
#include <asm/mach-types.h>
#include <linux/hardware_self_adapt.h>
/*< DTS2011010505694  muyongquan 20110218 begin */     
#include "../../arch/arm/mach-msm/include/mach/socinfo.h"
/* DTS2011010505694  muyongquan 220110218 end >*/    
/*< DTS2012031203104 duanfei 20120313 begin */
#include <linux/touch_platform_config.h>
/* DTS2012031203104 duanfei 20120313 end >*/
#define PROC_MANUFACTURER_STR_LEN 30
#define MAX_VERSION_CHAR 40
#define BOARD_ID_LEN 20
/*< DTS2012032003522 zengxiangguang 20120320 begin */
/* Redefine board sub version id len here */
#define BOARD_ID_SUB_VER_LEN 10
/* DTS2012032003522 zengxiangguang 20120320 end >*/
#define LCD_NAME_LEN 20
/* < DTS2011082201029 liwei 20110819 begin */
#define HW_VERSION   20
#define HW_VERSION_SUB_VER  6
/* DTS2011082201029 liwei 20110819 end > */
/* < DTS2012021402175 yangxiaocong 20120213 begin */
/* < DTS2011122304248 liurennianKF62391 20111227 begin */
#define AUDIO_PROPERTY_LEN 20
/* DTS2011122304248 liurennianKF62391 20111227 end > */
/* DTS2012021402175 yangxiaocong 20120213 end > */

static char appsboot_version[MAX_VERSION_CHAR + 1];
static char str_flash_nand_id[PROC_MANUFACTURER_STR_LEN] = {0};
static u32 camera_id;
static u32 ts_id;
/* <DTS2010071502918 shenjinming 20101008 begin */
#ifdef CONFIG_HUAWEI_POWER_DOWN_CHARGE
static u32 charge_flag;
#endif
/* DTS2010071502918 shenjinming 20101008 end> */ 
/* <DTS2012020903868 xiewen 20120209 begin */
typedef struct
{
   int  mach_type; 
   char s_board_id[BOARD_ID_LEN];
   char hw_version_id[HW_VERSION];
}s_board_hw_version_type;

/* this is s_board_id and hw_version_id list,
 * when you want to add s_board_id and hw_version_if for new product,
 * add you s_board_id and hw_version_id this list.
 */
const s_board_hw_version_type s_board_hw_version_table[] =
{  /* machine_arch_type        s_board_id      hw_version_id */
   /*27A platform*/
   {MACH_TYPE_MSM7X27A_U8815, "MSM7227A_U8815", "HD1U861M "},
   {MACH_TYPE_MSM7X27A_U8655, "MSM7225A_U8655", "HD1U8655M "},
   {MACH_TYPE_MSM7X27A_U8655_EMMC, "MSM7225A_U8665", "HD2U8655M "},
   {MACH_TYPE_MSM7X27A_C8655_NAND, "MSM7625A_C8655", "HC1C8655M "},
   {MACH_TYPE_MSM7X27A_U8185, "MSM7225A_U8185", "HD1U8185M "},
   {MACH_TYPE_MSM7X27A_UMTS, "MSM7X27A_UMTS", "BOM_MSM7X27A_UMTS "},
   {MACH_TYPE_MSM7X27A_CDMA, "MSM7X27A_CDMA", "BOM_MSM7X27A_CDMA "},
   {MACH_TYPE_MSM7X27A_M660, "MSM7625A_M660", "HC1M660M "},
   /* < DTS2012022504368 niguodong 20120228 begin */
   {MACH_TYPE_MSM7X27A_C8820, "MSM7627A_C8812","HC1C8812M "},
   /* DTS2012022504368 niguodong 20120228 end > */
   {MACH_TYPE_MSM7X27A_C8825D, "MSM7627A_C8825D","HC1C8820M "},
   {MACH_TYPE_MSM7X27A_U8661, "MSM7225A_U8661","HD1U8661M "},
   /*< DTS2012022300887 fengwei 20120224 begin */
   {MACH_TYPE_MSM7X27A_C8668D, "MSM7625A_C8668D","HC1C8668DM"},
   /* DTS2012022300887 fengwei 20120224 end >*/
   /*30 and 8X55 platform*/
   {MACH_TYPE_MSM7X30_U8800,"MSM7X30_U8800",""},
   {MACH_TYPE_MSM7X30_U8820,"MSM7X30_U8820",""},
   {MACH_TYPE_MSM7X30_U8800_51,"MSM7X30_U8800-51",""},
   {MACH_TYPE_MSM8255_U8800_PRO,"MSM8255_U8800-PRO",""},
   {MACH_TYPE_MSM8255_U8860,"MSM8255_U8860","HD2U886M "},
   {MACH_TYPE_MSM8255_C8860,"MSM8255_C8860","HC1C886M "},
   {MACH_TYPE_MSM8255_U8860LP,"MSM8255_U8860LP","HD2U886M "},
   {MACH_TYPE_MSM8255_U8860_51,"MSM8255_U8860-51","HD3U886M01 "},
   {MACH_TYPE_MSM8255_U8860_92,"MSM8255_U8860-92","HD4U886M "},
   {MACH_TYPE_MSM8255_U8680,"MSM8255_U8680","HD1U868M "},
   {MACH_TYPE_MSM8255_U8730,"MSM8255_U8730","HD1U873M "},
   {MACH_TYPE_MSM8255_U8667,"MSM8255_U8667","HD1U866M "},
   /* < DTS2012022905490 ganfan 20120301 begin */
   {MACH_TYPE_MSM8255_U8860_R,"MSM8255_U8860-R","HD5U886M "},
   /* DTS2012022905490 ganfan 20120301 end > */
};

void set_s_board_hw_version(char *s_board_id,char *hw_version_id)
{  
    unsigned int temp_num = 0;
    unsigned int table_num = 0;

    if ((NULL == s_board_id) || (NULL == hw_version_id))
    {
         printk("app_info : s_board_id or hw_version_type is null!\n");    
         return ;
    }

    table_num = sizeof(s_board_hw_version_table)/sizeof(s_board_hw_version_type);
    for(temp_num = 0;temp_num < table_num;temp_num++)
    {
         if(s_board_hw_version_table[temp_num].mach_type == machine_arch_type )
         {
             memcpy(s_board_id,s_board_hw_version_table[temp_num].s_board_id, BOARD_ID_LEN-1);
             memcpy(hw_version_id,s_board_hw_version_table[temp_num].hw_version_id, HW_VERSION-1);
             break;
         }
    }

    if(table_num == temp_num)
    {
        memcpy(s_board_id,"ERROR", (BOARD_ID_LEN-1));
        memcpy(hw_version_id,"ERROR", HW_VERSION-1);
    }
}
/*===========================================================================


FUNCTION     set_s_board_hw_version_special

DESCRIPTION
  This function deal with special hw_version_id s_board_id and so on
DEPENDENCIES
  
RETURN VALUE
  None

SIDE EFFECTS
  None
===========================================================================*/
static void set_s_board_hw_version_special(char *hw_version_id,char *hw_version_sub_ver,
                                char *s_board_id,char *sub_ver)
{
                                             
    if ((NULL == s_board_id) || (NULL == sub_ver) || (NULL == hw_version_id) || (NULL == hw_version_sub_ver))
    {
         printk("app_info : parameter pointer is null!\n");    
         return ;
    }

    /* < DTS2012022504368 niguodong 20120228 begin */
	/* U8815 silk-screen display to VerB */
    if((HW_VER_SUB_VB <= get_hw_sub_board_id()) 
       &&(MACH_TYPE_MSM7X27A_U8815 == machine_arch_type))
    {
        memcpy(hw_version_id,"HD1U8815M ", BOARD_ID_LEN-1);
        sprintf(hw_version_sub_ver, "VER.%c", 'A'+(char)get_hw_sub_board_id());
        strcat(hw_version_id, hw_version_sub_ver);
        hw_version_id[HW_VERSION-1] = '\0';

    }    
    /* DTS2012022504368 niguodong 20120228 end > */

    if((MACH_TYPE_MSM7X30_U8820 == machine_arch_type)
       &&(socinfo_get_msm_cpu() == MSM_CPU_8X55))
    {
        memcpy(s_board_id,"MSM8255_U8820", BOARD_ID_LEN-1);
    	sprintf(sub_ver, ".Ver%c", 'A'+(char)get_hw_sub_board_id());
    	strcat(s_board_id, sub_ver);
        s_board_id[BOARD_ID_LEN-1] = '\0';
    }

    /* < DTS2012042408732 lixin 20120502 begin */
    if((MACH_TYPE_MSM8255_C8860 == machine_arch_type)
       &&(socinfo_get_msm_cpu() == MSM_CPU_8X55)
       &&(HW_VER_SUB_VB <= get_hw_sub_board_id()))
    {
        memcpy(hw_version_id,"HC1C886M ", BOARD_ID_LEN-1);
        sprintf(hw_version_sub_ver, "VER.%c", 'B');
        strcat(hw_version_id, hw_version_sub_ver);
        hw_version_id[HW_VERSION-1] = '\0';
    }
    /* DTS2012042408732 lixin 20120502 end > */

	if((MACH_TYPE_MSM7X30_U8800_51 == machine_arch_type)
       &&(HW_VER_SUB_VD == get_hw_sub_board_id()))
    {
        memcpy(s_board_id,"MSM7X30_U8800-51", BOARD_ID_LEN-1);
        sprintf(sub_ver, ".Ver%c", 'C');
    	strcat(s_board_id, sub_ver);
        s_board_id[BOARD_ID_LEN-1] = '\0';
    }

    /* change U8185 hw_version to VerB */
    if(MACH_TYPE_MSM7X27A_U8185 == machine_arch_type) 
    {
        if(HW_VER_SUB_VE > get_hw_sub_board_id()) 
        {
            memcpy(hw_version_id,"HD1U8185M ", BOARD_ID_LEN-1);
            sprintf(hw_version_sub_ver, "VER.%c", 'A'+(char)get_hw_sub_board_id() + 1);
            strcat(hw_version_id, hw_version_sub_ver);
            hw_version_id[HW_VERSION-1] = '\0';
        }
        /* add U8186 hw_version 
         * and the U8186 sub ver keep same as U8185 sub ver. 
         */ 
        else if(HW_VER_SUB_VE <= get_hw_sub_board_id())
        {
            memcpy(hw_version_id,"HD1U8186M ", BOARD_ID_LEN-1);
            sprintf(hw_version_sub_ver, "VER.%c", 'A'+(char)get_hw_sub_board_id() - 3);
            strcat(hw_version_id, hw_version_sub_ver);
            hw_version_id[HW_VERSION-1] = '\0';
        }
    }

    /*< DTS2012030601756 xiewen 20120306 begin */
    /*< DTS2012030701335 xiewen 20120307 begin */
    /* change sub version to right version */
    if((HW_VER_SUB_VE <= get_hw_sub_board_id()) &&
           (MACH_TYPE_MSM7X27A_U8655_EMMC == machine_arch_type))
    /* DTS2012030701335 xiewen 20120307 end >*/
    {
       memcpy(hw_version_id,"HD2U8655M ", BOARD_ID_LEN-1);
       sprintf(hw_version_sub_ver, ".Ver%c", 'A'+(char)get_hw_sub_board_id() -3);
       strcat(hw_version_id, hw_version_sub_ver);
       hw_version_id[HW_VERSION-1] = '\0';
    }
    /* DTS2012030601756 xiewen 20120306 end >*/
}
/* DTS2012020903868 xiewen 20120209 end >*/


/* same as in proc_misc.c */
static int
proc_calc_metrics(char *page, char **start, off_t off, int count, int *eof, int len)
{
	if (len <= off + count)
		*eof = 1;
	*start = page + off;
	len -= off;
	if (len > count)
		len = count;
	if (len < 0)
		len = 0;
	return len;
}

#define ATAG_BOOT_READ_FLASH_ID 0x4d534D72
static int __init parse_tag_boot_flash_id(const struct tag *tag)
{
    char *tag_flash_id=(char*)&tag->u;
    memset(str_flash_nand_id, 0, PROC_MANUFACTURER_STR_LEN);
    memcpy(str_flash_nand_id, tag_flash_id, PROC_MANUFACTURER_STR_LEN);
    
    printk("########proc_misc.c: tag_boot_flash_id= %s\n", tag_flash_id);

    return 0;
}
__tagtable(ATAG_BOOT_READ_FLASH_ID, parse_tag_boot_flash_id);

/*parse atag passed by appsboot, ligang 00133091, 2009-4-13, start*/
#define ATAG_BOOT_VERSION 0x4d534D71 /* ATAG BOOT VERSION */
static int __init parse_tag_boot_version(const struct tag *tag)
{
    char *tag_boot_ver=(char*)&tag->u;
    memset(appsboot_version, 0, MAX_VERSION_CHAR + 1);
    memcpy(appsboot_version, tag_boot_ver, MAX_VERSION_CHAR);
     
    //printk("nand_partitions.c: appsboot_version= %s\n\n", appsboot_version);

    return 0;
}
__tagtable(ATAG_BOOT_VERSION, parse_tag_boot_version);


#define ATAG_CAMERA_ID 0x4d534D74
static int __init parse_tag_camera_id(const struct tag *tag)
{
    char *tag_boot_ver=(char*)&tag->u;
	
    memcpy((void*)&camera_id, tag_boot_ver, sizeof(u32));
     
    return 0;
}
__tagtable(ATAG_CAMERA_ID, parse_tag_camera_id);


#define ATAG_TS_ID 0x4d534D75
static int __init parse_tag_ts_id(const struct tag *tag)
{
    char *tag_boot_ver=(char*)&tag->u;
	
    memcpy((void*)&ts_id, tag_boot_ver, sizeof(u32));
     
    return 0;
}


__tagtable(ATAG_TS_ID, parse_tag_ts_id);


/* < DTS2011042703449  liujinggang 20110427 begin */
static int app_version_read_proc(char *page, char **start, off_t off,
				 int count, int *eof, void *data)
{
	int len;
    /* <BU5D10533 duangan 2010-5-26 begin */
	// char *ker_ver = "HUAWEI_KERNEL_VERSION";
	char *ker_ver = HUAWEI_KERNEL_VERSION;
    /* BU5D10533 duangan 2010-5-26 end> */
	char *lcd_name = NULL;
	/*< DTS2012031203104 duanfei 20120313 begin */
	char * touch_info = NULL;
	/* DTS2012031203104 duanfei 20120313 end >*/
	/* <DTS2012020706466 xiewen 20120207 begin */
	char *wifi_device_name = NULL;
	/* DTS2012020706466 xiewen 20120207 end> */
	/* < DTS2012021402175 yangxiaocong 20120213 begin */
	/* < DTS2011122304248 liurennianKF62391 20111227 begin */
	char audio_property[AUDIO_PROPERTY_LEN] = {0};
	/* DTS2011122304248 liurennianKF62391 20111227 end > */
	/* DTS2012021402175 yangxiaocong 20120213 end > */
	/* < DTS2012020902104 zhangmin 20120209 begin */
	/*print sensor info into app_info*/
	/*< DTS2012032003522 zengxiangguang 20120320 begin */
	/* Array **_**_id must be large enough to hold both id and sub id */
	/* 'cause the following code would call strcat function to connect */
	/* sub id to array **_**_id[] */
	char s_board_id[BOARD_ID_LEN + BOARD_ID_SUB_VER_LEN] = {0};
    char sub_ver[BOARD_ID_SUB_VER_LEN] = {0};
	/* < DTS2011082201029 liwei 20110819 begin */
	char hw_version_id[HW_VERSION + HW_VERSION_SUB_VER] = {0};
	char hw_version_sub_ver[HW_VERSION_SUB_VER] = {0};	
	/* DTS2011082201029 liwei 20110819 end > */
	/* DTS2012032003522 zengxiangguang 20120320 end >*/
	char *compass_gs_name = NULL;
	char *sensors_list_name = NULL;
    /*<DTS2012020903868 xiewen 20120209 begin */
    set_s_board_hw_version(s_board_id,hw_version_id);
    sprintf(sub_ver, ".Ver%c", 'A'+(char)get_hw_sub_board_id());
   sprintf(hw_version_sub_ver, "VER.%c", 'A'+(char)get_hw_sub_board_id());
    /* DTS2012020903868 xiewen 20120209 end >*/
    strcat(s_board_id, sub_ver);
    /* < DTS2011082201029 liwei 20110819 begin */
    strcat(hw_version_id, hw_version_sub_ver);
	/* DTS2011082201029 liwei 20110819 end > */
    /*<DTS2012020903868 xiewen 20120209 begin */
    set_s_board_hw_version_special(hw_version_id,hw_version_sub_ver,s_board_id,sub_ver);
    /* DTS2012020903868 xiewen 20120209 end >*/
	compass_gs_name=get_compass_gs_position_name();
	sensors_list_name = get_sensors_list_name();
/* < BU5D10365 liujinggang 20100521 begin*/
	lcd_name = get_lcd_panel_name();
/* BU5D10365 liujinggang 20100521 end > */
	/* <DTS2012020706466 xiewen 20120207 begin */
	wifi_device_name = get_wifi_device_name();
	/* DTS2012020706466 xiewen 20120207 end> */
	/* < DTS2012021402175 yangxiaocong 20120213 begin */
	/* < DTS2011122304248 liurennianKF62391 20111227 begin */
	get_audio_property(audio_property);
	/* DTS2011122304248 liurennianKF62391 20111227 end > */
	/* DTS2012021402175 yangxiaocong 20120213 end > */
	/*< DTS2012031203104 duanfei 20120313 begin */
	touch_info = get_touch_info();
	if (touch_info == NULL)
	{
		touch_info = "Unknow touch";
	}
	/* DTS2012031203104 duanfei 20120313 end >*/
	
/* <DTS2010071502918 shenjinming 20101008 begin */
#ifdef CONFIG_HUAWEI_POWER_DOWN_CHARGE
    charge_flag = get_charge_flag();
    /* < DTS2011082201029 liwei 20110819 begin */
	/*< DTS2012031203104 duanfei 20120313 begin */
	/* <DTS2012020706466 xiewen 20120207 begin */
	/* < DTS2012021402175 yangxiaocong 20120213 begin */
	/* < DTS2011122304248 liurennianKF62391 20111227 begin */
	len = snprintf(page, PAGE_SIZE, "APPSBOOT:\n"
	"%s\n"
	"KERNEL_VER:\n"
	"%s\n"
	 "FLASH_ID:\n"
	"%s\n"
	"board_id:\n%s\n"
	"lcd_id:\n%s\n"
	"cam_id:\n%d\n"
	"ts_id:\n%d\n"
	"charge_flag:\n%d\n"
	"compass_gs_position:\n%s\n"
	"sensors_list:\n%s\n"
	"hw_version:\n%s\n"
    "wifi_chip:\n%s\n"
	"audio_property:\n%s\n"
	"touch_info:\n%s\n",
	appsboot_version, ker_ver, str_flash_nand_id, s_board_id, lcd_name, camera_id, ts_id,charge_flag, compass_gs_name,sensors_list_name, hw_version_id,wifi_device_name,audio_property, touch_info);
	/* DTS2012020706466 xiewen 20120207 end> */
#else
	len = snprintf(page, PAGE_SIZE, "APPSBOOT:\n"
	"%s\n"
	"KERNEL_VER:\n"
	"%s\n"
	 "FLASH_ID:\n"
	"%s\n"
	"board_id:\n%s\n"
	"lcd_id:\n%s\n"
	"cam_id:\n%d\n"
	"ts_id:\n%d\n"
	"compass_gs_position:\n%s\n"
	"sensors_list:\n%s\n"
	"hw_version:\n%s\n"
	"audio_property:\n%s\n"
	"touch_info:\n%s\n",
	appsboot_version, ker_ver, str_flash_nand_id, s_board_id, lcd_name, camera_id, ts_id, compass_gs_name,sensors_list_name, hw_version_id,audio_property, touch_info);
	/* DTS2011122304248 liurennianKF62391 20111227 end > */
	/* DTS2012021402175 yangxiaocong 20120213 end > */
	/* DTS2012031203104 duanfei 20120313 end >*/
	/* DTS2011082201029 liwei 20110819 end > */
#endif
	/* DTS2012020902104 zhangmin 20120209 end > */
/* DTS2010071502918 shenjinming 20101008 end> */ 	
	
	return proc_calc_metrics(page, start, off, count, eof, len);
}
/* DTS2011042703449  liujinggang 20110427 end > */

void __init proc_app_info_init(void)
{
	static struct {
		char *name;
		int (*read_proc)(char*,char**,off_t,int,int*,void*);
	} *p, simple_ones[] = {
		
        {"app_info", app_version_read_proc},
		{NULL,}
	};
	for (p = simple_ones; p->name; p++)
		create_proc_read_entry(p->name, 0, NULL, p->read_proc, NULL);

}


