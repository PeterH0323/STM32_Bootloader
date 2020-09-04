/*-----------------------------------------------------------
 * Includes files
 *----------------------------------------------------------*/

/* lib includes. */
#include "bsp_iap.h"

typedef void (*iap_func)(void);				//定义一个函数类型的参数.   

iap_func jump2app; 


/*!
* @brief 设置栈顶地址
*        执行条件：无
* @param[in1] : 栈顶地址
*
* @retval: 无
*/
__asm void MSR_MSP(uint32_t addr) 
{
	MSR MSP, r0 			//set Main Stack value
	BX r14
}

/*!
* @brief 跳转到应用程序段
*        执行条件：无
* @param[in1] : 用户代码起始地址.
*
* @retval: 无
*/
void iap_load_app(uint32_t appxaddr)
{ 
	if(((*(volatile uint32_t*)appxaddr)&0x2FF00000)==0x20000000)	//检查栈顶地址是否合法.
	{ 
		jump2app=(iap_func)*(volatile uint32_t*)(appxaddr+4);		//用户代码区第二个字为程序开始地址(复位地址)		
		MSR_MSP(*(volatile uint32_t*)appxaddr);					//初始化APP堆栈指针(用户代码区的第一个字用于存放栈顶地址)
		jump2app();									//跳转到APP.
	}
}		 
