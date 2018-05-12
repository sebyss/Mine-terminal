#include <sys/wait.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <glob.h>
#include <errno.h>
#include <fcntl.h>
#include <pwd.h>
#include <grp.h>
#include <dirent.h>
#include <sys/types.h>
#include <sys/stat.h>

#include <readline/readline.h>
#include <readline/history.h>

 int shell_cd (char **args);
 int shell_help (char **args);
 int shell_exit (char **args);
 int shell_ls(int argc,char *argv[]);


char *impl_string[] = {

  "cd",
  "help",
  "exit",
  "ls -a",
  "ls ",
  "ls -s",
  "ls -F",
  "ls -l"


};

int (*impl_functii[]) (char **) = {
  &shell_cd ,
  &shell_help ,
  &shell_exit ,
  &shell_ls,
};

int shell_afis_impl() {
  return sizeof(impl_string) / sizeof(char *);
}


int shell_cd(char **args)

{

  if (args[1] == NULL) {
    chdir("/home");
    fprintf(stderr, "shell: expected argument to \"cd\"\n");
  } else {
    if (chdir(args[1]) != 0) {
      perror("shell");
    }
  }
  return 1;
}


int shell_ls(int argc,char *argv[]){

{
      struct dirent *de;
      struct stat *buf;
      struct stat sa;
      struct group *grup;
      struct passwd *password;
      char *timp;
      de=(struct dirent*)malloc(sizeof(struct dirent));
      DIR *d;
      buf=(struct stat*)malloc(sizeof(struct stat));
      if(argc<1)
         printf("Informatii insuficiente!\n");
         else
          {
           if(argc==1)
		   {d=opendir(".");
		    while ((de=readdir (d)) != NULL)
		   if(strcmp(de->d_name,".")!=0&&strcmp(de->d_name,"..")!=0) printf("%s \n", de->d_name);}
             else
              {
               if(argc==2)
                 {
                   d=opendir(argv[1]);
                   while ((de=readdir (d)) != NULL)
		    {
		      if(strcmp(de->d_name,".")!=0&&strcmp(de->d_name,"..")!=0)
		      printf ("%s \n ", de->d_name);
		    }
		   closedir(d);
                 }
                 else
                  {
                    if(argc==3)
                     {
                       d=opendir(argv[2]);
                       int i;
                       for(i=0;i<argc;i++)
                        {
                          if(strcmp(argv[i],"-a")==0)
                            {
                              while ((de=readdir (d)) != NULL)
		              printf ("%s \n ", de->d_name);
		            }
                          else
                           {
                             if(strcmp(argv[i],"-l")==0)
                              {
                                 while ((de=readdir (d)) !=NULL)
                                   {
                                     if(S_ISDIR(sa.st_mode)) printf("d");
                                      else printf("-");
                                     if(sa.st_mode & S_IWUSR) printf("w");
                                      else printf("-");
                                     if(sa.st_mode & S_IRUSR) printf("r");
                                      else printf("-");
                                     if(sa.st_mode & S_IXUSR) printf("x");
                                      else printf("-");
                                     if(sa.st_mode & S_IWGRP) printf("w");
	                              else printf("-");
                                     if(sa.st_mode & S_IRGRP) printf("r");
	                              else printf("-");
                                     if(sa.st_mode & S_IXGRP) printf("x");
	                              else printf("-");
                                     if(sa.st_mode & S_IWOTH) printf("w");
	                              else printf("-");
                                     if(sa.st_mode & S_IROTH) printf("r");
	                              else printf("-");
                                     if(sa.st_mode & S_IXOTH) printf("x");
	                              else printf("-");
                                     if(de->d_name !=0)
                                       {
                                          stat(de->d_name, &sa);
                                          timp= (char*)ctime(&sa.st_mtime);
                                          timp[16] = '\0';
                                          timp += 4;
                                          password=getpwuid(sa.st_uid);
                                          grup=getgrgid(sa.st_gid);
                                          printf("%3u %-8s %-7s %9d %s %s\n",sa.st_nlink, password->pw_name, grup->gr_name,sa.st_size,timp, de->d_name);

                                        }
                                   }
                              }
                              else
                               {
                                 if(strcmp(argv[i],"-s")==0)
                                   {
                                     while((de=readdir (d)) !=NULL)
                                      {
                                        if(strcmp(de->d_name,".")!=0&&strcmp(de->d_name,"..")!=0)
                                           {
                                             if(de->d_name !=0)
                                              {
                                                stat(de->d_name, &sa);
                                                printf("%3d %s\n",(int)sa.st_size,de->d_name);
                                              }
                                           }
                                      }
                                   }
                                   else
                                     {
                                        if(strcmp(argv[i],"-F")==0)
                                          {
                                            while((de=readdir (d)) !=NULL)
                                             {
                                               if(strcmp(de->d_name,".")!=0&&strcmp(de->d_name,"..")!=0)
                                                {
                                                  stat(de->d_name, &sa);
                                                  if(S_ISDIR(sa.st_mode)) printf("%3s/ ",de->d_name);
                                                      else
                                                        {
                                                          if(S_ISREG(sa.st_mode)) printf("%3s=> ",de->d_name);
                                                            else
                                                              if(S_ISBLK(sa.st_mode)) printf("%3s@ ",de->d_name);
                                                                else
                                                                  if(S_ISLNK(sa.st_mode)) printf("%3s| ",de->d_name);
                                                                    else printf("%3s* ",de->d_name);
                                                        }
                                                  printf("\n");
                                                }
                                             }
                                          }
                                     }
                               }
                           }
                       }
                     closedir(d);
                   }
                }
            }
   }
}
}


