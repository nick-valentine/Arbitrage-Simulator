PIXI.loader
	.add("img/worldMap.png")
	.load(setup)
;

function setup() {
	gameWindow = new GameWindow();

	var worldMap = new WorldMap();

	gameWindow.getStage().addChild(worldMap.sprite);

	gameLoop();
}

function gameLoop() {
	requestAnimationFrame(gameLoop);

	gameWindow.draw();
}

