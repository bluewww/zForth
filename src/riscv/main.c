
/*
 * Example zforth main app for atmega8. This is about the smallest environment
 * in which zForth can be useful. Memory could be saved by leaving out
 * ZF_ENABLE_BOOTSTRAP and provide the basic dictionary through some other
 * method, but that would make this example overly complicated.
 */

#include <stdint.h>
#include <stdarg.h>
#include <stddef.h>

#include "zforth.h"

#define UART_BAUD(baudrate)     ((F_CPU / baudrate) / 16 - 1)

typedef int FILE;
static int stdout;
static int stdin;

static void uart_init(uint16_t baudrate);
static int uart_tx(char c, FILE *f);
static int uart_rx(FILE *);
static FILE f;

static char buf[32];


int main(void)
{
	/* Setup stdin/stdout */

	uart_init(0);
	stdout = stdin = &f;


	/* Initialize zforth */

	zf_init(1);
	zf_bootstrap();
	zf_eval(": . 1 sys ;");


	/* Main loop: read words and eval */

	uint8_t l = 0;

	for(;;) {
		int c = getchar();
		putchar(c);
		if(c == 10 || c == 13 || c == 32) {
			zf_result r = zf_eval(buf);
			if(r != ZF_OK) puts("A");
			l = 0;
		} else if(l < sizeof(buf)-1) {
			buf[l++] = c;
		}

		buf[l] = '\0';
	}

}


zf_input_state zf_host_sys(zf_syscall_id id, const char *input)
{
	char buf[16];

	switch((int)id) {

		case ZF_SYSCALL_EMIT:
			putchar((char)zf_pop());
			fflush(stdout);
			break;

		case ZF_SYSCALL_PRINT:
			itoa(zf_pop(), buf, 10);
			puts(buf);
			break;
	}

	return 0;
}


zf_cell zf_host_parse_num(const char *buf)
{
	char *end;
        zf_cell v = strtol(buf, &end, 0);
	if(*end != '\0') {
                zf_abort(ZF_ABORT_NOT_A_WORD);
        }
        return v;
}


void uart_init(uint16_t baudrate)
{
}


static int uart_tx(char c, FILE *f)
{
    return 0;
}


int uart_rx(FILE *f)
{
    return 0;
}


/*
 * End
 */

