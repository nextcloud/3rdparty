<?php

/**
 * Insert a pie chart into a Word document.
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

$legends = array(
    'legend1' => array(10),
    'legend2' => array(20),
    'legend3' => array(40)
);

$paramsChart = array(
    'data' => $legends,
    'type' => 'pie3DChart',
    'title' => 'Title',
    'rotX' => 20,
    'rotY' => 20,
    'perspective' => 30,
    'color' => 2,
    'textWrap' => 0,
    'sizeX' => 10,
    'sizeY' => 10,
    'jc' => 'right',
    'showPercent' => 1,
    'font' => 'Times New Roman'
);
$docx->addChart($paramsChart);


$docx->createDocx('../docx/example_chart');
