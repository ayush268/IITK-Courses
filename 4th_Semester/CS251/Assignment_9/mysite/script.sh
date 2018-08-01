docker stop $(docker ps -a -q)
docker build -t mysite .
docker run -p 8080:80 -d mysite
