/*
 * CH32V003J4M6 — UART Daisy-Chain Hall Effect Node — PATCHED
 * ==========================================================
 *
 * Same protocol & wiring as the button node — drop-in compatible.
 *
 * Changes vs. the original Hall node code:
 *   1. UART baud raised 9600 -> 115200 to match the patched button nodes and
 *      the XIAO host. Mixing baud rates in the chain would break it.
 *   2. Added a 5-second LED blink at boot (10 cycles of 500 ms) so you can
 *      visually confirm the node has powered up.
 *   3. rx_buf / rx_new_byte cleared after the boot blink to discard any
 *      stale poll bytes captured while the blink was running.
 *
 * (rx_buf was already 96 bytes here, so no buffer bump needed — that limit
 *  already supports >40 nodes.)
 *
 * Pin assignment (SOP8):
 *   Pin 1 (PD6) = UART RX
 *   Pin 2 (VSS) = GND
 *   Pin 3 (PA2) = Status LED  (ON  = no magnet      / tool removed)
 *                             (OFF = magnet present / tool in place)
 *   Pin 4 (VDD) = 3.3 V
 *   Pin 5 (PC1) = Hall sensor OUT (active LOW, open-drain, internal pull-up)
 *   Pin 6 (PC2) = free
 *   Pin 7 (PC4) = free
 *   Pin 8 (PD5) = UART TX
 *
 * sensor_state byte sent on the chain:
 *   0x00 = magnet present (tool in place)
 *   0x01 = no magnet     (tool removed)
 */

#include "debug.h"

#define POLL_CMD      0xAA
#define UART_BAUD     115200      // was 9600
#define RX_BUF_SIZE   96
#define BYTE_TIMEOUT  3           // ms of idle line before treating message as complete

volatile uint8_t rx_buf[RX_BUF_SIZE];
volatile uint8_t rx_len = 0;
volatile uint8_t rx_new_byte = 0;

/* ---- UART ---- */

void UART_Init(void)
{
    GPIO_InitTypeDef  GPIO_InitStructure  = {0};
    USART_InitTypeDef USART_InitStructure = {0};
    NVIC_InitTypeDef  NVIC_InitStructure  = {0};

    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOD | RCC_APB2Periph_USART1, ENABLE);

    GPIO_InitStructure.GPIO_Pin  = GPIO_Pin_6;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
    GPIO_Init(GPIOD, &GPIO_InitStructure);

    GPIO_InitStructure.GPIO_Pin   = GPIO_Pin_5;
    GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_AF_PP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOD, &GPIO_InitStructure);

    USART_InitStructure.USART_BaudRate            = UART_BAUD;
    USART_InitStructure.USART_WordLength          = USART_WordLength_8b;
    USART_InitStructure.USART_StopBits            = USART_StopBits_1;
    USART_InitStructure.USART_Parity              = USART_Parity_No;
    USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
    USART_InitStructure.USART_Mode                = USART_Mode_Tx | USART_Mode_Rx;
    USART_Init(USART1, &USART_InitStructure);

    USART_ITConfig(USART1, USART_IT_RXNE, ENABLE);
    NVIC_InitStructure.NVIC_IRQChannel                   = USART1_IRQn;
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;
    NVIC_InitStructure.NVIC_IRQChannelSubPriority        = 0;
    NVIC_InitStructure.NVIC_IRQChannelCmd                = ENABLE;
    NVIC_Init(&NVIC_InitStructure);

    USART_Cmd(USART1, ENABLE);
}

void USART1_IRQHandler(void) __attribute__((interrupt("WCH-Interrupt-fast")));
void USART1_IRQHandler(void)
{
    if(USART_GetITStatus(USART1, USART_IT_RXNE) != RESET)
    {
        uint8_t data = (uint8_t)USART_ReceiveData(USART1);
        if(rx_len < RX_BUF_SIZE)
            rx_buf[rx_len++] = data;
        rx_new_byte = 1;
    }
}

void UART_SendByte(uint8_t data)
{
    while(USART_GetFlagStatus(USART1, USART_FLAG_TXE) == RESET);
    USART_SendData(USART1, data);
    while(USART_GetFlagStatus(USART1, USART_FLAG_TC) == RESET);
}

void UART_SendBuf(volatile uint8_t *buf, uint8_t len)
{
    for(uint8_t i = 0; i < len; i++)
        UART_SendByte(buf[i]);
}

/* ---- LED ---- */

void LED_Init(void)
{
    GPIO_InitTypeDef GPIO_InitStructure = {0};
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
    RCC_HSEConfig(RCC_HSE_OFF);
    GPIO_InitStructure.GPIO_Pin   = GPIO_Pin_2;
    GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_Out_PP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOA, &GPIO_InitStructure);
}

/* ---- Hall Sensor ---- */

void Hall_Init(void)
{
    GPIO_InitTypeDef GPIO_InitStructure = {0};
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE);
    GPIO_InitStructure.GPIO_Pin  = GPIO_Pin_1;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;  // open-drain output needs pull-up
    GPIO_Init(GPIOC, &GPIO_InitStructure);
}

uint8_t Hall_Read(void)
{
    /*
     * A3144 / OH3114: output pulls LOW when a magnet is present (active-low).
     * Returns 0x00 = magnet present (tool in place)
     *         0x01 = no magnet     (tool removed)
     */
    return (GPIO_ReadInputDataBit(GPIOC, GPIO_Pin_1) == Bit_RESET) ? 0x00 : 0x01;
}

/* ---- Main ---- */

int main(void)
{
    SystemCoreClockUpdate();
    Delay_Init();
    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_1);

    LED_Init();
    Hall_Init();
    UART_Init();

    // Power-up indicator: flash the LED for 5 seconds (10 cycles of 500 ms).
    // Lets you visually confirm the node has booted before the chain starts.
    for (uint8_t i = 0; i < 10; i++)
    {
        GPIO_WriteBit(GPIOA, GPIO_Pin_2, Bit_SET);
        Delay_Ms(250);
        GPIO_WriteBit(GPIOA, GPIO_Pin_2, Bit_RESET);
        Delay_Ms(250);
    }

    // Discard any bytes the host may have sent during the boot blink so we
    // don't process a stale poll as soon as the main loop starts.
    rx_len      = 0;
    rx_new_byte = 0;

    while(1)
    {
        uint8_t sensor = Hall_Read();

        /* LED on = magnet ABSENT = tool removed. (sensor itself stays correct
           for the UART protocol — only the LED polarity is flipped.) */
        GPIO_WriteBit(GPIOA, GPIO_Pin_2, sensor ? Bit_SET : Bit_RESET);

        if(rx_new_byte)
        {
            rx_new_byte = 0;

            // Wait for the line to go idle for BYTE_TIMEOUT ms before
            // deciding the upstream message is complete. This is robust
            // across any chain length without needing a fixed delay.
            uint8_t waited = 0;
            while(waited < BYTE_TIMEOUT)
            {
                Delay_Ms(1);
                if(rx_new_byte) { rx_new_byte = 0; waited = 0; }
                else            { waited++; }
            }

            if(rx_len > 0 && rx_buf[0] == POLL_CMD)
            {
                UART_SendBuf(rx_buf, rx_len);

                uint8_t node_id = (rx_len - 1) / 2 + 1;

                UART_SendByte(node_id);
                UART_SendByte(sensor);   // 0x00 = tool present, 0x01 = tool removed
            }

            rx_len = 0;
        }
    }
}
