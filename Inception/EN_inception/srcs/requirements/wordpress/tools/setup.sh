#!/bin/bash

# ============================================================================
#           WORDPRESS INITIALIZATION SCRIPT - INCEPTION
# ============================================================================
# This script waits for MariaDB to be available and then installs/configures
# WordPress using WP-CLI (official command-line tool).
# ============================================================================

# Timeout configuration to wait for MariaDB
MAX_WAIT=120
WAITED=0
SLEEP=3

# Wait until MariaDB is ready and accepting connections
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

# Check if WordPress is already installed (checking wp-config.php)
if [ ! -f /var/www/html/wp-config.php ]; then
	echo "Installing WordPress..."
	
	# Download WordPress core files
	wp core download --allow-root
	
	# Create wp-config.php file with DB connection data
	wp config create \
		--dbname=$MYSQL_DATABASE \
		--dbuser=$MYSQL_USER \
		--dbpass=$MYSQL_PASSWORD \
		--dbhost=mariadb:3306 \
		--allow-root
	
	# Install WordPress (create tables and initial configuration)
	wp core install \
		--url=$DOMAIN_NAME \
		--title="$WP_TITLE" \
		--admin_user=$WP_ADMIN_USER \
		--admin_password=$WP_ADMIN_PASSWORD \
		--admin_email=$WP_ADMIN_EMAIL \
		--allow-root
	
	# Create additional user with author role
	wp user create \
		$WP_USER \
		$WP_USER_EMAIL \
		--role=author \
		--user_pass=$WP_USER_PASSWORD \
		--allow-root
	
	echo "WordPress installed successfully!"
fi

# Set correct permissions for the web server
chown -R www-data:www-data /var/www/html
chmod -R 755 /var/www/html

# Start PHP-FPM in foreground
exec php-fpm8.2 -F