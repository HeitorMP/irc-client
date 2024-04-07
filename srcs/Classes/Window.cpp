/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Window.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmaciel- <hmaciel-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/07 19:49:19 by hmaciel-          #+#    #+#             */
/*   Updated: 2024/04/07 21:44:05 by hmaciel-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Window.hpp"
#include <iostream>

Window::Window()
{
    
    getmaxyx(stdscr, parent_y, parent_x);
    prompt_height = 3;
    list_width = 20;

    chat = newwin(parent_y - prompt_height, parent_x - list_width, 0, 0);
    list = newwin(parent_y - prompt_height, list_width , 0, parent_x - list_width);
    prompt = newwin(prompt_height, parent_x, parent_y - prompt_height, 0);
    
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
    draw_borders(chat);
    draw_borders(prompt);
    draw_borders(list);
}

void    Window::refreshAll()
{
    wrefresh(chat);
    wrefresh(prompt);
    wrefresh(list);
}


