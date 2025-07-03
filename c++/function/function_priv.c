/*******************************************************************************
* 文 件 名: function_priv.c
* 文件描述: 
* 备    注: 
* 作    者: HanKin
* 创建日期: 2025.06.26
* 修改日期：2025.06.26
*
* Copyright (c) 2025 HanKin. All rights reserved.
*******************************************************************************/
#include <stdio.h>

typedef struct usbmagic_automap_conf_callbacks {
    void *priv;
    /**
     * @brief 自动映射配置查询回调函数定义
     * @param priv usbmagic_mapctrl_open调用时传入的priv
     * @param conf 自动映射配置
     * @remark
     */
    void (*on_device_automap_conf_query)(void *priv, void *conf);
} usbmagic_automap_conf_callbacks;

int main( void )
{
    greeting_omit("" );
    greeting_unuse("");
    greeting_nowarning("");
    return  0 ;
}
/*

*/