/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Command.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmaciel- <hmaciel-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/03 16:21:48 by hmaciel-          #+#    #+#             */
/*   Updated: 2024/04/04 23:13:03 by hmaciel-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <iostream>
#include <sstream>
#include <vector>
#include <map>
#include "User.hpp"

class User;

class Command
{
    private:

        std::string prefix;
        std::string command;
        std::vector<std::string> params;
        std::string data;
        std::string type;
        
    public:
        Command(std::string);
        ~Command();

        std::string getPrefix() const;
        std::string getCommand() const;
        std::string getData() const;
        std::vector<std::string> getParams() const;

        static std::vector<std::string>             split(const std::string &request);
        static std::string                          rejoin(std::vector<std::string>);
        
        // /* Client request */
        static std::map<std::string, std::string>   generateCommandMap();

        // /* Server response */
        // static std::vector<std::vector<std::string>>    parseResponse(std::string);
        // static bool                                     executeCommand(User user1, std::vector<std::vector<std::string>> response);

        // /* Join */
        // static std::vector<std::string>    getUsersFromJoin(std::vector<std::string>);

};

std::ostream& operator<<(std::ostream& os, Command& cmd);

