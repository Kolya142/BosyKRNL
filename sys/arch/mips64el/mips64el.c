#define UART_BASE 0xBFD003F8
#define UART_REG(offset) (*(volatile unsigned char*)(UART_BASE + (offset)))

void uart_init() {
    UART_REG(3) = 0x80;

    UART_REG(0) = 0x01;
    UART_REG(1) = 0x00;

    UART_REG(3) = 0x03;

    UART_REG(2) = 0xC7;

    UART_REG(4) = 0x0B;
}

void uart_putc(char c) {
    while ((UART_REG(5) & 0x20) == 0);
    UART_REG(0) = c;
}

void cpu_init() {
    uart_init();
}
