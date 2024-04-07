/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd-proto.hpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmaciel- <hmaciel-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/05 11:16:54 by hmaciel-          #+#    #+#             */
/*   Updated: 2024/04/05 12:43:03 by hmaciel-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

# include "User.hpp"
# include "Command.hpp"

class Command;
class User;

bool    executeChannelCommands(Command *cmd, User *user);