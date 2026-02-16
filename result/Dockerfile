##
## EPITECH PROJECT, 2025
## G-DOP-200-LYN-2-1-popeye-27
## File description:
## Dockerfile
##

FROM node:20-alpine
WORKDIR /app
COPY . .
RUN npm install
EXPOSE 80
CMD ["node", "server.js"]