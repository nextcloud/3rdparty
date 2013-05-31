<?php

/**
 * Inserts a simple table into the Word document.
 *
 * @category   Phpdocx
 * @package    examples
 * @subpackage easy
 * @copyright  Copyright (c) Narcea Producciones Multimedia S.L.
 *             (http://www.2mdc.com)
 * @license    LGPL
 * @version    3.0
 * @link       http://www.phpdocx.com
 * @since      File available since Release 3.0
 */
require_once '../../classes/CreateDocx.inc';

$docx = new CreateDocx();

$valuesTable = array(
    array(
        11,
        12
    ),
    array(
        21,
        22
    ),
);

$paramsTable = array(
    'border' => 'single',
    'border_sz' => 20
);


$docx->addTable($valuesTable, $paramsTable);

$docx->createDocx('../docx/example_table');