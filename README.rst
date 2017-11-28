Projetos de Computação Gráfica
------------------------------

Neste repositório estão os laboratórios da disciplina de Introdução à Computação Gráfica de 2017/2, na UFAM.

Os laboratórios em si, estão na pasta `exercises`, e todos possuem um makefile, que em geral, gera um executável, `main`

Docker
------

A única dependência deste repositório é o [Docker (Community Edition)](https://www.docker.com)

Este repositório é um fork de um projeto de docker com OpenGL. Para rodar um container docker.

```
cd exercises
docker build -t icg-image .
./run.sh
```

Abra um outro terminal e rode o comando abaixo para entrar na pasta do projeto, no container criado acima

```
docker exec -it icg bash
```

docker-opengl
=============
A docker image that supports rendering graphical applications, including OpenGL apps.

.. image:: https://circleci.com/gh/thewtex/docker-opengl.svg?style=svg
    :target: https://circleci.com/gh/thewtex/docker-opengl

.. image:: https://images.microbadger.com/badges/image/thewtex/opengl.svg
  :target: https://microbadger.com/images/thewtex/opengl

Overview
--------

This Docker image supports portable, CPU-based graphical application
rendering, including rendering OpenGL-based applications. An X session is
running on display `:0` and can be viewed through HTML5 viewer on any device
with a modern web browser (Mac OSX, Windows, Linux, Android, iOS, ChromeOS,
...). It can be used to expose a graphical interface from a Docker container
or to run continuous integration tests that require a graphical environment.

Quick-start
-----------

Execute the `run.sh` script.

Details
--------

By default, the `run.sh` start up the graphical session and points the user to
a URL on the local host where they can view and interact with the session. On
application exit, the `run.sh` will print the application's console output and
exit with the application's return code.

The session runs `Openbox <http://openbox.org>`_ as a non-root user, *user*
that has password-less sudo privileges. The browser view is an HTML5 viewer
that talks over websockets to a VNC Server. The VNC Server displays a running
Xdummy session.

To customize the Docker image for your graphical application, set the `APP`
environmental variable to the shell command required to start the application.
For example::

  ENV APP /usr/bin/my-gui-app

The `run.sh` script can be used to drive start-up. It is customizable with
flags::

  Usage: run.sh [-h] [-q] [-c CONTAINER] [-i IMAGE] [-p PORT] [-r DOCKER_RUN_FLAGS]

  This script is a convenience script to run Docker images based on
  thewtex/opengl. It:

  - Makes sure docker is available
  - On Windows and Mac OSX, creates a docker machine if required
  - Informs the user of the URL to access the container with a web browser
  - Stops and removes containers from previous runs to avoid conflicts
  - Mounts the present working directory to /home/user/work on Linux and Mac OSX
  - Prints out the graphical app output log following execution
  - Exits with the same return code as the graphical app

  Options:

    -h             Display this help and exit.
    -c             Container name to use (default opengl).
    -i             Image name (default thewtex/opengl).
    -p             Port to expose HTTP server (default 6080). If an empty
                   string, the port is not exposed.
    -r             Extra arguments to pass to 'docker run'. E.g.
                   --env="APP=glxgears"
    -q             Do not output informational messages.


See the *example* directory for a derived image and `run.sh` script that runs the
*glxgears* OpenGL demo program.

Credits
-------

This configuration was largely inspired by the `dit4c project <https://dit4c.github.io>`_.
