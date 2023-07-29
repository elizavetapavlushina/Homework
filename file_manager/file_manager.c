#include <dirent.h>
#include <stdlib.h>
#include <sys/ioctl.h>
#include <signal.h>
#include <curses.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>

#define STR_SIZE 256

int dir_size;

typedef struct {

  char name[STR_SIZE];
  int type;

} file;

void sig_winch(int signo){                                                      

    struct winsize size;
    ioctl(fileno(stdout), TIOCGWINSZ, (char *) &size);
    resizeterm(size.ws_row, size.ws_col);
    nodelay(stdscr, 1);
    while (wgetch(stdscr) != ERR);
    nodelay(stdscr, 0);
}

int main(int argc, char ** argv){

    WINDOW * wnd_0;
    struct dirent **namelist;
    DIR *dir;
    struct dirent *entry;

    int window = 0;
    while (window == 0){

    dir_size = scandir(".", &namelist, 0, alphasort);
    if (dir_size < 0){
      perror("scandir");
      exit (1);
    }
    free(namelist);   

    dir = opendir(".");
    if (!dir) {
        perror("diropen");
        exit(1);
    }

    file *files = (file *)malloc(dir_size * sizeof(file));
    int i = 0;
    int size_dir = 1;

    while ( (entry = readdir(dir)) != NULL) {

        files[i].type = entry->d_type;
        strncpy(files[i].name, entry->d_name, sizeof(entry->d_name));

        i++;
    }

    free(entry);
    closedir(dir);

    initscr();
    signal(SIGWINCH, sig_winch);
    keypad(stdscr, 1);
    noecho();

    start_color();
    init_pair(1, COLOR_WHITE, COLOR_YELLOW);
    
    wnd_0 = newwin(0, 0, 0, 0);
    wbkgd(wnd_0, COLOR_PAIR(1));
    wattron(wnd_0, A_BOLD);
    
    wrefresh(wnd_0);

    for (int i = 0; i < dir_size; i++){
      wprintw(wnd_0, "%s\n", files[i].name);
    }
    wrefresh(wnd_0);

    int ex = 1;                                                       
    int col = 0;                                                          
    int row = 0;                                                          
    int c = 0;       
    int status;
    
    pid_t cpid;  
                                                                                                                                
    wmove(wnd_0, row, col); 
    wrefresh(wnd_0);

    while (ex == 1) {
    
      wmove(wnd_0, row, col);                                                
      wrefresh(wnd_0);                                                       
      c = wgetch(wnd_0);

      switch (c) {    
                                                         
        case 's':  // down                                             
          if (row < LINES - 1) row++;              

          else flash();                                                   
          break;                                                          
                                                                                
        case 'w':  //up                                                    
          if (row > 0) row--;                                
          else flash ();                                                 
          break;                                                   

        case 27: // exit Esc                                                                                                 
          ex = 0; 
          window = 1;  
          delwin(wnd_0);
          endwin();
          
          break;  

        case 10: // Enter

          if(row < dir_size){

            if (strcmp(files[row].name, ".") == 0) break;
            if ((files[row].type) == 4){

              ex = 0;
              chdir(files[row].name);
              break;

            } 
            
            delwin(wnd_0);
            endwin();

            cpid = fork();
            if (cpid == -1){

              perror("fork error");
              exit(EXIT_FAILURE);
            }
            if (cpid == 0){
              
              execl("/bin/vim", "vim", files[row].name, NULL);
              exit(EXIT_SUCCESS);

            }
            else {

              wait(&status);
              ex = 0;

              break;
            }
          } else break;                                                        

        case 'r': //run
        
          if(row < dir_size){

            delwin(wnd_0);
            endwin();

            cpid = fork();
            if (cpid == -1){

              perror("fork error");
              exit(EXIT_FAILURE);
            }
            if (cpid == 0){
              
              execl(files[row].name, files[row].name, NULL);

              exit(EXIT_SUCCESS);

            }
            else {
              wait(&status);
              ex = 0;
              break;
            }
          } else break;
      }
    }
    free(files);
  }
    exit(EXIT_SUCCESS);
}