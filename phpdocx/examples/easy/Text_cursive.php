<?php

/**
 * Inserts a text in cursive format.
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

$text = 'Lorem ipsum dolor sit amet, consectetur adipisicing elit, ' .
    'sed do eiusmod tempor incididunt ut labore et dolore magna aliqua. Ut ' .
    'enim ad minim veniam, quis nostrud exercitation ullamco laboris nisi ut' .
    'aliquip ex ea commodo consequat. Duis aute irure dolor in reprehenderit ' .
    'in voluptate velit esse cillum dolore eu fugiat nulla pariatur. ' .
    'Excepteur sint occaecat cupidatat non proident, sunt in culpa qui.';

$paramsText = array(
	'i' => 'single',
	'jc' => 'distribute',
    'sz' => 14,
    'color' => '76923C'
);
$docx->addText($text, $paramsText);

$docx->createDocx('../docx/example_textCursive');