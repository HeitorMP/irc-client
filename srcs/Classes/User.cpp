/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   User.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmaciel- <hmaciel-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/30 16:31:25 by hmaciel-          #+#    #+#             */
/*   Updated: 2024/04/08 13:31:53 by hmaciel-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "User.hpp"

User::User(std::string nick, std::string user, std::string realname)
{
    this->nick = nick;
    this->user = user;
    this->realname = realname;
    this->currentChannel = new Channel("#Server", {"-"});
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
    if (req[0] == '/')
    {
        std::vector<std::string>    splitedCmd = Command::split(req);
        std::map<std::string, std::string>::iterator it = this->commandMap.find(splitedCmd[0]);
        
        if (it == commandMap.end())
        {
            return (nullptr);
        }
        splitedCmd[0] = it->second;
        req = Command::rejoin(splitedCmd);
        this->request = req;
    }
    else
    {
        if (!req.empty())
        {
            std::string toLog = "[" + this->nick + "] - you say: " + req;
            this->currentChannel->addMessage(toLog);
            this->request = "PRIVMSG " + this->currentChannel->getName() + " :" + req + "\r\n";      
        }
        else
            return (nullptr);
    }
    return (this->request);
}

void    User::executeCommand(std::string response) // provisorio
{
    std::vector<Command *>  cmds;

    /* get line by line */
    std::stringstream   ss(response);
    std::string         line;
    while (std::getline(ss, line)) {
        // generate a vector of commands, each line is a command.
        cmds.push_back(new Command(line));
    }

    for (auto cmd: cmds) {
        
        if(executeChannelCommands(cmd, this))
        {
            ;
            // std::cout << "executou join commands" << std::endl;
        }
        else if (cmd->getCommand() == "PRIVMSG")
        {
            int pos = cmd->getPrefix().find("!");
            std::string msgOwner = cmd->getPrefix().substr(0,pos);
            std::string msgFrom = cmd->getParams()[0];
            std::string message = cmd->getData();
            std::string toLog;
            if (msgFrom[0] != '#')
            {
                toLog = "[PRIVATE][" + msgOwner + "] - says in private: " + message;
            }
            else
            {
                toLog = "[" + msgOwner + "] - says: " + message;
            }
            this->currentChannel->addMessage(toLog);
        }
        else if(cmd->getCommand() == "001")
        {
            std::string toLog = cmd->getData();
            this->currentChannel->addMessage(toLog);
        }
        else
        {
            ;
            // std::cout << "entrou no else\n";
            // std::cout << cmd[0] << std::endl;
        }
    }
    

    for (auto cmd: cmds) {
        delete (cmd);
    }
}