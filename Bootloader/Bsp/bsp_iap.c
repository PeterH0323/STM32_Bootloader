/*-----------------------------------------------------------
 * Includes files
 *----------------------------------------------------------*/

/* lib includes. */
#include "bsp_iap.h"
#include "stm32f7xx.h"

typedef  void (*pFunction)(void);

/*!
* @brief 跳转到应用程序段
*        执行条件：无
* @param[in1] : 用户代码起始地址.
*
* @retval: 无
*/
void jump_to_app(uint32_t app_addr)
{ 
    
    pFunction jump_to_application;
    uint32_t jump_address;
    
    /* Check if valid stack address (RAM address) then jump to user application */
    if (((*(__IO uint32_t*)app_addr) & 0x2FFE0000 ) == 0x20000000)
    {
      /* Jump to user application */
      jump_address = *(__IO uint32_t*) (app_addr + 4);
      jump_to_application = (pFunction) jump_address;
      /* Initialize user application's Stack Pointer */
      __set_MSP(*(__IO uint32_t*) jump_address);
      jump_to_application();
    }    
    
}		 
