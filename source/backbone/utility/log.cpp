#include "log.hpp"

#include <iostream>
#include <fcntl.h>
#include <sys/ioctl.h>
#include <unistd.h>
#include <err.h>

/* ------------------------------------------------------------------------------------------------------- */

int
GetShellColumns() {
   struct winsize ws;
   int            fd;
   fd = open("/dev/tty", O_RDWR);
   if (fd < 0 || ioctl(fd, TIOCGWINSZ, &ws) < 0)
      err(8, "/dev/tty");
   const int shellColumns = ws.ws_col;
   close(fd);

   return shellColumns;
}

/* ------------------------------------------------------------------------------------------------------- */

void
PrintSeparator(char separator) {
   const int shellColumns = GetShellColumns();
   printf("%s", std::string(shellColumns, separator).c_str());
}

/* ------------------------------------------------------------------------------------------------------- */

void
PrintAtCenter(std::string message,
              std::string startDecorator,
              std::string endDecorator,
              bool        separatorAtStart,
              bool        separatorAtEnd) {
   const int shellColumns = GetShellColumns();

   int totalWhitespaces = shellColumns              //
                          - startDecorator.size()   //
                          - endDecorator.size()     //
                          - message.size();
   int leftWhitespaces  = totalWhitespaces / 2;
   int rightWhitespaces = totalWhitespaces - leftWhitespaces;

   if (separatorAtStart)
      printf("%s", std::string(shellColumns, '-').c_str());

   printf("\n%s", startDecorator.c_str());
   printf("%s", std::string(leftWhitespaces, ' ').c_str());
   printf("%s", message.c_str());
   printf("%s", std::string(rightWhitespaces, ' ').c_str());
   printf("%s\n", endDecorator.c_str());

   if (separatorAtEnd)
      printf("%s", std::string(shellColumns, '-').c_str());
}

/* ------------------------------------------------------------------------------------------------------- */
