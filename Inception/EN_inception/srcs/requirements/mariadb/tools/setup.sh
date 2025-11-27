#!/bin/bash

# ============================================================================
#            MARIADB INITIALIZATION SCRIPT - INCEPTION
# ============================================================================
# This script configures MariaDB the first time the container runs.
# If already initialized, it simply starts the server.
# ============================================================================

# Check if WordPress database already exists
if [ ! -d "/var/lib/mysql/$MYSQL_DATABASE" ]; then
    echo "Initializing MariaDB..."
    
    # Start MariaDB in temporary mode (no network, local socket only)
    mysqld --user=mysql --skip-networking --socket=/tmp/mysql_init.sock &
    MYSQL_PID=$!
    
    # Wait for MariaDB to be ready to receive commands
    for i in {1..30}; do
        if mysql --socket=/tmp/mysql_init.sock -e "SELECT 1" &>/dev/null; then
            break
        fi
        echo "Waiting for MySQL to start..."
        sleep 1
    done
    
    # Initial security configuration and DB creation
    mysql --socket=/tmp/mysql_init.sock -u root << EOF
-- Set password for root
ALTER USER 'root'@'localhost' IDENTIFIED BY '$MYSQL_ROOT_PASSWORD';

-- Remove anonymous users (security)
DELETE FROM mysql.user WHERE User='';

-- Remove remote root access (security)
DELETE FROM mysql.user WHERE User='root' AND Host NOT IN ('localhost', '127.0.0.1', '::1');

-- Remove test database
DROP DATABASE IF EXISTS test;
DELETE FROM mysql.db WHERE Db='test' OR Db='test\\_%';

-- Create database for WordPress
CREATE DATABASE IF NOT EXISTS $MYSQL_DATABASE;

-- Create user for WordPress with access from any host
CREATE USER IF NOT EXISTS '$MYSQL_USER'@'%' IDENTIFIED BY '$MYSQL_PASSWORD';

-- Grant all privileges on WordPress DB
GRANT ALL PRIVILEGES ON $MYSQL_DATABASE.* TO '$MYSQL_USER'@'%';

-- Apply changes
FLUSH PRIVILEGES;
EOF

    # Stop temporary MariaDB cleanly
    kill $MYSQL_PID
    wait $MYSQL_PID
    
    echo "MariaDB initialized!"
else
    echo "MariaDB already initialized!"
fi

# Start MariaDB in normal mode (with network enabled)
exec mysqld --user=mysql