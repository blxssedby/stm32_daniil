#include <stdint.h>

int main(void) {
    volatile uint32_t* RCC_APB2ENR = (uint32_t*)0x40021018;
    volatile uint32_t* GPIOA_CRH   = (uint32_t*)0x40010804;
    volatile uint32_t* USART1_BRR  = (uint32_t*)0x40013808;
    volatile uint32_t* USART1_CR1  = (uint32_t*)0x4001380C;
    volatile uint32_t* USART1_SR   = (uint32_t*)0x40013800;
    volatile uint32_t* USART1_DR   = (uint32_t*)0x40013804;

    *RCC_APB2ENR |= (1 << 2) | (1 << 14);
    *GPIOA_CRH = (*GPIOA_CRH & ~0xF0) | 0xB0;
    *USART1_BRR = (39 << 4) | 1;
    *USART1_CR1 = (1 << 13) | (1 << 3) | (1 << 2);

    int style = 0;
    
    while(1) {
        char* message;
        
        switch(style) {
            case 0: message = "DANIIL\n"; break;
            case 1: message = "** Daniil **\n"; break;
            case 2: message = "==> Daniil <==\n"; break;
            case 3: message = "-D-A-N-I-I-L-\n"; break;
        }
        
        for(int i = 0; message[i] != '\0'; i++) {
            while(!(*USART1_SR & (1 << 7)));
            *USART1_DR = message[i];
        }
        
        style = (style + 1) % 4;
        for(volatile int j = 0; j < 1000000; j++);
    }
    
    return 0;
}