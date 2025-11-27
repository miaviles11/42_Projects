# ============================================================================
#                      DOCKERFILE ADMINER - INCEPTION
# ============================================================================

# Imagen base: Debian 12 (Bookworm) - distribución estable
FROM debian:bookworm

# Instalar PHP-FPM y extensión MySQL para Adminer
RUN apt-get update && apt-get install -y \
    php8.2-fpm \
    php8.2-mysql \
    wget \
    && rm -rf /var/lib/apt/lists/*

# Establecer directorio de trabajo
WORKDIR /var/www/html

# Descargar Adminer (herramienta ligera de gestión de BD - 1 solo archivo PHP)
RUN wget https://github.com/vrana/adminer/releases/download/v4.8.1/adminer-4.8.1.php \
    && mv adminer-4.8.1.php index.php

# Configurar PHP-FPM para escuchar en puerto 9001 (diferente a WordPress)
RUN sed -i 's|listen = .*|listen = 9001|' /etc/php/8.2/fpm/pool.d/www.conf

# Exponer puerto 9001 (PHP-FPM)
EXPOSE 9001

# Iniciar PHP-FPM en primer plano
CMD ["php-fpm8.2", "-F"]