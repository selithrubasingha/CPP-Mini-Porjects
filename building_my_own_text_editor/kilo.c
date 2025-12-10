#include <stdlib.h>
#include <termios.h>
#include <unistd.h>

// GLOBAL VARIABLE
// We need to store the original settings here so we can access them 
// later to restore the terminal when we quit.
struct termios orig_termios;

// FUNCTION: disableRawMode
// This is the "Cleanup Crew". It restores the terminal to normal.
void disableRawMode() {
  // Apply the 'orig_termios' settings to Standard Input.
  // TCSAFLUSH means "Wait for output to finish, and discard unread input."
  tcsetattr(STDIN_FILENO, TCSAFLUSH, &orig_termios);
}

// FUNCTION: enableRawMode
// This sets up the terminal for our text editor.
void enableRawMode() {
  // 1. Take a snapshot of the current terminal settings and save it in 'orig_termios'
  tcgetattr(STDIN_FILENO, &orig_termios);

  // 2. Register 'disableRawMode'. If the program crashes or finishes main(),
  //    the OS ensures disableRawMode is called automatically.
  atexit(disableRawMode);

  // 3. Make a copy of the settings into a new variable called 'raw'
  struct termios raw = orig_termios;

  // 4. Turn off the ECHO flag in the local flags (c_lflag).
  //    (Stop the terminal from printing typed keys automatically).
  raw.c_lflag &= ~(ECHO);

  // 5. Apply these new 'raw' settings to the terminal.
  tcsetattr(STDIN_FILENO, TCSAFLUSH, &raw);
}

int main() {
  // Turn on our custom settings immediately.
  enableRawMode();

  char c;
  
  // THE LOOP
  // read(STDIN_FILENO, &c, 1): Try to read 1 byte from keyboard into variable 'c'.
  // == 1: Did we successfully read 1 byte?
  // && c != 'q': AND is that byte NOT the letter 'q'?
  while (read(STDIN_FILENO, &c, 1) == 1 && c != 'q'); 
      // The semicolon ; here means "Do nothing inside the loop."
      // We are just processing input until 'q' is pressed.

  return 0;
}