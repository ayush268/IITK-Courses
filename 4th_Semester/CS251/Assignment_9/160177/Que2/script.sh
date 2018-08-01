docker stop $(docker ps -a -q)
docker build -t myapache .
docker run -p 8080:80 -d myapache
