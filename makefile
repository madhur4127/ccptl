%: %.cc
	g++ -DLOCAL -Wall -Wextra -std=c++17 -Wfatal-errors -g -fsanitize=address,undefined -fno-omit-frame-pointer -I/home/madhur/HDD/Prgs $< -o $@
