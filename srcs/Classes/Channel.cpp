/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Channel.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmaciel- <hmaciel-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/30 16:32:04 by hmaciel-          #+#    #+#             */
/*   Updated: 2024/04/05 17:20:53 by hmaciel-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Channel.hpp"

Channel::Channel(std::string name, std::vector<std::string> users)
{
    this->name = name;
    this->topic = "";
    this->users = users;
    // this->fileName = "." + name;
    

    // this->file.open(this->fileName, std::fstream::out | std::fstream::app);
    // this->file.close();
    // this->file.open(this->fileName, std::fstream::in | std::fstream::out | std::fstream::app);
    
}
Channel::~Channel()
{
    std::cout << "Channel deleted" << std::endl;
}

std::string                 Channel::getName()
{
    return (this->name);
}
std::string                 Channel::getTopic()
{
    return (this->topic);
}

std::vector<std::string>    Channel::getUsers()
{
    return (this->users);
}

std::vector<std::string>    Channel::getChat()
{
    return (this->chat);
}

void                        Channel::setName(std::string newName)
{
    this->name = newName;
}

void                        Channel::setTopic(std::string newTopic)
{
    this->topic = newTopic;
}

void                        Channel::setPrivate(bool newIsPrivate)
{
    this->isPrivate = newIsPrivate;
}

void                        Channel::addMessage(std::string message)
{
    this->chat.push_back(message);
}

void                        Channel::addUser(std::string newUser)
{
    this->users.push_back(newUser);
}

// void                       Channel::writeToFile(std::string message)
// {
//     this->file << message;
//     this->file.close();
//     this->file.open(this->fileName, std::fstream::in | std::fstream::out | std::fstream::app);
// }

// std::vector<std::string>                        Channel::readFile()
// {
//     std::string line;
    
//     if (this->file.is_open())
//     {
//         while (getline(this->file, line))
//         {
//             this->lines.push_back(line);
//         }    
//     }

//     return (this->lines);
// }