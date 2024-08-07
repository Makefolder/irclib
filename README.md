![banner](./banner.png)

# 📲 IRCLib
<div align="center">
  <img src="https://img.shields.io/badge/support%20project-contribute-green" />
  <img src="https://img.shields.io/badge/std-C99-blue" />
  <a href="https://choosealicense.com/licenses/apache-2.0/">
    <img src="https://img.shields.io/badge/license-Apache-orange" />
  </a>
</div>

<div align="center">
  The IRC library... So you don't have to waste yo' time on it...
  <br />Feel free to contribute! ;D
</div>

## 🛠️ Functionality

* Find address by hostname.
* Connect to a server.
* Authentication (set nickname as username and description).
* Handle PING-PONG

## 🔗 Linker flags

```bash
-Llib -Iinclude -lirclib
```

## 🔩 Header file

```C
#include <stdbool.h>

const char* convert_host(const char *host);
int establish_conn(const char *address, const int port);
int authenticate(int sockfd, const char *nickname, bool show_msg);
int pong(int sockfd);
```

set `bool show_msg` to true in order to see the commands library sends during authentication.

## 🏗️ Build from source

**Makefile options:**
* `make` - build release client and tests.
* `make lib` - build the library only. This command build the library
into `/lib/` directory and copies all header files into `/include/irclib/`.
All .o files that are needed for packaging the lib are in `/obj/`.
* `make test` and `make exec` - Build only test/executable client.
* `make clean` - cleans all building directories such as: `/lib/`
`/include/irclib/` etc.

## 📝 License
<div align="center">
  <a href="https://choosealicense.com/licenses/apache-2.0/">
    <b>Apache</b>
  </a>
</div>
