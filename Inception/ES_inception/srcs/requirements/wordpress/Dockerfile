# ============================================================================
#                     DOCKERFILE WORDPRESS - INCEPTION
# ============================================================================

# Imagen base: Debian 12 (Bookworm) - distribución estable
FROM debian:bookworm

# Instalar PHP-FPM y extensiones necesarias para WordPress
RUN apt-get update && apt-get install -y \
    php8.2-fpm \
    php8.2-mysql \
    php8.2-curl \
    php8.2-gd \
    php8.2-intl \
    php8.2-mbstring \
    php8.2-soap \
    php8.2-xml \
    php8.2-xmlrpc \
    php8.2-zip \
    curl \
    mariadb-client \
    && rm -rf /var/lib/apt/lists/*

# Descargar e instalar WP-CLI (herramienta de gestión de WordPress)
RUN curl -O https://raw.githubusercontent.com/wp-cli/builds/gh-pages/phar/wp-cli.phar \
    && chmod +x wp-cli.phar && mv wp-cli.phar /usr/local/bin/wp

# Configurar PHP-FPM para escuchar en puerto 9000 (FastCGI)
RUN mkdir -p /run/php && \
    sed -i 's|listen = .*|listen = 9000|' /etc/php/8.2/fpm/pool.d/www.conf

# Establecer directorio de trabajo
WORKDIR /var/www/html

# Copiar script de inicialización y hacerlo ejecutable
COPY tools/setup.sh /usr/local/bin/setup.sh
RUN chmod +x /usr/local/bin/setup.sh

# Exponer puerto 9000 (PHP-FPM)
EXPOSE 9000

# Ejecutar script de setup al iniciar el contenedor
CMD ["/usr/local/bin/setup.sh"]
