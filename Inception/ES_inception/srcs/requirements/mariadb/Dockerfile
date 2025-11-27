# ============================================================================
#                      DOCKERFILE MARIADB - INCEPTION
# ============================================================================

# Imagen base: Debian 12 (Bookworm) - distribución estable
FROM debian:bookworm

# Instalar MariaDB Server y limpiar caché de apt
RUN apt-get update && apt-get install -y \
    mariadb-server \
    && rm -rf /var/lib/apt/lists/*

# Copiar configuración personalizada del servidor
COPY conf/50-server.cnf /etc/mysql/mariadb.conf.d/50-server.cnf

# Crear directorios necesarios y establecer permisos correctos
# - /var/run/mysqld: socket de MariaDB
# - /var/log/mysql: logs del servidor
# - /var/lib/mysql: datos de la base de datos
RUN mkdir -p /var/run/mysqld /var/log/mysql && \
    chown -R mysql:mysql /var/run/mysqld /var/log/mysql /var/lib/mysql && \
    chmod 755 /var/log/mysql && \
    chmod 777 /var/run/mysqld

# Copiar script de inicialización y hacerlo ejecutable
COPY tools/setup.sh /usr/local/bin/setup.sh
RUN chmod +x /usr/local/bin/setup.sh

# Exponer puerto 3306 (puerto estándar de MySQL/MariaDB)
EXPOSE 3306

# Ejecutar script de setup al iniciar el contenedor
CMD ["/usr/local/bin/setup.sh"]