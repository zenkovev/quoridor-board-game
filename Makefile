build_image:
	docker build --tag 'quoridor-game' .

run:
	export DISPLAY=:0.0
	xhost +local:docker
	docker run \
		--name 'quoridor-game' \
		-v /tmp/.X11-unix:/tmp/.X11-unix \
		-e DISPLAY=$$DISPLAY \
		--detach 'quoridor-game'

stop:
	docker stop quoridor-game
	docker rm quoridor-game

clean_image:
	docker rmi quoridor-game
