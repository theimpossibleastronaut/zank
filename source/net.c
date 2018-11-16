#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BUF_SIZE 500

void
run_server (void)
{
  struct addrinfo hints;
  struct addrinfo *result, *rp;
  int sfd, s;
  struct sockaddr_storage peer_addr;
  socklen_t peer_addr_len;
  ssize_t nread;
  char buf[BUF_SIZE];

  memset (&hints, 0, sizeof (struct addrinfo));
  hints.ai_family = AF_UNSPEC;
  hints.ai_socktype = SOCK_DGRAM;
  hints.ai_flags = AI_PASSIVE;
  hints.ai_protocol = 0;
  hints.ai_canonname = NULL;
  hints.ai_addr = NULL;
  hints.ai_next = NULL;

  s = getaddrinfo (NULL, "7001", &hints, &result);
  if (s != 0)
  {
    fprintf (stderr, "getaddrinfo: %s\n", gai_strerror(s));
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

  for (;;) {
    peer_addr_len = sizeof (struct sockaddr_storage);
    nread = recvfrom (sfd, buf, BUF_SIZE, 0, (struct sockaddr *) &peer_addr, &peer_addr_len);
    if (nread == -1)
      continue;

  char host[NI_MAXHOST], service[NI_MAXSERV];

  s = getnameinfo ((struct sockaddr *) &peer_addr,
                  peer_addr_len, host, NI_MAXHOST,
                  service, NI_MAXSERV, NI_NUMERICSERV);

  if (s == 0)
    printf ("Received %zd bytes from %s:%s\n", nread, host, service);
  else
    fprintf (stderr, "getnameinfo: %s\n", gai_strerror (s));

  if  (sendto (sfd, buf, nread, 0, (struct sockaddr *)
      &peer_addr, peer_addr_len) != nread)
    fprintf (stderr, "Error sending response\n");
  }
}
