# Libft - Escuela 42

## 📖 Descripción
Libft es una biblioteca de funciones escritas en C que replican y amplían las funcionalidades de la biblioteca estándar de C (libc). Este proyecto es parte del currículo de la escuela 42.

## 📋 Funcionalidades principales
- Manipulación de cadenas (`ft_strlen`, `ft_strcpy`, `ft_strdup`, etc.)
- Manipulación de memoria (`ft_memcpy`, `ft_memset`, etc.)
- Funciones de impresión (`ft_putchar_fd`, `ft_putstr_fd`, `ft_printf`, etc.)
- Lectura de archivos (`get_next_line`)
- Funciones de listas enlazadas (bonus)

## 🗂️ Estructura del proyecto
- **libft.h**: Archivo de cabecera con las declaraciones de todas las funciones.
- **libft.a**: Biblioteca estática generada tras la compilación.
- **src/**: Código fuente de todas las funciones.
- **bonus/**: Funciones adicionales para listas enlazadas.
- **main.c**: Archivo principal para realizar pruebas.
- **Makefile**: Archivo de automatización para compilar la biblioteca.

## 💾 Instalación
1. Clona el repositorio:
    ```bash
    git clone <URL_DEL_REPOSITORIO>
    ```
2. Compila la biblioteca:
    ```bash
    make
    ```

## 🚀 Uso
Para usar la biblioteca en un proyecto, compila tu código junto con `libft.a`:
```bash
cc main.c -L. -lft -o program_name
