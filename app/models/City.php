<?php

use Phalcon\Mvc\Model;

class City extends Model
{
	/**
	 * @Primary
	 * @Identity
	 * @Column(type="integer", nullable=false) 
	 */
	private $id;

	/**
	 * @Column(type="string", nullable=false) 
	 */
	private $name;

	/**
	 * @Column(type="string", nullable=false)
	 */
	private $description;

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
