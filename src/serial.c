#include "gb.h"
#include "tcp.h"


#define GAMEBOY_CLOCK_SPEED                 4194304
#define SOCKET_RECONNECT_DELAY              4194304
#define SERIAL_CLOCK_SPEED                  8192

#define BIT_TRANSFER_CYCLES                 (GAMEBOY_CLOCK_SPEED / SERIAL_CLOCK_SPEED)
#define BYTE_TRANSFER_CYCLES                (BIT_TRANSFER_CYCLES * 8)

bool    is_online()
{
    if ((state->is_server) && (server.status & sock_created) && (server.status & sock_connected)) return true ;
    if ((state->is_client) && (client.status & sock_created) && (client.status & sock_connected)) return true ;
    return false ;
}

bool    socket_send(uint8_t *octet)
{
    if (!is_online()) return false ;
    if (state->is_server) return server_send(octet);
    if (state->is_client) return client_send(octet);
    return false ;
}

bool    socket_receive(uint8_t *octet)
{
    if (!is_online()) return false ;
    if (state->is_server) return server_recv(octet);
    if (state->is_client) return client_recv(octet);
    return false ;
}

void    serial_cleanup()
{
    if (state->is_server)
    {
        close(server.client_sock);
        close(server.server_sock);
        (void)memset(&server, 0, sizeof(t_server));
    }
    if (state->is_client)
    {
        close(client.sock);
        (void)memset(&client, 0, sizeof(t_client));
    }
}

void    set_blocking()
{
    if ((state->is_server) && (!server.is_blocking))
    {
        fcntl(server.client_sock, F_SETFL, server.client_sock_flags & (~O_NONBLOCK));
        server.is_blocking = true ;
    }
    if ((state->is_client) && (!client.is_blocking))
    {
        fcntl(client.sock, F_SETFL, client.sock_flags & (~O_NONBLOCK));
        client.is_blocking = true ;
    }
}

void    set_nonblocking()
{
    if ((state->is_server) && (server.is_blocking))
    {
        fcntl(server.client_sock, F_SETFL, server.client_sock_flags | O_NONBLOCK);
        server.is_blocking = false ;
    }
    if ((state->is_client) && (client.is_blocking))
    {
        fcntl(client.sock, F_SETFL, client.sock_flags | O_NONBLOCK);
        client.is_blocking = false ;
    }
}

void    serial_connect()
{
    static  uint64_t    create_cooldown;
    if (create_cooldown) {
        create_cooldown--;
        return ;
    }

    if (state->is_server)
    {
        if (!(server.status & sock_created))
        {
            if (!server_create(state->network_address, state->network_port))
                create_cooldown = SOCKET_RECONNECT_DELAY;
            return ;
        }
        if (!(server.status & sock_connected))
        {
            if (!server_accept())
                create_cooldown = SOCKET_RECONNECT_DELAY;
            return ;
        }
    }

    if (state->is_client)
    {
        if (!(client.status & sock_created))
        {
            if (!client_create(state->network_address, state->network_port))
                create_cooldown = SOCKET_RECONNECT_DELAY;
        }
        if (!(client.status & sock_connected))
        {
            if (!client_connect())
                create_cooldown = SOCKET_RECONNECT_DELAY;
        }
    }
}

/* static  uint8_t bit_counter; */
static  uint8_t current_bit;
static  bool    serial_init;
static  bool    is_master;
static  bool    is_slave;

