DOCKER_COMPOSE = docker compose -f ./docker-compose.yml

all:
	@$(DOCKER_COMPOSE) up --build -d
	@echo "Containers are up and running!"

clean:
	@$(DOCKER_COMPOSE) down
	@echo "Containers stopped and removed."

fclean: clean
	@docker network prune -f
	@docker volume prune -f
	@echo "Unused networks cleaned."

re: fclean all
	@echo "Environment rebuilt!"
