
function GameWindow()
{
	this.renderer = null;
	this.stage = null;
	this.init();
}

GameWindow.prototype.init = function() {
	//create a renderer at the size of the window
	this.renderer = PIXI.autoDetectRenderer(1,1);
	this.renderer.autoResize = true;
	this.renderer.view.style.position = "absolute";
	this.renderer.view.style.display = "block";
	this.renderer.resize(window.innerWidth, window.innerHeight);

	//add it to the dom
	document.body.appendChild(this.renderer.view);

	this.stage = new PIXI.Container();
	this.stage.width = window.innerWidth;
	this.stage.height = window.innerHeight;
	this.stage.alpha = 1;

	this.renderer.render(this.stage);

	$(window).resize(function() {
		renderer.resize(window.innerWidth, window.innerHeight);
	});

};

GameWindow.prototype.draw = function() {
	this.renderer.render(this.stage);
}

GameWindow.prototype.getRenderer = function() {
	return this.renderer;
};

GameWindow.prototype.getStage = function() {
	return this.stage;
};

