##
## EPITECH PROJECT, 2025
## G-DOP-200-LYN-2-1-popeye-27
## File description:
## Dockerfile
##

FROM python:3
WORKDIR /app
COPY . .
RUN pip3 install -r requirements.txt
EXPOSE 80
CMD ["flask", "run", "--host=0.0.0.0", "--port=80"]