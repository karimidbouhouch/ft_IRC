/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kid-bouh <kid-bouh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/13 10:11:31 by ilahyani          #+#    #+#             */
/*   Updated: 2023/05/30 23:46:20 by kid-bouh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "client.hpp"

client::client() {
    isGuest = true;
    isOpreator = false;
    loggedIn = false;
    isRegistered = false;
    wallops = true;
}

client:: client(int socket) : _socket(socket) {
    isGuest = true;
    isOpreator = false;
    loggedIn = false;
    isRegistered = false;
    wallops = true;
}

client::~client() {}

const int& client::getsocket() {
    return _socket;
}

const std::string& client::getNickname() {
    return _nickname;
}

const std::string& client::getRealname() {
    return _realname;
}

const std::string& client::getUsername() {
    return _username;
}

const std::string& client::getHostname() {
    return _hostname;
}

const std::string& client::getHostIp(){
    return _hostip;
}

void client::setHostIp(std::string hostip){
    _hostip = hostip;
}

const std::string& client::getPasswd() {
    return _passwd;
}

void client::setNickname(std::string nickname) {
    _nickname = nickname;
}

void client::setHostname(std::string hostName) {
   _hostname = hostName;
}

std::string client::get_format() {
    return getNickname() + "!" + getUsername() + "@" + getHostIp() + " ";
}

void client::response(std::string str) {
    print(":" + get_format() + str);
}

void client::responsefromServer(std::string str) {
    print(":" + getHostIp() + " " + str);
}

void client::print(std::string str) {
    std::string buff = str + "\r\n";
    if (send(_socket, buff.c_str(), buff.length(), 0) < 0)
        throw std::runtime_error("An error occurred while attempting to send a message to the client.\n");
}

void client::welcome(std::string dateCreated) {
    if (isGuest && !getNickname().empty() && !getRealname().empty() && !getUsername().empty())
    {
        isGuest = false;
        isRegistered = true;
        responsefromServer(RPL_WELCOME(getNickname(), "IRC", getUsername(), getHostIp()));   
        responsefromServer(RPL_YOURHOST(getNickname(), getHostIp()));
        responsefromServer(RPL_CREATED(getNickname(), dateCreated)); 
        responsefromServer(RPL_MOTD(getNickname(), "- " + getHostIp() + " Message of the day"));
        responsefromServer(RPL_MOTD(getNickname(), " ___________  _____  _____ ___________ _   _ "));
        responsefromServer(RPL_MOTD(getNickname(), "|_   _| ___ \\/  __ \\/  ___|  ___| ___ \\ | | |"));
        responsefromServer(RPL_MOTD(getNickname(), "  | | | |_/ /| /  \\/\\ `--.| |__ | |_/ / | | |"));
        responsefromServer(RPL_MOTD(getNickname(), "  | | |    / | |     `--. \\  __||    /| | | |"));
        responsefromServer(RPL_MOTD(getNickname(), " _| |_| |\\ \\ | \\__/\\/\\__/ / |___| |\\ \\\\ \\_/ /"));
        responsefromServer(RPL_MOTD(getNickname(), " \\___/\\_| \\_| \\____/\\____/\\____/\\_| \\_|\\___/ "));
        responsefromServer(RPL_MOTD(getNickname(), " "));
        responsefromServer(RPL_ENDOFMOTD(getNickname()));
        responsefromServer(RPL_UMODEIS(getNickname(), "+w"));
    }
}

void client::setRealname(std::string realname) { _realname = realname; }
void client::setUsername(std::string username) { _username = username; }
