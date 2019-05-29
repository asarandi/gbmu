#include "tcp.h"

bool    server_create()
{
    (void)memset(&server, 0, sizeof(t_server));

    if ((server.server_sock = socket(AF_INET, SOCK_STREAM, 0)) == -1)
    {
        if (SOCKET_DEBUG)
            printf("%s: socket() failed\n", __func__);
        return false;
    }

    if ((server.server_sock_flags = fcntl(server.server_sock, F_GETFL)) == -1)
    {
        (void)close(server.server_sock);
        if (SOCKET_DEBUG)
            printf("%s: fcntl(F_GETFL) failed\n", __func__);
        return false;
    }

    if (fcntl(server.server_sock, F_SETFL, server.server_sock_flags | O_NONBLOCK) == -1)
    {
        (void)close(server.server_sock);
        if (SOCKET_DEBUG)
            printf("%s: fcntl(F_SETFL, O_NONBLOCK) failed\n", __func__);
        return false;
    }


    server.server_opt = 1;
    if (setsockopt(server.server_sock, SOL_SOCKET, SO_REUSEADDR, &server.server_opt, sizeof(server.server_opt)) == -1)
    {
        (void)close(server.server_sock);
        if (SOCKET_DEBUG)
            printf("%s: setsockopt() failed\n", __func__);
        return false;
    }

    server.server_opt = 1;
    if (setsockopt(server.server_sock, SOL_SOCKET, SO_REUSEPORT, &server.server_opt, sizeof(server.server_opt)) == -1)
    {
        (void)close(server.server_sock);
        if (SOCKET_DEBUG)
            printf("%s: setsockopt() failed\n", __func__);
        return false;
    }

    server.server_address.sin_family = AF_INET;
    server.server_address.sin_addr.s_addr = inet_addr(server_listen_address);
    server.server_address.sin_port = htons(server_listen_port);
/*    server.server_address.sin_len = sizeof(server.server_address); */

	if (bind(server.server_sock, (struct sockaddr *)&server.server_address, (socklen_t)sizeof(server.server_address)) == -1)
    {
        (void)close(server.server_sock);
        if (SOCKET_DEBUG)
            printf("%s: bind() failed\n", __func__);
        return false;
    }

	if (listen(server.server_sock, 1) == -1)
    {
        (void)close(server.server_sock);
        if (SOCKET_DEBUG)
            printf("%s: listen() failed\n", __func__);
        return false;
    }

    server.status |= sock_created;
    return true;
}

bool server_accept()
{
    errno = 0;
    server.client_sock = accept(server.server_sock, (struct sockaddr *)&server.client_address, (socklen_t *) &server.client_address_len);
    if (server.client_sock == -1)
    {
        if ((errno == EWOULDBLOCK) || (errno == EAGAIN))
            return false ;                                  //wait
        else
        {
            server.status &= ~sock_created;                 //fail
            return false;
        }
    }
    else
        server.status |= sock_connected;                    //ok


    server.client_sock_flags = fcntl(server.client_sock, F_GETFL);
    fcntl(server.client_sock, F_SETFL, server.client_sock_flags | O_NONBLOCK);
    server.is_blocking = false ;

    return true;
}

bool server_send(uint8_t *octet)
{
    errno = 0;
    if (write(server.client_sock, octet, 1) != 1)
    {
        if ((errno == EWOULDBLOCK) || (errno == EAGAIN))
            return false ;                                  //wait
        server.status &= ~sock_connected;
        return false ;                                      //fail
    }
    server.status |= sock_data_sent;                        //ok
    return true ;
}

bool server_recv(uint8_t *octet)
{
    errno = 0;
    if (read(server.client_sock, octet, 1) != 1)
    {
        if ((errno == EWOULDBLOCK) || (errno == EAGAIN))
            return false ;                                  //wait
        perror("server_recv()");
        server.status &= ~sock_connected;                   //fail
        return false ;
    }
    server.status |= sock_data_received;                    //ok
    return true ;
}