void    bit_transfer_ok(uint8_t octet_recv)
{
    gb_mem[0xff01] = octet_recv;
/*    
    current_bit++;
    if (current_bit <= 8) return ;
    printf("new SB: 0x%02x\n", gb_mem[0xff01]);
*/
    current_bit = 1;
    gb_mem[0xff0f] |= 8;
	gb_mem[0xff02] &= 1;
    state->is_transfer = false ;
    state->serial_cycles = 0;
    serial_init = false;    
    is_master = false ;
    is_slave = false ;
}
void    master_offline()
{
    gb_mem[0xff01] = 0xff;
    gb_mem[0xff02] &= 1;
    gb_mem[0xff0f] |= 8;

}
void    master_init()
{
    uint8_t octet_send, octet_recv;

    set_blocking();
    octet_send = 0xfe;
    if (!socket_send(&octet_send)) {
        (void)master_offline();
        return ;
    }
    octet_recv = 0x00;
    if (!socket_receive(&octet_recv)) {
        (void)master_offline();
        return ;
    }
    if (octet_recv != 0xfc) {
        printf("master missed recv: %02x\n", octet_recv);
        (void)master_offline();
        return ;
    }
/*  
    printf("master SC: 0x%02x, SB: 0x%02x, ", gb_mem[0xff02], gb_mem[0xff01]);
 */
    state->is_transfer = true;
    current_bit = 1;
    serial_init = true;
    is_master = true ;
    is_slave = false ;
}

void    slave_init()
{
    uint8_t octet_send, octet_recv;

    set_nonblocking();
    octet_recv = 0x00;
    if (!socket_receive(&octet_recv)) return ;
    set_blocking();
    octet_send = 0xfc;
    if (!socket_send(&octet_send))    return ;
    if (octet_recv != 0xfe) {printf("slave missed recv: %02x\n", octet_recv); return ;}
/*    
    printf(" slave SC: 0x%02x, SB: 0x%02x, ", gb_mem[0xff02], gb_mem[0xff01]);
*/
    state->is_transfer = true;
    current_bit = 1;
    serial_init = true;    
    is_master = false ;
    is_slave = true ;
}

void    master_bit_transfer()
{
    uint8_t octet_send = 0, octet_recv = 0;

    octet_send = gb_mem[0xff01];
    if (!socket_send(&octet_send)) {
        (void)printf("%s: socketsend() failed\n", __func__);
        return ;
    }
    if (!socket_receive(&octet_recv)) {
        (void)printf("%s: socket_receive() failed\n", __func__);
        return ;
    }
    bit_transfer_ok(octet_recv);
}

void    slave_bit_transfer()
{
    uint8_t octet_send = 0, octet_recv = 0;

    set_blocking();
    if (!socket_receive(&octet_recv)) {
        (void)printf("%s: socket_receive() failed\n", __func__);
        return ;
    }
    octet_send =gb_mem[0xff01];
    if (!socket_send(&octet_send)) {
        (void)printf("%s: socket_send() failed\n", __func__);
        return ;
    }
    bit_transfer_ok(octet_recv);
}


void    serial(uint8_t current_cycles)
{
    serial_connect();

    if (!serial_init)
    {
        if ((gb_mem[0xff02] & 0x81) == 0x80)
            slave_init();   /* listen for incoming */
        if ((gb_mem[0xff02] & 0x81) == 0x81)
            master_init();  /* start transfer */
        return ;
    }

    if (!state->is_transfer)
        return ;

    state->serial_cycles += current_cycles;
    if ((state->serial_cycles >> 12) < current_bit)
        return ;
    if (is_slave)
        slave_bit_transfer();
    if (is_master)
        master_bit_transfer();
}

void    serial_data(uint8_t data)
{
    if (state->is_transfer)
        printf("writing to SB during transfer: current = %02x, new = %02x\n", gb_mem[0xff01], data);
    gb_mem[0xff01] = data;
}

void    serial_control(uint8_t data)
{
    gb_mem[0xff02] = data & 0x81;
    if (state->is_transfer)
        printf("writing to SC during transfer");
/*
    printf("serial control: %02x\n", gb_mem[0xff02]);
*/
    if ((!state->is_transfer) && ((gb_mem[0xff02] & 0x81) == 0x81))
    {
        if (!is_online()) {
            (void)master_offline();
            return ;
        }
        state->is_transfer = true;
    }
}
