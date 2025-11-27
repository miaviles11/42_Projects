# 🐳 Inception

> **Complete Docker infrastructure with NGINX, WordPress, MariaDB, and bonus services**

<div align="center">

![Docker](https://img.shields.io/badge/Docker-2496ED?style=for-the-badge&logo=docker&logoColor=white)
![NGINX](https://img.shields.io/badge/NGINX-009639?style=for-the-badge&logo=nginx&logoColor=white)
![WordPress](https://img.shields.io/badge/WordPress-21759B?style=for-the-badge&logo=wordpress&logoColor=white)
![MariaDB](https://img.shields.io/badge/MariaDB-003545?style=for-the-badge&logo=mariadb&logoColor=white)

**System Administration Project - 42 School**

[🇪🇸 Español](./ES_inception/README.md) • [🇬🇧 English](./EN_inception/README.md)

</div>

---

## 🚀 What is this?

A **production-ready Docker infrastructure** that deploys a complete web stack:

- ✅ **NGINX** with TLS 1.2/1.3 as reverse proxy
- ✅ **WordPress** with PHP-FPM (automated installation)
- ✅ **MariaDB** with persistent data
- ✅ **Adminer** for database management
- ✅ **Static site** (HTML/CSS/JS portfolio)
- ✅ **Portainer** for Docker management

All orchestrated with **docker-compose**, isolated in containers, with automated backups.

---

## 📸 Quick Preview

```
                    Internet (HTTPS:443)
                            ↓
                    ┌───────────────┐
                    │     NGINX     │  ← Single entry point
                    │   (Reverse    │     TLS termination
                    │    Proxy)     │
                    └───────┬───────┘
                            │
            ┌───────────────┼───────────────┐
            ↓               ↓               ↓
    ┌──────────┐    ┌──────────┐    ┌──────────┐
    │WordPress │    │ Adminer  │    │  Static  │
    │PHP-FPM   │    │ (bonus)  │    │   Site   │
    └────┬─────┘    └────┬─────┘    └──────────┘
         │               │
         └───────┬───────┘
                 ↓
         ┌──────────┐
         │ MariaDB  │
         └──────────┘
```

---

## ⚡ Quick Start

```bash
# Clone the repository
git clone <repo-url> && cd inception

# Configure environment
cp srcs/.env.example srcs/.env
nano srcs/.env

# Add domain to /etc/hosts
echo "127.0.0.1 miaviles.42.fr" | sudo tee -a /etc/hosts

# Launch everything
make

# Access services
firefox https://miaviles.42.fr
```

---

## 🎯 Key Features

### 🏗️ **Professional Architecture**
- Microservices isolated in containers
- Internal bridge network
- Persistent volumes with bind mounts
- Automated orchestration

### 🔒 **Security First**
- HTTPS only (TLS 1.2/1.3)
- Isolated database (no external exposure)
- Non-root users (www-data)
- Environment variables (.env)

### 🛠️ **DevOps Ready**
- Complete Makefile with 20+ commands
- Automated backups and restore
- Hot rebuild without data loss
- Access to container shells

### 📦 **Bonus Services**
- Adminer (web DB manager)
- Static portfolio (no PHP)
- Portainer (Docker dashboard)

---

## 📚 Full Documentation

Choose your language:

<table>
<tr>
<td width="50%" align="center">

### 🇪🇸 Español

**[📖 README Completo](./ES_inception/README.md)**

Documentación detallada en español:
- Instalación paso a paso
- Guía de comandos
- Troubleshooting
- Arquitectura explicada

</td>
<td width="50%" align="center">

### 🇬🇧 English

**[📖 Complete README](./EN_inception/README.md)**

Detailed documentation in English:
- Step-by-step installation
- Commands guide
- Troubleshooting
- Architecture explained

</td>
</tr>
</table>

---

## 🎓 Concepts Documentation

Comprehensive PDF guides explaining all Docker concepts (no code, just theory):

- 📄 **[Conceptos en Español](./ES_inception/Inception_Conceptos_ES.pdf)** - 16 chapters covering Docker, NGINX, PHP-FPM, FastCGI, etc.
- 📄 **[Concepts in English](./EN_inception/Inception_Concepts_EN.pdf)** - Complete translation with glossary

Perfect for studying before evaluation or understanding how everything works.

---

## 🛠️ Tech Stack

| Component | Technology | Purpose |
|-----------|-----------|---------|
| **Web Server** | NGINX | Reverse proxy + SSL/TLS |
| **Application** | WordPress + PHP-FPM | Dynamic CMS |
| **Database** | MariaDB | Data persistence |
| **Orchestration** | Docker Compose | Multi-container management |
| **Base OS** | Debian Bookworm | Stable Linux distribution |

---

## 🎯 Highlights

✨ **Clean Architecture** - Every service in its own container  
🔐 **Secure by Default** - TLS only, isolated network, no root  
📦 **Easy to Deploy** - One command to launch everything  
🔄 **Zero Data Loss** - Automated backups and restore  
📖 **Well Documented** - Bilingual comprehensive guides  
🎨 **Production Ready** - Follows Docker best practices  

---

## 🤝 Contributing

This project is part of the 42 School curriculum. If you find it useful:

- ⭐ Star the repository
- 🐛 Report issues
- 💡 Suggest improvements
- 📖 Share with fellow students

---

## 👨‍💻 Author

**miaviles** - 42 Madrid

Built with ❤️ and 🐳 for 42 School's Inception project

---

## 📄 License

Educational project - 42 School curriculum

---

<div align="center">

</div>
