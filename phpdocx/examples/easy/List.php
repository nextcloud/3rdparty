<?php

/**
 * Insert an unordered list into a Word document.
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

$valuesList = array(
    'Line 1',
    'Line 2',
    'Line 3',
    'Line 4',
    'Line 5'
);

$paramsList = array(
    'val' => 1
);

$docx->addList($valuesList, $paramsList);

$docx->createDocx('../docx/example_list');