/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Window.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmaciel- <hmaciel-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/07 19:46:47 by hmaciel-          #+#    #+#             */
/*   Updated: 2024/04/07 20:54:24 by hmaciel-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

# include <ncurses.h>

class Window
{
    private:
        int parent_x, parent_y, new_x, new_y;
        int prompt_height;
        int list_width;


    public:
        WINDOW *chat;
        WINDOW *prompt;
        WINDOW *list;
        
        Window();
        ~Window();
        
        void    draw_borders(WINDOW *screen);
        void    refreshAll();
        void    redraw();

};