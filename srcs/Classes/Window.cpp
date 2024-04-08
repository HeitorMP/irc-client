/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Window.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmaciel- <hmaciel-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/07 19:49:19 by hmaciel-          #+#    #+#             */
/*   Updated: 2024/04/08 19:54:37 by hmaciel-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Window.hpp"

Window::Window()
{
    
    getmaxyx(stdscr, parent_y, parent_x);
    prompt_height = 3;
    list_width = 20;

    chat_scr = newwin(parent_y - prompt_height, parent_x - list_width, 0, 0);
    list_scr = newwin(parent_y - prompt_height, list_width , 0, parent_x - list_width);
    prompt_scr = newwin(prompt_height, parent_x, parent_y - prompt_height, 0);
    
}

Window::~Window()
{
    ;
}

void Window::draw_borders(WINDOW *screen)
{
    int x, y, i;

    getmaxyx(screen, y, x);

    wclear(screen);

    // 4 corners
    mvwprintw(screen, 0, 0, "+");
    mvwprintw(screen, y - 1, 0, "+");
    mvwprintw(screen, 0, x - 1, "+");
    mvwprintw(screen, y - 1, x - 1, "+");

    // sides
    for (i = 1; i < (y - 1); i++) {
        mvwprintw(screen, i, 0, "|");
        mvwprintw(screen, i, x - 1, "|");
    }

    // top and bottom
    for (i = 1; i < (x - 1); i++) {
        mvwprintw(screen, 0, i, "-");
        mvwprintw(screen, y - 1, i, "-");
    }
}

void    Window::redraw()
{
    wbkgd(prompt_scr, COLOR_PAIR(PROMPT_COLOR));
    wbkgd(list_scr, COLOR_PAIR(USERLI_COLOR));
    wclear(chat_scr);
    wclear(prompt_scr);
    wclear(list_scr);
    // draw_borders(chat);
    // draw_borders(prompt);
    // draw_borders(list);
}

void    Window::refreshAll()
{
    wrefresh(chat_scr);
    wrefresh(prompt_scr);
    wrefresh(list_scr);
}

void    Window::initColors()
{
    init_pair(PROMPT_COLOR, COLOR_WHITE, COLOR_BLUE);
    init_pair(USERLI_COLOR, COLOR_WHITE, COLOR_BLUE);
    init_pair(CH_OPR_COLOR, COLOR_YELLOW, COLOR_BLUE);
    init_pair(MY_MSG_COLOR, COLOR_GREEN, COLOR_BLACK);
    init_pair(PV_MSG_COLOR, COLOR_RED, COLOR_BLACK);
}

std::string Window::getUserInput(std::string const &prompt)
{
    char str[100] = {0};

    mvwprintw(prompt_scr, 1, 1, prompt.c_str());
    mvwgetstr(prompt_scr, 1, prompt.size() + 1, str);

    size_t length = strlen(str);
    if (length > 0 && str[length - 1] == '\n')
        snprintf(str + length - 1, sizeof(str) - length + 1, "\r\n");

    return(str);
}

void    Window::renderChatScreen(User *usr)
{
    std::vector<std::string> users = usr->getCurrentChannel()->getUsers();
    std::vector<std::string> msgs = usr->getCurrentChannel()->getChat();
    for ( int i = 0; i < users.size(); i++)
    {
        (users[i][0] == '@') ? wattron(list_scr, COLOR_PAIR(CH_OPR_COLOR)) : wattroff(list_scr, COLOR_PAIR(CH_OPR_COLOR));
        mvwprintw(list_scr, 1 + i, 1, users[i].c_str());
    }
    for ( int i = 0; i < msgs.size(); i++)
    {
        std::string user_format = "[" + usr->getNick(); + "]";
        std::string private_format = "[PRIVATE]";
        if (msgs[i].compare(0, user_format.length(), user_format) == 0)
        {
            wattron(chat_scr, COLOR_PAIR(MY_MSG_COLOR));
        }
        else if (msgs[i].compare(0, private_format.length(), private_format) == 0)
        {
            wattron(chat_scr, COLOR_PAIR(PV_MSG_COLOR));
        }
        else 
        {
            wattroff(chat_scr, COLOR_PAIR(PV_MSG_COLOR));
            wattroff(chat_scr, COLOR_PAIR(MY_MSG_COLOR));
        }
        mvwprintw(chat_scr, 1 + i, 1, msgs[i].c_str());
    }
}


