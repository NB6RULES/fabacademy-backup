// CH32V003J4M6 daisy-chain node firmware - PATCHED
//
// Drop-in replacement for the original main.c. Re-flash every node in the
// chain with this file - they all run the same code.
//
// Changes vs. original:
//   1. rx_buf bumped from 32 -> 64 bytes. Supports chains up to 31 nodes
//      without overflow (was: 16 nodes).
//   2. UART baud raised from 9600 -> 115200. At 9600 baud the original
//      10 ms "wait for full message" delay only covered ~9.6 byte-times,
//      so beyond ~node 5 the message would be processed before all upstream
//      bytes had arrived. 115200 makes the 10 ms wait cover ~115 byte-times,
//      so any reasonable chain length now works.
//
// Pin map (unchanged):
//   PD6 = USART1 RX  (board pin 1 = DIN connector)
//   PD5 = USART1 TX  (board pin 8 = DOUT connector)
//   PC1 = button input, active LOW, internal pull-up
//   PA2 = status LED, mirrors own button state
//
// Protocol (unchanged):
//   Host sends:  0xAA
//   Each node forwards what it received, then appends:  <node_id> <state>
//   Final response back to host:
//     0xAA 0x01 <btn1> 0x02 <btn2> ... 0xNN <btnN>
//   where <btn> = 0x00 released, 0x01 pressed.

#include "debug.h"
#include <string.h>

#define POLL_CMD     0xAA
#define UART_BAUD    115200          // was 9600

volatile uint8_t rx_buf[64];         // was [32]
volatile uint8_t rx_len   = 0;
volatile uint8_t rx_ready = 0;

void UART_Init(void)
{
    GPIO_InitTypeDef  GPIO_InitStructure  = {0};
    USART_InitTypeDef USART_InitStructure = {0};
    NVIC_InitTypeDef  NVIC_InitStructure  = {0};

    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOD | RCC_APB2Periph_USART1, ENABLE);

    // PD6 = RX (pin 1) - floating input
    GPIO_InitStructure.GPIO_Pin   = GPIO_Pin_6;
    GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_IN_FLOATING;
    GPIO_Init(GPIOD, &GPIO_InitStructure);

    // PD5 = TX (pin 8) - alt-function push-pull
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
    NVIC_InitStructure.NVIC_IRQChannel                    = USART1_IRQn;
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority  = 1;
    NVIC_InitStructure.NVIC_IRQChannelSubPriority         = 1;
    NVIC_InitStructure.NVIC_IRQChannelCmd                 = ENABLE;
    NVIC_Init(&NVIC_InitStructure);

    USART_Cmd(USART1, ENABLE);
}

void USART1_IRQHandler(void) __attribute__((interrupt("WCH-Interrupt-fast")));
void USART1_IRQHandler(void)
{
    if (USART_GetITStatus(USART1, USART_IT_RXNE) != RESET)
    {
        uint8_t data = USART_ReceiveData(USART1);
        if (rx_len < sizeof(rx_buf))
        {
            rx_buf[rx_len++] = data;
        }
        rx_ready = 1;
    }
}

void UART_SendByte(uint8_t data)
{
    while (USART_GetFlagStatus(USART1, USART_FLAG_TXE) == RESET);
    USART_SendData(USART1, data);
    while (USART_GetFlagStatus(USART1, USART_FLAG_TC) == RESET);
}

void UART_SendBuf(uint8_t *buf, uint8_t len)
{
    for (uint8_t i = 0; i < len; i++)
    {
        UART_SendByte(buf[i]);
    }
}

void LED_Init(void)
{
    GPIO_InitTypeDef GPIO_InitStructure = {0};
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
    RCC_HSEConfig(RCC_HSE_OFF);                    // free PA2 from HSE alt-fn
    GPIO_InitStructure.GPIO_Pin   = GPIO_Pin_2;
    GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_Out_PP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOA, &GPIO_InitStructure);
}

void Button_Init(void)
{
    GPIO_InitTypeDef GPIO_InitStructure = {0};
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE);
    GPIO_InitStructure.GPIO_Pin   = GPIO_Pin_1;
    GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_IPU;   // input, pull-up
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOC, &GPIO_InitStructure);
}

uint8_t ReadButton(void)
{
    // Active-low button: pressed reads as 0, so invert.
    return (GPIO_ReadInputDataBit(GPIOC, GPIO_Pin_1) == Bit_RESET) ? 1 : 0;
}

int main(void)
{
    SystemCoreClockUpdate();
    Delay_Init();
    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_1);

    LED_Init();
    Button_Init();
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
    rx_len   = 0;
    rx_ready = 0;

    uint8_t my_state = 0;

    while (1)
    {
        my_state = ReadButton();
        // LED is inverted vs button: released = LED on, pressed = LED off.
        // my_state itself stays correct (1 = pressed) for the UART protocol.
        GPIO_WriteBit(GPIOA, GPIO_Pin_2, my_state ? Bit_RESET : Bit_SET);

        if (rx_ready)
        {
            // Wait briefly for any tail bytes still on the wire to land
            // in the ISR. At 115200 baud, 10 ms covers ~115 byte-times,
            // which is plenty for any realistic chain.
            Delay_Ms(10);
            rx_ready = 0;

            if (rx_buf[0] == POLL_CMD)
            {
                // Forward exactly what we received, untouched.
                UART_SendBuf((uint8_t *)rx_buf, rx_len);

                // Append our own data. node_id is auto-derived from how
                // many id/state pairs preceded us in the chain.
                uint8_t node_id = (rx_len - 1) / 2 + 1;
                UART_SendByte(node_id);
                UART_SendByte(my_state);
            }

            rx_len = 0;
        }
    }
}
