#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "Zank.h"
#include "utils.h"

#define CLIENTS_MAX 10

/*
 * Later this will be passed from the command line
 *
 */
#define STR_PORT_NUM "7001"

void
run_server (void)
{
  struct addrinfo hints;
  struct addrinfo *result, *rp;
  int sfd, s;
  struct sockaddr_storage peer_addr;
  socklen_t peer_addr_len;
  char buf[BUF_SIZE];

  memset (&hints, 0, sizeof (struct addrinfo));
  hints.ai_family = AF_UNSPEC;
  hints.ai_socktype = SOCK_DGRAM;
  hints.ai_flags = AI_PASSIVE;
  hints.ai_protocol = 0;
  hints.ai_canonname = NULL;
  hints.ai_addr = NULL;
  hints.ai_next = NULL;

  s = getaddrinfo (NULL, STR_PORT_NUM, &hints, &result);
  if (s != 0)
  {
    fprintf (stderr, "getaddrinfo: %s\n", gai_strerror (s));
    exit (EXIT_FAILURE);
  }

  for (rp = result; rp != NULL; rp = rp->ai_next)
  {
    sfd = socket (rp->ai_family, rp->ai_socktype, rp->ai_protocol);
    if (sfd == -1)
      continue;

    if (bind (sfd, rp->ai_addr, rp->ai_addrlen) == 0)
      break;

    close (sfd);
  }

  if (rp == NULL)
  {
    fprintf (stderr, "Could not bind\n");
    exit (EXIT_FAILURE);
  }

  freeaddrinfo (result);

  st_player_data *clients[CLIENTS_MAX];
  *clients = (st_player_data*)malloc (sizeof (st_player_data) * CLIENTS_MAX);
  if (*clients == NULL)
  {
    fprintf (stderr, "Error allocating memory...\n");
    exit (EXIT_FAILURE);
  }

  int cl_num;

  for (cl_num = 0; cl_num < CLIENTS_MAX; cl_num++)
    clients[cl_num] = NULL;

  for (;;)
  {
    peer_addr_len = sizeof (struct sockaddr_storage);
    ssize_t nread =
      recvfrom (sfd, buf, BUF_SIZE, 0, (struct sockaddr *) &peer_addr,
                &peer_addr_len);
    if (nread == -1)
      continue;

    char host[NI_MAXHOST], service[NI_MAXSERV];

    s = getnameinfo ((struct sockaddr *) &peer_addr,
                     peer_addr_len, host, NI_MAXHOST,
                     service, NI_MAXSERV, NI_NUMERICSERV);

    if (s == 0)
    {
      cl_num = 0;

      while (cl_num < CLIENTS_MAX)
      {
        if (clients[cl_num] != NULL)
        {
          if (strcmp (host, clients[cl_num]->address) == 0)
            break;
        }

        cl_num++;
      }

      if (cl_num == CLIENTS_MAX && clients[cl_num - 1] == NULL)
      {
        cl_num = 0;

        printf ("%d\n", cl_num);

        do
        {
          if (clients[cl_num] == NULL)
          {
            clients[cl_num] = (st_player_data*)malloc (sizeof (st_player_data));
            if (clients[cl_num] == NULL)
            {
              fprintf (stderr, "Error allocating memory.\n");
              exit (EXIT_FAILURE);
            }
            snprintf (clients[cl_num]->address, BUF_SIZE, "%s", host);
            break;
          }
          cl_num++;

        }while (cl_num < CLIENTS_MAX);
      }

      if (cl_num == CLIENTS_MAX)
      {
        printf ("Cannot accept input, max connected clients (%d) reached.", CLIENTS_MAX);
        continue;
      }

      printf ("incoming string from %s: %s\n", host, buf);

      if (strncmp (buf, "cell", 4) == 0)
      {
        char *chomp_ptr = strtok (buf, "=");
        chomp_ptr = strtok (NULL, "=");
        clients[cl_num]->cell = atoi (chomp_ptr);

        extern const st_map map;
        printf ("position for %s is %d,%d\n",
                host,
                map.cell[clients[cl_num]->cell].pos_y,
                map.cell[clients[cl_num]->cell].pos_x);
      }

      printf ("Received %zd bytes from %s:%s\n\n", nread, host, service);
    }
    else
      fprintf (stderr, "getnameinfo: %s\n", gai_strerror (s));

    if (sendto (sfd, buf, nread, 0, (struct sockaddr *)
                &peer_addr, peer_addr_len) != nread)
      fprintf (stderr, "Error sending response\n");
  }
}

int
zank_connect (char *const *argv, const char *zank_host)
{
  struct addrinfo hints;
  struct addrinfo *result, *rp;
  int sfd, s;
  size_t len;
  ssize_t nread;
  char buf[BUF_SIZE];

  /* Obtain address(es) matching host/port */

  memset (&hints, 0, sizeof (struct addrinfo));
  hints.ai_family = AF_UNSPEC;  /* Allow IPv4 or IPv6 */
  hints.ai_socktype = SOCK_DGRAM;       /* Datagram socket */
  hints.ai_flags = 0;
  hints.ai_protocol = 0;        /* Any protocol */

  s = getaddrinfo (zank_host, STR_PORT_NUM, &hints, &result);
  if (s != 0)
  {
    fprintf (stderr, "getaddrinfo: %s\n", gai_strerror (s));
    exit (EXIT_FAILURE);
  }

  /* getaddrinfo() returns a list of address structures.
     Try each address until we successfully connect(2).
     If socket(2) (or connect(2)) fails, we (close the socket
     and) try the next address. */

  for (rp = result; rp != NULL; rp = rp->ai_next)
  {
    sfd = socket (rp->ai_family, rp->ai_socktype, rp->ai_protocol);
    if (sfd == -1)
      continue;

    if (connect (sfd, rp->ai_addr, rp->ai_addrlen) != -1)
      break;                    /* Success */

    close (sfd);
  }

  if (rp == NULL)
  {                             /* No address succeeded */
    fprintf (stderr, "Could not connect\n");
    exit (EXIT_FAILURE);
  }

  freeaddrinfo (result);        /* No longer needed */
  return sfd;

  char test_string[] = "Hello, World";
  len = strlen (test_string) + 1;
  if (write (sfd, test_string, len) != len)
  {
    fprintf (stderr, "partial/failed write\n");
    exit (EXIT_FAILURE);
  }

  nread = read (sfd, buf, BUF_SIZE);
  if (nread == -1)
  {
    perror ("read");
    exit (EXIT_FAILURE);
  }

  printf ("Received %zd bytes: %s\n", nread, buf);

  exit (EXIT_SUCCESS);
}
