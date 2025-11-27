# ============================================================================
#                       DOCKERFILE NGINX - INCEPTION
# ============================================================================

# Base image: Debian 12 (Bookworm) - stable distribution
FROM debian:bookworm

# Install NGINX and OpenSSL (to generate SSL certificates)
RUN apt-get update && apt-get install -y \
    nginx \
    openssl \
    && rm -rf /var/lib/apt/lists/*

# Create directory for SSL/TLS certificates
RUN mkdir -p /etc/nginx/ssl

# Generate self-signed SSL certificate
# -x509: self-signed certificate
# -nodes: no private key encryption
# -days 365: valid for 1 year
# -newkey rsa:2048: 2048-bit RSA key
RUN openssl req -x509 -nodes -days 365 -newkey rsa:2048 \
    -keyout /etc/nginx/ssl/nginx.key \
    -out /etc/nginx/ssl/nginx.crt \
    -subj "/C=ES/ST=Madrid/L=Madrid/O=42Madrid/CN=miaviles.42.fr"

# Copy custom configuration files
COPY conf/nginx.conf /etc/nginx/nginx.conf
COPY conf/default.conf /etc/nginx/sites-enabled/default

# Create web directory and set correct permissions
RUN mkdir -p /var/www/html && \
    chown -R www-data:www-data /var/www/html && \
    chmod -R 755 /var/www/html

# Expose port 443 (HTTPS)
EXPOSE 443

# Start NGINX in foreground (daemon off for Docker)
CMD ["nginx", "-g", "daemon off;"]