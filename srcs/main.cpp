#include <iostream>
#include <boost/asio.hpp>
#include <thread>
#include <csignal>
#include <mutex>
#include "User.hpp"
#include "Window.hpp"

std::mutex mtx;
std::atomic<bool> stop_server(false);

void receiveFromServer(boost::asio::ip::tcp::socket& socket, User *user1, Window *screen) {
// void receiveFromServer(boost::asio::ip::tcp::socket& socket, User *user1) {
    const int BUFFER_SIZE = 1024;    
    std::string buffer; // Buffer para armazenar os dados recebidos
    std::string fullMessage = "";

    while (!stop_server) {

        char tempBuffer[BUFFER_SIZE];
        boost::system::error_code error;

        // Ler os dados do socket para o buffer temporário
        size_t bytesRead = socket.read_some(boost::asio::buffer(tempBuffer, BUFFER_SIZE), error);

        if (error == boost::asio::error::eof) {
            std::cout << "Conexão fechada pelo servidor\n";
            break;
        } else if (error) {
            std::cerr << "Erro ao ler do socket: " << error.message() << std::endl;
            break;
        }
        if (bytesRead == 0)
        {
            std::cout << "aqui\n";
        }

        // Adicionar os dados lidos ao buffer principal
        buffer.append(tempBuffer, bytesRead);

        // Procurar por uma nova linha no buffer
        size_t newlinePos;
        while ((newlinePos = buffer.find('\n')) != std::string::npos) {
            // Processar a mensagem até a nova linha
            std::string message = buffer.substr(0, newlinePos + 1);

            fullMessage += message + "\r\n";
            // Remover a mensagem do buffer
            buffer.erase(0, newlinePos + 1);
        }

        // Verificar se houve um erro durante a leitura
        if (error && error != boost::asio::error::eof) {
            std::cerr << "Erro ao ler do socket: " << error.message() << std::endl;
            break;
        }
        // std::cout << fullMessage << std::endl;
        user1->executeCommand(socket, fullMessage);
        fullMessage = "";

        screen->redraw();
        mvwprintw(screen->prompt, 1, 1, (user1->getCurrentChannel()->getName() + ": ").c_str());
        std::vector<std::string> users = user1->getCurrentChannel()->getUsers();
        for ( int i = 0; i < users.size(); i++)
        {
            mvwprintw(screen->list, 1 + i, 1, users[i].c_str());
        }
        std::vector<std::string>    lines = user1->getCurrentChannel()->getChat();
        for ( int i = 0; i < lines.size(); i++)
        {
            mvwprintw(screen->chat, 1 + i, 1, lines[i].c_str());
        }
        screen->refreshAll();
    }
}

int main(int argc, char *argv[]) {

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

    initscr();
    raw();      // Habilita o buffer de linha
    keypad(stdscr, TRUE); // Habilita teclas especiais
    setlocale(LC_CTYPE, "");

    curs_set(FALSE);
	
    Window  screen;

    // receive from server thread
    std::thread serverThread(receiveFromServer, std::ref(socket), user1, &screen);

    // Main Loop, send do server.
    while (!stop_server) {

        std::string userInput;
        char str[100] = {0};

        screen.redraw();
        
        mvwprintw(screen.prompt, 1, 1, (user1->getCurrentChannel()->getName() + ": ").c_str());
        mvwgetstr(screen.prompt, 1, user1->getCurrentChannel()->getName().size() + 3, str);

        size_t length = strlen(str);
        if (length > 0 && str[length - 1] == '\n')
            snprintf(str + length - 1, sizeof(str) - length + 1, "\r\n");
        userInput = str;

        if (!userInput.empty())
        {
            if (userInput == "/QUIT")
            {
                stop_server = 1;
                break;
            }
            // Enviar mensagem para o servidor
            // user1->setRequest(userInput);
            user1->prepRequest(userInput);
            user1->sendRequest(socket);
        }
        screen.refreshAll();

        //shows channel activity -- methods in the future.
        std::vector<std::string> users = user1->getCurrentChannel()->getUsers();
        for ( int i = 0; i < users.size(); i++)
        {
            mvwprintw(screen.list, 1 + i, 1, users[i].c_str());
        }
        screen.refreshAll();
        std::vector<std::string>    lines = user1->getCurrentChannel()->getChat();
        for ( int i = 0; i < lines.size(); i++)
        {
            mvwprintw(screen.chat, 1 + i, 1, lines[i].c_str());
        }
        screen.refreshAll();
    }
    endwin();
    serverThread.join();
    socket.close();

    return 0;
}
