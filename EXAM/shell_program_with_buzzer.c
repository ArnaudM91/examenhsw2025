#include <io.h>
#include <time.h>
#include <string.h>
#include <command.h>
#include <panic.h>
#include <assert.h>
#include <errno.h>


#define BUZZ GPIO_NR(0,8)

void play_tune(void) {
	int udelay = (500 * 1000);  
	for (int i = 0; i < 250; i++) {
		gpio_set(BUZZ, 1);  
		udelay(500 * 1000);               
		gpio_set(BUZZ, 0);  
		udelay(500 * 1000);               
	}
}

static int command_playtune(char **reply, int argc, char **argv) {
	play_tune();
	return 0;
}

static struct command shell_commands[] = {
	COMMAND_R,
	COMMAND_W,
	COMMAND_GPIO,
	COMMAND_COMMIT,
	COMMAND_HELP,
	{"playtune",command_playtune, 2,2, //Command for playing a tune in the shell
	}
};

void main(void)
{


	static char str[80];
	printf("%s: built on %s-%s\n", __FILE__, __DATE__, __TIME__);
	while (1) {

		if (polls(str, sizeof(str))) {
			command_parse(str, shell_commands);
			puts(command_reply);
			str[0] = '\0';
		}
	}
}
