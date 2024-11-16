CODE_PATH = ./src/ft_malcolm

DOCKER_COMPOSE = docker compose -f ./docker-compose.yml

all: code
	@$(DOCKER_COMPOSE) up --build -d
	@echo "Containers are up and running!"

code:
	@$(MAKE) --no-print-directory -C $(CODE_PATH) all

clean:
	@$(MAKE) --no-print-directory -C $(CODE_PATH) clean
	@$(DOCKER_COMPOSE) down
	@echo "Containers stopped and removed."

fclean:
	@$(MAKE) --no-print-directory -C $(CODE_PATH) fclean
	@$(DOCKER_COMPOSE) down
	@docker network prune -f
	@docker volume prune -f
	@echo "Unused networks cleaned."

re: fclean all
	@echo "Environment rebuilt!"
