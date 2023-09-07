
// These codes are in sync with configuration in the arduino code
#define UART_WRITE_RUMBLE() uart_write('r')
#define UART_WRITE_SEND_DATA() uart_write('d')
#define UART_WRITE_DISCONNECT() uart_write('x')

void led_on(void);
void led_off(void);
