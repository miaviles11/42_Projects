# ============================================================================
#                      DOCKERFILE ADMINER - INCEPTION
# ============================================================================

# Base image: Debian 12 (Bookworm) - stable distribution
FROM debian:bookworm

# Install PHP-FPM and MySQL extension for Adminer
RUN apt-get update && apt-get install -y \
    php8.2-fpm \
    php8.2-mysql \
    wget \
    && rm -rf /var/lib/apt/lists/*

# Set working directory
WORKDIR /var/www/html

# Download Adminer (lightweight DB management tool - single PHP file)
RUN wget https://github.com/vrana/adminer/releases/download/v4.8.1/adminer-4.8.1.php \
    && mv adminer-4.8.1.php index.php

# Configure PHP-FPM to listen on port 9001 (different from WordPress)
RUN sed -i 's|listen = .*|listen = 9001|' /etc/php/8.2/fpm/pool.d/www.conf

# Expose port 9001 (PHP-FPM)
EXPOSE 9001

# Start PHP-FPM in foreground
CMD ["php-fpm8.2", "-F"]