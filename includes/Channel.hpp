/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Channel.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmaciel- <hmaciel-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/30 16:09:58 by hmaciel-          #+#    #+#             */
/*   Updated: 2024/04/05 17:20:22 by hmaciel-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

# include <vector>
# include <iostream>
# include <fstream>

class Channel 
{
    private:
        std::string                 name;
        std::string                 topic;
        std::vector<std::string>    users;
        bool                        isPrivate;

        // std::fstream                file;
        // std::string                 fileName;
        std::vector<std::string>    chat;

        

    public:
        Channel(std::string name, std::vector<std::string>);
        ~Channel();

        std::string                 getName();  
        std::string                 getTopic();
        std::vector<std::string>    getUsers();
        std::vector<std::string>    getChat();

        void                        setName(std::string newName);
        void                        setTopic(std::string newTopic);
        void                        setPrivate(bool newIsPrivate);
        
        void                        addMessage(std::string message);
        // std::vector<std::string>    readFile();
        // void                        writeToFile(std::string message);
        void                        addUser(std::string newUser);
};