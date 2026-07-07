#! /bin/bash
docker compose down
docker volume rm nc_mysql_data
docker compose up --build -d