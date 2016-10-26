<?php

use Phalcon\Db\Column as Column;
use Phalcon\Db\Index as Index;
use Phalcon\Db\Reference as Reference;

class CityMigration_100 extends \Phalcon\Mvc\Model\Migration
{
	public function up()
	{
		$this->morphTable(
			"city",
			array(
				"columns" => array(
					new Column(
						"id",
						array(
							"primary"		=> true,
							"type"			=> Column::TYPE_INTEGER,
							"size"			=> 11,
							"unsigned"  	=> true,
							"notNull"		=> true,
							"autoIncrement" => true,
							"first"			=> true,
						)
					),
					new Column(
						"name",
						array(
							"type"			=> Column::TYPE_VARCHAR,
							"size"			=> 64,
							"notNull"		=> true,
							"after"			=> "id",
						)
					),
					new Column(
						"description",
						array(
							"type"			=> Column::TYPE_VARCHAR,
							"size"			=> 256,
							"notNull"		=> true,
							"after"			=> "name",
						)
					),
				),
				"options" => array(
					"TABLE_TYPE"			=> "BASE TABLE",
					"ENGINE"				=> "InnoDB",
					"TABLE_COLLITION"		=> "utf8_general_ci",
				)
			)
		);
	}

	public function down()
	{

	}
};