int shell_help(char **args)
{
  int i;
  printf("Miucin Sebastian SHELL\n");
  printf("Comenzi Implementate:\n");

  for (i = 0; i < shell_afis_impl(); i++) {
    printf("  %s\n", impl_string[i]);
  }

  return 1;
}


int shell_exit(char **args)
{
  return 0;
}

int shell_fork(char **args)
{
  pid_t pid;
  int status;

  pid = fork();
  if (pid == 0) {

    if (execvp(args[0], args) == -1) {
      perror("shell");
    }
    exit(EXIT_FAILURE);
  } else if (pid < 0) {

    perror("shell");
  } else {

    do {
      waitpid(pid, &status, WUNTRACED);
    } while (!WIFEXITED(status) && !WIFSIGNALED(status));
  }

  return 1;
}


int shell_exec(char **args)
{
  int i;

  if (args[0] == NULL) {

    return 1;
  }

  for (i = 0; i < shell_afis_impl(); i++) {
    if (strcmp(args[0], impl_string[i]) == 0) {
      return (*impl_functii[i])(args);
    }
  }

  return shell_fork(args);
}

#define SHELL_RL_BUFSIZE 1024


#define SHELL_TOK_BUFSIZE 64
#define SHELL_TOK_DELIM " \t\r\n\a"

char **shell_split_linie(char *linie)
{
  int bufsize = SHELL_TOK_BUFSIZE, position = 0;
  char **tokens = malloc(bufsize * sizeof(char*));
  char *token, **tokens_backup;

  if (!tokens) {
    fprintf(stderr, "shell: allocation error\n");
    exit(EXIT_FAILURE);
  }

  token = strtok(linie, SHELL_TOK_DELIM);
  while (token != NULL) {
    tokens[position] = token;
    position++;

    if (position >= bufsize) {
      bufsize += SHELL_TOK_BUFSIZE;
      tokens_backup = tokens;
      tokens = realloc(tokens, bufsize * sizeof(char*));
      if (!tokens) {
		free(tokens_backup);
        fprintf(stderr, "shell: allocation error\n");
        exit(EXIT_FAILURE);
      }
    }

    token = strtok(NULL, SHELL_TOK_DELIM);
  }
  tokens[position] = NULL;
  return tokens;
}


void shell_loop(void)
{
  char *linie;
  char **args;
  int status;


  do {

    char cwd[1024];
   if (getcwd(cwd, sizeof(cwd)) != NULL){
   printf(cwd);
    linie = readline(" >");
    }
    add_history(linie);
    args = shell_split_linie(linie);
    status = shell_exec(args);

    free(linie);
    free(args);
  } while (status);
}


int main(int argc, char **argv)
{

  shell_loop();

  return EXIT_SUCCESS;
}
