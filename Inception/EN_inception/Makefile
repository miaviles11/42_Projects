NAME		= inception

CYAN		= \033[0;96m
GREEN		= \033[0;32m
YELLOW		= \033[0;33m
RED			= \033[0;31m
RESET		= \033[0m

COMPOSE		= srcs/docker-compose.yml
DATA		= /home/$(USER)/data
BACKUP_DIR	= backups

all: up

up:
	@mkdir -p $(DATA)/wordpress $(DATA)/mariadb $(DATA)/adminer $(DATA)/mysql_log $(DATA)/portainer
	@echo "$(CYAN)Building and starting containers...$(RESET)"
	@docker compose -f $(COMPOSE) up -d --build
	@echo "$(GREEN)✓ Inception is up!$(RESET)"

down:
	@echo "$(YELLOW)Stopping containers...$(RESET)"
	@docker compose -f $(COMPOSE) down

start:
	@docker compose -f $(COMPOSE) start

stop:
	@docker compose -f $(COMPOSE) stop

restart: stop start

clean: down
	@docker compose -f $(COMPOSE) down -v

fclean: clean
	@echo "$(RED)Full cleanup...$(RESET)"
	@docker system prune -af --volumes
	@sudo rm -rf $(DATA)/wordpress $(DATA)/mariadb $(DATA)/adminer $(DATA)/mysql_log $(DATA)/portainer
	@echo "$(GREEN)✓ Everything cleaned$(RESET)"

re: fclean all

rebuild:
	@echo "$(YELLOW)Rebuilding containers without losing data...$(RESET)"
	@docker compose -f $(COMPOSE) down
	@docker rmi -f mariadb wordpress nginx adminer static-site portainer 2>/dev/null || true
	@mkdir -p $(DATA)/wordpress $(DATA)/mariadb $(DATA)/adminer $(DATA)/mysql_log $(DATA)/portainer
	@docker compose -f $(COMPOSE) up -d --build
	@echo "$(GREEN)✓ Rebuilt successfully! Your data is safe.$(RESET)"

backup:
	@echo "$(CYAN)Creating backup...$(RESET)"
	@mkdir -p $(BACKUP_DIR)
	@sudo tar -czf $(BACKUP_DIR)/wordpress-$(shell date +%Y%m%d-%H%M%S).tar.gz $(DATA)/wordpress
	@sudo tar -czf $(BACKUP_DIR)/mariadb-$(shell date +%Y%m%d-%H%M%S).tar.gz $(DATA)/mariadb
	@echo "$(GREEN)✓ Backup saved in ./$(BACKUP_DIR)/$(RESET)"
	@echo "$(CYAN)Backup files:$(RESET)"
	@ls -lh $(BACKUP_DIR)/ | tail -2

list-backups:
	@echo "$(CYAN)Available backups:$(RESET)"
	@if [ -d "$(BACKUP_DIR)" ]; then \
		ls -lht $(BACKUP_DIR)/ | grep -E '(wordpress|mariadb)' || echo "No backups found"; \
	else \
		echo "No backup directory found"; \
	fi

restore:
	@echo "$(YELLOW)Restoring last backup...$(RESET)"
	@if [ ! -d "$(BACKUP_DIR)" ]; then \
		echo "$(RED)Error: No backup directory found$(RESET)"; \
		exit 1; \
	fi
	@WORDPRESS_BACKUP=$$(ls -t $(BACKUP_DIR)/wordpress-*.tar.gz 2>/dev/null | head -1); \
	MARIADB_BACKUP=$$(ls -t $(BACKUP_DIR)/mariadb-*.tar.gz 2>/dev/null | head -1); \
	if [ -z "$$WORDPRESS_BACKUP" ] || [ -z "$$MARIADB_BACKUP" ]; then \
		echo "$(RED)Error: No backups found$(RESET)"; \
		exit 1; \
	fi; \
	echo "$(CYAN)Restoring WordPress from: $$(basename $$WORDPRESS_BACKUP)$(RESET)"; \
	echo "$(CYAN)Restoring MariaDB from: $$(basename $$MARIADB_BACKUP)$(RESET)"; \
	mkdir -p $(DATA); \
	sudo tar -xzf $$WORDPRESS_BACKUP -C /; \
	sudo tar -xzf $$MARIADB_BACKUP -C /; \
	echo "$(GREEN)✓ Backup restored successfully!$(RESET)"

restore-specific:
	@echo "$(CYAN)Available backups:$(RESET)"
	@ls -1 $(BACKUP_DIR)/ 2>/dev/null || echo "No backups found"
	@echo ""
	@read -p "Enter WordPress backup filename: " wp_backup; \
	read -p "Enter MariaDB backup filename: " db_backup; \
	if [ -f "$(BACKUP_DIR)/$$wp_backup" ] && [ -f "$(BACKUP_DIR)/$$db_backup" ]; then \
		echo "$(YELLOW)Restoring...$(RESET)"; \
		mkdir -p $(DATA); \
		sudo tar -xzf $(BACKUP_DIR)/$$wp_backup -C /; \
		sudo tar -xzf $(BACKUP_DIR)/$$db_backup -C /; \
		echo "$(GREEN)✓ Backup restored!$(RESET)"; \
	else \
		echo "$(RED)Error: Backup files not found$(RESET)"; \
	fi

safe-fclean:
	@echo "$(RED)⚠️  WARNING: This will DELETE ALL DATA! ⚠️$(RESET)"
	@echo "$(YELLOW)The following will be permanently deleted:$(RESET)"
	@echo "  - WordPress (blog, posts, pages, themes, plugins)"
	@echo "  - MariaDB (database)"
	@echo "  - Adminer data"
	@echo "  - All Docker images and containers"
	@echo ""
	@echo "$(CYAN)💡 Tip: Run 'make backup' first to save your data$(RESET)"
	@echo ""
	@read -p "Type 'yes' to confirm deletion: " confirm; \
	if [ "$$confirm" = "yes" ]; then \
		make fclean; \
	else \
		echo "$(GREEN)✅ Cancelled. Your data is safe.$(RESET)"; \
	fi

backup-and-fclean:
	@echo "$(CYAN)Creating backup before cleanup...$(RESET)"
	@make backup
	@echo ""
	@read -p "Backup created. Proceed with fclean? (yes/no): " confirm; \
	if [ "$$confirm" = "yes" ]; then \
		make fclean; \
		echo "$(CYAN)💡 To restore: make restore$(RESET)"; \
	else \
		echo "$(GREEN)✅ Cancelled.$(RESET)"; \
	fi

logs:
	@docker compose -f $(COMPOSE) logs -f

ps:
	@docker compose -f $(COMPOSE) ps

status:
	@echo "$(CYAN)Container Status:$(RESET)"
	@docker compose -f $(COMPOSE) ps
	@echo "\n$(CYAN)Volumes:$(RESET)"
	@docker volume ls | grep $(USER) || echo "No volumes found"
	@echo "\n$(CYAN)Data directories:$(RESET)"
	@du -sh $(DATA)/* 2>/dev/null || echo "No data directories"

sh-nginx:
	@docker compose -f $(COMPOSE) exec nginx sh

sh-wordpress:
	@docker compose -f $(COMPOSE) exec wordpress sh

sh-mariadb:
	@docker compose -f $(COMPOSE) exec mariadb sh

sh-adminer:
	@docker compose -f $(COMPOSE) exec adminer sh

# Ayuda - Muestra todos los comandos disponibles
help:
	@echo "$(CYAN)═══════════════════════════════════════════════════════════$(RESET)"
	@echo "$(GREEN)                    INCEPTION - COMMANDS                    $(RESET)"
	@echo "$(CYAN)═══════════════════════════════════════════════════════════$(RESET)"
	@echo ""
	@echo "$(YELLOW)Basic Commands:$(RESET)"
	@echo "  make / make up    - Build and start all containers"
	@echo "  make down         - Stop containers (keeps data)"
	@echo "  make start        - Start existing containers"
	@echo "  make stop         - Stop containers without removing"
	@echo "  make restart      - Restart containers"
	@echo "  make clean        - Stop and remove containers + volumes"
	@echo "  make fclean       - Full cleanup (⚠️  DELETES ALL DATA)"
	@echo "  make re           - Full rebuild (fclean + up)"
	@echo ""
	@echo "$(YELLOW)Safe Commands (Preserve Data):$(RESET)"
	@echo "  make rebuild      - Rebuild images without losing data"
	@echo "  make safe-fclean  - fclean with confirmation prompt"
	@echo ""
	@echo "$(YELLOW)Backup & Restore:$(RESET)"
	@echo "  make backup              - Create backup of all data"
	@echo "  make list-backups        - List available backups"
	@echo "  make restore             - Restore last backup"
	@echo "  make restore-specific    - Restore specific backup (interactive)"
	@echo "  make backup-and-fclean   - Backup then fclean (safe)"
	@echo ""
	@echo "$(YELLOW)Monitoring:$(RESET)"
	@echo "  make logs         - Show container logs (follow mode)"
	@echo "  make ps           - List running containers"
	@echo "  make status       - Detailed status (containers + volumes + data)"
	@echo ""
	@echo "$(YELLOW)Shell Access:$(RESET)"
	@echo "  make sh-nginx     - Access NGINX container shell"
	@echo "  make sh-wordpress - Access WordPress container shell"
	@echo "  make sh-mariadb   - Access MariaDB container shell"
	@echo "  make sh-adminer   - Access Adminer container shell"
	@echo ""
	@echo "$(YELLOW)Help:$(RESET)"
	@echo "  make help         - Show this help message"
	@echo ""
	@echo "$(CYAN)═══════════════════════════════════════════════════════════$(RESET)"
	@echo "$(GREEN)💡 Tip: Use 'make backup' before 'make fclean'$(RESET)"
	@echo "$(CYAN)═══════════════════════════════════════════════════════════$(RESET)"

.PHONY: all up down start stop restart clean fclean re logs ps status \
		sh-nginx sh-wordpress sh-mariadb sh-adminer rebuild backup \
		list-backups restore restore-specific safe-fclean backup-and-fclean help