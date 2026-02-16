##
## EPITECH PROJECT, 2025
## G-DOP-200-LYN-2-1-popeye-27
## File description:
## Dockerfile
##

FROM maven:3.9.6-eclipse-temurin-21-alpine AS builder
WORKDIR /app
COPY pom.xml .
RUN ["mvn", "dependency:resolve"]
COPY src ./src
RUN ["mvn", "package"]
FROM eclipse-temurin:21-jre-alpine
WORKDIR /app
COPY --from=builder /app/target/worker-jar-with-dependencies.jar .
CMD ["java", "-jar", "worker-jar-with-dependencies.jar"]