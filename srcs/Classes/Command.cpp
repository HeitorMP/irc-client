/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Command.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmaciel- <hmaciel-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/03 16:23:55 by hmaciel-          #+#    #+#             */
/*   Updated: 2024/04/08 19:42:48 by hmaciel-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Command.hpp"

Command::Command(std::string response)
{
    size_t pos = 0;
    // Verifica se a mensagem começa com prefixo
    if (response[pos] == ':') {
        size_t endPrefix = response.find(' ', pos);
        if (endPrefix != std::string::npos) {
            this->prefix = response.substr(pos + 1, endPrefix - pos - 1);
            pos = endPrefix + 1;
        }
    } else { // checa se eh PONG
        size_t endPrefix = response.find(' ', pos);
         if (endPrefix != std::string::npos) {
            this->prefix = response.substr(pos, endPrefix - pos);
            pos = endPrefix + 1;
        }
    }
    // Encontra o comando
    size_t endCommand = response.find(' ', pos);

    if (endCommand != std::string::npos) {
        this->command = response.substr(pos, endCommand - pos);
        pos = endCommand + 1;
    } else {
        this->command = response.substr(pos);
        pos = response.size();
    }
     
    // Encontra os parâmetros
    while (pos < response.size()) {
        if (response[pos] == ':') {
            this->data = response.substr(pos + 1);
            this->params.push_back(response.substr(pos + 1));
            break;
        } else if (response[pos] != ' ') {
            size_t endParam = response.find(' ', pos);
            if (endParam != std::string::npos) {
                this->params.push_back(response.substr(pos, endParam - pos));
                pos = endParam + 1;
            } else {
                this->params.push_back(response.substr(pos));
                break;
            }
        }
    }
}

Command::~Command()
{
    ;
}

/* Getters */

std::string Command::getPrefix() const
{
    return (this->prefix);
}
std::string Command::getCommand() const
{
    return (this->command);
}

std::vector<std::string>    Command::getParams() const
{
    return (this->params);
}

std::string    Command::getData() const
{
    return (this->data);
}

// std::vector<std::string> Command::split(const std::string &request)
// {
//     std::stringstream ss(request);  
//     std::string word;
//     std::vector<std::string> ret;
//     while (ss >> word)
//     {
//         ret.push_back(word);
//     }

//     return (ret);
// }

// std::string Command::rejoin(std::vector<std::string> splited)
// {
//     std::string ret = "";
    
//     if (splited.size() > 0)
//     {
//         size_t i = 0;

//         for (i = 0; i < splited.size() - 1; i++)
//         {
//             ret += splited[i] + " ";
//         }
//         ret += splited[i] + "\r\n";
//     }
    
//     return (ret);
// }

std::map<std::string, std::string> Command::generateCommandMap()
{
    std::map<std::string , std::string> map;
    
    map["/join"] = "JOIN";
    map["/part"] = "PART";
    map["/msg"] = "PRIVMSG";
    
    return (map);
}

std::ostream& operator<<(std::ostream& os, Command& cmd)
{
    os << "Prefix: " << cmd.getPrefix() << std::endl;
    os << "Command: " << cmd.getCommand() << std::endl;
    os << "Params:" << std::endl;
    for (const auto& param : cmd.getParams()) {
        os << "- " << param << std::endl;
    }
    return os;
}


bool        Command::execute(boost::asio::ip::tcp::socket& socket, User *user)
{
    boost::system::error_code error;
    if(this->getPrefix() == "PING")
        {
            std::string sub = this->getCommand().substr(1);
            std::string response = "PONG " + sub + "\r\n";
          
            size_t bytes_transferred = socket.write_some(boost::asio::buffer(response), error); // no PING o ping eh prefixo e o parametro eh o command

            if (error) {
                std::cerr << "Erro ao enviar dados: " << error.message() << std::endl;
            }
        }
        else if(executeChannelCommands(this, user))
        {
            ;
            // std::cout << "executou join commands" << std::endl;
        }
        else if (this->getCommand() == "PRIVMSG")
        {
            int pos = this->getPrefix().find("!");
            std::string msgOwner = this->getPrefix().substr(0,pos);
            std::string msgFrom = this->getParams()[0];
            std::string message = this->getData();
            std::string toLog;
            if (msgFrom[0] != '#')
            {
                toLog = "[PRIVATE][" + msgOwner + "] - says in private: " + message;
            }
            else
            {
                toLog = "[" + msgOwner + "] - says: " + message;
            }
            user->getCurrentChannel()->addMessage(toLog);
        }
        else if(this->getCommand() == "001")
        {
            std::string toLog = this->getData();
            user->getCurrentChannel()->addMessage(toLog);
        }
        else
        {
            ;
            // std::cout << "entrou no else\n";
            // std::cout << cmd[0] << std::endl;
        }
        return (true);
}


        
        