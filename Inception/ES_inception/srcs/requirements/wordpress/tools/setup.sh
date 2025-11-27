#!/bin/bash

# ============================================================================
#           SCRIPT DE INICIALIZACIÓN DE WORDPRESS - INCEPTION
# ============================================================================
# Este script espera a que MariaDB esté disponible y luego instala/configura
# WordPress usando WP-CLI (herramienta de línea de comandos oficial).
# ============================================================================

# Configuración de timeout para esperar MariaDB
MAX_WAIT=120
WAITED=0
SLEEP=3

# Esperar a que MariaDB esté lista y acepte conexiones
until MYSQL_PWD="$MYSQL_PASSWORD" mysql -h mariadb -u"$MYSQL_USER" -e "SELECT 1" &>/dev/null; do
if [ $WAITED -ge $MAX_WAIT ]; then
	echo "ERROR: MariaDB not ready after $MAX_WAIT seconds" >&2
	exit 1
fi
echo "Waiting for MariaDB..."
sleep $SLEEP
WAITED=$((WAITED + SLEEP))
done

echo "MariaDB is ready!"

# Verificar si WordPress ya está instalado (comprobando wp-config.php)
if [ ! -f /var/www/html/wp-config.php ]; then
	echo "Installing WordPress..."
	
	# Descargar archivos core de WordPress
	wp core download --allow-root
	
	# Crear archivo wp-config.php con datos de conexión a BD
	wp config create \
		--dbname=$MYSQL_DATABASE \
		--dbuser=$MYSQL_USER \
		--dbpass=$MYSQL_PASSWORD \
		--dbhost=mariadb:3306 \
		--allow-root
	
	# Instalar WordPress (crear tablas y configuración inicial)
	wp core install \
		--url=$DOMAIN_NAME \
		--title="$WP_TITLE" \
		--admin_user=$WP_ADMIN_USER \
		--admin_password=$WP_ADMIN_PASSWORD \
		--admin_email=$WP_ADMIN_EMAIL \
		--allow-root
	
	# Crear usuario adicional con rol de autor
	wp user create \
		$WP_USER \
		$WP_USER_EMAIL \
		--role=author \
		--user_pass=$WP_USER_PASSWORD \
		--allow-root
	
	echo "WordPress installed successfully!"
fi

# Establecer permisos correctos para el servidor web
chown -R www-data:www-data /var/www/html
chmod -R 755 /var/www/html

# Iniciar PHP-FPM en primer plano
exec php-fpm8.2 -F