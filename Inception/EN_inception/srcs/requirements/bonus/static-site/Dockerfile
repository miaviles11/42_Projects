# ============================================================================
#                   DOCKERFILE STATIC-SITE - INCEPTION
# ============================================================================

# Base image: Debian 12 (Bookworm) - stable distribution
FROM debian:bookworm

# Install NGINX (lightweight web server for static content)
RUN apt-get update && apt-get install -y \
    nginx \
    && rm -rf /var/lib/apt/lists/*

# Copy HTML/CSS/JS files to the site directory
COPY html /var/www/html/portfolio

# Copy custom NGINX configuration
COPY conf/nginx.conf /etc/nginx/nginx.conf

# Set correct permissions
RUN chown -R www-data:www-data /var/www/html/portfolio

# Expose port 8080 (internal, accessible via proxy)
EXPOSE 8080

# Start NGINX in foreground
CMD ["nginx", "-g", "daemon off;"]