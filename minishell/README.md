# ![Minishell](https://img.shields.io/badge/Minishell-42-blue?style=flat-square)

📌 **Proyecto de 42** - Implementación de un shell en C inspirado en Bash.

---

## 📖 **Índice**
- [📌 Introducción](#introducción)
- [📜 Requisitos](#requisitos)
- [📂 Estructura del Proyecto](#estructura-del-proyecto)
- [⚙️ Instalación y Uso](#instalación-y-uso)
- [🚀 Características Implementadas](#características-implementadas)
- [📌 Built-in Commands](#built-in-commands)
- [🔧 Redirecciones y Pipes](#redirecciones-y-pipes)
- [📋 Expansión de Variables](#expansión-de-variables)
- [🛠️ Herramientas Utilizadas](#herramientas-utilizadas)
- [📌 Normas de Código](#normas-de-código)
- [🛡️ Gestión de Errores](#gestión-de-errores)
- [🧪 Testing](#testing)
- [📜 Autores](#autores)

---

## 📌 **Introducción**

**Minishell** es una implementación de una shell interactiva en C, inspirada en Bash.  
El objetivo principal de este proyecto es comprender cómo funcionan internamente los **procesos**, los **descriptores de archivos**, el **manejo de señales**, así como la gestión de **redirecciones** y **pipes** típicos en sistemas UNIX.  

Un shell permite a los usuarios:
- Ejecutar programas y scripts.
- Redirigir la entrada/salida a archivos o tuberías.
- Manejar señales del sistema (ej. `Ctrl+C`, `Ctrl+D`, `Ctrl+\`).
- Expandir variables de entorno (ej. `$HOME`, `$PATH`, `$?`).
- Implementar sus propios *built-in commands*.

### 🔍 **¿Qué aprenderás con este proyecto?**
- Conceptos de procesos y llamadas al sistema: `fork()`, `execve()`, `wait()`.
- Manejo de tuberías y redirecciones.
- Implementación de *built-ins* como `cd`, `pwd`, `env`, `export`, etc.
- Gestión de señales y cómo reaccionar ante eventos de teclado.
- Buenas prácticas de programación en C bajo la Norm de 42.

---

## 📜 **Requisitos**

Antes de compilar y ejecutar **Minishell**, necesitas:

- 🛠️ **Sistema Operativo**: Linux o macOS.
- 🔧 **Compilador**: `gcc` (GCC 9+ recomendado).
- 🔗 **Make** (para automatizar la compilación).
- 📚 **Librería `readline`**: para manejo de historial y entrada interactiva (opcional, pero altamente recomendada).
  - En Ubuntu/Debian: `sudo apt-get install libreadline-dev`
- 📂 **libft**: Librería auxiliar (si la Norm y el proyecto lo permiten; se incluye en la carpeta `libft/` con su propio Makefile).

---

## 📂 **Estructura del Proyecto**

La estructura típica de este repositorio es la siguiente:

```plaintext
minishell/
├── include/
│   └── minishell.h         # Header principal del proyecto
├── libft/
│   └── ...                 # Librería libft (si corresponde al proyecto)
├── src/
│   ├── builtins/           # Implementaciones de comandos internos (cd, env, etc.)
│   ├── execution/          # Lógica de ejecución (pipes, redirecciones...)
│   ├── parser/             # Parsing, manejo de tokens, expansión, etc.
│   ├── signals/            # Manejadores de señales
│   └── main.c              # Punto de entrada principal de minishell
├── Makefile                # Script de compilación principal
└── README.md               # Documentación