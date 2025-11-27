# ============================================================================
#                     DOCKERFILE WORDPRESS - INCEPTION
# ============================================================================

# Base image: Debian 12 (Bookworm) - stable distribution
FROM debian:bookworm

# Install PHP-FPM and necessary extensions for WordPress
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

# Download and install WP-CLI (WordPress management tool)
RUN curl -O https://raw.githubusercontent.com/wp-cli/builds/gh-pages/phar/wp-cli.phar \
    && chmod +x wp-cli.phar && mv wp-cli.phar /usr/local/bin/wp

# Configure PHP-FPM to listen on port 9000 (FastCGI)
RUN mkdir -p /run/php && \
    sed -i 's|listen = .*|listen = 9000|' /etc/php/8.2/fpm/pool.d/www.conf

# Set working directory
WORKDIR /var/www/html

# Copy initialization script and make it executable
COPY tools/setup.sh /usr/local/bin/setup.sh
RUN chmod +x /usr/local/bin/setup.sh

# Expose port 9000 (PHP-FPM)
EXPOSE 9000

# Run setup script when starting the container
CMD ["/usr/local/bin/setup.sh"]
