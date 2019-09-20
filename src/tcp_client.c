#include "tcp.h"

bool    client_create(char *network_address, int network_port)
{
    (void)memset(&client, 0, sizeof(t_client));

    if ((client.sock = socket(AF_INET, SOCK_STREAM, 0)) == -1) {
        if (SOCKET_DEBUG)
            printf("%s: socket() failed\n", __func__);
        return false;
    }

    if ((client.sock_flags = fcntl(client.sock, F_GETFL)) == -1) {
        (void)close(client.sock);
        if (SOCKET_DEBUG)
            printf("%s: fcntl(F_GETFL) failed\n", __func__);
        return false;
    }

    if (fcntl(client.sock, F_SETFL, client.sock_flags | O_NONBLOCK) == -1) {
        (void)close(client.sock);
        if (SOCKET_DEBUG)
            printf("%s: fcntl(F_SETFL, O_NONBLOCK) failed\n", __func__);
        return false;
    }
    client.is_blocking = false;

    client.server_address.sin_family = AF_INET;
    client.server_address.sin_port = htons(network_port);                                 /* PORT */

    if (inet_pton(AF_INET, network_address, &client.server_address.sin_addr) == -1) {     /* ADDR */
        (void)close(client.sock);
        if (SOCKET_DEBUG)
            printf("%s: inet_pton(%s) failed\n", __func__, network_address);
        return false;
    }

    client.status |= sock_created;
    errno = 0;
    if (connect(client.sock, (struct sockaddr *)&client.server_address, (socklen_t)sizeof(client.server_address)) == -1)
    {
        if (errno == EINPROGRESS)
            return true ;        
        if (SOCKET_DEBUG)
            printf("%s: connect() failed\n", __func__);
        client.status &= ~sock_created;
        (void)close(client.sock);
        return false ;
    }

    client.status |= sock_connected;
    return true;
}

bool client_connect()
{
    int ret, sock_error, sock_len;

    FD_ZERO(&client.fdset);
    FD_SET(client.sock, &client.fdset);
    client.tv.tv_sec = 0;
    client.tv.tv_usec = 1000;
    ret = select(client.sock + 1, NULL, &client.fdset, NULL, &client.tv);
    if (ret == 0)
        return false ;                              /* select timed out, wait? */
    if (ret == 1)
    {
        sock_error = -1;
        sock_len = sizeof(sock_error);

        if (getsockopt(client.sock, SOL_SOCKET, SO_ERROR, &sock_error, (socklen_t *)&sock_len) == 0)
        {
            if (sock_error == 0)
            {
                client.status |= sock_connected;    /* ok */
                return true;
            }
            if (sock_error == EINPROGRESS)
                return false;                       /* wait */
        }
    }
    client.status &= ~sock_created;                 /* fail */
    close(client.sock);
    return false ;
}

bool client_send(uint8_t *octet)
{
    errno = 0;
    if (write(client.sock, octet, 1) != 1)
    {
        if ((errno == EWOULDBLOCK) || (errno == EAGAIN))
            return false ;                          /* wait */
        client.status &= ~sock_connected;           /* fail */
        return false ;
    }
    client.status |= sock_data_sent;                /* ok */
    return true ;
}

bool client_recv(uint8_t *octet)
{
    errno = 0;
    if (read(client.sock, octet, 1) != 1)
    {
        if ((errno == EWOULDBLOCK) || (errno == EAGAIN))
            return false ;                          /* wait */
        client.status &= ~sock_connected;           /* fail */
        return false ;
    }
    client.status |= sock_data_received;            /* ok */
    return true ;
}
