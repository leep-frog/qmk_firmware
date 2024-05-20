
// These codes are in sync with configuration in the arduino code
#define UART_WRITE_RUMBLE() uart_write('r')
#define UART_WRITE_SEND_DATA() uart_write('d')
#define UART_WRITE_DISCONNECT() uart_write('x')
#define UART_WRITE_LED_ON() uart_write('n')
#define UART_WRITE_LED_OFF() uart_write('f')

void led_on(void);
void led_off(void);
