/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   User.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmaciel- <hmaciel-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/30 16:31:25 by hmaciel-          #+#    #+#             */
/*   Updated: 2024/04/08 21:55:53 by hmaciel-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "User.hpp"
#include "Command.hpp"

class Command;

User::User(std::string nick, std::string user, std::string realname)
{
    this->nick = nick;
    this->user = user;
    this->realname = realname;
    this->currentChannel = new Channel("#Server", {""});
    this->request = "NICK " + nick + "\r\n" + "USER " + user + " * *:" + realname +"\r\n"; // fisrt send.
    this->userInput = "";
    

    this->commandMap = Command::generateCommandMap();
    
}

User::~User()
{
    ;
}

std::string User::getNick()
{
    return (this->nick);
}
std::string User::getUser()
{
    return (this->user);
}
std::string User::getRealName()
{
    return (this->realname);
}
Channel*    User::getCurrentChannel()
{
    return (this->currentChannel);
}
std::string User::getRequest()
{
    return (this->request);
}

std::vector<Channel *>  User::getChannels()
{
    return (this->channels);
}

void    User::setRequest(std::string newRequest)
{
    this->request = newRequest;
}

void    User::setCurrentChannel(Channel *newChannel)
{
    this->currentChannel = newChannel;
}

void    User::setNewChannel(Channel * newChannel)
{
    this->channels.push_back(newChannel);
}

std::string    User::prepRequest(std::string req)
{
    std::string ret = "";
    if (req[0] == '/')
    {
        std::vector<std::string>    splitedCmd = split(req);
        std::map<std::string, std::string>::iterator it = this->commandMap.find(splitedCmd[0]);
        
        if (it != commandMap.end())
        {
            splitedCmd[0] = it->second;
            ret = rejoin(splitedCmd);
        }
    }
    else
    {
        if (!req.empty())
        {
            std::string toLog = "[" + this->nick + "] - you say: " + req;
            this->currentChannel->addMessage(toLog);
            ret = "PRIVMSG " + this->currentChannel->getName() + " :" + req + "\r\n";
        }
        else
            return "";
    }
    return (ret);
}

