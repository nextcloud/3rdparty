<?php

/**
 * Inserts blocks of text with different line spacings.
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
    'sed do eiusmod tempor incididunt ut labore et dolore magna aliqua.';

$paramsText = array(
    'b' => 'single',
    'font' => 'Arial',
    'lineSpacing' => 240
);

$docx->addText($text, $paramsText);

$text = 'Lorem ipsum dolor sit amet, consectetur adipisicing elit, ' .
    'sed do eiusmod tempor incididunt ut labore et dolore magna aliqua.';

$paramsText = array(
    'b' => 'single',
    'font' => 'Arial',
    'lineSpacing' => 480
);

$docx->addText($text, $paramsText);

$text = 'Lorem ipsum dolor sit amet, consectetur adipisicing elit, ' .
    'sed do eiusmod tempor incididunt ut labore et dolore magna aliqua.';

$paramsText = array(
    'b' => 'single',
    'font' => 'Arial',
    'lineSpacing' => 120
);

$docx->addText($text, $paramsText);

$docx->createDocx('../docx/example_text_linespacing');