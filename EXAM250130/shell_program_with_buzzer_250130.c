#include <io.h>
#include <time.h>
#include <string.h>
#include <command.h>
#include <panic.h>
#include <assert.h>
#include <errno.h>


#define BUZZ GPIO_NR(0,8) // Here we are defining the GPIO pin for the buzzer


void play_note(int frequency, int ms ) { // This is just a function to play one note, we gonna use it for play a tune.
	int delay_ms = 1/ (frequency);  // We calculate here the period
        int cycles = (frequency * ms)/1000; // And here how many cycles
	for (int i = 0; i < cycles; i++) {
		gpio_set(BUZZ, 1);  
		udelay(delay_ms);               
		gpio_set(BUZZ, 0);  
		udelay(delay_ms);               
	}
}

void play_tune(void) { // Function to play a simple tune
	play_note(260, 300); 
	play_note(280, 300);  
	play_note(300, 300);  
	play_note(320, 300);  
}

static int command_playtune(char **reply, int argc, char **argv) { // Declaring a function to add a shell command (same as the other comman)
	play_tune();
	return 0;
}

static struct command shell_commands[] = {
	COMMAND_R,
	COMMAND_W,
	COMMAND_GPIO,
	COMMAND_COMMIT,
	COMMAND_HELP,
	{"playtune",command_playtune, 2,2, // Command for playing a tune in the shell
	}
};

void main(void)
{

  buzzer_init(); // Calling the function into the main to initialize the GPIO
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
