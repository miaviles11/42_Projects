#!/bin/bash

# ============================================================================
#            SCRIPT DE INICIALIZACIÓN DE MARIADB - INCEPTION
# ============================================================================
# Este script configura MariaDB la primera vez que se ejecuta el contenedor.
# Si ya está inicializado, simplemente arranca el servidor.
# ============================================================================

# Verificar si la base de datos de WordPress ya existe
if [ ! -d "/var/lib/mysql/$MYSQL_DATABASE" ]; then
    echo "Initializing MariaDB..."
    
    # Iniciar MariaDB en modo temporal (sin red, solo socket local)
    mysqld --user=mysql --skip-networking --socket=/tmp/mysql_init.sock &
    MYSQL_PID=$!
    
    # Esperar a que MariaDB esté lista para recibir comandos
    for i in {1..30}; do
        if mysql --socket=/tmp/mysql_init.sock -e "SELECT 1" &>/dev/null; then
            break
        fi
        echo "Waiting for MySQL to start..."
        sleep 1
    done
    
    # Configuración inicial de seguridad y creación de BD
    mysql --socket=/tmp/mysql_init.sock -u root << EOF
-- Establecer contraseña para root
ALTER USER 'root'@'localhost' IDENTIFIED BY '$MYSQL_ROOT_PASSWORD';

-- Eliminar usuarios anónimos (seguridad)
DELETE FROM mysql.user WHERE User='';

-- Eliminar accesos remotos de root (seguridad)
DELETE FROM mysql.user WHERE User='root' AND Host NOT IN ('localhost', '127.0.0.1', '::1');

-- Eliminar base de datos de prueba
DROP DATABASE IF EXISTS test;
DELETE FROM mysql.db WHERE Db='test' OR Db='test\\_%';

-- Crear base de datos para WordPress
CREATE DATABASE IF NOT EXISTS $MYSQL_DATABASE;

-- Crear usuario para WordPress con acceso desde cualquier host
CREATE USER IF NOT EXISTS '$MYSQL_USER'@'%' IDENTIFIED BY '$MYSQL_PASSWORD';

-- Dar todos los permisos sobre la BD de WordPress
GRANT ALL PRIVILEGES ON $MYSQL_DATABASE.* TO '$MYSQL_USER'@'%';

-- Aplicar los cambios
FLUSH PRIVILEGES;
EOF

    # Detener MariaDB temporal de forma limpia
    kill $MYSQL_PID
    wait $MYSQL_PID
    
    echo "MariaDB initialized!"
else
    echo "MariaDB already initialized!"
fi

# Arrancar MariaDB en modo normal (con red habilitada)
exec mysqld --user=mysql