
function WorldMap(callback)
{
	this.imgUrl = "img/worldMap.png";
	this.init();
}

WorldMap.prototype.init = function() {
	this.sprite = new PIXI.Sprite(
		PIXI.loader.resources[this.imgUrl].texture
	);
};
