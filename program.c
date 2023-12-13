#define _POSIX_C_SOURCE 200201L
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <curses.h>
#include <time.h>

void draw(const int width, const int height);
void snake(const int width, const int height);

int main(){
    srand(time(NULL));
    initscr();
    start_color();
    init_pair(1, COLOR_YELLOW, COLOR_BLACK);
    init_pair(2, COLOR_GREEN, COLOR_BLACK);
    init_pair(3, COLOR_CYAN, COLOR_BLACK);
    init_pair(4, COLOR_BLUE, COLOR_BLUE);
    init_pair(5, COLOR_RED, COLOR_BLACK);
    init_pair(6, COLOR_MAGENTA, COLOR_BLACK);
    noecho();
    cbreak();
    keypad(stdscr, TRUE);
    // invisible cursor, visibility of cursor (0,1,2)
    curs_set(FALSE);
    // getch() will be non-blocking
    nodelay(stdscr, TRUE);

    int height = 8;
    int width = 30;
    draw(width, height);
    snake(width, height);
  

   
}
void snake(const int width, const int height){
    struct timespec ts = {
    .tv_sec = 0,                    // nr of secs
    .tv_nsec = 0.06 * 1000000000L  // nr of nanosecs
};
    char input;
    char snake = 'o';
    char drop = '#';
    char snack = '@';
    int z,l,j,c,i,u,o,a,b,help,score;
    help = 0;
    score = 0;
    u = 1;
    o = width - 1;
    z = (rand() % ((height-1)+1-1)+1);
    l = (rand() % ((width-1)+1-1)+1);
    j = (rand() % ((width-1)+1-1)+1);
    i = (rand() % ((width-1)+1-1)+1);

    c = 1;
    mvprintw(z, l, "%c", snake);
    refresh();
    nodelay(stdscr, TRUE);
    while(1){
            //random drops
            attron(COLOR_PAIR(4));
            mvprintw(c, i, "%c", drop);
            mvprintw(c, j, "%c", drop);
            mvprintw(c, o, "%c", drop);
            mvprintw(c, u, "%c", drop);
            attroff(COLOR_PAIR(4));
            if(c != 1){
                mvprintw(c - 1, i, " ");
                mvprintw(c - 1, j, " ");
                mvprintw(c - 1, u, " ");
                mvprintw(c - 1, o, " ");
            }
            refresh();
            nanosleep(&ts, NULL);  
            if(c < height){
                c++;
            }else{
                u = j;
                o = i;
                c = 0;
                j = (rand() % ((width-1)+1-1)+1);
                i = (rand() % ((width-1)+1-1)+1);
            }

            //random snack
            if(help == 0){
                a = (rand() % ((height-1)+1-1)+1);
                b = (rand() % ((width-1)+1-1)+1);
                while(b == i || b == j || b == o || b == u){
                    b = (rand() % ((width-1)+1-1)+1);
                }
                help = 1;
                mvprintw(a, b, "%c", snack);
            }else if((z == a) && (l == b)){
                score = score + help;
                help = 0;
                mvprintw(a, b, " ");
            }
            
            //movement of the snake
            input = getch();
            switch(input)   
            {
                case 's' : case 'S':
                    z++;
                    mvprintw(z - 1, l, " ");
                    break;
                case 'w' : case 'W':
                    z--;
                    mvprintw(z + 1, l, " ");
                    break;
                case 'd' : case 'D':
                    l++;
                    mvprintw(z, l - 1, " ");
                    break;
                case 'a' : case  'A':
                    l--;
                    mvprintw(z, l + 1, " ");
                    break;

            }
            if(((z == c) && (l == i)) || ((z == c) && (l == j)) || ((z == c) && (l == u)) || ((z == c) && (l == o))){
                beep();
                attron(COLOR_PAIR(5));
                mvprintw(height + 2, 2, "Game over! You hit the drop. ");
                refresh();
                attroff(COLOR_PAIR(5));
                break;
            }
            if(z  == height || l  == width || z  == 0 || l  == 0){
                beep();
                attron(COLOR_PAIR(5));
                mvprintw(height + 2, 2, "Game over! You hit the wall.");
                refresh();
                attroff(COLOR_PAIR(5));
                break;
            }else{
                mvprintw(z, l, "%c", snake);
                refresh();
                nanosleep(&ts, NULL);
            }
            
            attron(COLOR_PAIR(2));
            mvprintw(height + 1, 1, "Your score: %d",score); 
            refresh();    
            attroff(COLOR_PAIR(2)); 
                    
    }
    
    
    nodelay(stdscr, FALSE);
    getch();
    getch();
    endwin();
}
void draw(const int width, const int height){
   
    for(int i = 0; i <= height; i++){
        for(int j = 0; j <= width; j++){
            if(i == height || i == 0){
                attron(COLOR_PAIR(4));
                mvprintw(i,j,"#");
                refresh();
                attroff(COLOR_PAIR(4));
               
            }else if(j == 0 || j == width){
                attron(COLOR_PAIR(1));
                mvprintw(i,j,"|");
                refresh();
                attroff(COLOR_PAIR(1));
            }else{
                mvprintw(i,j," ");
                refresh();
            }
            
            
        }
        mvprintw(height - 4, width + 3, "Controls:");
        mvprintw(height - 3, width + 3, "[w]");
        mvprintw(height - 2, width + 3, "[a]");
        mvprintw(height - 1, width + 3, "[s]");
        mvprintw(height, width + 3, "[d]");
       
        refresh();
        
    }
    
}