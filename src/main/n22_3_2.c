#include <arpa/inet.h>
#include <errno.h>
#include <malloc.h>
#include <mqueue.h>
#include <netinet/in.h>
#include <pthread.h>
#include <semaphore.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/ipc.h>
#include <sys/socket.h> //server
#include <sys/types.h>
#include <time.h>

#define addr "127.0.0.1"
#define port "8898"

mqd_t queue;
sem_t *semaphore;
pid_t child_proc[4];
short ports[4] = { 9805, 9806, 9807, 9808 };

int
main (int args, char **argv)
{

  int request_fd;
  char *received_msg = (char *)malloc (256);

  struct sockaddr_in server, client;

  socklen_t length = sizeof (struct sockaddr_in);

  request_fd = socket (AF_INET, SOCK_DGRAM, 0);
  if (request_fd == -1)
    {
      perror ("socket");
      exit (EXIT_FAILURE);
    }

  memset (&server, 0, sizeof (server));
  server.sin_family = AF_INET;
  server.sin_addr.s_addr = inet_addr (addr);
  server.sin_port = htons (atoi (port));

  semaphore = sem_open ("/semaphore", O_CREAT, 0666, 1);

  if (bind (request_fd, (struct sockaddr *)&server,
            sizeof (struct sockaddr_in)))
    {
      perror ("bind");
      close (request_fd);
      exit (EXIT_FAILURE);
    }

  queue
      = mq_open ("/requestbuffer", O_CREAT | O_RDWR, S_IRUSR | S_IWUSR, NULL);

  for (int i = 0; i < 4; i++)
    {

      child_proc[i] = fork ();
      if (-1 == child_proc[i])
        {
          perror ("fork");
          exit (EXIT_FAILURE);
        }

      if (child_proc[i] == 0)
        {

          char *sended_info;
          char *proc_received;

          mqd_t proc_queue;
          sem_t *childsem;
          socklen_t lengthforchild = sizeof (struct sockaddr_in);

          struct sockaddr_in proc_struct;
          time_t time_struct;
          struct mq_attr attr;

          int *semval = malloc (4);
          int proc_fd = socket (AF_INET, SOCK_DGRAM, 0);
          if (proc_fd == -1)
            {
              perror ("socket");
              exit (EXIT_FAILURE);
            }

          proc_struct.sin_family = AF_INET;
          proc_struct.sin_addr.s_addr = inet_addr (addr);
          proc_struct.sin_port = htons (ports[i]);

          sended_info = (char *)malloc (sizeof (proc_struct));
          proc_received = (char *)malloc (64);

          if (bind (proc_fd, (struct sockaddr *)&proc_struct,
                    sizeof (struct sockaddr_in)))
            {
              perror ("bind");
              close (request_fd);
              exit (EXIT_FAILURE);
            }

          proc_queue
              = mq_open ("/requestbuffer", O_RDONLY, S_IRUSR | S_IWUSR, NULL);
          if (-1 == proc_queue)
            {
              perror ("mq_open");
              exit (EXIT_FAILURE);
            }

          childsem = sem_open ("/semaphore", NULL);

          while (1)
            {
              sem_wait (childsem);

              mq_receive (proc_queue, proc_received, attr.mq_msgsize, NULL);

              sem_post (childsem);

              memset (sended_info, 0, strlen (sended_info));
              strcpy (sended_info, ctime (&time_struct));

              if (-1
                  == sendto (proc_fd, sended_info, strlen (sended_info), 0,
                             (struct sockaddr *)proc_received, lengthforchild))
                {
                  perror ("sendto");
                  close (request_fd);
                  exit (EXIT_FAILURE);
                }

              memset (proc_received, 0, sizeof (struct sockaddr_in));
            }

          exit (EXIT_SUCCESS);
        }
    }

  while (1)
    {

      int flag = 1;
      char *port_to_send = malloc (8);

      memset (&client, '\0', sizeof (client));

      if (-1
          == recvfrom (request_fd, received_msg, strlen (received_msg), 0,
                       (struct sockaddr *)&client, &length))
        {
          perror ("Socket receive ERR");
          close (request_fd);
          exit (EXIT_FAILURE);
        }

      mq_send (queue, (char *)&client, sizeof (struct sockaddr_in), 1);
    }

  exit (EXIT_SUCCESS);
}
