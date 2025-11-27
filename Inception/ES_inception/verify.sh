#!/usr/bin/env bash

make up

set -e
set -o allexport; source srcs/.env; set +o allexport

echo "=== Containers ==="
docker ps --format "table {{.Names}}\t{{.Image}}\t{{.Status}}\t{{.Ports}}"

echo; echo "=== Volumes ==="
docker volume ls

echo; echo "=== DB users ==="
docker exec -it mariadb bash -c "mysql -uroot -p\"${MYSQL_ROOT_PASSWORD}\" -e \"SELECT User,Host FROM mysql.user;\""

echo; echo "=== WP files ==="
docker exec -it wordpress bash -c "ls -la /var/www/html | sed -n '1,120p'"

echo; echo "=== WP users ==="
docker exec -it wordpress bash -c "wp user list --allow-root"

echo; echo "=== Nginx TLS test ==="
docker exec -it nginx openssl s_client -connect localhost:443 -tls1_2 </dev/null 2>/dev/null | sed -n '1,5p' || true

echo; echo "=== HTTP HEAD ==="
curl -k -I https://miaviles.42.fr | sed -n '1,20p'

echo; echo "=== Restart policy ==="
for c in mariadb wordpress nginx; do
  echo -n "$c: "
  docker inspect -f '{{.HostConfig.RestartPolicy.Name}}' $c || true
done

echo; echo "=== PID 1 processes ==="
for c in mariadb wordpress nginx; do
  echo "container: $c"
  docker top $c
done

make down

echo; echo "=== DONE ==="
