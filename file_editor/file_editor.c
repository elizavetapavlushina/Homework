#include <termios.h>
#include <sys/ioctl.h>
#include <signal.h>
#include <stdlib.h>
#include <curses.h>
#include <fcntl.h>

#define MAX_SIZE 255

void sig_winch(int signo){

  struct winsize size;
  ioctl(fileno(stdout), TIOCGWINSZ, (char *) &size);
  resizeterm(size.ws_row, size.ws_col);
  nodelay(stdscr, 1);
  while (wgetch(stdscr) != ERR);
  nodelay(stdscr, 0);
}
bool get_f_name(char * file_name){
  
  int c;                                                                
  int i = 0;                                                            
  while ((c = getch()) != '\n') {                                   
    if (i < MAX_SIZE - 1){                                              
      file_name[i] = c;                                             
      i++;                                                          
    }                                                               
    else{                                                           
     // printw("the name is full\n");                                 
      return false;                                                        
    }
  }                                                                 
  refresh();                                                        
  file_name[i]='\0';

  return true;
}

int key_processing (WINDOW * wnd, char * buffer) {

  bool ex = true;                                                       
  int col = 0;                                                          
  int row = 0;                                                          
  int c = 0;                                                                                                                                   
  wmove(wnd, row, col);                                                 
  waddstr(wnd, buffer);                                                 
  wrefresh(wnd);                                                        
  noecho();

  while (ex) {
    wmove(wnd, row, col);                                                
    wrefresh(wnd);                                                       
    c = getch();

    switch (c) {                                                         
      case KEY_LEFT:                                                    
        if (col > 0) col--;                                             
        else flash();                                                  
         break;                                                          
                                                                         
      case KEY_DOWN:                                                    
        if (row < LINES - 1) row++;                                     
        else flash();                                                   
        break;                                                          
                                                                                
      case KEY_UP:                                                      
        if (row > 0) row--;                                             
        else flash ();                                                 
        break;                                                          
                                                                                
      case KEY_RIGHT:                                                   
        if (col < COLS - 1) col++;                                      
        else flash ();                                                  
        break;

      case KEY_BACKSPACE:
        if (col !=  0) {
          buffer[col] = ' ';
          waddch(wnd, ' ');
          col--;
          wmove(wnd, row, col);
        }
        else {
          waddch(wnd, ' ');
          buffer[col] = ' ';
        }
        break;

      case 27: // exit                                                  
        delwin(wnd);                                                    
        ex = false;                                                     
        break;                                                          

      default:                                                          
        waddch(wnd, c);                                                 
        buffer[col] = c;                                                
        col++;                                                          
        wmove(wnd, row, col);                                           
        break; 
    }
  }

  return 0;
}

int main(int argc, char ** argv){

  WINDOW * wnd;
  initscr();
  signal(SIGWINCH, sig_winch);
  keypad(stdscr, 1);
  noecho();

  bkgd(COLOR_PAIR(1));
  printw("Enter 'esc' to exit\n");
  printw("Enter 'o' to open the file\n");
  refresh();

  bool exit = true;
    while ( exit ){

       int ch = getch();
       switch (ch) {

          case 27: // exit
          exit = false;
          break;

          case 'o': // open 
          printw("\nEnter the file name:\n");
          echo();
          refresh();
          
          char file_name[MAX_SIZE] = "";
          if (get_f_name(file_name) == false) {
            printw("the name is full\n");
            refresh();
            exit = false;
            break;
          }

          int fd = 0;
          if((fd = open (file_name, O_CREAT, 0777)) == -1) {

            printw("Error opening the file\n");
            refresh();
            break;
          }

          char buffer[MAX_SIZE] = "";
          int size = 0;
          if ((size = read(fd, buffer, sizeof(buffer))) == -1)
          {
            printw("\nError reading the file\n");
            refresh();
            break;
          }
          close(fd);

          wnd = newwin(0, 0, 1, 0);
          wattron(wnd, A_BOLD);

          key_processing(wnd, buffer);
          delwin(wnd);

          if((fd = open (file_name,O_WRONLY, 0777)) == -1)
          {
            printw("Error opening the file\n");
            refresh();
            break;
          }
  
          if ((size = write(fd, buffer, sizeof(buffer))) == -1)
          {
            printw("Error reading the file\n");
            refresh();
            break;
          }
          close(fd);
       }

       clear();
       printw("Enter 'esc' to exit\n"); 
       printw("Enter 'o' to open the file\n");

       refresh();
    }

  endwin();

  return 0;
}
