<?php

use Phalcon\Mvc\Model;

class TradePath extends Model
{
	private $id;

	/**
	 * time in seconds
	 */	
	private $time_to_travel;

	/**
	 * 0% to 100%
	 */
	private $chance_of_attack;

	private $attack_difficulty_level;

	/**
	 * explicitly declare from and to
	 * so that travel can be assymetric
	 * i.e. travelling down a hill
	 * should be easier than travelling 
	 * up it
	 */
	private $city_from;

	private $city_to;

	public function initialize()
	{
		$this->belongsTo(
			'city_from',
			City::class,
			'id'
		);

		$this->belongsTo(
			'city_to',
			City::class,
			'id'
		);
	}

};
