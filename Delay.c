/**
 * @file    Delay.c
 * @brief   软件延时函数实现，适用于STC89C52等单片机
 */

/**
 * @brief  毫秒级延时函数（阻塞式）
 * @param  xms 延时时间，单位：毫秒
 * @note   该函数基于循环空操作实现，延时时间与主频相关
 */
void Delay(unsigned int xms)
{
    unsigned char i, j;
    while(xms--)
    {
        i = 2;      // 外层循环计数
        j = 239;    // 内层循环计数
        do
        {
            while (--j); // 内层延时
        } while (--i);   // 外层延时
    }
}

