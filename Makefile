
# Computer Science 142 Project
# N Chancellors Move
# Authors:
# 	Baticos, Andric Quinn
# 	Nicolas, Mark Jay
# 	Reblora, Kyle Matthew

install:

	#	npm installation
	sudo apt-get install npm

	# package installation
	npm install express

update:

	sudo apt-get update

	#	update node using package manager
	sudo npm cache clean -f
	sudo npm install -g n
	sudo n stable

run:

	clear
	npm start