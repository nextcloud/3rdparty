<?php

/**
 * Inserts a col and a bar chart into a Word document.
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

$colChartValues = array(
    'legend' => array('Internet Explorer'),
    'January 2011' => array('26.6'),
    'February 2011' => array('26.5'),
    'March 2011' => array('25.8'),
    'April 2011' => array('24.3'),
    'May 2011' => array('24.9'),
    'June 2011' => array('23.2')
);

$paramsChart = array(
    'data' => $colChartValues,
    'type' => 'barChart',
    'title' => 'W3C Browser Statistics',
    'color' => 2,
    'sizeX' => 15,
    'sizeY' => 15,
    'jc' => 'center',

);

$docx->addChart($paramsChart);

$paramsChart = array(
    'data' => $colChartValues,
    'type' => 'colChart',
    'title' => 'W3C Browser Statistics',
    'color' => 2,
    'sizeX' => 15,
    'sizeY' => 15,
    'jc' => 'center',

);

$docx->addChart($paramsChart);

$docx->createDocx('../docx/example_chart_bar');