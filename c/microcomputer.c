

/**
 �������BTNC��16λLED�Ƶĵ�8λ��LD[7:0]����ʱ��ʾ��Ӧ��8λ�������أ�sw[7:0]�����������8λLED��Ϩ��
 �������BTNLһ�Σ���ʾ��LED�ƴ�������һλ�����Ƶ����λʱ���ٴλص����λ��ʾ��
 ����������Ϊ01100001ʱ��LED[15:0]��ʾΪ���������������� �������� ������������Lһ�Σ�LED����������һλ
 */

#include <stdio.h>
#include "xil_printf.h"
#include "xil_io.h"
#include "xgpio_l.h"

// 16��LED�Ϳ��صĶ���
#define SWITCHES_BASEADDR XPAR_AXI_GPIO_0_BASEADDR
#define LEDS_BASEADDR XPAR_AXI_GPIO_0_BASEADDR

// ��ť�Ķ���
#define BTNS_BASEADDR XPAR_AXI_GPIO_2_BASEADDR
#define BTNC_MASK 0x01 // BTNC
#define BTNL_MASK 0x04 // BTNL

int main() {
    unsigned short currentSwitchState;
    unsigned short led;  // LED��ʾ
    unsigned short currentBtn, lastBtn, realBtn;

    // ��ʼ��GPIO
    Xil_Out16(SWITCHES_BASEADDR + XGPIO_TRI_OFFSET, 0xffff);  // ���ÿ���Ϊ����
    Xil_Out16(LEDS_BASEADDR + XGPIO_TRI2_OFFSET, 0x0);  // ����LEDΪ���
    Xil_Out16(BTNS_BASEADDR + XGPIO_TRI_OFFSET, 0x1f);  // ���ð�ťΪ����

    while (1) {
        currentSwitchState = Xil_In16(SWITCHES_BASEADDR + XGPIO_DATA_OFFSET) & 0xffff;
        currentBtn = Xil_In8(BTNS_BASEADDR + XGPIO_DATA_OFFSET) & 0x1f;
        if (currentBtn) {  // ��ť������
            while (currentBtn) {  // ��ťδ�ͷ�
                currentBtn = Xil_In8(BTNS_BASEADDR + XGPIO_DATA_OFFSET) & 0x1f;
                realBtn = (currentBtn ^ lastBtn) & lastBtn;  // ��ȡ�����µİ�ť
                lastBtn = currentBtn;
                if (realBtn) {
                    break;
                }
            }
            // �ж��ĸ���ť������
            switch (realBtn) {
                case BTNC_MASK:  // BTNC����
                    led = currentSwitchState & 0x00FF;  // ��8λ��ʾ
                    break;

                case BTNL_MASK:  // BTNL����
					 if (led & 0x8000) {  // ������λ��1
                         led = (led << 1) | 1;  // ����һλ���������λ��1
					} else {
						led = led << 1;  // ����ֻ����һλ
					}
					break;
            }
        }

        // �����LED
        Xil_Out16(LEDS_BASEADDR + XGPIO_DATA2_OFFSET, led);
    }

    return 0;
}






