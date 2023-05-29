/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pjang <pjang@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/25 19:26:26 by sucho             #+#    #+#             */
/*   Updated: 2023/05/29 19:59:20 by pjang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

#include <cstring>
#include <iostream>
#include <map>
#include <string>

static const char *basic_env[] = {
    "AUTH_TYPE",
    "CONTENT_LENGTH",
    "CONTENT_TYPE",
    "GATEWAY_INTERFACE",
    "PATH_INFO",
    "PATH_TRANSLATED",
    "QUERY_STRING",
    "REMOTE_ADDR",
    "REMOTE_IDENT",
    "REMOTE_USER",
    "REQUEST_METHOD",
    "REQUEST_URI",
    "SCRIPT_NAME",
    "SERVER_NAME",
    "SERVER_PORT",
    "SERVER_PROTOCOL",
    "SERVER_SOFTWARE",
    "REDIRECT_STATUS",
    NULL};

char **setEnviron(std::map<std::string, std::string> env) {
  char **return_value;
  std::string temp;

  return_value = (char **)malloc(sizeof(char *) * (env.size() + 1));
  int i = 0;
  std::map<std::string, std::string>::iterator it;
  for (it = env.begin(); it != env.end(); it++) {
    temp = (*it).first + "=" + (*it).second;
    char *p = (char *)malloc(temp.size() + 1);
    strcpy(p, temp.c_str());
    return_value[i] = p;
    i++;
  }
  return_value[i] = NULL;
  return (return_value);
}

char **setCommand(std::string command, std::string path) {
  char **return_value;
  return_value = (char **)malloc(sizeof(char *) * (3));

  char *temp;

  temp = (char *)malloc(sizeof(char) * (command.size() + 1));
  strcpy(temp, command.c_str());
  return_value[0] = temp;

  temp = (char *)malloc(sizeof(char) * (path.size() + 1));
  strcpy(temp, path.c_str());
  return_value[1] = temp;
  return_value[2] = NULL;
  return (return_value);
}
std::string setPathInfo(char *path) {
  std::string result(path);

  //result = result.substr(0, result.size());

  return (result);
}

std::string setPathTranslated(char *path) {
  std::string result;

  char current_dir[512];
  getcwd(current_dir, 512);
  result += current_dir;
  result += *(path + 1);
  return (result);
}

std::string setContentLength(char *query_string) {
  std::string result;

  int length = strlen(query_string);
  result = std::to_string(length);
  return (result);
}
/*
**  Available Functions:
**
**  fork, wait, waitpid, wait3, wait4, signal, kill, exit
**  execve, dup, dup2, pipe, strerror, errno
**
*/
int main(int argc, char *argv[]) {
  if (argc == 5) {
    char **environ;
    char **command;
    pid_t pid;
    int pipe_fd[2];
    char foo[4096];

    command = setCommand(argv[1], argv[2]);

    std::map<std::string, std::string> env_set;
    for (int i = 0; basic_env[i] != NULL; i++) {
      std::pair<std::string, std::string> env_temp;
      env_temp.first = basic_env[i];
      env_temp.second = "";
      env_set.insert(env_temp);
    }
    {
      if (std::string(argv[4]).size() > 0) {
        env_set["CONTENT_LENGTH"] = std::to_string(std::string(argv[4]).size());
        env_set["QUERY_STRING"] = std::string(argv[4]);
      } else
        env_set["QUERY_STRING"] = std::to_string(10);
      env_set["REQUEST_METHOD"] = std::string(argv[2]);
      env_set["REDIRECT_STATUS"] = "CGI";
      env_set["SCRIPT_FILENAME"] = std::string(argv[3]);
      env_set["SERVER_PROTOCOL"] = "HTTP/1.1";
      env_set["PATH_INFO"] = setPathInfo(argv[3]);
      // env_set["CONTENT_TYPE"] = "application/x-www-form-urlencoded";
      env_set["CONTENT_TYPE"] = "text/plain";
      env_set["GATEWAY_INTERFACE"] = "CGI/1.1";
      env_set["PATH_TRANSLATED"] = setPathTranslated(argv[3]);
      env_set["REMOTE_ADDR"] = "127.0.0.1";
      env_set["REQUEST_URI"] = setPathInfo(argv[3]);
      env_set["SERVER_PORT"] = "80";
      env_set["SERVER_PROTOCOL"] = "HTTP/1.1";
      env_set["SERVER_SOFTWARE"] = "versbew";
    }
    // Content-Length 만큼 body가 들어가게 됨
    // env_set["CONTENT_LENGTH"] = ???;

    if (!strcmp(command[0], "php-cgi")) {
      env_set["SCRIPT_NAME"] = "/opt/homebrew/bin/php-cgi";

    } else if (!strcmp(command[0], "cgi_tester")) {
      env_set["SCRIPT_NAME"] = "/Users/wwaya/cgi_practice/cgi_tester";
    }

    environ = setEnviron(env_set);

    /*
    **  link: https://stackoverflow.com/questions/7292642/grabbing-output-from-exec
    */

    pipe(pipe_fd);
    pid = fork();
    if (!pid) {
      dup2(pipe_fd[1], STDOUT_FILENO);
      close(pipe_fd[0]);
      close(pipe_fd[1]);
      if (!strcmp(command[0], "php-cgi"))
        execve("/opt/homebrew/bin/php-cgi", command, environ);
      // personal mac -> /opt/homebrew/bin/php-cgi
      // cluster mac  -> 1) install php on host
      //              -> 2) /Users/$(USER)/.brew/bin/php-cgi
      else if (!strcmp(command[0], "cgi_tester"))
        execve("./cgi_tester", command, environ);
      // exit(1);
    } else {
      // close(pipe_fd[1]);
      int nbytes;
      int i = 0;
      // while ((nbytes = read(pipe_fd[0], foo, sizeof(foo)))) {
      //   write(STDOUT_FILENO, foo, strlen(foo));
      //   i++;
      //   memset(foo, 0, 4096);
      // }
      write(pipe_fd[0], &"abcdehelloworld", 10);
      write(pipe_fd[0], &"\0", 1);
      close(pipe_fd[1]);

      while ((nbytes = read(pipe_fd[0], foo, sizeof(foo)))) {
        write(STDOUT_FILENO, foo, strlen(foo));
        i++;
        memset(foo, 0, 4096);
      }
      close(pipe_fd[1]);
      close(pipe_fd[0]);
      wait(NULL);
    }
  } else
    std::cout << "Usage: ./a.out [cgi_tester or php-cgi] [HTTP method] [filepath] [query string]" << std::endl;
}