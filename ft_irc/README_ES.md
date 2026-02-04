# 🌐 FT_IRC - Internet Relay Chat Server

_Este proyecto ha sido creado como parte del currículo de 42 por miaviles, rmunoz-c, carlsanc_

- Miguel Ángel Avilés (miaviles) - [GitHub](https://github.com/miaviles11)
- Rubén Muñoz Calderón (rmunoz-c) - [GitHub](https://github.com/rmunoz-c)
- Carlos Vicente Sánchez (carlsanc) - [GitHub](https://github.com/CarlosVSL)

## 📖 Descripción

> 📡 Un servidor IRC completo implementado en C++98 siguiendo el RFC 1459, con soporte para canales, operadores, modos y un bot interactivo como bonus.

### Objetivo del Proyecto

El objetivo principal es comprender y dominar:
- **Programación de sockets TCP/IP** en C++
- **Manejo de E/S multiplexada** con `poll()`
- **Gestión de múltiples conexiones simultáneas** sin threads
- **Implementación del protocolo IRC** (autenticación, canales, operadores, modos)
- **Arquitectura cliente-servidor** y comunicación en red
- **Trabajo en equipo y asignación de tareas**
- **Automatización y manejo de comandos** en la parte bonus

### Características Principales

- ✅ **Autenticación segura** mediante contraseña
- ✅ **Gestión de canales** con operadores y modos (+i, +t, +k, +o, +l)
- ✅ **Comandos IRC estándar** (JOIN, PART, PRIVMSG, KICK, INVITE, TOPIC, MODE, etc.)
- ✅ **Soporte para múltiples usuarios y canales** simultáneos
- ✅ **Compatible con clientes IRC reales** (HexChat, Irssi, WeeChat)
- ✅ **Bot interactivo (bonus)** con comandos útiles y entretenidos

El servidor está optimizado para manejar conexiones concurrentes de manera eficiente, utilizando un modelo de I/O no bloqueante que garantiza la escalabilidad y el rendimiento.

---

## 📋 Tabla de Contenidos

- [🚀 Inicio Rápido](#-inicio-rápido)
- [✨ Características](#-características)
- [🧪 Testing](#-testing)
  - [Fase 1: Arranque del Servidor](#fase-1-arranque-del-servidor)
  - [Fase 2: Autenticación](#-fase-2-autenticación)
  - [Fase 3: Canales Básicos](#-fase-3-canales-básicos)
  - [Fase 4: Operadores de Canal](#-fase-4-operadores-de-canal)
  - [Fase 5: Modos de Canal](#-fase-5-modos-de-canal)
  - [Fase 6: Modos de Usuario](#-fase-6-modos-de-usuario)
  - [Fase 7: Múltiples Usuarios](#-fase-7-múltiples-usuarios-y-canales)
  - [Fase 8: Casos Edge](#️-fase-8-casos-edge-y-errores)
  - [Fase 9: Clientes IRC Reales](#-fase-9-integración-con-clientes-irc-reales)
  - [🤖 BONUS: HelpBot](#-bonus-helpbot-bot-de-irc)
- [👥 Usuarios de Prueba](#-usuarios-de-prueba)
- [📚 Recursos](#-recursos)

---

## 🚀 Instrucciones

### Requisitos del Sistema

- **Sistema Operativo:** Linux/macOS
- **Compilador:** g++ con soporte C++98
- **Herramientas:** make, netcat (nc)

### Compilación

```bash
# Clonar el repositorio
git clone https://github.com/tu-usuario/ft_irc.git
cd ft_irc

# Compilar el servidor IRC
make

# Compilar el bot (bonus)
make bot

# Limpiar archivos objeto
make clean

# Limpiar todo (binarios incluidos)
make fclean

# Recompilar todo desde cero
make re
```

---

## 🧪 Testing

> **Nota:** Todos los tests están diseñados para ejecutarse con `nc` (netcat) o clientes IRC reales.

---

<details>
<summary><h3>📌 FASE 1: ARRANQUE DEL SERVIDOR</h3></summary>

#### Test 1.1: Inicio básico
```bash
# Terminal 1 (Servidor)
./ircserv 6667 password123
```

**✅ Output esperado:**

```
[SERVER] Initializing on port 6667
[SOCKET] Socket created (fd=3)
[SOCKET] ✓ Socket configured (non-blocking + SO_REUSEADDR)
[SOCKET] ✓ Bound to 0.0.0.0:6667
[SOCKET] ✓ Listening (backlog=4096)
[SERVER] ✓ Ready on port 6667

╔══════════════════════════════════════╗
║   IRC SERVER STARTED                 ║
║   Port: 6667                         ║
║   Press Ctrl+C to exit               ║
╚══════════════════════════════════════╝

[SERVER] Main loop started
```

---

#### Test 1.2: Puerto inválido

```bash
# Probar puertos inválidos
./ircserv 80 test      # ❌ Puerto privilegiado
./ircserv 70000 test   # ❌ Fuera de rango
./ircserv abc test     # ❌ No numérico
```

**✅ Resultado esperado:** Todos deben dar error sin crashear

---

#### Test 1.3: Password vacío

```bash
./ircserv 6667 ""      # ❌ Debe rechazar
```

**✅ Resultado esperado:**
```
[ERROR] Password cannot be empty
```

</details>

---

<details>
<summary><h3>🔐 FASE 2: AUTENTICACIÓN</h3></summary>

#### Test 2.1: Conexión básica

```bash
# Terminal 2 (USER1)
nc localhost 6667
```

**✅ En el servidor debes ver:**
```
[SOCKET] ✓ Accepted connection from 127.0.0.1 (fd=4)
[SERVER] ✓ New client from 127.0.0.1 (fd=4, total=1)
```

---

#### Test 2.2: Password incorrecto

```bash
# Terminal 2
PASS wrongpassword
NICK TestUser
USER test 0 * :Test
```

**✅ Debes ver:**
```
:ft_irc 464 * :Password incorrect
```
Y luego se cierra la conexión

---

#### Test 2.3: Secuencia correcta (PASS → NICK → USER)

```bash
# Terminal 2 (Reconectar si se cerró)
nc localhost 6667

PASS password123
NICK Alice
USER alice 0 * :Alice Wonderland
```

**✅ Debes ver mensajes de bienvenida:**
```
:ft_irc 001 Alice :Welcome to the FT_IRC Network Alice!alice@127.0.0.1
:ft_irc 002 Alice :Your host is ft_irc, running version 1.0
:ft_irc 003 Alice :This server was created today
:ft_irc 004 Alice ft_irc 1.0 io tkl
```

---

#### Test 2.4: Secuencia incorrecta (sin PASS)

```bash
# Terminal 3 (nuevo cliente)
nc localhost 6667

NICK Bob
USER bob 0 * :Bob

# Intenta hacer algo:
JOIN #test
```

**✅ Debe ver error de no registrado**

---

#### Test 2.5: Nickname duplicado

```bash
# Terminal 3 (con PASS correcto ahora)
nc localhost 6667

PASS password123
NICK Alice    # ❌ Ya existe
```

**✅ Debes ver:**
```
:ft_irc 433 * Alice :Nickname is already in use
```

---

#### Test 2.6: Nickname inválido

```bash
# Terminal 3
PASS password123
NICK Alice@123   # ❌ Carácter inválido
NICK 123Alice    # ❌ Empieza con número
```

**✅ Debe rechazar con:**
```
:ft_irc 432 * <nick> :Erroneous nickname
```

---

#### Test 2.7: Cambio de nickname

```bash
# Terminal 2 (Alice conectada)
NICK AliceNew
```

**✅ Debes ver confirmación:**
```
:Alice!alice@127.0.0.1 NICK :AliceNew
```

</details>

---

<details>
<summary><h3>📢 FASE 3: CANALES BÁSICOS</h3></summary>

#### Test 3.1: Crear y unirse a canal

```bash
# Terminal 2 (Alice)
JOIN #general
```

**✅ Debes ver:**
```
:AliceNew!alice@127.0.0.1 JOIN #general
:ft_irc 331 AliceNew #general :No topic is set
:ft_irc 353 AliceNew = #general :@AliceNew
:ft_irc 366 AliceNew #general :End of /NAMES list
```

> **Nota:** `@` indica que eres operador (creador del canal)

---

#### Test 3.2: Segundo usuario se une

```bash
# Terminal 3 (Bob - asegúrate de estar registrado)
nc localhost 6667
PASS password123
NICK Bob
USER bob 0 * :Bob Builder
JOIN #general
```

**✅ Bob ve:**
```
:Bob!bob@127.0.0.1 JOIN #general
:ft_irc 331 Bob #general :No topic is set
:ft_irc 353 Bob = #general :@AliceNew Bob
:ft_irc 366 Bob #general :End of /NAMES list
```

**✅ Alice ve (en Terminal 2):**
```
:Bob!bob@127.0.0.1 JOIN #general
```

---

#### Test 3.3: Enviar mensajes al canal

```bash
# Terminal 2 (Alice)
PRIVMSG #general :Hello everyone!
```

**✅ Bob ve (Terminal 3):**
```
:AliceNew!alice@127.0.0.1 PRIVMSG #general :Hello everyone!
```

```bash
# Terminal 3 (Bob responde)
PRIVMSG #general :Hi Alice!
```

**✅ Alice ve:**
```
:Bob!bob@127.0.0.1 PRIVMSG #general :Hi Alice!
```

---

#### Test 3.4: Mensaje privado (usuario a usuario)

```bash
# Terminal 2 (Alice)
PRIVMSG Bob :This is a private message
```

**✅ Bob ve (Terminal 3):**
```
:AliceNew!alice@127.0.0.1 PRIVMSG Bob :This is a private message
```

> **⚠️ IMPORTANTE:** Alice NO debe ver este mensaje reflejado

---

#### Test 3.5: Unirse a múltiples canales

```bash
# Terminal 2 (Alice)
JOIN #random
JOIN #dev

# Terminal 3 (Bob)
JOIN #dev
```

Ahora:
- Alice está en: `#general`, `#random`, `#dev`
- Bob está en: `#general`, `#dev`

---

#### Test 3.6: PART (salir de canal)

```bash
# Terminal 2 (Alice)
PART #random
```

**✅ Alice ve:**
```
:AliceNew!alice@127.0.0.1 PART #random :Leaving
```

```bash
# Probar con razón:
PART #dev :Going to sleep
```

**✅ Debes ver:**
```
:AliceNew!alice@127.0.0.1 PART #dev :Going to sleep
```

> **✅ Bob también ve esto (porque está en #dev)**

---

#### Test 3.7: NAMES (listar usuarios en canal)

```bash
# Terminal 2 (Alice en #general con Bob y Charlie)
NAMES #general
```

**✅ Debes ver:**
```
:ft_irc 353 AliceNew = #general :@AliceNew Bob Charlie
:ft_irc 366 AliceNew #general :End of /NAMES list
```

> **Nota:** `@` indica operador

```bash
# Probar sin parámetros (lista TODOS los canales):
NAMES
```

**✅ Debes ver todos los canales donde estás:**
```
:ft_irc 353 AliceNew = #general :@AliceNew Bob Charlie
:ft_irc 353 AliceNew = #random :@AliceNew
:ft_irc 366 AliceNew * :End of /NAMES list
```

---

#### Test 3.8: NAMES (sin # autocorrección)

```bash
# Terminal 2
NAMES general
```

**✅ El servidor añade # automáticamente:**
```
:ft_irc 353 AliceNew = #general :@AliceNew Bob Charlie
:ft_irc 366 AliceNew #general :End of /NAMES list
```

---

#### Test 3.9: NAMES (canal inexistente)

```bash
NAMES #noexiste
```

**✅ Debe dar error:**
```
:ft_irc 403 AliceNew #noexiste :No such channel
```

---

#### Test 3.10: NAMES (sin estar registrado)

```bash
# Terminal nueva sin autenticar
nc localhost 6667
PASS password123
NAMES #general
```

**❌ Debe fallar:**
```
:ft_irc 451 * :You have not registered
```

---

#### Test 3.11: WHO (información detallada de usuarios en canal)

```bash
# Terminal 2 (Alice en #general con Bob)
WHO #general
```

**✅ Debes ver (formato tabla con colores):**
```
:ft_irc 352 AliceNew #general alice 127.0.0.1 ft_irc AliceNew H@ :0 Alice Johnson
:ft_irc 352 AliceNew #general bob 127.0.0.1 ft_irc Bob H :0 Bob Smith
:ft_irc 315 AliceNew #general :End of /WHO list
```

> **Formato:** `<canal> <user> <host> <server> <nick> <flags> :<hop> <realname>`  
> **Flags:** `H` = presente, `H@` = presente + operador del canal

---

#### Test 3.12: WHO (buscar usuario por nickname)

```bash
# Terminal 2 (Alice busca a Bob)
WHO Bob
```

**✅ Debes ver:**
```
:ft_irc 352 AliceNew * bob 127.0.0.1 ft_irc Bob H :0 Bob Smith
:ft_irc 315 AliceNew Bob :End of /WHO list
```

> **Nota:** `*` indica que no se especifica canal (búsqueda de usuario)

---

#### Test 3.13-3.16: Tests adicionales de WHO

```bash
# Sin parámetros
WHO

# Usuario inexistente
WHO Charlie    # ✅ Error 401

# Canal inexistente
WHO #noexiste  # ✅ Error 403

# Sin estar registrado
# ✅ Error 451
```

---

#### Test 3.17: WHOIS (perfil completo de usuario)

```bash
# Terminal 3 (Bob ejecuta WHOIS)
WHOIS Alice
```

**✅ Debes ver (5 líneas con colores):**
```
:ft_irc 311 Bob Alice alice 127.0.0.1 * :Alice Wonderland
:ft_irc 319 Bob Alice :@#general
:ft_irc 312 Bob Alice ft_irc :FT IRC Server
:ft_irc 317 Bob Alice 0 1766171247 :seconds idle, signon time
:ft_irc 318 Bob Alice :End of /WHOIS list
```

**Formato explicado:**
- `[311]` RPL_WHOISUSER: `<nick> <username> <host> * :<realname>`
- `[319]` RPL_WHOISCHANNELS: `<nick> :<canales>` (`@` = operador)
- `[312]` RPL_WHOISSERVER: `<nick> <servidor> :<info servidor>`
- `[317]` RPL_WHOISIDLE: `<nick> <idle_segundos> <timestamp_conexión> :descripción`
- `[318]` RPL_ENDOFWHOIS: `<nick> :End of /WHOIS list`

---

#### Test 3.18: WHOIS (múltiples canales)

```bash
# Terminal 2 (Alice en #general, #random, #dev)
JOIN #random
JOIN #dev

# Terminal 3 (Bob)
WHOIS Alice
```

**✅ Línea 319 debe mostrar:**
```
:ft_irc 319 Bob Alice :@#general @#random @#dev
```

---

#### Test 3.19: WHOIS (idle time aumenta)

```bash
# Terminal 2 (Alice sin escribir nada por 30 segundos)

# Terminal 3 (Bob hace WHOIS)
WHOIS Alice
```

**✅ Debe mostrar:**
```
:ft_irc 317 Bob Alice 30 1766171247 :seconds idle, signon time
```

Si Alice escribe algo, el idle se resetea a 0-2 segundos.

---

#### Test 3.20-3.23: Tests adicionales de WHOIS

```bash
# Usuario inexistente
WHOIS Charlie    # ✅ Error 401

# Sin parámetros
WHOIS            # ✅ Error 431

# Sin estar registrado
# ✅ Error 451

# Comparación WHO vs WHOIS:
# WHO  = rápido, múltiples usuarios, formato tabla
# WHOIS = detallado, un usuario, perfil completo
```

</details>

---

<details>
<summary><h3>👑 FASE 4: OPERADORES DE CANAL</h3></summary>

#### Test 4.1: TOPIC (ver y cambiar)

```bash
# Terminal 2 (Alice - operador de #general)
TOPIC #general
```

**✅ Ver topic actual:**
```
:ft_irc 331 AliceNew #general :No topic is set
```

```bash
# Cambiar topic:
TOPIC #general :Welcome to the general channel!
```

**✅ Todos en el canal ven:**
```
:AliceNew!alice@127.0.0.1 TOPIC #general :Welcome to the general channel!
```

---

#### Test 4.2: TOPIC (usuario no operador intenta cambiar)

```bash
# Terminal 3 (Bob - NO es operador)
TOPIC #general :Bob's topic
```

**✅ Debe fallar con:**
```
:ft_irc 482 Bob #general :You're not channel operator
```

> (Solo si el modo +t está activo, que es por defecto)

---

#### Test 4.3: MODE +o (dar operador)

```bash
# Terminal 2 (Alice)
MODE #general +o Bob
```

**✅ Todos ven:**
```
:AliceNew!alice@127.0.0.1 MODE #general +o Bob
```

```bash
# Ahora Bob puede cambiar el topic:
# Terminal 3 (Bob)
TOPIC #general :Bob is now OP!
```

**✅ Funciona**

---

#### Test 4.4: KICK (expulsar usuario)

```bash
# Terminal 4 (Charlie - nuevo usuario)
nc localhost 6667
PASS password123
NICK Charlie
USER charlie 0 * :Charlie
JOIN #general

# Terminal 2 (Alice expulsa a Charlie)
KICK #general Charlie :Bad behavior
```

**✅ Todos en el canal ven:**
```
:AliceNew!alice@127.0.0.1 KICK #general Charlie :Bad behavior
```

**✅ Charlie (Terminal 4) es expulsado del canal**

---

#### Test 4.5: INVITE (invitar a canal +i)

```bash
# Terminal 2 (Alice activa modo invite-only)
MODE #general +i
```

**✅ Todos ven:**
```
:AliceNew!alice@127.0.0.1 MODE #general +i
```

```bash
# Terminal 4 (Charlie intenta unirse)
JOIN #general
```

**❌ Debe fallar:**
```
:ft_irc 473 Charlie #general :Cannot join channel (+i)
```

```bash
# Terminal 2 (Alice invita a Charlie)
INVITE Charlie #general
```

**✅ Alice ve:**
```
:ft_irc 341 AliceNew Charlie #general
```

**✅ Charlie ve:**
```
:AliceNew!alice@127.0.0.1 INVITE Charlie #general
```

```bash
# Ahora Charlie puede unirse:
# Terminal 4
JOIN #general
```

**✅ Funciona**

</details>

---

<details>
<summary><h3>🔧 FASE 5: MODOS DE CANAL</h3></summary>

#### Test 5.1: MODE +k (canal con contraseña)

```bash
# Terminal 2 (Alice)
MODE #general +k secretpass
```

**✅ Confirmación:**
```
:AliceNew!alice@127.0.0.1 MODE #general +k secretpass
```

```bash
# Terminal 4 (Charlie desconectado, reconecta)
nc localhost 6667
PASS password123
NICK Charlie
USER charlie 0 * :Charlie
JOIN #general
```

**❌ Debe fallar:**
```
:ft_irc 475 Charlie #general :Cannot join channel (+k)
```

```bash
# Intentar con clave:
JOIN #general secretpass
```

**✅ Funciona**

---

#### Test 5.2: MODE -k (quitar contraseña)

```bash
# Terminal 2 (Alice)
MODE #general -k secretpass
```

**✅ Confirmación:**
```
:AliceNew!alice@127.0.0.1 MODE #general -k *
```

Ahora cualquiera puede unirse sin clave

---

#### Test 5.3: MODE +l (límite de usuarios)

```bash
# Terminal 2 (Alice)
MODE #general +l 3
```

**✅ Confirmación:**
```
:AliceNew!alice@127.0.0.1 MODE #general +l 3
```

```bash
# Verificar usuarios actuales:
# Alice, Bob, Charlie = 3 usuarios (límite alcanzado)

# Terminal 5 (nuevo usuario Dave)
nc localhost 6667
PASS password123
NICK Dave
USER dave 0 * :Dave
JOIN #general
```

**❌ Debe fallar:**
```
:ft_irc 471 Dave #general :Cannot join channel (+l)
```

---

#### Test 5.4: MODE -l (quitar límite)

```bash
# Terminal 2 (Alice)
MODE #general -l
```

**✅ Confirmación:**
```
:AliceNew!alice@127.0.0.1 MODE #general -l
```

```bash
# Ahora Dave puede unirse:
# Terminal 5
JOIN #general
```

**✅ Funciona**

---

#### Test 5.5: MODE +t (topic restringido a OPs)

```bash
# Terminal 2 (Alice)
MODE #general -t
```

**✅ Ahora Bob (no-OP) puede cambiar el topic:**
```bash
# Terminal 3 (Bob)
TOPIC #general :Anyone can change this
```

**✅ Funciona**

```bash
# Reactivar restricción:
# Terminal 2 (Alice)
MODE #general +t

# Ahora Bob no puede:
# Terminal 3
TOPIC #general :Bob tries again
```

**❌ Falla:**
```
:ft_irc 482 Bob #general :You're not channel operator
```

---

#### Test 5.6: Consultar modos actuales

```bash
# Cualquier usuario en el canal
MODE #general
```

**✅ Debe mostrar:**
```
:ft_irc 324 <nick> #general +it
```

</details>

---

<details>
<summary><h3>👤 FASE 6: MODOS DE USUARIO</h3></summary>

#### Test 6.1: MODE +i (invisible)

```bash
# Terminal 2 (Alice)
MODE Alice +i
```

**✅ Confirmación:**
```
:AliceNew!alice@127.0.0.1 MODE AliceNew :+i
```

```bash
# Consultar modo:
MODE Alice
```

**✅ Debe mostrar:**
```
:ft_irc 221 AliceNew +i
```

---

#### Test 6.2: MODE -i (visible)

```bash
# Terminal 2
MODE Alice -i
```

**✅ Confirmación:**
```
:AliceNew!alice@127.0.0.1 MODE AliceNew :-i
```

</details>

---

<details>
<summary><h3>🔄 FASE 7: MÚLTIPLES USUARIOS Y CANALES</h3></summary>

#### Test 7.1: Broadcast en canal con 3+ usuarios

```bash
# Setup: Alice, Bob, Charlie en #general

# Terminal 2 (Alice)
PRIVMSG #general :Testing broadcast
```

- ✅ Bob (Terminal 3) debe ver el mensaje
- ✅ Charlie (Terminal 4) debe ver el mensaje
- ⚠️ Alice NO debe ver su propio mensaje reflejado

---

#### Test 7.2: Usuario en múltiples canales recibe solo del canal correcto

```bash
# Setup:
# Alice: #general, #dev
# Bob: #general
# Charlie: #dev

# Terminal 2 (Alice en #general)
PRIVMSG #general :Message to general
```

- ✅ Bob lo ve
- ❌ Charlie NO lo ve (no está en #general)

```bash
# Terminal 2 (Alice en #dev)
PRIVMSG #dev :Message to dev
```

- ✅ Charlie lo ve
- ❌ Bob NO lo ve (no está en #dev)

---

#### Test 7.3: QUIT propaga a todos los canales

```bash
# Setup: Alice en #general y #dev con otros usuarios

# Terminal 2 (Alice)
QUIT :Goodbye!
```

**✅ Todos los usuarios en #general y #dev ven:**
```
:AliceNew!alice@127.0.0.1 QUIT :Goodbye!
```

**✅ En el servidor:**
```
[DISCONNECT] fd=4 (graceful close)
```

</details>

---

<details>
<summary><h3>⚠️ FASE 8: CASOS EDGE Y ERRORES</h3></summary>

#### Test 8.1: Comandos sin registro

```bash
# Terminal nueva sin PASS/NICK/USER
nc localhost 6667

JOIN #test
PRIVMSG #test :Hello
KICK #test Bob
```

**✅ Todos deben dar:**
```
:ft_irc 451 * :You have not registered
```

---

#### Test 8.2: Parámetros faltantes

```bash
# Terminal registrado
JOIN
MODE
KICK #test
INVITE Charlie
TOPIC
```

**✅ Todos deben dar:**
```
:ft_irc 461 <nick> <CMD> :Not enough parameters
```

---

#### Test 8.3: Canal inexistente

```bash
PART #nonexistent
PRIVMSG #nonexistent :Hello
```

**✅ Debe dar:**
```
:ft_irc 403 <nick> #nonexistent :No such channel
```

---

#### Test 8.4: Usuario inexistente

```bash
PRIVMSG NonExistentUser :Hello
```

**✅ Debe dar:**
```
:ft_irc 401 <nick> NonExistentUser :No such nick/channel
```

---

#### Test 8.5: Intentar kickear sin ser OP

```bash
# Terminal 3 (Bob, no-OP)
KICK #general Charlie :Bye
```

**✅ Debe dar:**
```
:ft_irc 482 Bob #general :You're not channel operator
```

---

#### Test 8.6: Flood de mensajes (stress test)

```bash
# Terminal 2
for i in {1..100}; do echo "PRIVMSG #general :Message $i"; done | nc localhost 6667
```

- ✅ El servidor NO debe crashear
- ✅ Todos los mensajes deben llegar (puede tomar unos segundos)

---

#### Test 8.7: Desconexión abrupta (Ctrl+C en cliente)

```bash
# Terminal 3 (Bob)
# Presionar Ctrl+C sin QUIT
```

**✅ En servidor:**
```
[DISCONNECT] fd=X (POLLHUP/ERR)
```

**✅ Otros usuarios en los canales de Bob ven:**
```
:Bob!bob@127.0.0.1 QUIT :Connection closed
```

---

#### Test 8.8: Caracteres especiales en mensajes

```bash
PRIVMSG #general :Test with émojis 🚀 and spëcial çhars
```

**✅ Debe transmitirse correctamente**

</details>

---

<details>
<summary><h3>🧪 FASE 9: INTEGRACIÓN CON CLIENTES IRC REALES</h3></summary>

#### Test 9.1: HexChat

```bash
# 1. Abrir HexChat
# 2. Network List → Add
# 3. Name: "ft_irc_test"
# 4. Servers: localhost/6667
# 5. Edit → Password: password123
# 6. Conectar
```

- ✅ Debe conectarse exitosamente
- ✅ Debe poder hacer JOIN, PRIVMSG, etc.

---

#### Test 9.2: Irssi

```bash
irssi

# Dentro de irssi:
/server add ft_irc localhost 6667 password123
/connect localhost 6667 password123 TestUser
/join #general
```

**✅ Debe funcionar como servidor real**

---

#### Test 9.3: WeeChat

```bash
weechat

# Dentro de weechat:
/server add ft_irc localhost/6667
/set irc.server.ft_irc.password password123
/connect ft_irc
/join #general
```

**✅ Debe funcionar**

</details>

---

## 👥 Usuarios de Prueba

```bash
# Usuario 1 (Alice)
PASS pass123
NICK Alice
USER alice 0 * :Alice

# Usuario 2 (Bob)
PASS pass123
NICK Bob
USER bob 0 * :Bob

# Usuario 3 (Charlie)
PASS pass123
NICK Charlie
USER charlie 0 * :Charlie
```

### Canal de Prueba

```bash
JOIN #general
```

### Mensaje de Prueba

```bash
PRIVMSG #general :HOLAAA
```

---

<details>
<summary><h3>🤖 BONUS: HELPBOT (BOT DE IRC)</h3></summary>

### Requisitos Previos

```bash
# 1. Compilar el bot
make bot

# 2. En un terminal separado, asegúrate de tener el servidor corriendo:
./ircserv 6667 pass123
```

---

#### Test B.1: Iniciar el bot

```bash
# Terminal Bot
./bot 127.0.0.1 6667 pass123
```

**✅ Debes ver:**
```
[BOT] Connected to 127.0.0.1:6667
[BOT] -> PASS pass123
[BOT] -> NICK HelpBot
[BOT] -> USER helpbot 0 * :IRC Help Bot
[BOT] Authentication sent
[BOT] -> JOIN #general
[BOT] Joining channel: #general
[BOT] -> JOIN #help
[BOT] Joining channel: #help
[BOT] Bot is now running. Listening for messages...
```

> **Nota:** El bot se une automáticamente a #general y #help

---

#### Test B.2: Verificar que el bot está en el canal

```bash
# Terminal 2 (Alice)
nc localhost 6667
PASS pass123
NICK Alice
USER alice 0 * :Alice
JOIN #general
NAMES #general
```

**✅ Debes ver:**
```
:ft_irc 353 Alice = #general :@HelpBot Alice
                              ^^^^^^^^
                              El bot está presente con OP
```

---

#### Test B.3: Comando !help (lista de comandos)

```bash
# Terminal 2 (Alice en #general)
PRIVMSG #general :!help
```

**✅ Alice recibe:**
```
:HelpBot!helpbot@127.0.0.1 PRIVMSG #general :Available commands: !help, !time, !uptime, !echo <msg>, !joke, !ping
```

**✅ En el bot (Terminal Bot):**
```
[BOT] <- :Alice!alice@127.0.0.1 PRIVMSG #general :!help
[BOT] -> PRIVMSG #general :Available commands: !help, !time, !uptime, !echo <msg>, !joke, !ping
```

---

#### Test B.4: Comando !time (hora actual)

```bash
# Terminal 2 (Alice)
PRIVMSG #general :!time
```

**✅ Alice recibe:**
```
:HelpBot!helpbot@127.0.0.1 PRIVMSG #general :Current time: 2026-01-20 18:45:30
                                                            ^^^^^^^^^^^^^^^^^^^^^^^
                                                            Hora del sistema
```

---

#### Test B.5: Comando !uptime (tiempo de funcionamiento)

```bash
# Terminal 2 (Alice - esperar unos segundos después de iniciar el bot)
PRIVMSG #general :!uptime
```

**✅ Alice recibe:**
```
:HelpBot!helpbot@127.0.0.1 PRIVMSG #general :Bot uptime: 0h 2m 45s
                                                         ^^^^^^^^^^^
                                                         Tiempo desde que arrancó
```

---

#### Test B.6: Comando !echo (repetir mensaje)

```bash
# Terminal 2 (Alice)
PRIVMSG #general :!echo Hello IRC World!
```

**✅ Alice recibe:**
```
:HelpBot!helpbot@127.0.0.1 PRIVMSG #general :Hello IRC World!
```

```bash
# Probar sin argumentos:
PRIVMSG #general :!echo
```

**✅ Alice recibe:**
```
:HelpBot!helpbot@127.0.0.1 PRIVMSG #general :Usage: !echo <message>
```

---

#### Test B.7: Comando !joke (chiste aleatorio)

```bash
# Terminal 2 (Alice)
PRIVMSG #general :!joke
```

**✅ Alice recibe (uno de 10 chistes aleatorios):**
```
:HelpBot!helpbot@127.0.0.1 PRIVMSG #general :Why do programmers prefer dark mode? Because light attracts bugs!
```

```bash
# Ejecutar varias veces para ver diferentes chistes:
PRIVMSG #general :!joke
PRIVMSG #general :!joke
```

---

#### Test B.8: Comando !ping (test de conexión)

```bash
# Terminal 2 (Alice)
PRIVMSG #general :!ping
```

**✅ Alice recibe:**
```
:HelpBot!helpbot@127.0.0.1 PRIVMSG #general :Pong! 🏓
```

---

#### Test B.9: Comandos case-insensitive

```bash
# Terminal 2 (Alice)
PRIVMSG #general :!HELP
PRIVMSG #general :!Time
PRIVMSG #general :!PiNg
```

**✅ Todos funcionan (el bot convierte a lowercase)**

---

#### Test B.10: Mensaje privado directo al bot

```bash
# Terminal 2 (Alice)
PRIVMSG HelpBot :!help
```

**✅ Alice recibe (en PRIVADO, NO en el canal):**
```
:HelpBot!helpbot@127.0.0.1 PRIVMSG Alice :Available commands: !help, !time, !uptime, !echo <msg>, !joke, !ping
                                   ^^^^^
                                   Respuesta privada a Alice
```

> **⚠️ IMPORTANTE:** Otros usuarios en #general NO ven este intercambio

---

#### Test B.11: Comandos privados (todas las funciones)

```bash
# Terminal 2 (Alice en privado con el bot)
PRIVMSG HelpBot :!time
PRIVMSG HelpBot :!uptime
PRIVMSG HelpBot :!echo Testing private echo
PRIVMSG HelpBot :!joke
PRIVMSG HelpBot :!ping
```

**✅ Todas las respuestas llegan en PRIVADO a Alice**

---

#### Test B.12: Múltiples usuarios usando el bot simultáneamente

```bash
# Terminal 2 (Alice)
PRIVMSG #general :!time

# Terminal 3 (Bob - conectado en #general)
nc localhost 6667
PASS pass123
NICK Bob
USER bob 0 * :Bob
JOIN #general
PRIVMSG #general :!joke
```

- ✅ Ambos reciben sus respuestas en el canal
- ✅ El bot NO se confunde entre usuarios

---

#### Test B.13: Bot en canal #help

```bash
# Terminal 2 (Alice)
JOIN #help
PRIVMSG #help :!help
```

**✅ El bot también responde en #help:**
```
:HelpBot!helpbot@127.0.0.1 PRIVMSG #help :Available commands: !help, !time, !uptime, !echo <msg>, !joke, !ping
```

---

#### Test B.14: Comandos inválidos ignorados

```bash
# Terminal 2 (Alice)
PRIVMSG #general :!invalid
PRIVMSG #general :!xyz123
PRIVMSG #general :Hello everyone
```

- ✅ El bot NO responde (solo procesa comandos válidos que empiezan con !)
- ✅ Mensajes normales sin '!' son ignorados

---

#### Test B.15: Bot responde a PING del servidor automáticamente

```bash
# Verificar en el Terminal Bot mientras está corriendo
```

**✅ Si el servidor envía PING, debes ver:**
```
[BOT] <- PING :ft_irc
[BOT] -> PONG :ft_irc
```

> **⚠️ IMPORTANTE:** Esto sucede automáticamente, no requiere intervención

---

#### Test B.16: Verificar que el bot limpia códigos ANSI correctamente

```bash
# Terminal 2 (Alice)
PRIVMSG #general :!help
```

**✅ El bot debe responder correctamente incluso si el servidor envía mensajes con códigos de color ANSI**

**✅ No debe enviar "56:13" o caracteres extraños como target**

**Verificar en el servidor que NO aparecen errores:**
- ❌ NO debe ver: `[SERVER DEBUG] ERROR: Channel not found`
- ✅ El mensaje se transmite limpiamente

---

#### Test B.17: Bot permanece activo con servidor bajo carga

```bash
# Terminal 4 (generar tráfico)
for i in {1..50}; do 
  echo "PRIVMSG #general :Message $i"; 
done | nc localhost 6667 &

# Terminal 2 (Alice - mientras hay tráfico)
PRIVMSG #general :!ping
```

- ✅ El bot sigue respondiendo correctamente
- ✅ NO se crashea con múltiples mensajes

---

#### Test B.18: Detener el bot con Ctrl+C

```bash
# Terminal Bot
# Presionar Ctrl+C
```

**✅ El bot debería cerrarse limpiamente:**
```
^C
[BOT] Bot stopped.
```

**✅ En el servidor:**
```
[DISCONNECT] fd=X (graceful close)
```

**✅ Otros usuarios en #general y #help ven:**
```
:HelpBot!helpbot@127.0.0.1 QUIT :Connection closed
```

---

#### Test B.19: Reiniciar el bot y verificar uptime reseteado

```bash
# Terminal Bot (después de cerrar y reiniciar)
./bot 127.0.0.1 6667 pass123

# Esperar unos segundos...

# Terminal 2 (Alice)
PRIVMSG #general :!uptime
```

**✅ Alice recibe:**
```
:HelpBot!helpbot@127.0.0.1 PRIVMSG #general :Bot uptime: 0h 0m 15s
                                                         ^^^^^^^^^^^
                                                         Tiempo desde el nuevo inicio
```

---

#### Test B.20: Bot con parámetros incorrectos

```bash
# Probar con IP inválida
./bot 999.999.999.999 6667 pass123
```

**✅ Debe mostrar error sin crashear:**
```
[BOT] Error: Invalid IP address
```

```bash
# Probar con puerto inválido
./bot 127.0.0.1 99999 pass123
```

**✅ Debe fallar al conectar:**
```
[BOT] Error: Failed to connect to 127.0.0.1:99999
```

```bash
# Probar con contraseña incorrecta
./bot 127.0.0.1 6667 wrongpass
```

**✅ Debe conectar pero ser rechazado:**
```
[BOT] <- :ft_irc 464 * :Password incorrect
```
Y luego se cierra

---

### 🎯 Resumen del Bot

#### Comandos disponibles:

| Comando | Descripción |
|---------|-------------|
| `!help` | Lista de comandos disponibles |
| `!time` | Muestra la hora actual del sistema |
| `!uptime` | Muestra cuánto tiempo lleva corriendo el bot |
| `!echo <msg>` | Repite el mensaje proporcionado |
| `!joke` | Cuenta un chiste aleatorio de programación |
| `!ping` | Responde con "Pong! 🏓" |

#### Características:

```
✅ Se conecta automáticamente al servidor
✅ Se une a #general y #help al iniciar
✅ Responde en canales públicos
✅ Responde a mensajes privados
✅ Comandos case-insensitive
✅ Maneja PING/PONG automáticamente
✅ Limpia códigos ANSI del servidor
✅ No se crashea con múltiples usuarios
✅ Cierre limpio con Ctrl+C
```

#### Uso:

```bash
make bot
./bot <IP> <PORT> <PASSWORD>
```

#### Ejemplo:

```bash
./bot 127.0.0.1 6667 pass123
```

</details>

---

## 📚 Recursos

### Documentación

- [RFC 2811 - Internet Relay Chat: Channel Management](https://tools.ietf.org/html/rfc2811) - Gestión de canales IRC
- [RFC 2812 - IRC Client Protocol](https://tools.ietf.org/html/rfc2812) - Protocolo cliente IRC actualizado
- [RFC 2813 - IRC Server Protocol](https://tools.ietf.org/html/rfc2813) - Protocolo servidor IRC
- [📄 Subject del proyecto (PDF)](https://cdn.intra.42.fr/pdf/pdf/188979/es.subject.pdf) - Enunciado oficial de 42.


### Herramientas Utilizadas

- **netcat (nc)** - Cliente TCP/IP simple para testing
- **HexChat** - Cliente IRC gráfico para pruebas
- **Irssi** - Cliente IRC en terminal
- **WeeChat** - Cliente IRC extensible
- **Valgrind** - Detección de memory leaks y errores de memoria

### Uso de Inteligencia Artificial

En este proyecto se ha utilizado **GitHub Copilot** y **ChatGPT** como herramientas de asistencia en las siguientes áreas:

- **Corrección de errores de parseo y código**
- **Optimización de código**
- **Explicaciones técnicas de C++ y del protocolo IRC**
- **Ayuda a la organización y distribución del trabajo**
- **Ayuda en el planteamiento general y estructura de archivos**
- **Sugerencias de testeo y gestión de casos límite**

**Importante:** Todo el código generado o sugerido por IA fue:
- ✅ Revisado y comprendido completamente por el equipo
- ✅ Adaptado a los requisitos específicos del proyecto
- ✅ Testeado exhaustivamente en múltiples escenarios
- ✅ Validado contra la norma de 42 y el C++98 estándar

La IA se utilizó como **herramienta de apoyo**, no como generador automático de código. El diseño, arquitectura y decisiones técnicas principales fueron realizadas por el equipo de desarrollo.

---