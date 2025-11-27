Documentation: https://deepwiki.com/miaviles11/Inception/1-overview

# 🐳 Inception

> *Infraestructura Docker multi-contenedor con NGINX, WordPress y MariaDB*

![Docker](https://img.shields.io/badge/Docker-2496ED?style=for-the-badge&logo=docker&logoColor=white)
![NGINX](https://img.shields.io/badge/NGINX-009639?style=for-the-badge&logo=nginx&logoColor=white)
![WordPress](https://img.shields.io/badge/WordPress-21759B?style=for-the-badge&logo=wordpress&logoColor=white)
![MariaDB](https://img.shields.io/badge/MariaDB-003545?style=for-the-badge&logo=mariadb&logoColor=white)

---

## 📋 Índice

- [Descripción](#-descripción)
- [Arquitectura](#-arquitectura)
- [Requisitos](#-requisitos)
- [Instalación](#-instalación)
- [Uso](#-uso)
- [Servicios](#-servicios)
- [Estructura del Proyecto](#-estructura-del-proyecto)
- [Comandos Útiles](#-comandos-útiles)
- [Bonus](#-bonus)
- [Troubleshooting](#-troubleshooting)
- [Recursos](#-recursos)
- [Autor](#-autor)

---

## 📖 Descripción

**Inception** es un proyecto de administración de sistemas que implementa una infraestructura completa de servicios web utilizando **Docker** y **docker-compose**. 

El proyecto despliega un stack LEMP (Linux, NGINX, MariaDB, PHP) con WordPress como CMS, todo containerizado y orquestado mediante docker-compose.

### 🎯 Objetivos del Proyecto

- Virtualizar múltiples servicios usando Docker
- Implementar buenas prácticas de containerización
- Configurar comunicación segura entre contenedores
- Gestionar volúmenes persistentes para datos
- Implementar HTTPS con TLS 1.2/1.3

---

## 🏗️ Arquitectura

```
                            INTERNET (HTTPS)
                                  ↓
                            Puerto 443
                                  ↓
                    ┌─────────────────────────┐
                    │    NGINX (Reverse Proxy)│
                    │    TLSv1.2/1.3          │
                    └───────────┬─────────────┘
                                │
                ┌───────────────┼───────────────┐
                ↓               ↓               ↓
        ┌──────────────┐ ┌──────────────┐ ┌──────────────┐
        │  WordPress   │ │   Adminer    │ │ Static Site  │
        │  PHP-FPM     │ │  (Bonus)     │ │   (Bonus)    │
        │  :9000       │ │  :9001       │ │   :8080      │
        └──────┬───────┘ └──────┬───────┘ └──────────────┘
               │                │
               └────────┬───────┘
                        ↓
                ┌──────────────┐
                │   MariaDB    │
                │   :3306      │
                └──────────────┘
```

### 🔗 Red Docker Bridge

Todos los contenedores se comunican a través de una red privada tipo **bridge** llamada `inception`, permitiendo:
- Aislamiento del host
- DNS interno (los contenedores se conocen por nombre)
- Comunicación segura entre servicios

---

## ✅ Requisitos

### Software Necesario

- **Sistema Operativo**: Debian Bookworm (recomendado) o Ubuntu
- **Docker**: >= 20.10
- **Docker Compose**: >= 2.0
- **Make**: Para ejecutar comandos del Makefile

### Requisitos del Sistema

- RAM: >= 2GB
- Disco: >= 10GB libres
- CPU: >= 2 cores

---

## 🚀 Instalación

### 1. Clonar el Repositorio

```bash
git clone https://github.com/tu-usuario/inception.git
cd inception
```

### 2. Configurar Variables de Entorno

Crea el archivo `srcs/.env` con tus credenciales:

```bash
# Dominio
DOMAIN_NAME=miaviles.42.fr

# MariaDB Configuration
MYSQL_ROOT_PASSWORD=tu_password_root_seguro
MYSQL_DATABASE=wordpress_db
MYSQL_USER=wp_user
MYSQL_PASSWORD=tu_password_seguro

# WordPress Configuration
WP_ADMIN_USER=admin_user
WP_ADMIN_PASSWORD=tu_admin_password_seguro
WP_ADMIN_EMAIL=tu_email@example.com
WP_TITLE="Mi Sitio WordPress"
WP_URL=https://miaviles.42.fr

WP_USER=editor_user
WP_USER_PASSWORD=tu_user_password_seguro
WP_USER_EMAIL=usuario@example.com
```

⚠️ **Importante**: 
- NO usar contraseñas débiles
- NO subir el archivo `.env` a Git
- El archivo `.env` debe estar en `.gitignore`

### 3. Configurar /etc/hosts

Añade tu dominio al archivo hosts:

```bash
sudo nano /etc/hosts

# Añadir esta línea:
127.0.0.1   miaviles.42.fr
```

### 4. Crear Directorios de Datos

Los directorios se crean automáticamente con `make`, pero puedes crearlos manualmente:

```bash
mkdir -p /home/$USER/data/{wordpress,mariadb,adminer,portainer,mysql_log}
```

---

## 💻 Uso

### Comandos Principales

```bash
# Levantar toda la infraestructura
make

# Ver estado de los contenedores
make status

# Ver logs en tiempo real
make logs

# Detener contenedores (conserva datos)
make down

# Reiniciar contenedores
make restart

# Limpiar todo (⚠️ BORRA DATOS)
make fclean

# Rebuild (útil tras cambios en Dockerfiles)
make rebuild
```

### Comandos de Backup

```bash
# Crear backup de datos
make backup

# Listar backups disponibles
make list-backups

# Restaurar último backup
make restore

# Backup + fclean seguro
make backup-and-fclean
```

### Acceder a los Shells de Contenedores

```bash
# NGINX
make sh-nginx

# WordPress
make sh-wordpress

# MariaDB
make sh-mariadb

# Adminer
make sh-adminer
```

---

## 🌐 Servicios

### 1. NGINX (Mandatory)

- **Puerto**: 443 (HTTPS)
- **Función**: Reverse proxy y servidor web
- **TLS**: 1.2 y 1.3
- **Acceso**: https://miaviles.42.fr

**Características**:
- Certificados SSL autofirmados
- Proxy a WordPress (PHP-FPM)
- Compresión gzip
- Logs de acceso y errores

---

### 2. WordPress (Mandatory)

- **Puerto interno**: 9000 (PHP-FPM)
- **Función**: Sistema de gestión de contenido
- **Acceso**: https://miaviles.42.fr

**Características**:
- Instalación automática vía WP-CLI
- 2 usuarios (admin + editor)
- PHP 8.2 con PHP-FPM
- Conexión a MariaDB

**Credenciales**:
- Admin: Definido en `.env` (`WP_ADMIN_USER`)
- Usuario: Definido en `.env` (`WP_USER`)

---

### 3. MariaDB (Mandatory)

- **Puerto interno**: 3306
- **Función**: Base de datos relacional
- **Acceso**: Solo desde red interna Docker

**Características**:
- MySQL 10.11 (compatible con MySQL)
- Base de datos persistente
- 2 usuarios (root + usuario WordPress)
- Configuración optimizada

---

### 4. Adminer (Bonus)

- **Puerto interno**: 9001 (PHP-FPM)
- **Función**: Gestor de base de datos web
- **Acceso**: https://miaviles.42.fr/adminer/

**Características**:
- Interfaz web para gestionar MariaDB
- Ejecutar queries SQL
- Ver estructura de tablas
- Importar/exportar datos

**Login**:
- Sistema: MySQL
- Servidor: mariadb
- Usuario: Definido en `.env`
- Contraseña: Definida en `.env`
- Base de datos: wordpress_db

---

### 5. Static Site (Bonus)

- **Puerto interno**: 8080
- **Función**: Sitio estático (portfolio personal)
- **Acceso**: https://miaviles.42.fr/portfolio

**Características**:
- HTML/CSS/JavaScript puro
- Sin PHP ni backend
- Portfolio personal
- Servidor NGINX independiente

---

### 6. Portainer (Bonus)

- **Puerto**: 9443
- **Función**: Dashboard de gestión Docker
- **Acceso**: https://localhost:9443

**Características**:
- Interfaz web para Docker
- Monitoreo de contenedores
- Logs visuales
- Estadísticas de recursos

**Primera vez**:
1. Crear usuario admin
2. Conectar a Docker local
3. Explorar dashboard

---

## 📁 Estructura del Proyecto

```
inception/
├── Makefile                    # Comandos de gestión
├── README.md                   # Este archivo
├── backups/                    # Backups automáticos
│   ├── wordpress-*.tar.gz
│   └── mariadb-*.tar.gz
└── srcs/
    ├── .env                    # Variables de entorno (NO subir a Git)
    ├── docker-compose.yml      # Orquestación de servicios
    └── requirements/
        ├── mariadb/
        │   ├── Dockerfile
        │   ├── conf/
        │   │   └── mariadb.cnf
        │   └── tools/
        │       └── init.sh
        ├── wordpress/
        │   ├── Dockerfile
        │   └── tools/
        │       └── setup.sh
        ├── nginx/
        │   ├── Dockerfile
        │   ├── conf/
        │   │   ├── nginx.conf
        │   │   └── default.conf
        │   └── tools/
        │       └── generate-certs.sh
        └── bonus/
            ├── adminer/
            │   └── Dockerfile
            ├── static-site/
            │   ├── Dockerfile
            │   ├── conf/
            │   │   └── nginx.conf
            │   └── html/
            │       └── index.html
            └── portainer/
                # Sin Dockerfile (usa imagen oficial)
```

---

## 🛠️ Comandos Útiles

### Docker

```bash
# Ver contenedores corriendo
docker ps

# Ver todos los contenedores
docker ps -a

# Ver logs de un contenedor
docker logs -f <container_name>

# Entrar a un contenedor
docker exec -it <container_name> bash

# Ver uso de recursos
docker stats

# Ver volúmenes
docker volume ls

# Ver redes
docker network ls
```

### Docker Compose

```bash
# Levantar servicios
docker compose -f srcs/docker-compose.yml up -d

# Ver logs
docker compose -f srcs/docker-compose.yml logs -f

# Parar servicios
docker compose -f srcs/docker-compose.yml down

# Rebuild
docker compose -f srcs/docker-compose.yml up -d --build
```

### Verificación de Servicios

```bash
# Comprobar NGINX
curl -k https://miaviles.42.fr

# Comprobar WordPress
curl -k https://miaviles.42.fr/wp-admin/

# Comprobar Adminer
curl -k https://miaviles.42.fr/adminer/

# Comprobar Portfolio
curl -k https://miaviles.42.fr/portfolio

# Comprobar MariaDB (desde contenedor WordPress)
docker exec wordpress mysql -h mariadb -u wp_user -p
```

---

## 🎁 Bonus

### Bonuses Implementados

| Bonus | Dificultad | Descripción |
|-------|-----------|-------------|
| ✅ **Adminer** | Fácil | Gestor web de base de datos |
| ✅ **Static Site** | Fácil | Portfolio personal en HTML/CSS/JS |
| ✅ **Portainer** | Fácil | Dashboard de gestión Docker |

### Bonuses NO Implementados

- ❌ **Redis Cache**: Caché para WordPress
- ❌ **FTP Server**: Servidor FTP para archivos

**Razón**: Se priorizó calidad sobre cantidad. 3 bonuses bien implementados > 5 bonuses mediocres.

---

## 🐛 Troubleshooting

### Problema: Contenedor se detiene inmediatamente

**Causa**: Proceso no se ejecuta en foreground

**Solución**:
```bash
# Ver logs
docker logs <container_name>

# Verificar que CMD usa foreground mode
# NGINX: nginx -g "daemon off;"
# PHP-FPM: php-fpm8.2 -F
# MariaDB: mariadbd
```

---

### Problema: No puedo acceder a miaviles.42.fr

**Causa**: /etc/hosts no configurado

**Solución**:
```bash
# Añadir a /etc/hosts
sudo nano /etc/hosts
127.0.0.1   miaviles.42.fr
```

---

### Problema: Error de certificado SSL en navegador

**Causa**: Certificado autofirmado

**Solución**:
- Es normal
- Click en "Avanzado" → "Proceder de todas formas"
- O añadir certificado a excepciones del navegador

---

### Problema: WordPress no conecta con MariaDB

**Causa**: MariaDB no está listo o credenciales incorrectas

**Solución**:
```bash
# Verificar que MariaDB está corriendo
docker ps | grep mariadb

# Ver logs de MariaDB
make logs

# Verificar credenciales en .env
cat srcs/.env

# Reintentar conexión
make restart
```

---

### Problema: Permisos de archivos WordPress

**Causa**: www-data no tiene permisos

**Solución**:
```bash
# Dentro del contenedor WordPress
docker exec wordpress chown -R www-data:www-data /var/www/html
```

---

### Problema: Error al hacer backup

**Causa**: Permisos insuficientes

**Solución**:
```bash
# Crear directorio con permisos
mkdir -p backups
chmod 755 backups

# Ejecutar con sudo si es necesario
sudo make backup
```

---

### Problema: Puerto 443 ya en uso

**Causa**: Otro servicio usando el puerto

**Solución**:
```bash
# Ver qué usa el puerto
sudo lsof -i :443

# Detener servicio conflictivo (ejemplo Apache)
sudo systemctl stop apache2
sudo systemctl disable apache2
```

---

## 📚 Recursos

### Documentación Oficial

- [Docker Documentation](https://docs.docker.com/)
- [Docker Compose](https://docs.docker.com/compose/)
- [NGINX Documentation](https://nginx.org/en/docs/)
- [WordPress Codex](https://codex.wordpress.org/)
- [MariaDB Documentation](https://mariadb.com/kb/en/)

### Herramientas Utilizadas

- **WP-CLI**: Interfaz de línea de comandos para WordPress
- **OpenSSL**: Generación de certificados SSL
- **Docker Compose**: Orquestación de contenedores

---

## 📝 Notas

### Seguridad

- ⚠️ Certificados SSL son **autofirmados** (solo para desarrollo)
- ⚠️ NO exponer MariaDB al exterior (solo red interna)
- ✅ Contraseñas en `.env` (fuera de Git)
- ✅ Usuario `www-data` (no root) en contenedores
- ✅ TLS 1.2/1.3 únicamente

### Persistencia de Datos

Los datos se guardan en:
```
/home/$USER/data/
├── wordpress/      # Archivos WordPress (themes, plugins, uploads)
├── mariadb/        # Base de datos MySQL
├── adminer/        # Datos de Adminer
├── portainer/      # Configuración Portainer
└── mysql_log/      # Logs de MariaDB
```

**⚠️ IMPORTANTE**: 
- `make fclean` **BORRA** estos directorios
- Usa `make backup` antes de hacer `fclean`

---

## 👨‍💻 Autor

**Miguel Avilés**
- 42 Login: `miaviles`
- Proyecto: Inception (42 Madrid)
- Fecha: Noviembre 2025

---

## 📄 Licencia

Este proyecto es parte del curriculum de 42 School y tiene propósitos educativos.

---

## 🙏 Agradecimientos

- 42 Madrid por el proyecto
- La comunidad de Docker por la documentación
- Compañeros de 42 por el peer-learning

---

## ⚡ Quick Start

```bash
# 1. Clonar
git clone <repo-url> && cd inception

# 2. Configurar .env
cp srcs/.env.example srcs/.env
nano srcs/.env

# 3. Configurar dominio
echo "127.0.0.1 miaviles.42.fr" | sudo tee -a /etc/hosts

# 4. Levantar
make

# 5. Acceder
firefox https://miaviles.42.fr
```

---

## 🎯 Checklist de Evaluación

### Mandatory

- [x] Makefile en raíz con reglas all, clean, fclean, re
- [x] docker-compose.yml en srcs/
- [x] Dockerfiles personalizados (uno por servicio)
- [x] Imágenes construidas desde Debian Bookworm
- [x] NGINX con TLSv1.2/1.3 en puerto 443
- [x] WordPress con PHP-FPM (sin NGINX)
- [x] MariaDB (sin NGINX)
- [x] 2 volúmenes (WordPress files + MariaDB data)
- [x] Red Docker bridge
- [x] Contenedores con restart automático
- [x] Variables de entorno en .env
- [x] Datos en /home/login/data
- [x] Dominio apunta a IP local
- [x] 2 usuarios en WordPress
- [x] Usuario admin sin "admin" en el nombre
- [x] NO usar :latest tag
- [x] NO usar network: host o --link
- [x] NO usar tail -f, sleep infinity, while true
- [x] Procesos en foreground (daemon off)

### Bonus

- [x] Adminer implementado
- [x] Sitio estático (no PHP) implementado
- [x] Servicio útil adicional (Portainer)
- [x] Total: 3 bonuses funcionales

---

<div align="center">

**Made with ❤️ and 🐳 for 42 School**

[⬆ Volver arriba](#-inception)

</div>
