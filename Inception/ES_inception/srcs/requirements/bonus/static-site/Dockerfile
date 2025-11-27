# ============================================================================
#                   DOCKERFILE STATIC-SITE - INCEPTION
# ============================================================================

# Imagen base: Debian 12 (Bookworm) - distribución estable
FROM debian:bookworm

# Instalar NGINX (servidor web ligero para contenido estático)
RUN apt-get update && apt-get install -y \
    nginx \
    && rm -rf /var/lib/apt/lists/*

# Copiar archivos HTML/CSS/JS al directorio del sitio
COPY html /var/www/html/portfolio

# Copiar configuración personalizada de NGINX
COPY conf/nginx.conf /etc/nginx/nginx.conf

# Establecer permisos correctos
RUN chown -R www-data:www-data /var/www/html/portfolio

# Exponer puerto 8080 (interno, accesible vía proxy)
EXPOSE 8080

# Iniciar NGINX en primer plano
CMD ["nginx", "-g", "daemon off;"]