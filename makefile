%: %.cc
	g++ -Wall -Wextra -std=c++14 -Wfatal-errors -g -fsanitize=address,undefined -fno-omit-frame-pointer -I/home/madhur/HDD/Prgs $< -o $@
