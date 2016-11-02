<?php

use Phalcon\Mvc\Model;

class City extends Model
{
	private $id;

	private $name;

	private $description;

	private $tradePaths;

	public function initialize()
	{
		$this->hasMany(
			'tradePaths',
			TradePath::class,
			'id'
		);
	}

	public function getId()
	{
		return $this->id;
	}

	public function getName()
	{
		return $this->name;
	}

	public function setName($name)
	{
		$this->name = name;
	}

	public function getDescription()
	{
		return $this->description;
	}

	public function setDescription($description)
	{
		$this->description = $description;
	}
};
