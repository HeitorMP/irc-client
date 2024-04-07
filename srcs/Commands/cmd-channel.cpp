/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd-channel.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmaciel- <hmaciel-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/05 11:15:04 by hmaciel-          #+#    #+#             */
/*   Updated: 2024/04/05 17:09:45 by hmaciel-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cmd-proto.hpp"
#include <algorithm>
#include "User.hpp"


bool    executeChannelCommands(Command *cmd, User *user)
{
    std::vector<std::string> list = {"JOIN", "332", "353", "366"};
    std::string commandName = cmd->getCommand();

    if (find(list.begin(), list.end(), commandName) == list.end()) 
    {
        return (false);
    }

    if (commandName == "JOIN")
    {
        int pos = cmd->getPrefix().find("!");
        std::string msgOwner = cmd->getPrefix().substr(0,pos);
        std::string channelName = cmd->getData();
        
        if (msgOwner != user->getNick())
        {
            user->getCurrentChannel()->addUser(msgOwner);
        }
        // std::cout << msgOwner << " joined the channel: " << channelName << std::endl;
    }
    else if (commandName == "332")
    {
        std::vector<std::string>    params = cmd->getParams();
        std::string                 channelName = params[1]; // check for #
        std::string                 topic = cmd->getCommand();

        //futuramente adicionar a classe current channel.
        // std::cout << "Topic: " << topic << std::endl;
    }
    else if (commandName == "353")
    {
        std::vector<std::string>    params = cmd->getParams();
        std::string                 channelName = params[2]; // check for #

        std::vector<std::string> users = Command::split(cmd->getData());
        Channel *temp = new Channel(channelName, users);
        user->setNewChannel(temp);
        user->setCurrentChannel(temp);
    }
    return (true);
}


