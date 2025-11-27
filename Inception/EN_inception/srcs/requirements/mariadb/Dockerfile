# ============================================================================
#                      DOCKERFILE MARIADB - INCEPTION
# ============================================================================

# Base image: Debian 12 (Bookworm) - stable distribution
FROM debian:bookworm

# Install MariaDB Server and clean apt cache
RUN apt-get update && apt-get install -y \
    mariadb-server \
    && rm -rf /var/lib/apt/lists/*

# Copy custom server configuration
COPY conf/50-server.cnf /etc/mysql/mariadb.conf.d/50-server.cnf

# Create necessary directories and set correct permissions
# - /var/run/mysqld: MariaDB socket
# - /var/log/mysql: server logs
# - /var/lib/mysql: database data
RUN mkdir -p /var/run/mysqld /var/log/mysql && \
    chown -R mysql:mysql /var/run/mysqld /var/log/mysql /var/lib/mysql && \
    chmod 755 /var/log/mysql && \
    chmod 777 /var/run/mysqld

# Copy initialization script and make it executable
COPY tools/setup.sh /usr/local/bin/setup.sh
RUN chmod +x /usr/local/bin/setup.sh

# Expose port 3306 (standard MySQL/MariaDB port)
EXPOSE 3306

# Run setup script when starting the container
CMD ["/usr/local/bin/setup.sh"]