#include <iostream>
#include <boost/asio.hpp>
#include <thread>
#include <csignal>
#include <mutex>
#include "User.hpp"
#include "Window.hpp"
#include "Command.hpp"

std::atomic<bool> stop_server(false);


std::vector<Command *>    getCommandList(std::string response)
{
    std::vector<Command *>  cmds;

    std::stringstream   ss(response);
    std::string         line;
    while (std::getline(ss, line)) {
        // generate a vector of commands, each line is a command.
        cmds.push_back(new Command(line));
    }
    return (cmds);
}

void receiveFromServer(boost::asio::ip::tcp::socket& socket, User *user1, Window *screen)
{
    const int BUFFER_SIZE = 1024;    
    std::string buffer;
    std::string fullMessage = "";

    while (!stop_server) {

        char tempBuffer[BUFFER_SIZE];
        boost::system::error_code error;

        size_t bytesRead = socket.read_some(boost::asio::buffer(tempBuffer, BUFFER_SIZE), error);
        if (error == boost::asio::error::eof) {
            std::cout << "Conexão fechada pelo servidor\n";
            stop_server = true;
            break;
        } else if (error) {
            std::cerr << "Erro ao ler do socket: " << error.message() << std::endl;
            stop_server = true;
            break;
        }

        buffer.append(tempBuffer, bytesRead);

        size_t newlinePos;
        while ((newlinePos = buffer.find('\n')) != std::string::npos) {
            std::string message = buffer.substr(0, newlinePos + 1);

            fullMessage += message + "\r\n";
            buffer.erase(0, newlinePos + 1);
        }

        std::vector<Command*>   cmds = getCommandList(fullMessage);

        for(auto cmd: cmds)
        {
            cmd->execute(socket, user1);
        }
        fullMessage = "";

        screen->redraw();
        std::string prompt = user1->getCurrentChannel()->getName() + ": ";
        mvwprintw(screen->prompt_scr, 1, 1, prompt.c_str());
        screen->renderChatScreen(user1);
        screen->refreshAll();
        wmove(screen->prompt_scr, 1, prompt.size());
        wrefresh(screen->prompt_scr);

        for(auto cmd: cmds)
        {
            delete (cmd);
        }
    }
}


bool    sendRequest(boost::asio::ip::tcp::socket& serverFd, std::string const &request)
{
    boost::system::error_code error;
    size_t bytes_transferred = serverFd.write_some(boost::asio::buffer(request), error);

    if (error) {
        std::cerr << "Erro ao enviar dados: " << error.message() << std::endl;
        return (false);
    }
    return (true);

}

int main(int argc, char *argv[])
{
    //TODO: all info from config file... 
    if (argc != 4)
    {
        std::cout << "/simple-irc NIKC SERVER PORT\n";
        exit (1);
    }

    std::string nick = argv[1];

    boost::asio::io_context io_context;
    boost::asio::ip::tcp::resolver resolver(io_context);
    auto endpoints = resolver.resolve(argv[2], argv[3]);
    boost::asio::ip::tcp::socket socket(io_context);
    boost::system::error_code erro_connection;

    boost::asio::connect(socket, endpoints, erro_connection);

    if (!erro_connection) {
        // std::cout << "Conexão bem-sucedida!" << std::endl;
    } else {
        std::cout << "Servidor indisponivel: " << erro_connection.message() << std::endl;
        exit(1);
    }
    std::string user = nick + "1";
    std::string realname = nick + " 1";
    User *user1 = new User(nick, user, realname);

    boost::system::error_code error;
    size_t bytes_transferred = socket.write_some(boost::asio::buffer(user1->getRequest()), error);
    if (error) {
        std::cerr << "Erro ao enviar dados: " << error.message() << std::endl;
        return (false);
    }

    if(!has_colors)
    {
        std::cout << "no colors\n";
    }
    initscr();

    raw();      // Habilita o buffer de linha
    keypad(stdscr, TRUE); // Habilita teclas especiais
    setlocale(LC_CTYPE, "");
    start_color();
    Window  screen;
    screen.initColors();

    // receive from server thread
    std::thread serverThread(receiveFromServer, std::ref(socket), user1, &screen);

    // Main Loop, send do server.
    while (!stop_server) {

        screen.redraw();

        std::string prompt = user1->getCurrentChannel()->getName() + ": ";
        std::string userInput = screen.getUserInput(prompt);
        wmove(screen.prompt_scr, 1, prompt.size());
        wrefresh(screen.prompt_scr);
        wrefresh(screen.chat_scr);
        if (!userInput.empty())
        {
            if (userInput.compare(0, 5, "/QUIT") == 0)
            {
                stop_server = true;
                break;
            }
            std::string request = user1->prepRequest(userInput);
            
            sendRequest(socket, request);
        }
        screen.renderChatScreen(user1);
        screen.refreshAll();
    }
    serverThread.join();
    socket.close();
    delwin(screen.chat_scr);
    delwin(screen.prompt_scr);
    delwin(screen.list_scr);
    endwin();

    return 0;
}
