/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   User.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmaciel- <hmaciel-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/30 16:05:26 by hmaciel-          #+#    #+#             */
/*   Updated: 2024/04/07 22:21:59 by hmaciel-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

# include <vector>
# include <map>
# include <iostream>
# include <sys/socket.h>
# include "Channel.hpp"
# include "Command.hpp"
# include <boost/asio.hpp>
#include "cmd-proto.hpp"


class Window;

class User
{
    private:
        Channel*    currentChannel;
        
        std::string nick;
        std::string user;
        std::string realname;
        std::string request;
        
        std::map<std::string, std::string> commandMap;
        std::vector<Channel *>    channels;

    public:
        std::string userInput;
        
        User(std::string nick, std::string user, std::string realname);
        ~User();

        std::string getNick();
        std::string getUser();
        std::string getRealName();
        Channel *   getCurrentChannel();
        std::string getRequest();
        std::vector<Channel *> getChannels();

        void    setRequest(std::string newRequest);
        void    setCurrentChannel(Channel * newChannel);
        void    setNewChannel(Channel * newChannel);
        bool    sendRequest(boost::asio::ip::tcp::socket& serverFd);

        /* commands */
        bool    prepRequest(std::string request);
        void    executeCommand(boost::asio::ip::tcp::socket& serverFd, std::string response);
};