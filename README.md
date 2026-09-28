# COS214_prac5
## Docker run instructions
Requirements:
•	Installed Docker and running it
•	Installed Docker Compose

From the project root type (in terminal) “docker compose build” 
Then to build type “docker build -t campusguard:latest .”
You may then run the program by typing “docker run --rm -it campusguard:latest”

To use valgrind (to check for memory leaks) type “docker compose run --rm campusguard make valgrind” and it will run the valgrind.