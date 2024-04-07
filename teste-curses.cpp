
#include <ncurses.h>
#include <iostream>

int main(int argc, char *argv[]) 
{

    initscr();              //inicia o terminal em modo curses
    start_color();          // ativa cores;

    noraw();                // atividade apenas quando aperta enter;
    echo();                 // mostra oq ue esta sendo digitado;
    keypad(stdscr, TRUE);   //permite leitura de teclas de funcoes

    printw("Escreve na posicao 0,0");
    refresh();

    printw("Digite f1 f2 ou f3")
    do {

    } while( c!=KEY_F)

    endwin();

    return 0;
}
