
# 42 group project - ft_irc

## How to create our own IRC server!

The project's goal is to implement a IRC server in c++, we have to use an actual IRC client (like IRSSI) to connect it to our server and test it.
The server must be capable of handling multiple clients at the same time and never
hang.

### How to run the program

To run the server:

```bash
    make
```
```bash
    ./ircserv <port> <password>
```
``port``: choose on which port you want to connect the server and client.

``password``: choose a password or leave it " " empty.

To connect the client:

```bash
    irssi -c localhost -p <port> -w <password>
```
Using the same ``port`` and ``password`` you choose when running the server.
You can also add the ``-n <nickname>`` option to set your nickname with irssi.
### What command can we use ?

We implemented some command following the IRC norm (1459) :

|command|in client|behaviour|
| ------|--|--- |
|/PING| | health check of the server|
|/QUIT| /quit |to quit the server|
|/PRIVMSG| /msg [user/#channel] [message] |to send a private message to another user|
|/JOIN| /join [channel] [chan pass] |to join a channel|
|/NICK| /nick [new nick/none] |to change or display your nickname|
|/MODE| /mode [+/-][i/t/l/o/k]|to change a channel's options|
|/INVITE|/invite [user] [#chan]|to invite another user to a channel|
|/TOPIC| /topic [new topic/none] |to set, change or display the channel's topic|
|/PART|/part |to quit a channel|
|/KICK| /kick [user] [reason]|to kick another user form a channel|

you can use them via the client !

### Screenshots
![screen_client](https://github.com/shikalou/ft_irc/assets/94800038/e63ab37e-75a3-43ab-89c4-e815ec6c5bb9)
![screenshot_server](https://github.com/shikalou/ft_irc/assets/94800038/b02054a9-a6f3-4051-a9ce-83b0fdbbdfbe)

### Bonus

We implemented a small bot as bonus for this project. 
Here is how to run it !

```bash
    cd bot/
    make 
```
```bash
    ./julieng <port> <password>
```
``port`` : same as the server.

``password`` : same as the server.

The bot will connect to the server like another client. You can send him a private message, try asking him to tell you a joke ;)
![bot_screen](https://github.com/shikalou/ft_irc/assets/94800038/e2c39f43-23fa-4b0c-aa5d-4d68abe34511)

## Authors

- [@JoLMG42](https://www.github.com/JoLMG42)
- [@karaskp](https://www.github.com/karaskp)
- [@shikalou](https://www.github.com/shikalou)


