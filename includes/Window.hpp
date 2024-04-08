/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Window.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmaciel- <hmaciel-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/07 19:46:47 by hmaciel-          #+#    #+#             */
/*   Updated: 2024/04/08 18:56:07 by hmaciel-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

# include <ncurses.h>
# include <iostream>
# include <vector>
# include <cstring>
# include "macros.hpp"
# include "User.hpp"


class Window
{
    private:
        int parent_x, parent_y, new_x, new_y;
        int prompt_height;
        int list_width;


    public:
        WINDOW *chat_scr;
        WINDOW *prompt_scr;
        WINDOW *list_scr;
        
        Window();
        ~Window();
        
        void    draw_borders(WINDOW *screen);
        void    refreshAll();
        void    redraw();

        void            initColors();
        void            renderChatScreen(User *usr);
        std::string     getUserInput(std::string const &pr);


};