<?php 

use Phalcon\Db\Column;
use Phalcon\Db\Index;
use Phalcon\Db\Reference;
use Phalcon\Mvc\Model\Migration;

/**
 * Class TradePathMigration_101
 */
class TradePathMigration_101 extends Migration
{
    /**
     * Run the migrations
     *
     * @return void
     */
    public function up()
    {
        $this->morphTable('trade_path', [
                'columns' => [
                    new Column(
                        'id',
                        [
                            'type' => Column::TYPE_INTEGER,
                            'unsigned' => true,
                            'notNull' => true,
                            'autoIncrement' => true,
                            'size' => 11,
                            'first' => true
                        ]
                    ),
                    new Column(
                        'time_to_travel',
                        [
                            'type' => Column::TYPE_INTEGER,
                            'notNull' => true,
                            'size' => 11,
                            'after' => 'id'
                        ]
                    ),
                    new Column(
						'chance_of_attack',
                        [
							'type' => Column::TYPE_INTEGER,
                            'notNull' => true,
                            'size' => 11,
                            'after' => 'time_to_travel'
                        ]
                    ),
                    new Column(
						'attack_difficulty_level',
                        [
							'type' => Column::TYPE_INTEGER,
                            'notNull' => true,
                            'size' => 11,
                            'after' => 'chance_of_attack'
                        ]
                    ),
                    new Column(
						'city_from',
                        [
							'type' => Column::TYPE_INTEGER,
                            'unsigned' => true,
                            'notNull' => true,
                            'size' => 11,
                            'after' => 'attack_difficulty_level'
                        ]
                    ),
                    new Column(
						'city_to',
                        [
							'type' => Column::TYPE_INTEGER,
                            'unsigned' => true,
                            'notNull' => true,
                            'size' => 11,
                            'after' => 'city_from'
                        ]
                    )
                ],
                'indexes' => [
                    new Index('PRIMARY', ['id'], 'PRIMARY')
				],
				'references' => [
					new Reference(
						"trade_routes_city_from_fk_1",
						[
							"referencedTable" => 'city',
							"columns" => ['city_from'],
							"referencedColumns" => ['id'],
						]
					),
					new Reference(
						"trade_routes_city_to_fk_2",
						[
							"referencedTable" => 'city',
							"columns" => ['city_to'],
							"referencedColumns" => ['id'],
						]
					),
				],
                'options' => [
                    'TABLE_TYPE' => 'BASE TABLE',
                    'AUTO_INCREMENT' => '1',
                    'ENGINE' => 'InnoDB',
                    'TABLE_COLLATION' => 'latin1_swedish_ci'
                ],
            ]
        );
    }

    /**
     * Reverse the migrations
     *
     * @return void
     */
    public function down()
    {

    }

}
