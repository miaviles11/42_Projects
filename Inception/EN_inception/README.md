Documentation: https://deepwiki.com/miaviles11/Inception/1-overview

# 🐳 Inception

> *Multi-container Docker infrastructure with NGINX, WordPress and MariaDB*

![Docker](https://img.shields.io/badge/Docker-2496ED?style=for-the-badge&logo=docker&logoColor=white)
![NGINX](https://img.shields.io/badge/NGINX-009639?style=for-the-badge&logo=nginx&logoColor=white)
![WordPress](https://img.shields.io/badge/WordPress-21759B?style=for-the-badge&logo=wordpress&logoColor=white)
![MariaDB](https://img.shields.io/badge/MariaDB-003545?style=for-the-badge&logo=mariadb&logoColor=white)

---

## 📋 Table of Contents

- [Description](#-description)
- [Architecture](#-architecture)
- [Requirements](#-requirements)
- [Installation](#-installation)
- [Usage](#-usage)
- [Services](#-services)
- [Project Structure](#-project-structure)
- [Useful Commands](#-useful-commands)
- [Bonus](#-bonus)
- [Troubleshooting](#-troubleshooting)
- [Resources](#-resources)
- [Author](#-author)

---

## 📖 Description

**Inception** is a system administration project that implements a complete web services infrastructure using **Docker** and **docker-compose**. 

The project deploys a LEMP stack (Linux, NGINX, MariaDB, PHP) with WordPress as CMS, all containerized and orchestrated through docker-compose.

### 🎯 Project Objectives

- Virtualize multiple services using Docker
- Implement containerization best practices
- Configure secure communication between containers
- Manage persistent volumes for data
- Implement HTTPS with TLS 1.2/1.3

---

## 🏗️ Architecture

```
                            INTERNET (HTTPS)
                                  ↓
                            Port 443
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

### 🔗 Docker Bridge Network

All containers communicate through a private **bridge** network called `inception`, allowing:
- Host isolation
- Internal DNS (containers know each other by name)
- Secure communication between services

---

## ✅ Requirements

### Required Software

- **Operating System**: Debian Bookworm (recommended) or Ubuntu
- **Docker**: >= 20.10
- **Docker Compose**: >= 2.0
- **Make**: To execute Makefile commands

### System Requirements

- RAM: >= 2GB
- Disk: >= 10GB free
- CPU: >= 2 cores

---

## 🚀 Installation

### 1. Clone the Repository

```bash
git clone https://github.com/your-username/inception.git
cd inception
```

### 2. Configure Environment Variables

Create the `srcs/.env` file with your credentials:

```bash
# Domain
DOMAIN_NAME=miaviles.42.fr

# MariaDB Configuration
MYSQL_ROOT_PASSWORD=your_secure_root_password
MYSQL_DATABASE=wordpress_db
MYSQL_USER=wp_user
MYSQL_PASSWORD=your_secure_password

# WordPress Configuration
WP_ADMIN_USER=admin_user
WP_ADMIN_PASSWORD=your_secure_admin_password
WP_ADMIN_EMAIL=your_email@example.com
WP_TITLE="My WordPress Site"
WP_URL=https://miaviles.42.fr

WP_USER=editor_user
WP_USER_PASSWORD=your_secure_user_password
WP_USER_EMAIL=user@example.com
```

⚠️ **Important**: 
- DO NOT use weak passwords
- DO NOT upload the `.env` file to Git
- The `.env` file must be in `.gitignore`

### 3. Configure /etc/hosts

Add your domain to the hosts file:

```bash
sudo nano /etc/hosts

# Add this line:
127.0.0.1   miaviles.42.fr
```

### 4. Create Data Directories

Directories are created automatically with `make`, but you can create them manually:

```bash
mkdir -p /home/$USER/data/{wordpress,mariadb,adminer,portainer,mysql_log}
```

---

## 💻 Usage

### Main Commands

```bash
# Start the entire infrastructure
make

# Check container status
make status

# View logs in real-time
make logs

# Stop containers (preserves data)
make down

# Restart containers
make restart

# Clean everything (⚠️ DELETES DATA)
make fclean

# Rebuild (useful after Dockerfile changes)
make rebuild
```

### Backup Commands

```bash
# Create data backup
make backup

# List available backups
make list-backups

# Restore latest backup
make restore

# Backup + safe fclean
make backup-and-fclean
```

### Access Container Shells

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

## 🌐 Services

### 1. NGINX (Mandatory)

- **Port**: 443 (HTTPS)
- **Function**: Reverse proxy and web server
- **TLS**: 1.2 and 1.3
- **Access**: https://miaviles.42.fr

**Features**:
- Self-signed SSL certificates
- Proxy to WordPress (PHP-FPM)
- Gzip compression
- Access and error logs

---

### 2. WordPress (Mandatory)

- **Internal port**: 9000 (PHP-FPM)
- **Function**: Content management system
- **Access**: https://miaviles.42.fr

**Features**:
- Automatic installation via WP-CLI
- 2 users (admin + editor)
- PHP 8.2 with PHP-FPM
- MariaDB connection

**Credentials**:
- Admin: Defined in `.env` (`WP_ADMIN_USER`)
- User: Defined in `.env` (`WP_USER`)

---

### 3. MariaDB (Mandatory)

- **Internal port**: 3306
- **Function**: Relational database
- **Access**: Only from Docker internal network

**Features**:
- MySQL 10.11 (MySQL compatible)
- Persistent database
- 2 users (root + WordPress user)
- Optimized configuration

---

### 4. Adminer (Bonus)

- **Internal port**: 9001 (PHP-FPM)
- **Function**: Web database manager
- **Access**: https://miaviles.42.fr/adminer/

**Features**:
- Web interface to manage MariaDB
- Execute SQL queries
- View table structure
- Import/export data

**Login**:
- System: MySQL
- Server: mariadb
- User: Defined in `.env`
- Password: Defined in `.env`
- Database: wordpress_db

---

### 5. Static Site (Bonus)

- **Internal port**: 8080
- **Function**: Static site (personal portfolio)
- **Access**: https://miaviles.42.fr/portfolio

**Features**:
- Pure HTML/CSS/JavaScript
- No PHP or backend
- Personal portfolio
- Independent NGINX server

---

### 6. Portainer (Bonus)

- **Port**: 9443
- **Function**: Docker management dashboard
- **Access**: https://localhost:9443

**Features**:
- Web interface for Docker
- Container monitoring
- Visual logs
- Resource statistics

**First time**:
1. Create admin user
2. Connect to local Docker
3. Explore dashboard

---

## 📁 Project Structure

```
inception/
├── Makefile                    # Management commands
├── README.md                   # This file
├── backups/                    # Automatic backups
│   ├── wordpress-*.tar.gz
│   └── mariadb-*.tar.gz
└── srcs/
    ├── .env                    # Environment variables (DO NOT upload to Git)
    ├── docker-compose.yml      # Service orchestration
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
                # No Dockerfile (uses official image)
```

---

## 🛠️ Useful Commands

### Docker

```bash
# View running containers
docker ps

# View all containers
docker ps -a

# View container logs
docker logs -f <container_name>

# Enter a container
docker exec -it <container_name> bash

# View resource usage
docker stats

# View volumes
docker volume ls

# View networks
docker network ls
```

### Docker Compose

```bash
# Start services
docker compose -f srcs/docker-compose.yml up -d

# View logs
docker compose -f srcs/docker-compose.yml logs -f

# Stop services
docker compose -f srcs/docker-compose.yml down

# Rebuild
docker compose -f srcs/docker-compose.yml up -d --build
```

### Service Verification

```bash
# Check NGINX
curl -k https://miaviles.42.fr

# Check WordPress
curl -k https://miaviles.42.fr/wp-admin/

# Check Adminer
curl -k https://miaviles.42.fr/adminer/

# Check Portfolio
curl -k https://miaviles.42.fr/portfolio

# Check MariaDB (from WordPress container)
docker exec wordpress mysql -h mariadb -u wp_user -p
```

---

## 🎁 Bonus

### Implemented Bonuses

| Bonus | Difficulty | Description |
|-------|-----------|-------------|
| ✅ **Adminer** | Easy | Web database manager |
| ✅ **Static Site** | Easy | Personal portfolio in HTML/CSS/JS |
| ✅ **Portainer** | Easy | Docker management dashboard |

### NOT Implemented Bonuses

- ❌ **Redis Cache**: Cache for WordPress
- ❌ **FTP Server**: FTP server for files

**Reason**: Quality was prioritized over quantity. 3 well-implemented bonuses > 5 mediocre bonuses.

---

## 🐛 Troubleshooting

### Problem: Container stops immediately

**Cause**: Process not running in foreground

**Solution**:
```bash
# View logs
docker logs <container_name>

# Verify CMD uses foreground mode
# NGINX: nginx -g "daemon off;"
# PHP-FPM: php-fpm8.2 -F
# MariaDB: mariadbd
```

---

### Problem: Cannot access miaviles.42.fr

**Cause**: /etc/hosts not configured

**Solution**:
```bash
# Add to /etc/hosts
sudo nano /etc/hosts
127.0.0.1   miaviles.42.fr
```

---

### Problem: SSL certificate error in browser

**Cause**: Self-signed certificate

**Solution**:
- This is normal
- Click on "Advanced" → "Proceed anyway"
- Or add certificate to browser exceptions

---

### Problem: WordPress cannot connect to MariaDB

**Cause**: MariaDB not ready or incorrect credentials

**Solution**:
```bash
# Verify MariaDB is running
docker ps | grep mariadb

# View MariaDB logs
make logs

# Verify credentials in .env
cat srcs/.env

# Retry connection
make restart
```

---

### Problem: WordPress file permissions

**Cause**: www-data doesn't have permissions

**Solution**:
```bash
# Inside WordPress container
docker exec wordpress chown -R www-data:www-data /var/www/html
```

---

### Problem: Backup error

**Cause**: Insufficient permissions

**Solution**:
```bash
# Create directory with permissions
mkdir -p backups
chmod 755 backups

# Execute with sudo if necessary
sudo make backup
```

---

### Problem: Port 443 already in use

**Cause**: Another service using the port

**Solution**:
```bash
# See what's using the port
sudo lsof -i :443

# Stop conflicting service (example Apache)
sudo systemctl stop apache2
sudo systemctl disable apache2
```

---

## 📚 Resources

### Official Documentation

- [Docker Documentation](https://docs.docker.com/)
- [Docker Compose](https://docs.docker.com/compose/)
- [NGINX Documentation](https://nginx.org/en/docs/)
- [WordPress Codex](https://codex.wordpress.org/)
- [MariaDB Documentation](https://mariadb.com/kb/en/)

### Used Tools

- **WP-CLI**: Command-line interface for WordPress
- **OpenSSL**: SSL certificate generation
- **Docker Compose**: Container orchestration

---

## 📝 Notes

### Security

- ⚠️ SSL certificates are **self-signed** (for development only)
- ⚠️ DO NOT expose MariaDB externally (internal network only)
- ✅ Passwords in `.env` (outside Git)
- ✅ User `www-data` (not root) in containers
- ✅ TLS 1.2/1.3 only

### Data Persistence

Data is saved in:
```
/home/$USER/data/
├── wordpress/      # WordPress files (themes, plugins, uploads)
├── mariadb/        # MySQL database
├── adminer/        # Adminer data
├── portainer/      # Portainer configuration
└── mysql_log/      # MariaDB logs
```

**⚠️ IMPORTANT**: 
- `make fclean` **DELETES** these directories
- Use `make backup` before doing `fclean`

---

## 👨‍💻 Author

**Miguel Avilés**
- 42 Login: `miaviles`
- Project: Inception (42 Madrid)
- Date: November 2025

---

## 📄 License

This project is part of the 42 School curriculum and is for educational purposes.

---

## 🙏 Acknowledgments

- 42 Madrid for the project
- Docker community for the documentation
- 42 peers for peer-learning

---

## ⚡ Quick Start

```bash
# 1. Clone
git clone <repo-url> && cd inception

# 2. Configure .env
cp srcs/.env.example srcs/.env
nano srcs/.env

# 3. Configure domain
echo "127.0.0.1 miaviles.42.fr" | sudo tee -a /etc/hosts

# 4. Start
make

# 5. Access
firefox https://miaviles.42.fr
```

---

## 🎯 Evaluation Checklist

### Mandatory

- [x] Makefile at root with rules all, clean, fclean, re
- [x] docker-compose.yml in srcs/
- [x] Custom Dockerfiles (one per service)
- [x] Images built from Debian Bookworm
- [x] NGINX with TLSv1.2/1.3 on port 443
- [x] WordPress with PHP-FPM (without NGINX)
- [x] MariaDB (without NGINX)
- [x] 2 volumes (WordPress files + MariaDB data)
- [x] Docker bridge network
- [x] Containers with automatic restart
- [x] Environment variables in .env
- [x] Data in /home/login/data
- [x] Domain points to local IP
- [x] 2 users in WordPress
- [x] Admin user without "admin" in name
- [x] DO NOT use :latest tag
- [x] DO NOT use network: host or --link
- [x] DO NOT use tail -f, sleep infinity, while true
- [x] Processes in foreground (daemon off)

### Bonus

- [x] Adminer implemented
- [x] Static site (no PHP) implemented
- [x] Additional useful service (Portainer)
- [x] Total: 3 functional bonuses

---

<div align="center">

**Made with ❤️ and 🐳 for 42 School**

[⬆ Back to top](#-inception)

</div>
