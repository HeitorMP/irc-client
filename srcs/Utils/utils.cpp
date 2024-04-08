/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmaciel- <hmaciel-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/08 18:43:36 by hmaciel-          #+#    #+#             */
/*   Updated: 2024/04/08 18:44:47 by hmaciel-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.hpp"


std::vector<std::string> split(const std::string &request)
{
    std::stringstream ss(request);  
    std::string word;
    std::vector<std::string> ret;
    while (ss >> word)
    {
        ret.push_back(word);
    }

    return (ret);
}

std::string  rejoin(std::vector<std::string> splited)
{
    std::string ret = "";
    
    if (splited.size() > 0)
    {
        size_t i = 0;

        for (i = 0; i < splited.size() - 1; i++)
        {
            ret += splited[i] + " ";
        }
        ret += splited[i] + "\r\n";
    }
    
    return (ret);
}