# ============================================================================
#                       DOCKERFILE NGINX - INCEPTION
# ============================================================================

# Imagen base: Debian 12 (Bookworm) - distribución estable
FROM debian:bookworm

# Instalar NGINX y OpenSSL (para generar certificados SSL)
RUN apt-get update && apt-get install -y \
    nginx \
    openssl \
    && rm -rf /var/lib/apt/lists/*

# Crear directorio para certificados SSL/TLS
RUN mkdir -p /etc/nginx/ssl

# Generar certificado SSL autofirmado
# -x509: certificado autofirmado
# -nodes: sin encriptación de clave privada
# -days 365: válido por 1 año
# -newkey rsa:2048: clave RSA de 2048 bits
RUN openssl req -x509 -nodes -days 365 -newkey rsa:2048 \
    -keyout /etc/nginx/ssl/nginx.key \
    -out /etc/nginx/ssl/nginx.crt \
    -subj "/C=ES/ST=Madrid/L=Madrid/O=42Madrid/CN=miaviles.42.fr"

# Copiar archivos de configuración personalizados
COPY conf/nginx.conf /etc/nginx/nginx.conf
COPY conf/default.conf /etc/nginx/sites-enabled/default

# Crear directorio web y establecer permisos correctos
RUN mkdir -p /var/www/html && \
    chown -R www-data:www-data /var/www/html && \
    chmod -R 755 /var/www/html

# Exponer puerto 443 (HTTPS)
EXPOSE 443

# Iniciar NGINX en primer plano (daemon off para Docker)
CMD ["nginx", "-g", "daemon off;"]