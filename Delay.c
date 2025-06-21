/**
 * @file    Delay.c
 * @brief   �����ʱ����ʵ�֣�������STC89C52�ȵ�Ƭ��
 */

/**
 * @brief  ���뼶��ʱ����������ʽ��
 * @param  xms ��ʱʱ�䣬��λ������
 * @note   �ú�������ѭ���ղ���ʵ�֣���ʱʱ������Ƶ���
 */
void Delay(unsigned int xms)
{
    unsigned char i, j;
    while(xms--)
    {
        i = 2;      // ���ѭ������
        j = 239;    // �ڲ�ѭ������
        do
        {
            while (--j); // �ڲ���ʱ
        } while (--i);   // �����ʱ
    }
}

